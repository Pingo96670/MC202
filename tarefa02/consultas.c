#include <stdio.h>
#include <string.h>
#define MAX_SLOTS 100

// Patients structure for ease of data management
typedef struct patients {
    char name[31];
    char cid[4];
    int crm;
    int free;
} patient;

// Function to fetch the corresponding diagnosis from the "doencas.txt" file
void fetch_cid(char cid[4], char diagnosis[]) {
    int n, i, j, exit=0;
    char cid_in_file[4], buffer[101];;
    FILE *doencas=fopen("dados/doencas.txt", "r");

    if (doencas == NULL) {
        perror("Não foi possivel abrir doencas.txt");
    }

    fscanf(doencas, "%d", &n);

    for (i=0; i<n; i++) {

        fscanf(doencas, " %[^\n]", buffer);

        for (j=0; j<3; j++) {
            cid_in_file[j]=buffer[j];
        }

        cid_in_file[3]='\0';

        if (strcmp(cid, cid_in_file)==0) {
            for (j=4; j<strlen(buffer); j++) {
                diagnosis[j-4]=buffer[j];
            }

            diagnosis[j-4]='\0';

            fclose(doencas);
            exit=1;
            break;
        }
    }
    if (!exit) {
        perror("cid nao encontrado");
        fclose(doencas); 
    }
}

// Function to fetch the assigned doctor's name from the "medicos.txt" file
void fetch_crm(int crm, char doctor_name[]) {
    int n, i, crm_in_file, exit=0;
    FILE *medicos=fopen("dados/medicos.txt", "r");

    if (medicos == NULL) {
        perror("Nao foi possivel abrir medicos.txt");
    }

    fscanf(medicos, "%d", &n);

    for (i=0; i<n; i++) {
        fscanf(medicos, "%d %s", &crm_in_file, doctor_name);

        if (crm==crm_in_file) {
            fclose(medicos);
            exit=1;
            break;
        }
    }

    if (!exit) {
        perror("crm nao encontrado");
        fclose(medicos);
    } 
}

// Function to register an appointment
void register_appointment(patient appointments[], char name[31], char cid[4], int crm) {
    int j;

    for (j=0; j<MAX_SLOTS; j++) {
        if (appointments[j].free) {
            strcpy(appointments[j].name, name);
            strcpy(appointments[j].cid, cid);
            appointments[j].crm=crm;
            appointments[j].free=0;
            break;
        }
    }
}

// Function to remove an appointment
// Shifts "appointments" array down by one from the removed slot and frees the last one in the list
void remove_appointment(patient appointments[], char name[31], int i, int n_registered) {
    int j;
    for (j=0; j<MAX_SLOTS; j++) {
        if (strcmp(appointments[j].name, name)==0) {
            break;
        }
    }

    for (; j<MAX_SLOTS-1; j++) {
        appointments[j]=appointments[j+1];
    }

    appointments[n_registered].free=1;
}

// Function to edit a patient's diagnostic
void change_diagnostic(patient appointments[], char name[31], char new_cid[4], int i) {
    int j;
    for (j=0; j<MAX_SLOTS; j++) {
        if (strcmp(appointments[j].name, name)==0) {
            strcpy(appointments[j].cid, new_cid);
            break;
        }
    }
}

// Prints final report
void close(patient appointments[], int n) {
    int i;
    char diagnosis[101], doctor_name[31];

    for (i=0; i<MAX_SLOTS; i++) {
        if (appointments[i].free==0) {
            fetch_cid(appointments[i].cid, diagnosis);
            fetch_crm(appointments[i].crm, doctor_name);
            printf("%s atendido por %s: %s\n", appointments[i].name, doctor_name, diagnosis);
        }
    }
}

int main() {
    int n, i, crm, n_registered=0;
    patient appointments[MAX_SLOTS];
    char command[10], name[31], cid[4];

    for (i=0; i<MAX_SLOTS; i++) {
        appointments[i].free=1;
    }

    scanf("%s%d", command, &n);

    // Loop to allow commands
    for (i=0; i<MAX_SLOTS*10; i++) {
        scanf("%s", command);

        if (strcmp(command, "registrar")==0) {
            scanf("%s %s %d", name, cid, &crm);
            register_appointment(appointments, name, cid, crm);
            n_registered++;
        }

        else if (strcmp(command, "remover")==0) {
            scanf("%s", name);
            n_registered--;
            remove_appointment(appointments, name, i, n_registered);
        }

        else if (strcmp(command, "alterar")==0) {
            scanf("%s %s", name, cid);
            change_diagnostic(appointments, name, cid, i);
        }

        else if (strcmp(command, "fechar")==0) {
            close(appointments, n);
            break;
        }

        else {
            printf("Comando incorreto");
        }
    }

    return 0;
}