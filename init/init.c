#include "init.h"

/**
 * @brief 
 * 
 * @param queue 
 */
void freeAll(QUEUE * queue){
    PROCESS * current  = queue->head;
    PROCESS * tmp = NULL;
    while(current != NULL){
        tmp = current;
        current = current->next;
        free(tmp);
    }
    free(queue);
}

/**
 * @brief Get the Name object
 * 
 * @return char* 
 */
char * getStatus(){
    static char status[20];
    printf("\t\tDonnez le status du processus. \n\t\tReady [1], Waitin [2], Running [3]\n");
    int choice = -1;
    while(choice == -1){
        choice = getIntBetween(1,3);
    }
    switch (choice) {
        case 1:
            strncpy(status, "Ready", 20);
            break;
        case 2:
            strncpy(status, "Waitin", 20);
            break;
        case 3:
            strncpy(status, "Running", 20);
            break;
    }
    return status;
}

/**
 * @brief Get the Priority object
 * 
 * @return int 
 */
int getPriority(){
    int choice = -1;
    printf("\t\tQuelle est la priorité du job [1-9]?\n");
    while(choice == -1){
        choice = getIntBetween(MIN_PRIORITY,MAX_PRIORITY);
    }
    return choice;
}

/**
 * @brief 
 * 
 * @return int 
 */
int getPID(){
    return getRandomBetween(0,9000);
}

/**
 * @brief 
 * 
 * @return PROCESS* 
 */
PROCESS * create(){
    PROCESS * process = malloc(sizeof(PROCESS));
    strncpy(process->state, getStatus(), 20);
    process->priority = getPriority();
    process->pid = getPID();
    process->next = NULL;
    return process;
}

/**
 * @brief 
 * 
 * @param choice est initialisé
 * @param queue est initialisé
 */
void run(int choice, QUEUE * queue){
    boolean isInserted = -1;
    boolean isDeleted = -1;
    PROCESS * p = NULL;
    switch(choice){
        case 1: 
            if(queue->size == 0){
                puts("\t\t Il n'y a pas de processus à afficher\n");
            } else {
                printHeap(queue);
                printf("\n\n");
            }
            menu(queue);
            break;
        case 2: 
            p = create();
            isInserted = insert(queue,p);
            if(!isInserted){
                printf("\t\tL'élément n'a pu être insérer\n");
                free(p);
            }
            menu(queue);
            break;
        case 3:
            isDeleted = delete(queue);
            if(!isDeleted){
                printf("\t\tL'élément n'a pu être supprimer\n");
            }
            menu(queue);
            break;
        case 4:
            freeAll(queue);
            printf("\n\t\tA bientôt! :D\n\n");
            break;
    }
}

/**
 * pré: choice est initialisé
 * pos: choice est inchangé
 * rés: vrai ssi choice est compris entre 1 et 3 inclus 
*/
boolean isNotChoiceCorrect(int choice){
    boolean isCorrect = true;
    if(choice < 1 || choice > 4){
        printf("\t\tChoix incorrect. Choisissez un chiffre entre [1-4]\n");
        isCorrect = false;
    }
    return isCorrect;
}

/**
 * pré: "../data/menu.txt" existe
 * pos: imprime le fichier "../data/menu.txt" à l'écran
 *      demande une saisie à l'utilisateur et boucle la demande
 *      tant que le joueur n'a pas entré une saisie valide
 * rés: //
*/
void menu(QUEUE * queue){

    FILE * menu = getFile(path_menu,read);
    char readChar;
    do{
        readChar = fgetc(menu);
        printf("%c",readChar);
    }while(readChar != EOF);
    fclose(menu);
    int choice = -1;
    boolean isSuccess;
    do{
        isSuccess = scanf("%d",&choice);
        flushStdin();
    }while(!isSuccess | !isNotChoiceCorrect(choice));

    run(choice,queue);
}