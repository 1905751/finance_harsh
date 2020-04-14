#include <stdio.h>
#include <cs50.h>

long luhn(long,long);

int main(void)
{
    long len=0,x=0,c,n;
    long number = get_long("Number: ");
    n=number;

    while (n != 0)
    {
        n = n/10;
        len++;
        if (len == 13 &&(n == 34||n == 37))
        {
            c=luhn(15,number);
            if(c%10==0)
            {
                printf("AMEX\n");
                x++;
            }
        }
        if ( len == 12 && n == 4)
        {
            c=luhn(13,number);
            if(c%10==0)
            {
                printf("VISA\n");
                x++;
            }
        }
        if(len==14&&(n>=51&&n<=55))
        {
            c=luhn(16,number);
            if(c%10==0)
            {
                printf("MASTERCARD\n");
                x++;
            }
        }
        if(len==15&&n==4)
        {
            c=luhn(16,number);
            if(c%10==0)
            {
                printf("VISA\n");
                x++;
            }
        }
    }

    if(x==0)
    {
        printf("INVALID\n");
    }

}


long luhn(long b,long num)
{
    long i,s=0,y=0;
    for(i=0;i<b;i++)
    {
        if(i%2==0)
        {
            s=s+num%10;
            num=num/10;
        }
        else
        {
            if(2*(num%10)>9)
            {
                y=2*(num%10);
                s=s+(y%10)+(y/10);
                num=num/10;
            }
            else
            {
                s=s+2*(num%10);
                num=num/10;
            }
        }
    }
    return s;
}


