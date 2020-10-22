import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    holdings = []
    gtotal = 0
    rows = db.execute("""
        select symbol, sum(shares) as tshares from trans where user_id = :user_id group by symbol
    """, user_id = session["user_id"])

    for row in rows:
        stock = lookup(row["symbol"])
        holdings.append({
            "symbol": row["symbol"],
            "name": stock["name"],
            "shares": row["tshares"],
            "price": usd(stock["price"]),
            "total": usd(stock["price"] * row["tshares"])
        })
        gtotal += stock["price"] * row["tshares"]
    cash = db.execute("SELECT cash FROM users WHERE id = :id", id = session["user_id"])[0]["cash"]
    gtotal += cash
    return render_template("index.html", holdings = holdings, cash = usd(cash), gtotal = usd(gtotal))

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":

        symbol = request.form.get("symbol").upper()
        stock = lookup(request.form.get("symbol").upper())
        shares = request.form.get("shares")

        if not symbol:
            return apology("must enter a symbol")
        elif not shares:
            return apology("must enter a shares")
        elif not shares.isdigit():
            return apology("must enter a valid number")
        elif not symbol:
            return apology("symbol not valid")
        cash = db.execute("SELECT cash FROM users WHERE id = :id", id = session["user_id"])[0]["cash"]
        new_cash = cash - int(shares) * stock['price']

        if not new_cash:
            return apology("insufficient cash")
        db.execute("UPDATE users SET cash = :new_cash WHERE id = :id", new_cash = new_cash, id = session["user_id"])

        db.execute("INSERT INTO trans (user_id, symbol, shares, price) VALUES(:user_id, :symbol, :shares, :price)",
                        user_id = session["user_id"],
                        symbol = stock["symbol"],
                        shares = shares,
                        price = stock["price"]
                )
        return redirect("/")
    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    holdings = []
    rows = db.execute("""
        select symbol, shares, transacted from trans where user_id = :user_id
    """, user_id = session["user_id"])

    for row in rows:
        stock = lookup(row["symbol"])
        holdings.append({
            "symbol": row["symbol"],
            "name": stock["name"],
            "shares": row["shares"],
            "price": usd(stock["price"]),
            "transaction": row["transacted"]
        })

    return render_template("history.html", holdings = holdings)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must enter a symbol")
        stock = lookup(request.form.get("symbol").upper())

        if stock == None:
            return apology("symbol not valid")
        else:
            return render_template("quoted.html",stock=stock)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        name = request.form.get("username")
        password = generate_password_hash(request.form.get("password"))
        status = True
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")
        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # Ensure confirmation was submitted
        elif not request.form.get("confirmation"):
            return apology("must provide confirmation")

            # Ensure password and confirmation is same
        elif not request.form.get("confirmation") == request.form.get("password"):
            return apology("password do not match")

        # check unique username
        exists = db.execute("SELECT username FROM users where username = :username", username = name)

        if exists:
            status = False
            return apology("Username already taken by another user")

        if status:
            register = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)", username = name , hash = password)
            return apology("Registration Was Successful")

            session["user_id"] = register

            # Redirect user to home page
            return redirect("/")
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":

        symbol = request.form.get("symbol").upper()
        stock = lookup(request.form.get("symbol").upper())
        shares = request.form.get("shares")
        rows = db.execute("SELECT SUM(shares) as tshares from trans WHERE symbol = :symbol AND user_id = :user_id group by symbol", symbol = stock["symbol"], user_id = session["user_id"])
        no_of_shares = rows[0]["tshares"]

        if int(shares) > no_of_shares:
            return apology("You don't have the enough number of shares to sell!", 400)
        if not symbol:
            return apology("must enter a symbol")
        elif not shares:
            return apology("must enter a shares")
        elif not shares.isdigit():
            return apology("must enter a valid number")
        elif not symbol:
            return apology("symbol not valid")

        cash = db.execute("SELECT cash FROM users WHERE id = :id", id = session["user_id"])[0]["cash"]
        new_cash = cash + int(shares) * stock['price']

        db.execute("UPDATE users SET cash = :new_cash WHERE id = :id", new_cash = new_cash, id = session["user_id"])

        exists = db.execute("SELECT symbol FROM trans WHERE symbol = :symbol AND user_id = :user_id", symbol = stock["symbol"], user_id = session["user_id"])

        if exists:
            status = False
            db.execute("INSERT INTO trans (user_id, symbol, shares, price) VALUES(:user_id, :symbol, :shares, :price)",
                        user_id = session["user_id"],
                        symbol = stock["symbol"],
                        shares = (-1 * int(shares)),
                        price = stock["price"]
                )
            if int(shares) == no_of_shares:
                db.execute("DELETE from trans WHERE symbol = :symbol AND user_id = :user_id", symbol = stock["symbol"], user_id = session["user_id"])
        if status:
            return apology("you dont have stocks of this company")

        return redirect("/")
    else:
        return render_template("sell.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
