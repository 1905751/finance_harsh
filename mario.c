#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int i, j;// initializing required variables
    int height;

    do
    {
        height = get_int("enter the height\n");     // asking height from the user
    }
    while (height < 1 || height > 8);

    for (i = 0; i < height; i++)// loop to change the line
    {
        for (j = 0; j < height; j++)//loop to print left pyramid
        {
            if (j >= height - 1 - i)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }

        printf("  ");       // to print thr gap btwn to pyramids

        for (j = 0; j <= i; j++) //to print the right pyramid
        {
            printf("#");
        }

        printf("\n");

    }
}
