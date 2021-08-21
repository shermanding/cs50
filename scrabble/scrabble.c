#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }

    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string

    // Declaring score variable, initialising to 0, setting loop to count up the number of letters in word
    int score = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        // check if word contains special characters and ignores, extracts letter score from POINTS array. char 'l' for letter
        // converts to lowercase and gets index of char 'l' in a 0-based index by subtracting the index 0 alphabet. e.g ASCII of 'a' - 'a' = 0 and ASCII of 'g' - 'a' = 6 respectively.
        char l = word[i];
        if (isalpha(l))
        {
            score += POINTS[tolower(l) - 'a'];
        }

    }

    return score;
}
