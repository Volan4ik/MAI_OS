#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define DECK_SIZE 52

typedef struct {
    int rounds;  
    int thread_id;  
    int matches;  
} ThreadData;

void shuffle_deck(int *deck) { // Fisher-Yates algorithm
    for (int i = DECK_SIZE - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

void* monte_carlo_simulation(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int deck[DECK_SIZE];

    for (int round = 0; round < data->rounds; ++round) {
        for (int i = 0; i < DECK_SIZE; ++i) {
            deck[i] = i % 13;  
        }

        shuffle_deck(deck);

        if (deck[0] == deck[1]) {
            data->matches++;
        }
    }

    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: %s <number_of_threads> <number_of_rounds>\n", argv[0]);
        return 1;
    }

    int num_threads = atoi(argv[1]); 
    int total_rounds = atoi(argv[2]); 

    if (num_threads <= 0 || total_rounds <= 0) {
        printf("Number of threads and rounds must be positive.\n");
        return 1;
    }

    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];

    int rounds_per_thread = total_rounds / num_threads;
    srand(time(NULL)); 

    for (int i = 0; i < num_threads; ++i) {
        thread_data[i].rounds = rounds_per_thread;
        thread_data[i].thread_id = i;
        thread_data[i].matches = 0;

        if (pthread_create(&threads[i], NULL, monte_carlo_simulation, &thread_data[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    int total_matches = 0;
    for (int i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], NULL);
        total_matches += thread_data[i].matches;
    }

    double probability = (double)total_matches / total_rounds;

    printf("Probability of matching top two cards: %.6f)\n", probability);

    return 0;
}
