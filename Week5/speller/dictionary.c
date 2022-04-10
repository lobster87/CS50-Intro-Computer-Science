// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

// initialise variable
int count = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool checkWord(node *element, const char *word);
bool check(const char *word)
{
    // TODO
    // hash
    int value = hash(word);

    // loop through linked list
    bool TF = checkWord(table[value], word);

    return TF;
}

bool checkWord(node *element, const char *word)
{
    // basecase
    if (element == NULL)
    {
        return false;
    }

    // check word
    if (strcasecmp(element->word, word) == 0)
    {
        return true;
    }

    // move to next element
    return checkWord(element->next, word);
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // load word from file
    FILE* words = fopen(dictionary,"r");
    // check file is true
    if (words == NULL)
    {
        return 1;
    }

    char selectedWord[LENGTH + 1];

    while(fscanf(words, "%s", selectedWord)!= EOF)
    {
        // create new node
        node *new = malloc(sizeof(node));

        if (new == NULL)
        {
            return 2;
        }

        // place new word into node
        strcpy(new->word, selectedWord);

        // place node into table
        new->next = table[hash(selectedWord)];
        table[hash(selectedWord)] = new;

        // count word
        count++;
    }

    // close file
    fclose(words);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (count>0)
    {
        return count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
void freeMemory(node *element);
bool unload(void)
{
    // TODO
    for (int i=0; i<N; i++)
    {
        freeMemory(table[i]);
    }
    return true;
}

void freeMemory(node *element)
{
    // base case
    if (element == NULL)
    {
        return;
    }

    node* tmp = element->next;
    free(element);
    freeMemory(tmp);
}
