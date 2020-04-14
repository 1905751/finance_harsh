#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int len=0,x=0;
    long n = get_long("Number: ");

    while (n != 0)
    {
        n = n/10;
        len++;
        if (len == 13 &&(n == 34||n == 37))
        {
            printf("AMEX\n");
            x++;
        }
        if ( len == 12 && n == 4)
        {
            printf("VISA\n");
            x++;
        }
        if(len==14&&(n>=51&&n<=55))
        {
            printf("MASTERCARD\n");
            x++;
        }
       /* if(len==15&&n==4)
        {
            printf("VISA\n");
            x++;
        }*/
    }

    if(x==0)
    {
        printf("INVALID\n");
    }

}
