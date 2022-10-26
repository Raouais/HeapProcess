#include "../structures/structures.h"
#include "heap.h"
#include <math.h>
/**
 * @brief 
 * 
 * @param queue 
 * @param parentIndex 
 * @param level 
 */
void showTree(QUEUE * queue, int parentIndex, int level){
    int spaces = 8;

    PROCESS * parent = getProcessByIndex(queue,parentIndex);
    PROCESS * sonLeft = NULL;
    PROCESS * sonRight = NULL;

    int index = parentIndex + 1;
    int lineFeed = index == 2 || index == 4|| index == 8 || index == 16;
    
    for(int i = 0; i < spaces; i++){
        printf(" ");
    }

    if(parentIndex == 0){
        printf("%d\n", parent->priority);
    } else if(lineFeed){
        printf("\n");
    }

    if(getLeftChild(parentIndex) < queue->size){
        sonLeft = getProcessByIndex(queue, getLeftChild(parentIndex));
        printf("%d", sonLeft->priority);
    }

    if(getRightChild(parentIndex) < queue->size){
        sonRight = getProcessByIndex(queue, getRightChild(parentIndex));
        printf("%d", sonRight->priority);
    }
   
    if(parentIndex < queue->size - 1){
        level = lineFeed ? level + 1 : level;
        showTree(queue,parentIndex+1,level);
    }

}

/**
 * @brief 
 * 
 * @param queue existe et est initialisé
 * Imprime à la console les processus contenus dans le tas 
 */
void printHeap(QUEUE * queue){
    PROCESS * current  = queue->head;
    PROCESS * tmp = NULL;
   
    while(current != NULL){
        tmp = current;
        printf("Priorité: %d, Status: %s PID: %d\n",tmp->priority,tmp->state,tmp->pid);
        current = current->next;
    }

    showTree(queue,0,0);

}

/**
 * @brief Get the Last Process object
 * 
 * @param queue existe et est initialisé
 * @return PROCESS* le dernier processus de la file
 */
PROCESS * getLastProcess(QUEUE * queue){
    PROCESS * current  = queue->head;
    PROCESS * tmp = NULL;
    while(current != NULL){
        tmp = current;
        current = current->next;
    }
    return tmp;
}
/**
 * @brief Get the Process By Index object
 * 
 * @param queue existe et est initialisé
 * @param index est initialisé
 * @return PROCESS* le processus à l'indice index
 */
PROCESS * getProcessByIndex(QUEUE * queue, int index){
    int count = 0;
    PROCESS * current  = queue->head;
    PROCESS * tmp = NULL;
    if(index == 0)
        return current;
    while(count != index){
        tmp = current;
        count++;
        current = current->next;
    }
    return tmp->next;
}

/**
 * @brief 
 * 
 * @param p1 existe et est initialisé
 * @param p2 existe et est initialisé
 * 
 * les valeurs du p1 dans p2 et inversement 
 */
void swap(PROCESS * p1, PROCESS * p2){
    int tempPriority = p2->priority;
    p2->priority = p1->priority;
    p1->priority = tempPriority;
    
    int tempPid = p2->pid;
    p2->pid = p1->pid;
    p1->pid = tempPid;

    char state[20];
    strncpy(state, p2->state, 20);
    strncpy(p2->state, p1->state, 20);
    strncpy(p1->state, state, 20);
}

/**
 * @brief Get the Parent object
 * 
 * @param index est initialisé
 * @return int l'indice du parent
 */
int getParent(int index){
    return (index % 2 == 0 ? index - 2: index -1)/2;
}

/**
 * @brief Get the Left Child object
 * 
 * @param index est initialisé
 * @return int l'indice hypothétique de l'enfant gauche
 */
int getLeftChild(int index){
    return 2 * index + 1;
}

/**
 * @brief Get the Right Child object
 * 
 * @param index est initialisé
 * @return int l'indice hypothétique de l'enfant droit
 */
int getRightChild(int index){
    return 2 * index + 2;
}

/**
 * @brief 
 * 
 * @param queue existe et est initialisé
 * @param parentIndex est initialisé
 * @param sonIndex est initialisé
 * 
 *
 * cherche le fils et le parent
 * si la priorité parent > priorité fils alors échange
 * recommence tant que l'indice du parent n'est pas 0
 */
void upHeap(QUEUE * queue, int parentIndex, int sonIndex){

    PROCESS * parent = getProcessByIndex(queue, parentIndex);
    PROCESS * son = getProcessByIndex(queue, sonIndex); 

    if(parent->priority > son->priority){
        swap(parent,son);
        if(parentIndex > 0)
            upHeap(queue,getParent(parentIndex),parentIndex);
    }
}

/**
 * @brief 
 * 
 * @param queue existe et est initialisé 
 * @param process est initialisé
 * @return boolean true si l'insertion a été faite
 */
boolean insert(QUEUE * queue, PROCESS * process){
    boolean isInserted = true;

    if(queue->head == NULL){
        queue->head = process;
        queue->size++;
    } else {
        if(queue->size == MAX_PROCESS){
            isInserted = false;
        } else {
            getLastProcess(queue)->next = process;
            queue->size++;
            int lastIndex = queue->size - 1; //queue->size -1 pour avoir l'index du dernier
            upHeap(queue, getParent(lastIndex), lastIndex);
        }
    }
    return isInserted;
}

/**
 * @brief 
 * 
 * @param queue existe et est initialisé
 * @param parentIndex est initialisé
 * @param sonLeftIndex est initialisé
 * @param sonRightIndex est initialisé
 * 
 * chercher les fils et le parent s'il y en a
 * échanger avec le fils gauche si la priorité du parent est plus grande
 * sinon
 * échanger avec le fils droit si la priorité du parent est plus grande 
 * recommencer tant qu'il y a des fils dont la priorité est plus petite
 */
void downHeap(QUEUE * queue, int parentIndex, int sonLeftIndex, int sonRightIndex){
    PROCESS * parent = getProcessByIndex(queue, parentIndex);
    PROCESS * sonLeft = NULL;
    PROCESS * sonRight = NULL;

    //il peut arriver qu'il n'y ait pas d'enfants 
    if(sonLeftIndex < queue->size){
        sonLeft = getProcessByIndex(queue, sonLeftIndex);
    }

    if(sonRightIndex < queue->size){
        sonRight = getProcessByIndex(queue, sonRightIndex);
    }

    if(sonLeft != NULL && parent->priority > sonLeft->priority){
        swap(parent,sonLeft);
        parentIndex++;
        downHeap(queue, parentIndex, getLeftChild(parentIndex), getRightChild(parentIndex));
    } else if(sonRight != NULL && parent->priority > sonRight->priority){
        swap(parent, sonRight);
        downHeap(queue, parentIndex, getLeftChild(parentIndex), getRightChild(parentIndex));
    }
}

/**
 * @brief 
 * 
 * @param queue existe et est initialisé
 */
void freeTail(QUEUE * queue){
    free(getProcessByIndex(queue, queue->size - 1));
    getProcessByIndex(queue, queue->size - 2)->next = NULL;
    queue->size--;
}

/**
 * @brief 
 * 
 * @param queue existe et est initialisé
 * @return boolean true si la suppression a été faite
 */
boolean delete(QUEUE * queue){
    boolean isDeleted = true;
    if(queue->size == 0){
        isDeleted = false;
    } else if(queue->size == 1){
        free(queue->head);
        queue->head = NULL;
        queue->size--;
    } else {
        PROCESS * head = getProcessByIndex(queue, 0);
        PROCESS * tail = getProcessByIndex(queue, queue->size - 1);
        swap(head,tail);
        freeTail(queue);
        int parent = 0;
        downHeap(queue, parent, getLeftChild(parent), getRightChild(parent));
    }
    return isDeleted;
}