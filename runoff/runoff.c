#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // initialise i, iterate each valid vote
    for (int i = 0; i < candidate_count; i++)
    {
        // checking for name match using string compare before adding updating each candidate in the [100][9] preferences array using function declared voter and rank ints.
        // returns true if name matched and preferences array updated
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // Loops through each voter in the preferences array
    for (int i = 0; i < voter_count; i++)
    {
        // loops through each candidate in the preferences array
        for (int j = 0; j < candidate_count; j++)
        {
            // checks whether the candidate is eliminated; and increases candidate vote if candidate is not eliminated
            // if candidate is eliminated, checkes for the next ranked preference
            int candidate_matrix = preferences[i][j];
            if (candidates[candidate_matrix].eliminated != 1)
            {
                candidates[candidate_matrix].votes++;
                break;
            }
        }

    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // initialise from 0 to the total number of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // check if any candidate has more than half of total votes, print candidate name if exists
        if (candidates[i].votes > (voter_count / 2))
        {
            printf("%s\n", candidates[i].name);
            return true;
        }

    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // if the election has no candidates with votes more than half, this function checks within all candidates for the
    // least amount of votes.
    // set lowest_votes variable as voter count, which starts from 0. Each loop checks to see if there are any lower votes.
    int lowest_votes = voter_count;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes < lowest_votes && candidates[i].eliminated != 1)
        {
            lowest_votes = candidates[i].votes;
        }
    }
    return lowest_votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // declare tie count and run count variables.
    int tie_count = 0;
    int run_count = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        // checks if non-eliminated running candidates have votes equivalent to the lowest votes and adds to both tie counter
        // and the run counter.
        if (candidates[i].eliminated != 1 && candidates[i].votes == min)
        {
            tie_count++;
            run_count++;
        }
        // checks if the candidate is eliminated; if not eliminated adds to the number of candidates running
        else if (candidates[i].eliminated != 1)
        {
            run_count++;
        }

    }
    // return true if running candidates that are tied exists
    if (tie_count == run_count)
    {
        return true;
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // Checks for uneliminated candidates which have the lowest vote count and eliminates them.
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated != 1 && candidates[i].votes == min)
        {
            candidates[i].eliminated = 1;
        }
    }
}