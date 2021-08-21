#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// custom boolean function
bool check_numeric(string s);

// command line argument to allow integers for key
int main(int argc, string argv[])
{
    // if total number of words including program name is != 2, or if custom boolean check returns not true, return 1.
    if (argc != 2 || !check_numeric(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    else
    {
        // converting command line number to int k, which is the key
        int k = atoi(argv[1]);

        // check if agrv number is a negative number
        if (k < 0)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
        else
        {
            // get user-input string for plaintext
            string p = get_string("Plaintext: ");

            // print Ciphertext by looping each character in string and applying the cipher
            printf("Ciphertext: ");

            // initialising i to 0 and to loop each character by the length of the plain text
            for (int i = 0; i < strlen(p); i++)
            {
                // assigning character c to each element in the plaintext string
                char c = p[i];
                // checks each character if it is alphabet
                if (isalpha(c))
                {
                    // check each character if it is lowercase alphabet
                    if (islower(c))
                    {
                        // if lowercase, subtract the base of lowercase ASCII, 'a' which is 97, apply cipher formulae and then add the base back to change them back to ASCII characters
                        printf("%c", (((c + k) - 'a') % 26) + 'a');
                    }
                    else
                    {
                        // if uppercase, subtract the base of uppercase ASCII, 'A' which is 65, apply cipher formulae and then add the base back to change them back to ASCII characters
                        printf("%c", (((c + k) - 'A') % 26) + 'A');
                    }

                }
                else
                {
                    // if character is not alphabet, then return whatever the character is
                    printf("%c", c);
                }

            }
        }
        printf("\n");
    }
}

// boolean function to check if each character in argv string input is numeric
bool check_numeric(string s)
{
    // iterate over i, check each character in s whether it is numeric
    for (int i = 0; i < strlen(s); i++)

        if (isdigit(s[i]))
        {
            return true;
        }
        else
        {
            return false;
        }

    return false;
}