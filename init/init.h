#include <stdio.h>
#include <stdlib.h>
#include "../utils/functions.h"
#include "../structures/structures.h"
#include "../heap/heap.h"

#ifndef INIT_H
#define INIT_H
#define MAX_PRIORITY 9
#define MIN_PRIORITY 1
#define path_menu "data/menu.txt"
#define read "r"
#define true 1
#define false 0

typedef int boolean;

void freeAll(QUEUE * queue);
char * getName();
int getPriority();
int getPID();
PROCESS * create();
void run(int choice, QUEUE * queue);
boolean isNotChoiceCorrect(int choice);
void menu(QUEUE * queue);

#endif