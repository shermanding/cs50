// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
// constant N can be changed to add more buckets
const unsigned int N = 1000000;

// Hash table, which will have the addresses of all nodes, which will store the words
node *table[N];

// Word_count variable to calculate number of words
int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // get the hash index of the word using hash function
    int hash_index = hash(word);

    // assessing the linked list
    node *cursor = table[hash_index];

    // cursor will go through a loop until it reaches NULL, which is the end of the linked list.
    while (cursor != NULL)
    {

        // looking through the linked list, one node at a time. Cursor traverses through the linked lists.
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;

    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Function should take a string and return an index
    // This hash function adds the ASCII values of all characters converted to lower case in the word together, mod N to ensure result is < N.
    int hash_value = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        hash_value = (hash_value + tolower(word[i]) - 'a') % N;
    }
    return hash_value;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open file in read mode
    FILE *dict = fopen(dictionary, "r");

    // declare word array with size LENGTH + 1 for null character
    char word_array[LENGTH + 1];

    // check if null, return false if cant
    if (dictionary == NULL)
    {
        printf("Unable to open %s\n", dictionary);
        return false;
    }

    // first argument file pointer of fopen, second argument string, third argument character array
    // loop scanf on the file, get one word at a time until fscanf returns EOF which signifies end of file.
    while (fscanf(dict, "%s", word_array) != EOF)
    {
        // create a new node
        node *n = malloc(sizeof(node));

        // if malloc doesnt have enough memory to store node, it will return NULL and bool should return false
        if (n == NULL)
        {
            return false;
        }
        // copy word into node
        strcpy(n->word, word_array);

        // insert node into hash table
        // hash function will take the string and obtain index
        int hash_index = hash(word_array);

        // insert word into linked list in hash table
        // firstly, we set the new node's pointer to the head of the list, then we set the node as the NEW head of list. New nodes will be added to the linked list for
        // all words in the dictionary.
        n->next = table[hash_index];
        table[hash_index] = n;
        word_count++;
    }

    // close the file
    fclose(dict);
    // return true if word has been loaded
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Returns the word count
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // initialise fro 0, while i is smaller than N.
    for (int i = 0; i < N; i++)
    {
        // assign cursor2 to ith node in hash table
        node *cursor2 = table[i];
        // checks if cursor2 still has nodes
        while (cursor2 != NULL)
        {
            node *tmp = cursor2->next;
            free(cursor2);
            cursor2 = tmp;
        }
        // if pointer is NULL & i is equivalent to N-1, this means it reached end of linked list and end of table.
        if (cursor2 == NULL && i == N - 1)
        {
            // returns true if all memory that was malloc-ed is freed.
            return true;
        }

    }
    return false;
}
