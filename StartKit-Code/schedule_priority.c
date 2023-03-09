#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "cpu.h"
#include "schedulers.h"

struct node *head = NULL;
int task_number = 0;

// merge-sort by priority
void sort(struct node **root)
{
    struct node *merge_head = *root;
    struct node *left, *right;
    if ((merge_head == NULL) || (merge_head->next == NULL))
    {
        return;
    }

    split(merge_head, &left, &right);

    sort(&left);
    sort(&right);

    *root = merge(left, right);
}

void split(struct node *root, struct node **left, struct node **right)
{
    struct node *a;
    struct node *b;
    a = root;
    b = root->next;

    while (b != NULL)
    {
        b = b->next;
        while (b != NULL)
        {
            a = a->next;
            b = b->next;
        }
    }

    *left = root;
    *right = a->next;
    a->next = NULL;
}

struct node *merge(struct node *left, struct node *right)
{
    struct node *result = NULL;

    if (left == NULL)
    {
        return right;
    }
    else if (right == NULL)
    {
        return left;
    }

    if (left->task->priority >= right->task->priority)
    {
        result = left;
        result->next = merge(left->next, right);
    }
    else
    {
        result = right;
        result->next = merge(left, right->next);
    }
    return result;
}

void add(char *name, int priority, int burst)
{
    Task *task = malloc(sizeof(Task));
    task->name = name;
    task->priority = priority;
    task->burst = burst;
    task->tid = task_number++;
    insert(&head, task);
}

void schedule()
{
    sort(&head);
    struct node *temp;
    temp = head;
    int wait_time[task_number];
    int task_waiting_time = 0;
    int wait_count = 0;
    while (temp != NULL)
    {
        run(temp->task, temp->task->burst);
        wait_time[wait_count++] = task_wait_time;
        task_waiting_time += (temp->task->burst);
        delete (&temp, temp->task);
    }

    int task_wait_time_sum = 0;
    for (int i = 0; i < wait_count; i++)
    {
        task_wait_time_sum += wait_time[i];
    }
    float avg_waiting_time = (float)task_wait_time_sum / wait_count;
    float avg_turnaround_time = avg_waiting_time + ((float)task_waiting_time / wait_count);


    printf("\n%s %f", "Average waiting time =", avg_waiting_time);
    printf("\n%s %f", "Average turnaround time =", avg_turnaround_time);
    printf("\n%s %f\n", "Average response time =", avg_waiting_time);
}