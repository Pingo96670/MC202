#include "corretor_funcoes.h"


// Hash function for a string
// Uses the division method
// Returns the hash integer
int hash_function(word word) {
    int i, hash=0;

    for (i=0; i<word.len; i++) {
        hash=(256*hash+word.word[i])%MAX;
    }

    return hash;
}

// Adds a word to the dictionary
// Uses linear probing
// Alters the dictionary directly
void add_to_dict(word* dict, word word) {
    int hash;

    hash=hash_function(word);

    while (dict[hash].len!=0) {
        hash=(hash+1)%MAX;
    }

    dict[hash]=word;    
}