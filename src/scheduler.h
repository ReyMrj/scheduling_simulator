#ifndef SCHEDULER_H
#define SCHEDULER_H
#define MAX_PROCESSES 100 // You can adjust this value depending on your use case

// Define the maximum number of queues
#define MAX_QUEUES 3

// Define a structure to represent a process
typedef struct Process {
    int pid;            // Process ID
    int priority;       // Priority (used in Multilevel Queue Scheduling)
    int burst_time;     // Initial burst time
    int remaining_time; // Remaining burst time
    int arrival_time;   // Arrival time (optional, if needed)
} Process;

// Define a node for the process queue
typedef struct ProcessNode {
    Process process;
    struct ProcessNode *next;
} ProcessNode;

// Define a queue to hold processes
typedef struct Queue {
    ProcessNode *front;
    ProcessNode *rear;
} Queue;

// Function prototypes
void initialize_queues(Queue *queues, int num_queues);
void destroy_queues(Queue *queues, int num_queues);
void enqueue(Queue *queue, Process process);
Process dequeue(Queue *queue);
void gather_input(Queue *queues, int num_queues, int choice);
void run_fcfs(Queue queues[], int num_queues);
void run_sjf(Queue queues[], int num_queues);
void run_round_robin(Queue queues[], int num_queues, int time_quantum);  // Fixed declaration
void run_multilevel_queue_scheduler(Queue queues[], int num_queues);
void run_selected_scheduling(int choice, Queue queues[], int num_queues);

#endif // SCHEDULER_H
