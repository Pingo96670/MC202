#include <stdio.h>
#define MAX 10000000000

// Reverses number
unsigned long long reverse_num(unsigned long long k) {
    unsigned long long i=10, reverse=0, aux_k=k;

    for (; i<MAX && aux_k!=0;) {
        reverse=reverse*10+aux_k%i;
        aux_k=(aux_k-aux_k%i)/10;
    };

    return reverse;
}

// Checks if a number is palindromic
int is_palindrome(unsigned long long k) {
    if (k == reverse_num(k)) {
        return 1;
    }

    return 0;
}

int main() {
    int n;
    long long k;

    scanf("%d", &n);

    for (int i=0; i<n; i++) {
        scanf("%lld", &k);
        if (is_palindrome(k)) {
            printf("%lld eh capicua\n", k);
        }
        else {
            printf("%lld nao eh capicua\n", k);
        }
    }

    return 0;
}
