#include <stdio.h>
#include "scheduler.h"

int main() {
    int num_queues = MAX_QUEUES;
    Queue queues[MAX_QUEUES];

    // Initialize queues
    initialize_queues(queues, num_queues);

    // Gather user input
    gather_input(queues, num_queues);

    // Run the scheduler
    printf("Starting the Multilevel Queue Scheduling Simulation...\n");
    run_multilevel_queue_scheduler(queues, num_queues);

    // Clean up
    destroy_queues(queues, num_queues);
    
    printf("Simulation completed.\n");
    return 0;
}
