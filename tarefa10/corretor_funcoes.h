#define MAX_WORD_LEN 25
#define MAX 101

// Word struct
// Stores the word itself, as well as its length
typedef struct word {
    char word[MAX_WORD_LEN];
    int len;
} word;


// Hash function for a string
// Uses the division method
// Returns the hash integer
int hash_function(word word);

// Adds a word to the dictionary
// Uses linear probing
// Alters the dictionary directly
void add_to_dict(word* dict, word word);

char compare_words(word wordA, word wordB, char current_result);