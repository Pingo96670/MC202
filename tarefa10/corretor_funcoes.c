#include <stdlib.h>
#include "corretor_funcoes.h"


// Evaluates the absolute difference between two integers
int diff(int a, int b) {
    return abs(a-b);
}

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

// Compares two words
// Returns the char 'r', 'y' or 'g' based on the results
char compare_words(word wordA, word wordB, char current_result) {
    int i, difference_counter=0;

    if (diff(wordA.len, wordB.len)>=2) {
        return 'r';
    } else if (diff(wordA.len, wordB.len)==1) {
        if (wordA.len>wordB.len) {
            for (i=0; i<wordB.len; i++) {
                if (wordA.word[i+difference_counter]!=wordB.word[i]) {
                    difference_counter++;
                }

                if (difference_counter==2) {
                    return 'r';
                }
            }

            return 'y';
        } else {
            for (i=0; i<wordA.len; i++) {
                if (wordB.word[i+difference_counter]!=wordA.word[i]) {
                    difference_counter++;
                }

                if (difference_counter==2) {
                    return 'r';
                }
            }

            return 'y';
        }
    } else {
        for (i=0; i<wordA.len; i++) {
            if (wordA.word[i]!=wordB.word[i]) {
                difference_counter++;
            }

            if (difference_counter==2) {
                return 'r';
            }
        }

        if (difference_counter==0) {
            return 'g';
        } else {
            return 'y';
        }
    }
}

// Compares a word against all others in the dictionary (if needed)
// Returns the highest result obtained ('g'>'y'>'r')
char spell_checker(word* dict, word word_to_check) {
    int i, hash, can_be_green=1;
    char check_result='r';

    hash=hash_function(word_to_check);

    for (i=0; i<MAX; i++) {
        if (dict[(hash+i)%MAX].len!=0) { 
            check_result=compare_words(dict[(hash+i)%MAX], word_to_check, check_result);
        } else {
            can_be_green=0;
        }

        if (check_result=='g' || (check_result=='y' && !can_be_green)) {
            return check_result;
        }
    }

    return check_result;

}