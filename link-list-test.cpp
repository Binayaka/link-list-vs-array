/**
 * This will test 2000000 link list insertion records 
 * 100 times, and store the best, worst and avg times
*/
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "tqdm/tqdm.h"

typedef struct node Node;
typedef struct list List;

// A linked list node
struct node
{
    int data;
    struct node *next;
};

struct list
{
    Node *head;
};

Node *createnode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode)
    {
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

List *makelist()
{
    List *list = (List *)malloc(sizeof(List));
    if (!list)
    {
        return NULL;
    }
    list->head = NULL;
    return list;
}

void add(int data, List *list)
{
    Node *current = NULL;
    if (list->head == NULL)
    {
        list->head = createnode(data);
    }
    else
    {
        current = list->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = createnode(data);
    }
}

void destroy(List *list)
{
    Node *current = list->head;
    Node *next = current;
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

void display(List *list)
{
    Node *current = list->head;
    if (list->head == NULL)
        return;

    for (; current != NULL; current = current->next)
    {
        printf("%d\n", current->data);
    }
}

int main()
{
    int limit = 200000;
    int times = 10;
    clock_t start, stop;
    double best = -9999999999, worst = 0, avg = 0;
    for (int i : tqdm::range(times))
    {
        start = clock();
        List *list = makelist();
        for (int j : tqdm::range(limit))
        {
            add(1, list);
        }
        destroy(list);
        stop = clock();
        double time_spent = (double)(stop - start) / CLOCKS_PER_SEC;
        avg += time_spent;
        if (best == -9999999999)
        {
            best = time_spent;
            worst = time_spent;
        }
        else
        {
            if (time_spent < best)
            {
                best = time_spent;
            }
            if (time_spent > worst)
            {
                worst = time_spent;
            }
        }
    }
    avg = avg / times;
    std::cout << "Best time    :: \t" << best << " seconds" << std::endl;
    std::cout << "Worst time   :: \t" << worst << " seconds" << std::endl;
    std::cout << "Avg time     :: \t" << avg << " seconds" << std::endl;
    return 0;
}