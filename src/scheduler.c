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

// Enqueue with debugging print statements
void enqueue(Queue *queue, Process process) {
    if (queue->size < queue->capacity) {
        queue->processes[queue->rear] = process;
        queue->rear = (queue->rear + 1) % queue->capacity;
        queue->size++;
        printf("Enqueued process %d (priority %d, remaining time %d)\n", 
               process.pid, process.priority, process.remaining_time);
    } else {
        printf("Queue is full, cannot enqueue process %d\n", process.pid);
    }
}

// Dequeue with debugging
Process dequeue(Queue *queue) {
    Process p = queue->processes[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    printf("Dequeued process %d (priority %d, remaining time %d)\n", 
           p.pid, p.priority, p.remaining_time);
    return p;
}

// Gather input with enqueue debug statements
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

// Shortest Job First for mid-priority queue
Process find_shortest_job(Queue *queue) {
    int min_index = queue->front;
    for (int i = 1; i < queue->size; i++) {
        int idx = (queue->front + i) % queue->capacity;
        if (queue->processes[idx].remaining_time < queue->processes[min_index].remaining_time) {
            min_index = idx;
        }
    }
    Process shortest_process = queue->processes[min_index];
    printf("Found shortest job: process %d with remaining time %d\n", 
           shortest_process.pid, shortest_process.remaining_time);

    // Shift elements left after removing the shortest job
    for (int i = min_index; i != queue->rear; i = (i + 1) % queue->capacity) {
        queue->processes[i] = queue->processes[(i + 1) % queue->capacity];
    }
    queue->rear = (queue->rear - 1 + queue->capacity) % queue->capacity;
    queue->size--;

    return shortest_process;
}

// Main scheduling function with debug output
void run_multilevel_queue_scheduler(Queue queues[], int num_queues) {
    printf("Starting the Multilevel Queue Scheduling Simulation...\n");

    while (1) {
        int processes_left = 0;

        for (int i = 0; i < num_queues; i++) {
            if (queues[i].size > 0) {
                processes_left = 1;
                printf("\nQueue %d (size: %d) - Executing...\n", i, queues[i].size);

                if (i == 0) { // High priority queue, Round Robin
                    Process p = dequeue(&queues[i]);
                    int exec_time = (p.remaining_time < queues[i].time_slice) ? p.remaining_time : queues[i].time_slice;
                    printf("Running process %d for %d units in Round Robin\n", p.pid, exec_time);
                    p.remaining_time -= exec_time;

                    if (p.remaining_time > 0) {
                        enqueue(&queues[i], p);
                    } else {
                        printf("Process %d completed.\n", p.pid);
                    }
                } else if (i == 1) { // Mid priority queue, Shortest Job First
                    Process p = find_shortest_job(&queues[i]);
                    printf("Running shortest job process %d to completion\n", p.pid);

                    p.remaining_time = 0; // Mark as completed
                    printf("Process %d completed.\n", p.pid);

                } else if (i == 2) { // Low priority queue, First-Come First-Served
                    Process p = dequeue(&queues[i]);
                    printf("Running process %d to completion in FCFS\n", p.pid);
                    while (p.remaining_time > 0) {
                        p.remaining_time--;
                    }
                    printf("Process %d completed.\n", p.pid);
                }
            }
        }

        if (!processes_left) break;
    }
    printf("Simulation completed.\n");
}
