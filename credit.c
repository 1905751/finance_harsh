#include <stdio.h>
#include <cs50.h>

long luhn(long, long); //function declaration

int main(void)   //main function
{
    long len = 0, x = 0, c, n;           //variables
    long number = get_long("Number: ");  //card number input
    n = number;

    while (n != 0)      //loop for checking various conditions
    {
        n = n / 10;
        len++;

        if (len == 13 && (n == 34 || n == 37))
        {
            c = luhn(15, number);
            if (c % 10 == 0)
            {
                printf("AMEX\n");                 //condition for amex
                x++;
            }
        } 

        if (len == 12 && n == 4)
        {
            c = luhn(13, number);
            if (c % 10 == 0)
            {
                printf("VISA\n");               //condition for visa
                x++;
            }
        }

        if (len == 14 && (n >= 51 && n <= 55))
        {
            c = luhn(16, number);
            if (c % 10 == 0)
            {
                printf("MASTERCARD\n");             //condition for mastercard
                x++;
            }
        }

        if (len == 15 && n == 4)
        {
            c = luhn(16, number);
            if (c % 10 == 0)
            {
                printf("VISA\n");                      //condition for visa
                x++;
            }
        }
    }

    if (x == 0)
    {
        printf("INVALID\n");     //invalid condition
    }

}


long luhn(long b, long num)  //function defination //function to check luhn's alogorithm
{ 
    
                                                        
    long i, s = 0, y = 0;    // variables

    for (i = 0; i < b; i++)  //loop to add the numbers according to luhn's algo
    {
        if (i % 2 == 0) //for calc. of every other digit, starting with last digit
        {
            s = s + num % 10;
            num = num / 10;   
        }
        else      //for calc. of every other digit, starting with second-last digit
        {
            if (2 * (num % 10) > 9) 
            {
                y = 2 * (num % 10);
                s = s + (y % 10) + (y / 10);
                num = num / 10;
            }
            else         
            {
                s = s + 2 * (num % 10);
                num = num / 10;
            }
        }
    }
    return s;
}
