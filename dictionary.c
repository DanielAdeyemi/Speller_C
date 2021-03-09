// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 676;

// Hash table
node *table[N];

int words_s = 0;
// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *temp = table[hash(word)];
    while (temp != NULL)
    {
        if (strcasecmp(word, temp->word) == 0)
        {
            return true;
        }
        else
        {
            temp = temp->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{

    char w1 = tolower(word[0]);
    char w2 = tolower(word[1]);
    unsigned int hash = (((w1 - 97) * 26 + (w2 - 97)) % N);
    return hash;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char dic[LENGTH + 1];
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    //loop going through all words in dicitionary and copy them into the hash table

    while (fscanf(dict, "%s", dic) != EOF)
    {
        node *wrd = malloc(sizeof(node));//allocate memory for word from dictionary to store the node
        if (wrd == NULL)
        {
            return false;
        }

        strcpy(wrd->word, dic); // copy this string into a word part of the node wrd
        wrd->next = NULL; //set pointer to the next node to NULL
        int index = hash(dic);
        if (table[index] == NULL)
        {
            table[index] = wrd;
        }
        else
        {
            wrd->next = table[index];
            table[index] = wrd;
        }
        words_s++;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (words_s != 0)
    {
        return words_s;
    }

    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            node *tmp = table[i];
            node *sav = tmp;
            while (tmp != NULL)
            {
                sav = sav->next;
                free(tmp);
                tmp = sav;
            }
        }
        else
        {
            continue;
        }
    }
    return true;
}
