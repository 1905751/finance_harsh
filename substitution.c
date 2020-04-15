#include <stdio.h>
#include <cs50.h>
#include <string.h>

int rev(string key);

int main(int argc, string argv[])
{

    if (argc == 2)
    {
        int x, i, z = 0, y;
        string str, pt;
       str = argv[1];
       for (i = 0; str[i] != '\0'; i++)
       {
           z++;
       }
       if(z != 26)
       {
           printf("Key must contain 26 characters.");
           return 1;
       }
       
       // to do checking of validity of key
       y = rev(str);
       if(y == 1)
       {
           printf("invalid");
           return 1;
       }


       pt = get_string("plaintext: ");
       printf("ciphertext: ");

       for (i = 0; pt[i] != '\0'; i++)
       {
           x = (int) pt[i];
           if (x >= 65 && x <= 90)
           {
               x = x - 65;
               if (str[i] >= 65 && str[i] <= 90)
               {
                   printf("%c",str[x]);
               }
               else
               {
                   printf("%c",str[x] - 32);
               }
           }
           else if (x >= 97 && x <= 122)
           {
               x = x - 97;
               if (str[i] >= 97 && str[i] <= 122)
               {
                   printf("%c",str[x]);
               }
               else
               {
                   printf("%c",str[x] + 32);
               }
           }
           else
           {
               printf("%c", pt[i]);
           }
           

       }
       printf("\n");
       return 0;

    }
        printf("no key");
        return 1;
}




int rev(string key)
{
    int i,k;
    int hash[26];
    for (i = 0; key[i] != '\0'; i++)
    {
        k = (int) key[i];
        if (k >= 65 && k <= 90)
        k = k - 65;
        else if (k >= 97 && k <= 122)
        k = k - 97;
        else
        return 1;
        if (hash[k] == 0)
        hash[k]++;
        else if (hash[k] == 1)
        return 1;
    }

    return 0;

}