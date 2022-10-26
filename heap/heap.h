
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef HEAP_H
#define HEAP_H
#define true 1
#define false 0
#define MAX_PROCESS 31

typedef int boolean;

void printHeap(QUEUE * queue);
PROCESS * getLastProcess(QUEUE * queue);
PROCESS * getProcessByIndex(QUEUE * queue, int index);
void swap(PROCESS * p1, PROCESS * p2);
int getParent(int index);
int getLeftChild(int index);
int getRightChild(int index);
void upHeap(QUEUE * queue, int parentIndex, int sonIndex);
boolean insert(QUEUE * queue, PROCESS * process);
void downHeap(QUEUE * queue, int parentIndex, int sonLeftIndex, int sonRightIndex);
void freeTail(QUEUE * queue);
boolean delete(QUEUE * queue);

#endif