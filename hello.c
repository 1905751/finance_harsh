#include <stdio.h>
#include <cs50.h> 

int main(void)
{
    string name = get_string("what is your name\n"); //taking name input from user
    printf("hello, %s\n", name); //saying hello to the user
}
