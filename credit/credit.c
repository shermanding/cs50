#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // declaring long user input & establishing do while loop
    long long n;
    do
    {
        n = get_long("Number: ");
    }
    while(n <= 0);

    // declaring digits variable
    long long digits = n;

    // declaring count variable and count digits input
    int count = 0;
    do
    {
        count++;
        digits = (long long)(digits / 10);
    }
    while(digits != 0);

    // checksum and initialise variables
    long long cc = n;
    long long sum_a = 0;
    long long sum_b = 0;
    int odd = 0;
    int even = 0;
    int x = 0;
    int y = 0;
    int total = 0;

    // while loop for checksum
    while(cc > 0)
    {
        // removing last digit from number and adding to sum
        odd = (int)(cc % 10);
        cc = cc / 10;
        sum_a = (int)(sum_a + odd);

        // removing 2nd last digit from number and adding to sum
        even = (int)(cc % 10);
        cc = cc / 10;

        // summing up every other digit from 2nd last digit
        even = (int)(even * 2);
        x = (int)(even % 10);
        y = (int)(even / 10);
        sum_b = sum_b + x + y;

        total = sum_a + sum_b;
    }

    if(total % 10 != 0)
    {
        printf("INVALID\n");
    }

    else
    {
        // get starting 2 digits
        long long first_2_digits = n;
        do
        {
            first_2_digits = (long long)(first_2_digits / 10);
        }
        while(first_2_digits > 100);

        // check for AMEX, VISA, MASTER
        if((first_2_digits == 51 || first_2_digits == 52 || first_2_digits == 53 || first_2_digits == 54 || first_2_digits == 55) && count == 16)
        {
            printf("MASTERCARD\n");
        }
        else if((first_2_digits == 34 || first_2_digits == 37) && count == 15)
        {
            printf("AMEX\n");
        }
        else if(((int)(first_2_digits / 10) == 4) && (count == 13 || count == 16))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
}
