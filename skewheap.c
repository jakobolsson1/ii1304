#include "common.h"

struct skewHeap heap;
int method, values, enqueues;

struct skewNode {
    double prio;
    struct skewNode *left;
    struct skewNode *right;
};

struct skewHeap {
    struct skewNode *root;
};

struct skewNode *merge(struct skewNode *root1, struct skewNode *root2)
{
    if(root1 == NULL)
        return root2;
    else if(root2 == NULL)
        return root1;

    if(root1->prio <= root2->prio) {
        struct skewNode *tempHeap = root1->right;

        root1->right = root1->left;
        root1->left = merge(root2, tempHeap);
        return root1;
    } else
        return merge(root2, root1);
} 

struct skewNode *dequeue()
{
    if(heap.root == NULL)
        return NULL;
    struct skewNode *tmp = heap.root;

    heap.root = merge(heap.root->left, heap.root->right);
    return tmp;
}

struct skewNode *create_node(double prio)
{
    struct skewNode *leaf = malloc(sizeof(struct skewNode));

    leaf->prio = prio;
    leaf->left = NULL;
    leaf->right = NULL;
    return leaf;
}

int transient()
{
    int i;

    for (i = 0; i < values; i++) {
        merge(heap.root, create_node(rand() % 100));
        free(dequeue());
    }

    return 0;
}

int steady()
{
    int i;

    for (i = 0; i < values; i++)
        merge(heap.root, create_node(rand() % 100));

    for (i = 0; i < enqueues; i++) {
        merge(heap.root, create_node(rand() % 100));
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

    clock_t end = clock();
    float seconds = (float)(end - start) / CLOCKS_PER_SEC;
    
    printf("Using method %s, and a list containing %d elements", method_type[method], values);
    if (enqueues)
        printf(" for %d enqueues", enqueues);
    printf(", took %f seconds\n", seconds);

exit:
    return 0;
}
