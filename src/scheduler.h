#ifndef SCHEDULER_H
#define SCHEDULER_H

// Define the maximum number of queues
#define MAX_QUEUES 3

// Process structure to represent each process
typedef struct Process {
    int pid;            // Process ID
    int priority;       // Priority level or queue level
    int burst_time;     // Total burst time required
    int remaining_time; // Time left to execute
    int waiting_time;   // Time spent waiting
} Process;

// Queue structure to represent each level of the scheduler
typedef struct Queue {
    Process *processes; // Dynamic array of processes in this queue
    int front;          // Front index for dequeue
    int rear;           // Rear index for enqueue
    int size;           // Current number of processes in the queue
    int capacity;       // Maximum capacity of the queue
    int time_slice;     // Time slice for processes in this queue
} Queue;

// Function prototypes
void initialize_queues(Queue queues[], int num_queues);
void enqueue(Queue *queue, Process process);
Process dequeue(Queue *queue);
void destroy_queues(Queue queues[], int num_queues);
void run_multilevel_queue_scheduler(Queue queues[], int num_queues);
void gather_input(Queue *queues, int num_queues);
Process find_shortest_job(Queue *queue);

#endif // SCHEDULER_H
