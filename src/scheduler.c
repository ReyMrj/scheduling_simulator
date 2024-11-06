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
void run_multilevel_queue_scheduler(Queue queues[], int num_queues) {
    while (1) {
        int processes_left = 0;
        for (int i = 0; i < num_queues; i++) {
            if (queues[i].size > 0) {
                processes_left = 1;
                Process current = dequeue(&queues[i]);
                
                // Simulate process execution based on time slice
                int execute_time = (current.remaining_time < queues[i].time_slice)
                                   ? current.remaining_time : queues[i].time_slice;
                
                current.remaining_time -= execute_time;
                
                printf("Running Process %d from Queue %d for %d units\n",
                        current.pid, i, execute_time);
                
                if (current.remaining_time > 0) {
                    // Re-enqueue in the same or lower-priority queue as needed
                    if (i < num_queues - 1) {
                        enqueue(&queues[i + 1], current);
                    } else {
                        enqueue(&queues[i], current);
                    }
                }
            }
        }
        if (!processes_left) break;
    }
}
