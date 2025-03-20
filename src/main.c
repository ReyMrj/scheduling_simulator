#include <stdio.h>
#include "scheduler.h"

int main() {
    int num_queues = MAX_QUEUES;
    Queue queues[MAX_QUEUES];

    initialize_queues(queues, num_queues);

    int choice;
    printf("Select a scheduling algorithm:\n");
    printf("1. Multilevel Queue Scheduling\n");
    printf("2. First-Come First-Served (FCFS)\n");
    printf("3. Shortest Job First (SJF)\n");
    printf("4. Round Robin\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    gather_input(queues, num_queues, choice);

    run_selected_scheduling(choice, queues, num_queues);

    destroy_queues(queues, num_queues);
    
    printf("Simulation completed.\n");
    return 0;
}
