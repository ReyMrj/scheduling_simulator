#include <stdio.h>
#include <stdlib.h>
#include "scheduler.h"

void initialize_queues(Queue *queues, int num_queues) {
    for (int i = 0; i < num_queues; i++) {
        queues[i].front = queues[i].rear = NULL;
    }
}

void destroy_queues(Queue *queues, int num_queues) {
    for (int i = 0; i < num_queues; i++) {
        ProcessNode *current = queues[i].front;
        while (current != NULL) {
            ProcessNode *temp = current;
            current = current->next;
            free(temp);
        }
    }
}

void enqueue(Queue *queue, Process process) {
    ProcessNode *new_node = (ProcessNode *)malloc(sizeof(ProcessNode));
    new_node->process = process;
    new_node->next = NULL;

    if (queue->rear == NULL) {
        queue->front = queue->rear = new_node;
    } else {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
}

Process dequeue(Queue *queue) {
    if (queue->front == NULL) {
        Process empty = {-1, -1, -1, -1, -1};  
        return empty;
    }
    ProcessNode *temp = queue->front;
    Process process = temp->process;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return process;
}

void gather_input(Queue *queues, int num_queues, int choice) {
    int pid, priority, burst_time;

    if (choice == 4 || choice == 2 || choice == 3) { 
        printf("Enter PID and Burst Time (or -1 to exit): \n");

        while (1) {
            printf("Enter PID: ");
            scanf("%d", &pid);
            if (pid == -1) {
                break;
            }

            printf("Enter Burst Time: ");
            scanf("%d", &burst_time);

            if (choice == 4) { 
                enqueue(&queues[0], (Process){pid, 0, burst_time, burst_time, 0});
            } else if (choice == 2) { 
                enqueue(&queues[0], (Process){pid, 0, burst_time, burst_time, 0});
            } else if (choice == 3) { 
                enqueue(&queues[0], (Process){pid, 0, burst_time, burst_time, 0});
            }
        }
    } else if (choice == 1) { 
        printf("Enter PID, Priority (0-%d), and Burst Time (or -1 to exit): \n", num_queues - 1);
        
        while (1) {
            printf("Enter PID: ");
            scanf("%d", &pid);
            if (pid == -1) {
                break;
            }

            printf("Enter Priority (0-%d): ", num_queues - 1);
            scanf("%d", &priority);
            if (priority < 0 || priority >= num_queues) {
                printf("Invalid priority! Try again.\n");
                continue;
            }

            printf("Enter Burst Time: ");
            scanf("%d", &burst_time);

            enqueue(&queues[priority], (Process){pid, priority, burst_time, burst_time, 0});
        }
    }
}

void run_fcfs(Queue queues[], int num_queues) {
    for (int i = 0; i < num_queues; i++) {
        if (queues[i].front != NULL) { 
            printf("Processing queue %d (FCFS)\n", i);
            while (queues[i].front != NULL) {
                Process process = dequeue(&queues[i]);
                printf("Dequeued process %d (priority %d, remaining time %d)\n", process.pid, process.priority, process.remaining_time);
                printf("Running process %d for %d units\n", process.pid, process.burst_time);
                process.remaining_time = 0;  
                printf("Process %d completed.\n", process.pid);
            }
        }
    }
}


void run_sjf(Queue queues[], int num_queues) {
    printf("Running Shortest Job First (SJF)...\n");

    Process processes[MAX_PROCESSES];
    int num_processes = 0;

    for (int i = 0; i < num_queues; i++) {
        while (queues[i].front != NULL) {
            Process process = dequeue(&queues[i]);
            if (num_processes < MAX_PROCESSES) {
                processes[num_processes++] = process;
            } else {
                printf("Error: Too many processes for SJF scheduling.\n");
                break;
            }
        }
    }

    for (int i = 0; i < num_processes - 1; i++) {
        for (int j = i + 1; j < num_processes; j++) {
            if (processes[i].burst_time > processes[j].burst_time) {
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    for (int i = 0; i < num_processes; i++) {
        Process process = processes[i];
        printf("Running process %d (priority %d) for %d units\n", process.pid, process.priority, process.burst_time);
        process.remaining_time = 0;
        printf("Process %d completed.\n", process.pid);
    }
}




void run_round_robin(Queue queues[], int num_queues, int time_quantum) {
    printf("Running Round Robin...\n");

    for (int i = 0; i < num_queues; i++) {
        while (queues[i].front != NULL) {
            Process process = dequeue(&queues[i]);
            int time_slice = (process.remaining_time > time_quantum) ? time_quantum : process.remaining_time;
            printf("Running process %d (priority %d) for %d units\n", process.pid, process.priority, time_slice);
            process.remaining_time -= time_slice;

            if (process.remaining_time > 0) {
                enqueue(&queues[i], process); 
            } else {
                printf("Process %d completed.\n", process.pid);
            }
        }
    }
}

void run_multilevel_queue_scheduler(Queue queues[], int num_queues) {
    for (int i = 0; i < num_queues; i++) {
        printf("Running queue %d (Multilevel Queue Scheduling)\n", i);
        while (queues[i].front != NULL) {
            Process process = dequeue(&queues[i]);
            printf("Dequeued process %d (priority %d, remaining time %d)\n", process.pid, process.priority, process.remaining_time);
            printf("Running process %d for %d units\n", process.pid, process.burst_time);
            process.remaining_time = 0;
            printf("Process %d completed.\n", process.pid);
        }
    }
}

void run_selected_scheduling(int choice, Queue queues[], int num_queues) {
    int time_quantum;

    if (choice == 4) {  
        printf("Enter Time Quantum for Round Robin: ");
        scanf("%d", &time_quantum);
    }

    switch (choice) {
        case 1:
            printf("Running Multilevel Queue Scheduling...\n");
            run_multilevel_queue_scheduler(queues, num_queues);
            break;
        case 2:
            printf("Running First-Come First-Served (FCFS)...\n");
            run_fcfs(queues, num_queues);
            break;
        case 3:
           
            run_sjf(queues, num_queues);  
            break;
        case 4:
            run_round_robin(queues, num_queues, time_quantum);
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
}

