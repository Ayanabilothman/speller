// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

//to track number of words
int count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);

    node *tmp = table[index];

    while (tmp != NULL)
    {
        if (strcasecmp(tmp -> word, word) ==  0)
        {
            return true;
        }
        else
        {
            tmp = tmp -> next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int key = tolower(word[0]) - 97;
    return key;
}


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dictionary_file = fopen(dictionary, "r");
    if (dictionary_file == NULL)
    {
        return false;
    }

    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }


    // read each word
    char read_word[LENGTH + 1];

    while (fscanf(dictionary_file, "%s", read_word) != EOF)
    {
        // create a node for each word
        node *ptr = malloc(sizeof(node));
        if (ptr == NULL)
        {
            printf("Failed to allocate memory for a node\n");
            return 2;
        }

        //insert the read word into the node
        strcpy(ptr -> word, read_word);
        ptr -> next = NULL;

        int index = hash(read_word);

        if (table[index] == NULL)
        {
            table[index] = ptr;
        }
        else
        {
            ptr -> next = table[index];
            table[index] = ptr;
        }
        // to use in size function
        count++;
    }
    fclose(dictionary_file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0 ; i < N; i++)
    {
        node *cursor = table[i];
        node *tmp = cursor;

        while (tmp != NULL)
        {
            cursor = cursor -> next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
