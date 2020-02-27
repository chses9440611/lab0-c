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
    if (!q)
        return NULL;
    q->head = q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    // when q is not NULL, we do free(q), free node from head
    if (q != NULL) {
        while (q->size > 0) {
            list_ele_t *tmp = q->head;
            q->head = q->head->next;
            free(tmp->value);
            free(tmp);
            q->size--;
        }
        free(q);
    }
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
    int length;
    if (!q)
        return false;

    newh = malloc(sizeof(list_ele_t));
    if (!newh) {
        printf("Fail to malloc a node\n");
        return false;
    }
    // get the string length of s, not including '\0'
    length = strlen(s);
    newh->value = malloc(length + 1);
    // if fail to malloc value, also free the node newh
    if (!newh->value) {
        printf("Fail to malloc value\n");
        free(newh);
        return false;
    }
    strncpy(newh->value, s, length);
    newh->value[length] = '\0';
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    /*
     * if q is an empty queue, first insert
     * will let tail and head point to same node
     */
    newh->next = q->head;
    q->head = newh;
    if (q->size == 0)
        q->tail = q->head;
    (q->size)++;
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
    /* Remember: It should operate in O(1) time */
    list_ele_t *newt;
    int length;
    if (!q)
        return false;

    newt = malloc(sizeof(list_ele_t));
    if (!newt) {
        printf("Fail to malloc a new node\n");
        return false;
    }

    length = strlen(s);
    newt->value = malloc(length + 1);
    if (!newt->value) {
        printf("Fail to malloc value\n");
        free(newt);
        return false;
    }
    strncpy(newt->value, s, length);
    newt->value[length] = '\0';
    // avoid newt->next NULL deference
    newt->next = NULL;

    if (q->size == 0) {
        q->head = q->tail = newt;
    } else {
        q->tail->next = newt;
        q->tail = q->tail->next;
    }

    (q->size)++;
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
    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || q->size == 0 || !sp)
        return false;

    list_ele_t *old = q->head;
    int length = strlen(old->value);
    if (bufsize < length + 1)
        length = bufsize - 1;
    // for sp is pointed to an allocated space, no need to malloc again.
    // sp = malloc(length + 1);
    // if(!sp) {
    //  	printf("sp malloc fail\n");
    //  	return false;
    // }
    strncpy(sp, old->value, length);
    sp[length] = '\0';

    q->head = q->head->next;
    free(old->value);
    free(old);

    if (q->size == 1)
        q->tail = q->head;
    (q->size)--;

    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (q == NULL || q->head == NULL)
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
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if (q && q->size > 1) {
        list_ele_t *left, *right;
        q->tail = q->head;
        left = q->head->next;
        while (left != NULL) {
            right = left->next;
            left->next = q->head;
            q->head = left;
            left = right;
        }
        q->tail->next = NULL;
    }
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
