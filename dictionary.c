// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 2];
    struct node *next;
}
node;

// Number of buckets in hash table
const int HASHTABLE_SIZE = 65536;

// Hash table
node *table[HASHTABLE_SIZE];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int len = strlen(word);
    char word_copy[len + 1];

    // convert word to lowercase and store it in word_copy
    for (int i = 0; i < len; i++)
    {
        word_copy[i] = tolower(word[i]);
    }

    // add null terminator to end of char array
    word_copy[len] = '\0';

    // get hash value (a.k.a. bucket)
    int h = hash(word_copy);

    // assign cursor node to the first node of the bucket
    node *cursor = table[h];

    // check until the end of the linked list
    while (cursor != NULL)
    {
        if (strcmp(cursor->word, word_copy) == 0)
        {
            // word is in dictionary
            return true;
        }
        else
        {
            // check next node
            cursor = cursor->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    unsigned int hash = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        hash = (hash << 2) ^ word[i];
    }
    return hash % HASHTABLE_SIZE;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // initialise word
    char word[LENGTH + 2];

    // open dictionary
    FILE *dicptr = fopen(dictionary, "r");

    // iterate through dictionary words
    while (fscanf(dicptr, "%s", word) != EOF)
    {
        // make a new word.
        node *new_node = malloc(sizeof(node));

        // check for error assigning memory
        if (new_node == NULL)
        {
            unload();
            return false;
        }
        else
        {
            // copy word into node
            strcpy(new_node->word, word);

            // use hash function to determine which bucket (linked list) to insert word into
            int n = hash(new_node->word);

            // insert into list
            new_node->next = table[n];
            table[n] = new_node;
        }
    }
    // close dictionary
    fclose(dicptr);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int counter = 0;

    // iterate through hashtable
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        // set pointer to head of list
        node *cursor = table[i];

        // traverse list
        while (cursor != NULL)
        {
            counter++;
            cursor = cursor->next;
        }
        free(cursor);
    }
    return counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        // set pointer to head of list
        node *cursor = table[i];

        // traverse list
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
            free(cursor);
        }

    }
    return true;
}
