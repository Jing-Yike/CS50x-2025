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
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 114;

// Hash table
node *table[N];

// Counter tracks the number of words have been loaded
int counter = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Hash the word to obtain its hash value
    int key = hash(word);

    // Search the hash table at the location specified by the word's hash value
    node *ref = table[key];
    while (ref != NULL)
    {
        if (strcasecmp(word, ref->word) == 0)
        {
            return true;
        }
        ref = ref->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return tolower(word[0]) - 2 * strlen(word);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];

    // Read each word in the file
    while (fscanf(source, "%s", word) != EOF)
    {
        // Add each word to the hash table
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, word);

        // Hash the word to obtain its hash value and insert the new node
        n->next = table[hash(n->word)];
        table[hash(n->word)] = n;
        counter++;
    }

    // Close the dictionary file
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 7; i <= 120; i++)
    {
        node *cursor = table[i];
        node *tmp = table[i];
        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
