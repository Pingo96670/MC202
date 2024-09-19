#include <stdio.h>
#include <string.h>
#define MAX_WORD_LENGTH 400

// Function to determine if a word is a k-quasi-palindrome
// Uses recursion to check words in "a-p-a" manner, where "p" is a palindrome and "a" is any letter
// Returns 0 if there are more mismatches (k_count) than requested (k)
// Returns 1 otherwise, reaching the end with k_count<=k
int is_k_quasi_palindrome(char *word, int k, int start, int end, int k_count) {

    if (start>=end) {
        return 1;
    }

    if (word[start]!=word[end]) {
        k_count+=2;
    }

    if (k_count>k) {
        return 0;
    }

    return is_k_quasi_palindrome(word, k, start+1, end-1, k_count);
}

int main() {
    int k, k_count=0;
    char word[MAX_WORD_LENGTH];

    scanf("%d %s", &k, word);

    if (is_k_quasi_palindrome(word, k, 0, strlen(word)-1, k_count)) {
        printf("sim");
    }

    else {
        printf("nao");
    }

    return 0;
}