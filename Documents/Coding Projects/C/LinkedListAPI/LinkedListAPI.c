#include "LinkedListAPI.h"
/**
 * @brief Pushes a Node structure onto the end of the list passed into the function via head and tail
 * 
 * @param head 
 * @param tail 
 * @param data 
 */
void pushBack(List * list, void * data)
{
    if(list == NULL || data == NULL)
    {
        printf("pushBack ERROR: list or data pointer is NULL\n");
        return;
    }

    Node * newNode = malloc(sizeof(Node)); // create a new Node structure

    //initialize newNode values
    newNode->next = NULL;
    newNode->prev = NULL;
    newNode->data = data;

    if(!isEmpty(list)) // checks if the list is empty, if not
    {
        list->tail->next = newNode; // makes tail node point to newNode
        newNode->prev = list->tail; // makes newNode point to the previous tail node
        list->tail = list->tail->next; // moves tail to newNode
    }
    else //if the list is empty
    {
        //sets head and tail
        list->head = newNode;
        list->tail = newNode;
    }
    list->length++;
}

/**
 * @brief places a new Node at the front of the list with the data given
 * 
 * @param list 
 * @param data 
 */
void pushFront(List * list, void * data)
{
    if(list == NULL || data == NULL) // invalid variables
    {
        printf("pushFront ERROR: list or data pointer is NULL\n");
        return;
    }

    Node * newNode = malloc(sizeof(Node)); // create a new Node structure

    //initialize newNode values
    newNode->next = NULL;
    newNode->prev = NULL;
    newNode->data = data;

    if(!isEmpty(list)) // checks if the list is empty, if not
    {
        newNode->next = list->head; //sets newNode->next to the current head node
        list->head = newNode; // moves head node to new head
    }
    else
    {
        list->head = newNode; // head of list is the newNode
        list->tail = newNode;
    }
    list->length++;
}

/**
 * @brief returns the first node off the front of the list, may return NULL
 * 
 * @param list 
 * @return Node* 
 */
Node * pop(List * list)
{
    if(list == NULL)
    {
        printf("pop ERROR: list is NULL\n");
        return NULL;
    }

    if(isEmpty(list)) //if the list is empty, return NULL
    {
        printf("pop WARNING: list is empty\n");
        return NULL;
    }

    Node * temp;

    temp = list->head; 
    list->head = list->head->next; //moves head to next node
    list->length--;

    if(list->head == NULL) // if there was only one node ie. head is now NULL
    {
        list->tail = NULL; 
    }

    temp->next = NULL;
    temp->prev = NULL;

    return temp;
}

/**
 * @brief Deletes the first node off the front of the list
 * 
 * @param list 
 * @param deleteData 
 */
void toss(List * list, void (*deleteData)(void* data))
{
    if(list == NULL || (*deleteData) == NULL)
    {
        printf("toss ERROR: list or deleteData function poiter is NULL");
        return;
    }

    if(isEmpty(list)) //if the list is empty, return NULL
    {
        printf("toss WARNING: list is empty");
        return;
    }

    Node * temp;

    temp = list->head; 
    list->head = list->head->next; //moves head to next node
    list->length--;

    if(list->head == NULL) // if there was only one node ie. head is now NULL
    {
        list->tail = NULL; 
    }

    temp->next = NULL;
    temp->prev = NULL;

    (*deleteData)(temp->data); // uses function pointer to delete the data inside temp
    free(temp); // frees the node pointed to by temp
}

/**
 * @brief deletes the node at the specified index and removes it from the list
 * 
 * @param list 
 * @param index 
 * @param deleteData 
 */
void deleteAtIndx(List * list, int index, void (*deleteData)(void *data))
{
    if(list == NULL || (*deleteData) == NULL || index < list->length - 1)
    {
        printf("deleteAtIndx ERROR: list or deleteData function pointer is NULL");
        return;
    }

    if(isEmpty(list)) //if the list is empty, return NULL
    {
        printf("deleteAtIndx WARNING: list is empty");
        return;
    }
    
    Node * temp = list->head;
    Node * prev = NULL;

    if(list->head != NULL && list->tail != NULL)
    {
        for(int i = 0; i < index; i++) // moves through list until at desired node
        {
            if(temp == NULL) // checks whether temp is NULL to prevent segmentation faults
            {
                printf("deleteAtIndx ERROR: temp gone past end of list");
                return;
            }
            temp = temp->next;
        }
        prev->next = temp->next; // makes the previous node point to the node after temp
        temp->next->prev = prev; // makes the node after temp point to the node before temp
    }

    temp->next = NULL;
    temp->prev = NULL;

    (*deleteData)(temp->data); // uses function pointer to delete the data inside temp
    free(temp); // frees the node pointed to by temp
}

/**
 * @brief 
 * 
 * @param list 
 * @param deleteData 
 */
void freeList(List * list, void (*deleteData)(void * data)) 
{
    if(list == NULL || (*deleteData == NULL))
    {
        printf("freeList ERROR: list or deleteData function poiter is NULL");
        return;
    }

    Node * temp;

    while (list->head != NULL) // while head is not NULL...
    {
        temp = list->head; // sets temp to point to where head points
        list->head = temp->next; // sets head to point to the next node
        (*deleteData)(temp->data);
        free(temp); // frees the node pointed to by temp
    }

    list->tail = NULL;
    list->length = 0;
}

/**
 * @brief returns a separate list that is a clone of the list passed into it
 * 
 * @param list 
 * @return List* 
 */
List * clone(List * list)
{
    if(list == NULL)
    {
        printf("peekNode ERROR: list is NULL");
        return NULL;
    }

    List * newList = malloc(sizeof(List)); // creates space for the list
    newList->head = NULL;
    newList->tail = NULL;
    newList->length = 0;
    newList->dataSize = list->dataSize;

    Node * temp = list->head;

    while(temp != NULL)
    {
        Node * newNode = malloc(sizeof(Node));

        void * dataCopy = malloc(newList->dataSize); // creates a void pointer and allocates memory to it
        memcpy(dataCopy, temp->data, newList->dataSize); // copies the data from orignal list into the new pointer
        
        pushBack(newList, dataCopy);
        free(dataCopy);
        temp = temp->next;
    }

}

/**
 * @brief returns the node in the list at the desired index
 * 
 * @param list 
 * @param index 
 * @return Node* 
 */
Node * peekNode(List * list, int index)
{
    if(list == NULL || index > list->length -1)
    {
        printf("peekNode ERROR: list is NULL");
        return NULL;
    }

    Node * temp = list->head;

    if(list->head != NULL && list->tail != NULL)
    {
        for(int i = 0; i < index; i++) // moves through list until at desired node
        {
            if(temp == NULL) // checks whether temp is NULL to prevent segmentation faults
            {
                printf("peekNode ERROR: temp gone past end of list");
                return NULL;
            }
            temp = temp->next;
        }
    }

    return temp;
}

/**
 * @brief removes and returns the node in the list at the desired index
 * 
 * @param list 
 * @param index 
 * @return Node* 
 */
Node * pullNode(List * list, int index)
{
    if(list == NULL || index > list->length -1)
    {
        printf("peekNode ERROR: list is NULL");
        return NULL;
    }

    Node * temp = list->head;
    Node * prev;

    if(list->head != NULL && list->tail != NULL)
    {
        for(int i = 0; i < index; i++) // moves through list until at desired node
        {
            if(temp == NULL) // checks whether temp is NULL to prevent segmentation faults
            {
                printf("peekNode ERROR: temp gone past end of list");
                return NULL;
            }
            prev = temp;
            temp = temp->next;
        }
        prev->next = temp->next; // makes the previous node point to the node after temp
        temp->next->prev = prev; // makes the node after temp point to the node before temp
    }

    temp->next = NULL;
    temp->prev = NULL;

    return temp;
}

/**
 * @brief returns the first node in the list without deleting it
 * 
 * @param list 
 * @return Node* 
 */
Node * peekFront(List * list)
{
    if(list == NULL) // checks if the list is NULL
    {
        printf("peekFront ERROR: list is NULL");
        return NULL;
    }

    if(isEmpty(list)) // checks if the list is empty
    {
        printf("peekFront WARNING: list is empty");
        return NULL;
    }

    return list->head;
}

/**
 * @brief returns the last node in the list without deleting it
 * 
 * @param list 
 * @return Node* 
 */
Node * peekBack(List * list)
{
    if(list == NULL) // checks if the list is NULL
    {
        printf("peekFront ERROR: list is NULL"); 
        return NULL;
    }

    if(list->head == NULL || list->tail == NULL) // checks if the list is empty or if the tail is NULL
    {
        printf("peekFront WARNING: list is empty");
        return NULL;
    }

    return list->tail;
}

/**
 * @brief Moves the head node to the end of the list
 * 
 * @param list 
 */
void headToTail(List * list) // checks if the list is NULL
{
    if(list == NULL)
    {
        printf("headToTail ERROR: list is NULL");
        return;
    }

    Node * temp = list->head;

    if(list->head != NULL && list->tail != NULL)
    {
        if(list->head != list->tail)
        {
            list->head = temp->next; // moves the head to the next node
            list->tail->next = temp; // moves the temp node to end of list
            temp->prev = list->tail; // sets the temp->prev to the previous tail node
            temp->next = NULL; // sets the temp->next to NULL
            list->tail = temp; // moves the tail of the list to the new node
        }
    }
}

/**
 * @brief Finds the length of the list
 * 
 * @param list 
 * @return int 
 */
int lenOfList(List * list)
{
    int numElems = 0;
    Node * temp = list->head;

    while(temp != NULL) // loops through the list
    {
        temp = temp->next;
        numElems++;
    }

    return numElems;
}

/**
 * @brief Determines if the list is empty
 * 
 * @param list 
 * @return true 
 * @return false 
 */
bool isEmpty(List * list)
{
    if(list->head == NULL && list->tail == NULL) // if head and tail are NULL
    {
        return true;
    }
    return false;
}