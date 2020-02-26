#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* Return NULL if malloc failed */
    if (!q)
        return NULL;
    /* Initialization of fields */
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* If queue is NULL, no need to free */
    if (!q) {
        return;
    }
    /* Extract first element */
    list_ele_t *cur = q->head;
    list_ele_t *tmp = NULL;
    while (cur) {
        tmp = cur;
        cur = cur->next;
        /* Free value space */
        free(tmp->value);
        /* Free element structure */
        free(tmp);
    }
    /* Free queue structure */
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    char *value;
    /* Return false if q is NULL */
    if (!q)
        return false;
    /* Allocate space for list_ele_t */
    newh = malloc(sizeof(list_ele_t));
    /* Check if space is allocated */
    if (!newh) {
        return false;
    }
    unsigned int value_length = strlen(s);
    /* Allocate space for string value */
    value = malloc(value_length + 1);
    /* Check if space is allocated */
    if (!value) {
        free(newh);
        return false;
    }
    memset(value, '\0', value_length + 1);
    /* Copy input string to allocated space */
    strncpy(value, s, value_length);
    /* Assign value and change head */
    newh->value = value;
    newh->next = q->head;
    /* If the queue was empty, assign tail pointer to its new head */
    if (q->size == 0) {
        q->head = q->tail = newh;
    } else
        q->head = newh;
    /* Update the size of the queue */
    q->size++;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    list_ele_t *newh;
    char *value;
    /* Return false if q is NULL */
    if (!q)
        return false;
    /* Allocate space for list_ele_t */
    newh = malloc(sizeof(list_ele_t));
    /* Check if space is allocated */
    if (!newh) {
        return false;
    }
    unsigned int value_length = strlen(s);
    /* Allocate space for string value */
    value = malloc(value_length + 1);
    /* Check if space is allocated */
    if (!value) {
        free(newh);
        return false;
    }
    memset(value, '\0', value_length + 1);
    /* Copy input string to allocated space */
    strncpy(value, s, value_length);
    /* Assign value */
    newh->value = value;
    newh->next = NULL;
    /* If the queue was empty, point both head and tail to newh*/
    if (q->size == 0) {
        q->head = q->tail = newh;
    } else {
        /* If the queue was not empty, concat newh behind tail and update tail
         */
        q->tail->next = newh;
        q->tail = newh;
    }
    /* Update the size of the queue */
    q->size++;
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* Return false if queue is NULL or empty */
    if (!q || q->size == 0) {
        return false;
    }
    /* Extract current queue head */
    list_ele_t *oldh = q->head;
    /* Change queue head to next element */
    if (q->size == 1) {
        /* If the queue only got 1 element */
        q->head = q->tail = NULL;
    } else {
        q->head = oldh->next;
    }
    q->size--;
    /* Copy removed string to sp if sp exists*/
    if (sp) {
        strncpy(sp, oldh->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    /* Free old value space and list element space*/
    free(oldh->value);
    free(oldh);
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* Check if q is valid */
    if (!q)
        return 0;
    else
        return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* q is NULL or empty */
    if (!q || q->size == 0) {
        return;
    }
    /* Queue has only 1 element */
    if (q->size == 1) {
        return;
    }
    /* Initialize prev, curr and next pointers */
    list_ele_t *prev = NULL;
    list_ele_t *curr = q->head;
    list_ele_t *next = NULL;
    /* Reverse the linked list using 3 pointers method */
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    /* Exchange the original head and tail pointers */
    list_ele_t *tmp = q->head;
    q->head = q->tail;
    q->tail = tmp;
    return;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}
