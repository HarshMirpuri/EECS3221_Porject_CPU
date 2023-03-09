#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "cpu.h"
#include "schedulers.h"

struct node *head = NULL;
int task_number = 0;

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
    struct node *temp;
    temp = head;
    int wait_time[task_number];
    int task_waiting_time = 0;
    int wait_count = 0;

    while (temp != NULL)
    {
        run(temp->task, QUANTUM);
        if (temp->task->burst > 0)
        {
            //printf("\n %d",temp->task->burst);
            temp->task->burst -= 10;
            //printf("\n %d",temp->task->burst);
        }
        else
        {
            wait_time[wait_count++] = task_waiting_time;
            task_waiting_time += (temp->task->burst);
            delete (&temp, temp->task);
        }    
    }

    int task_wait_time_sum = 0;

    for(int i = 0; i < wait_count; i++)
    {
        task_wait_time_sum += wait_time[i];
    }
    float avg_waiting_time = (float)task_wait_time_sum / wait_count;
    float avg_turnaround_time = avg_waiting_time + ((float)task_waiting_time / wait_count);


    printf("\n%s %f", "Average waiting time =", avg_waiting_time);
    printf("\n%s %f", "Average turnaround time =", avg_turnaround_time);
    printf("\n%s %f\n", "Average response time =", avg_waiting_time);
}