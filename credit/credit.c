#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // declaring long user input & establishing do while loop
    long n;
    do
    {
        n = get_long("Number: ");
    }
    while(n <= 0);

    // declaring count variable
    int count = 0;
    do
    {
        count++;
        n /= 10;
    }
    while(n != 0);

    // establish checksum constraint


    // Assigning card types
    string card = 0;

    if (count == 16)
    {
        card = "MASTER";
    }
    else if (count == 13)
    {
        card = "VISA";
    }
    else if (count == 15)
    {
        card = "AMEX";
    }
    else
    {
        card = "INVALID";
    }

    printf("%s\n", card);

}