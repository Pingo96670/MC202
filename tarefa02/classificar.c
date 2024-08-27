#include <stdio.h>
#include <string.h>
#define MAX_NAMES 100
#define MAX_CHAR 31

// Checks if the first name of each patient corresponds to the searched name
int check_first_name(char name[], char searched_name[]) {
    int i;
    char first_name[MAX_CHAR];

    for (i=0; name[i]!='_'; i++) {
        first_name[i]=name[i];
    }

    first_name[i]='\0';

    if (strcmp(first_name, searched_name)==0) {
        return 1;
    }

    return 0;
}

// Checks if the last name of each patient corresponds to the searched name
int check_last_name(char name[], char searched_name[]) {
    int i=0, j=0;
    char last_name[MAX_CHAR];

    while (name[i]!='_') {
        i++;
    }

    i++;

    for (; i<strlen(name); i++) {
        last_name[j]=name[i];
        j++;
    }

    last_name[j]='\0';

    if (strcmp(last_name, searched_name)==0) {
        return 1;
    }

    return 0;
}

int main() {
    int n, i;
    char name_list[MAX_NAMES][MAX_CHAR], selected_option[10], searched_name[MAX_CHAR];

    scanf("%d", &n);

    for (i=0; i<n; i++) {
        scanf("%s", name_list[i]);
    }

    scanf("%s %s", selected_option, searched_name);

    if (strcmp(selected_option, "homonimos")==0) {
        for (i=0; i!=n; i++) {
            if (check_first_name(name_list[i], searched_name)) {
                printf("%s\n", name_list[i]);
            }
        }
    }

    else if (strcmp(selected_option, "parentes")==0) {
        for (i=0; i!=n; i++) {
            if (check_last_name(name_list[i], searched_name)) {
                printf("%s\n", name_list[i]);
            }
        }
    }

    else {
        printf("Seleção inválida");
    }

    return 0;
}