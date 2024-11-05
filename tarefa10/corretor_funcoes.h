#define MAX_WORD_LEN 25
#define MAX 101

// Word struct
// Stores the word itself, as well as its length
typedef struct word {
    char word[MAX_WORD_LEN];
    int len;
} word;


// Evaluates the absolute difference between two integers
int diff(int a, int b);

// Hash function for a string
// Uses the division method
// Returns the hash integer
int hash_function(word word);

// Adds a word to the dictionary
// Uses linear probing
// Alters the dictionary directly
void add_to_dict(word* dict, word word);

// Compares two words
// Returns the char 'r', 'y' or 'g' based on the results
char compare_words(word wordA, word wordB, char current_result);

// Compares a word against all others in the dictionary (if needed)
// Returns the highest result obtained ('g'>'y'>'r')
char spell_checker(word* dict, word word_to_check);