#include <math.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

int main(void)
{
    string s = get_string("Text: ");

    // declaring letter, word and sentence count int variables
    int lettercount = 0, wordcount = 0, sentence_count = 0;

    // for loop that checks each character in the string array
    int i = 0;
    for (i = 0; i < strlen(s); i++)
    {
        // condition loop to check between special characters and alphabets, adds lettercount if check is passed
        if (isalpha(s[i]))
        {

            lettercount++;

        }
        // first condition loop to check if space is followed by a character for strings with more than 1 word. For input with more than 1 word.
        // second condition loop to check if it is first word, and checks if non space exists. For input with 1 word and special character.
        // third condition loop to check if first word and check for null character which determines end of word. For input with only 1 word and no special character.
        if ((s[i] == ' ' && s[i + 1] != ' ') || (i == 0 && s[i] != ' ') || (i == 0 && s[i] == '\0'))
        {

            wordcount++;

        }
        // condition loop to check for three special characters which marks the end of a sentence.
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {

            sentence_count++;

        }

    }

    //employing Coleman-Liau index, determining floating variables L & S by typecasting float into equation
    float L = (lettercount / (float) wordcount) * 100;
    float S = (sentence_count / (float) wordcount) * 100;
    // rounding the equation to the nearest number and truncating by getting int of index
    int index = round((0.0588 * L) - (0.296 * S) - 15.8);

    // constraints to determine which grade while setting limits below 1 and above 16
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }

    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}