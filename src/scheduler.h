#ifndef SCHEDULER_H
#define SCHEDULER_H
#define MAX_PROCESSES 100 // You can adjust this value depending on your use case

#define MAX_QUEUES 3

typedef struct Process {
    int pid;            
    int priority;       
    int burst_time;    
    int remaining_time; 
    int arrival_time;   
} Process;

typedef struct ProcessNode {
    Process process;
    struct ProcessNode *next;
} ProcessNode;

typedef struct Queue {
    ProcessNode *front;
    ProcessNode *rear;
} Queue;

void initialize_queues(Queue *queues, int num_queues);
void destroy_queues(Queue *queues, int num_queues);
void enqueue(Queue *queue, Process process);
Process dequeue(Queue *queue);
void gather_input(Queue *queues, int num_queues, int choice);
void run_fcfs(Queue queues[], int num_queues);
void run_sjf(Queue queues[], int num_queues);
void run_round_robin(Queue queues[], int num_queues, int time_quantum);  
void run_multilevel_queue_scheduler(Queue queues[], int num_queues);
void run_selected_scheduling(int choice, Queue queues[], int num_queues);

#endif 
