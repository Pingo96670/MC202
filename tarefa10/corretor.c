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

    free(dict);

    return 0;
}