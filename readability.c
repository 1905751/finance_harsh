#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //variables
    float index = 0.0;
    float l = 0.0, s = 0.0, w = 0.0;
    int i;
    string text;

    //getting text
    text = get_string("Text: ");

    //loop to calculate total no. of words and sentence
    for (i = 0; text[i] != '\0'; i++)
    {
        
        //letters
        if ((text[i] >= 97 && text[i] <= 122) || (text[i] >= 65 && text[i] <= 90))
        {
            l++;
        }
        
        //for word calculation
        if (text[i] == ' ' || text[i+1] == '\0')
        {
            w++;
        }
        
        //for sentence calculation
        if (text[i] == '.' || text[i] == '!')
        {
            s++;
        }
    }
    
    //letters and sectences per 100 words
    l = (l / w) * 100;
    s = (s / w) * 100;
    
    //index calculation
    index = 0.0588 * l - 0.296 * s - 15.8 ;
    
    if ((int) (index+0.5)> (int) index)
    printf("Grade %d", (int) index + 1);
    else
    printf("Grade %d", (int) index);

}