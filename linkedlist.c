#include "common.h"

struct linkedList linked_list;
int method, values, enqueues;
int total, counter;

struct node {
    int val;
    double prio;
    struct node *next;
    struct node *prev;
};

struct linkedList {
    struct node *head;
    struct node *tail;
};

double avg()
{
    return (double)total/counter;
}

void enqueue(struct node *elem)
{
    if (linked_list.head == NULL) {
        linked_list.head = elem;
        linked_list.tail = elem;
        return;
      }
    total += elem->prio;
    counter++;
    if(elem->prio < avg()) {
        struct node *n = linked_list.head;
        
        while((n->prio) < elem->prio)
            n=n->next;
        if(n == linked_list.head)           
            linked_list.head = elem;
        else {
            elem->prev=n->prev;
            n->prev->next = elem;
        }
        n->prev=elem;
        elem->next=n;
    } else {
        struct node *n = linked_list.tail;
        
        while((n->prio) > elem->prio)
            n=n->prev;
        if(n == linked_list.tail)
            linked_list.tail = elem;
        else {
            elem->next = n->next;
            n->next->prev = elem;
        }
        n->next=elem;
        elem->prev=n;
    }
}


struct node *create_node(double prio)
{
    struct node *el = malloc(sizeof(struct node));

    el->val = 0;
    el->prio = prio;
    el->prev = NULL;
    el->next = NULL;
    return el;
}

struct node *dequeue()
{
    if(linked_list.head == NULL)
        return NULL;
    struct node *el = linked_list.head;

    counter--;
    total -= el->prio;
    if(linked_list.head == linked_list.tail) {
        linked_list.head = NULL;
        linked_list.tail = NULL;
    } else {
        linked_list.head=linked_list.head->next;
        linked_list.head->prev = NULL;
    }

    return el;
}

int transient()
{
    int i;

    for (i = 0; i < values; i++) {
        enqueue(create_node(rand() % 100));
        free(dequeue());
    }

    return 0;
}

int steady()
{
    int i;

    for (i = 0; i < values; i++)
        enqueue(create_node(rand() % 100));

    for (i = 0; i < enqueues; i++) {
        enqueue(create_node(rand() % 100));
        free(dequeue());
    }

    return 0;
}

int main(int argc, char **argv) {
    int rv;

    rv = parse_args(argc, argv, &method, &values, &enqueues);
    if (rv < 0) {
        printf("Please provide a valid flag combination input!\n \
        linked {--transient --values <INT>} | {--steady --values <INT> --enqueues <INT>} \
        ");
        goto exit;
    }
    clock_t start = clock();

    if (method == TRANSIENT)
        transient();
    else if (method == STEADY)
        steady();
    else
        goto exit;

    clock_t end = clock();
    float seconds = (float)(end - start) / CLOCKS_PER_SEC;

    printf("Using method %s, and a list containing %d elements", method_type[method], values);
    if (enqueues)
        printf(" for %d enqueues", enqueues);
    printf(", took %f seconds\n", seconds);

exit:
    return 0;
}
