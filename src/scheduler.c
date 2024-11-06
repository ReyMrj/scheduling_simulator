#include "scheduler.h"
#include <stdio.h>
#include <stdlib.h>

// Initialize queues with given time slices
void initialize_queues(Queue queues[], int num_queues) {
    for (int i = 0; i < num_queues; i++) {
        queues[i].processes = (Process *)malloc(sizeof(Process) * 10); // Example capacity
        queues[i].front = 0;
        queues[i].rear = 0;
        queues[i].size = 0;
        queues[i].capacity = 10;
        queues[i].time_slice = (i + 1) * 2; // Assign different time slices per queue level
    }
}

void destroy_queues(Queue queues[], int num_queues) {
    for (int i = 0; i < num_queues; i++) {
        free(queues[i].processes);
    }
}
void enqueue(Queue *queue, Process process) {
    if (queue->size < queue->capacity) {
        queue->processes[queue->rear] = process;
        queue->rear = (queue->rear + 1) % queue->capacity;
        queue->size++;
    }
}

Process dequeue(Queue *queue) {
    Process p = queue->processes[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return p;
}
void gather_input(Queue *queues, int num_queues) {
    int pid, priority, burst_time;
    printf("Enter PID, Priority (0-%d), Burst Time (or -1 to exit): ", num_queues - 1);
    while (scanf("%d", &pid) && pid != -1) {
        scanf("%d %d", &priority, &burst_time);
        if (priority >= 0 && priority < num_queues) {
            Process p = {pid, priority, burst_time, burst_time, 0};
            enqueue(&queues[priority], p);
        }
        printf("Enter PID, Priority, Burst Time (or -1 to exit): ");
    }
}

Process find_shortest_job(Queue *queue) {
    int min_index = 0;
    for (int i = 1; i < queue->size; i++) {
        if (queue->processes[i].remaining_time < queue->processes[min_index].remaining_time) {
            min_index = i;
        }
    }
    // Extract the process with the shortest time
    Process shortest_process = queue->processes[min_index];

    // Remove this process from the queue and adjust the rest of the queue
    for (int i = min_index; i < queue->size - 1; i++) {
        queue->processes[i] = queue->processes[i + 1];
    }
    queue->size--;

    return shortest_process;
}

void run_multilevel_queue_scheduler(Queue queues[], int num_queues) {
    while (1) {
        int processes_left = 0;

        for (int i = 0; i < num_queues; i++) {
            if (queues[i].size > 0) {
                processes_left = 1;

                if (i == 0) { // High priority queue, Round Robin
                    Process p = dequeue(&queues[i]);
                    int exec_time = (p.remaining_time < queues[i].time_slice) ? p.remaining_time : queues[i].time_slice;
                    p.remaining_time -= exec_time;

                    if (p.remaining_time > 0) {
                        enqueue(&queues[i], p);
                    }
                } else if (i == 1) { // Mid priority queue, Shortest Job First
                    Process p = find_shortest_job(&queues[i]);
                    p.remaining_time--;

                    if (p.remaining_time > 0) {
                        enqueue(&queues[i], p);
                    }
                } else if (i == 2) { // Low priority queue, First-Come First-Served
                    Process p = dequeue(&queues[i]);
                    while (p.remaining_time > 0) {
                        p.remaining_time--;
                    }
                }
            }
        }

        if (!processes_left) break;
    }
}
