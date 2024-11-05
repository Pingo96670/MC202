#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "corretor_funcoes.h"


int main() {
    int i, dict_words_num, words_to_check;
    char result;
    word temp_word;
    word* dict;
   
    dict=calloc(MAX, sizeof(word));

    scanf("%d %d", &dict_words_num, &words_to_check);

    // Store dictionary words
    for (i=0; i<dict_words_num; i++) {
        scanf("%s", temp_word.word);
        temp_word.len=strlen(temp_word.word);
        add_to_dict(dict, temp_word);
    }

    // Check given words
    for (i=0; i<words_to_check; i++) {
        // Analyze word
        scanf("%s", temp_word.word);
        temp_word.len=strlen(temp_word.word);
        result=spell_checker(dict, temp_word);

        // Print results
        printf("%s: ", temp_word.word);

        switch (result) {
        case 'r':
            printf("vermelho\n");
            break;

        case 'y':
            printf("amarelo\n");
            break;

        case 'g':
            printf("verde\n");
            break;

        default:
            break;
        }
    }

    free(dict);

    return 0;
}