#ifndef STRUCTURES_H
#define STRUCTURES_H


typedef struct process {
    int priority;
    int pid;
    char state[20];
    struct process * next;
} PROCESS;


typedef struct queue {
    PROCESS * head;
    int size;
} QUEUE;



#endif