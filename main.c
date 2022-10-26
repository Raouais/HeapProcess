#include <stdio.h>
#include <stdlib.h>
#include "init/init.h"
#include "structures/structures.h"
#include "utils/functions.h"

int main(void){
    QUEUE * queue = malloc(sizeof(QUEUE));
    queue->head = NULL;
    queue->size = 0;
    clrsrc();
    menu(queue);
    return EXIT_SUCCESS;
}

