#include <stdio.h>
#include <cs50.h>
#include <string.h>

int rev(string key);

// main programme
int main(int argc, string argv[])
{

    if (argc == 2)
    {
        //variables
        int x, i, z = 0, y;
        string str, pt;
        str = argv[1];    //copying argv to str
        //loop to check length of sting
        for (i = 0; str[i] != '\0'; i++)
        {
            z++;
        }
        if (z != 26)
        {
            printf("Key must contain 26 characters.");
            return 1;
        }
       
        //checking of validity of key
        //calling rev
        y = rev(str);
        if (y == 1)
        {
            printf("invalid");
            return 1;
        }


        //taking user input
        pt = get_string("plaintext: ");
        printf("ciphertext: ");

        //loop to cipher the plaintext
        for (i = 0; pt[i] != '\0'; i++)
        {
            x = (int) pt[i];
            if (x >= 65 && x <= 90)
            {
                x = x - 65;
                if (str[x] >= 65 && str[x] <= 90)
                {
                    printf("%c", str[x]);
                }
                else
                {
                    printf("%c", str[x] - 32);
                }
            }                                                    //conditions to allign key according to plain test
            else if (x >= 97 && x <= 122)
            {
                x = x - 97;
                if (str[x] >= 97 && str[x] <= 122)
                {
                    printf("%c", str[x]);
                }
                else
                {
                    printf("%c", str[x] + 32);
                }
            }
            else
            {
                printf("%c", pt[i]);                            //to print characters rather than alphabets
            }
           

        }
        printf("\n");
        return 0;

    }
    printf("no key");         //no key condition
    return 1;
}




//function to check repetetion or key validity
int rev(string key)
{
    int i, j, k;
    for (i = 0; key[i] != '\0'; i++)
    {
        k = (int) key[i];
        if (k >= 65 && k <= 90)
        {
            k = k - 65;
        }
        else if (k >= 97 && k <= 122)         //for key validity
        {
            k = k - 97;
        }
        else
        {
            return 1;
        }
        
        
        for (j = i + 1; key[j] != '\0'; j++)
        {
            if (key[i] == key[j])           //for repetetion
            {
                return 1;
            }
        }
    }

    return 0;

}