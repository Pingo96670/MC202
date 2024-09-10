#include <stdio.h>
#include <string.h>
#define MAX 400

// Function to determine if a word is a k-quasi-palindrome
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
    char word[MAX];

    scanf("%d %s", &k, word);

    if (is_k_quasi_palindrome(word, k, 0, strlen(word)-1, k_count)) {
        printf("sim");
    }

    else {
        printf("nao");
    }

    return 0;
}