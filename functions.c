// Your CODE: Include everything necessary here
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "functions.h"


double generate_random(double min, double max)
{
    // Your CODE: implement a function to return a value between min and max
    if (min > max)
    {
        return -1; // Error: invalid range
    }

    return min + (double)rand() / RAND_MAX * (max - min);
}

int generate_int(int min, int max)
{
    // Your CODE: implement the function to return a random integer value

    int int_min = (int)round(min);
    int int_max = (int)round(max);

    // Ensure the range is valid
    if (int_min > int_max)
    {
        return -1; // Error: invalid range
    }

    // Generating random num
    return int_min + rand() % (int_max - int_min + 1);
}

// Function to initialize a random population
void generate_population(int POPULATION_SIZE, int NUM_VARIABLES, double population[POPULATION_SIZE][NUM_VARIABLES], double Lbound[NUM_VARIABLES], double Ubound[NUM_VARIABLES])
{
    // Your CODE: randomly initialize for all values in "population[i][j]""
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        for (int j = 0; j < NUM_VARIABLES; j++)
        {
            population[i][j] = generate_random(Lbound[j], Ubound[j]);
        }
    }
}

// Function to compute the objective function for each member of the population
void compute_objective_function(int POPULATION_SIZE, int NUM_VARIABLES, double population[POPULATION_SIZE][NUM_VARIABLES], double fitness[POPULATION_SIZE])
{

    /* Your CODE: compute "fitness[i]"" for each set of decision variables (individual) or each row in "population"
    by calling "Objective_function" */
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        fitness[i] = Objective_function(NUM_VARIABLES, population[i]);
    }
}

void crossover(int POPULATION_SIZE, int NUM_VARIABLES, double fitness[POPULATION_SIZE], double new_population[POPULATION_SIZE][NUM_VARIABLES], double population[POPULATION_SIZE][NUM_VARIABLES], double crossover_rate)
{
    /* Your CODE: Implement the logic of crossover function here based on "fitness_probs" or each set
    of decision variables (individual) or each row in "population".
    And save the new population in "new_population"*/


// Calculate and normalize fitness probabilities
double fitness_probs[POPULATION_SIZE];
double sum_fitness = 0.0;

// Computing the inverse of fitness for probabilities and their sum
for (int i = 0; i < POPULATION_SIZE; i++) {
    fitness_probs[i] = 1.0 / fitness[i];
    sum_fitness += fitness_probs[i];
}

// Normalizing the probabilities
for (int i = 0; i < POPULATION_SIZE; i++) {
    fitness_probs[i] /= sum_fitness;
}

// Calculating cumulative probabilities
double cumulative_probs[POPULATION_SIZE];
cumulative_probs[0] = fitness_probs[0];
for (int i = 1; i < POPULATION_SIZE; i++) {
    cumulative_probs[i] = cumulative_probs[i - 1] + fitness_probs[i];
}

// Selecting parents based on cumulative probs
for (int i = 0; i < POPULATION_SIZE; i += 2) {
    int parent1 = -1;
    int parent2 = -1;
    double rand_num1 = generate_random(0.0, 1.0);
    double rand_num2 = generate_random(0.0, 1.0);

    // Selecting parent1
    for (int j = 0; j < POPULATION_SIZE; j++) {
        if (rand_num1 <= cumulative_probs[j]) {
            parent1 = j;
            break;
        }
    }

    // Selecting parent2
    for (int j = 0; j < POPULATION_SIZE; j++) {
        if (rand_num2 <= cumulative_probs[j]) {
            parent2 = j;
            break;
        }
    }

    // Performing crossover based on crossover rate
    if (generate_random(0.0, 1.0) < crossover_rate) {
        int crossover_index = rand() % NUM_VARIABLES;

        // Crossover genetics
        for (int j = 0; j < NUM_VARIABLES; j++) {
            if (j < crossover_index) {
                new_population[i][j] = population[parent1][j];
                new_population[i + 1][j] = population[parent2][j];
            } else {
                new_population[i][j] = population[parent2][j];
                new_population[i + 1][j] = population[parent1][j];
            }
        }
    } else {
        // Copying parents to new population if no crossover happens
        for (int j = 0; j < NUM_VARIABLES; j++) {
            new_population[i][j] = population[parent1][j];
            new_population[i + 1][j] = population[parent2][j];
        }
    }
}

// THIS WAS MY OLD CODE, I LEFT IT HERE SO I CAN COMPARE WITH THE NEWER ONE ABOVE, I ADDED FITNESS PROBABILITIES SO ITS MORE EFFICIENT AND RANDOMIZED

    // int parent_indices[POPULATION_SIZE]; // creat array to keep track of parents selected
    // for (int i = 0; i < POPULATION_SIZE; i++)
    // {
    //     parent_indices[i] = i; // initializes indices
    // }

    // // performing crossover in pairs of individuals
    // for (int i = 0; i < POPULATION_SIZE; i += 2)
    // {
    //     if (i + 1 > POPULATION_SIZE)
    //         break; // enrue pair to crossover

    //     // check if crossover should happen
    //     if ((double)rand() / RAND_MAX < crossover_rate)
    //     {
    //         int crossover_point = rand() % NUM_VARIABLES;

    //         for (int j = 0; j < NUM_VARIABLES; j++)
    //         {
    //             if (j < crossover_point)
    //             {
    //                 new_population[i][j] = population[i][j];
    //                 new_population[i + 1][j] = population[i + 1][j];
    //             }
    //             else
    //             {
    //                 new_population[i][j] = population[i + 1][j];
    //                 new_population[i + 1][j] = population[i][j];
    //             }
    //         }
    //     }
    //     else
    //     {
    //         // no crossover, just copying parents to new pop
    //         for (int j = 0; j < NUM_VARIABLES; j++)
    //         {
    //             new_population[i][j] = population[i][j];
    //             new_population[i][j] = population[i + 1][j];
    //         }
    //     }
    // }
}

void mutate(int POPULATION_SIZE, int NUM_VARIABLES, double new_population[POPULATION_SIZE][NUM_VARIABLES], double population[POPULATION_SIZE][NUM_VARIABLES], double Lbound[NUM_VARIABLES], double Ubound[NUM_VARIABLES], double mutate_rate)
{
    /*Your CODE: Implement the logic of mutation on "new_population" and then copy everything into "population"*/

    // Loop through each individual in the new population
    // for (int i = 0; i < POPULATION_SIZE; i++)
    // {
    //     // Loop through each variable for the individual
    //     for (int j = 0; j < NUM_VARIABLES; j++)
    //     {
    //         // Check if mutation should occur based on the mutation rate
    //         if ((double)rand() / RAND_MAX < mutate_rate)
    //         {
    //             // Set the variable to a new random value
    //             new_population[i][j] = generate_random(Lbound[j], Ubound[j]);
    //         }
    //     }
    // }
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        for (int j = 0; j < NUM_VARIABLES; j++)
        {
            if ((double)rand() / RAND_MAX < mutate_rate)
            {
                new_population[i][j] = generate_random(Lbound[j], Ubound[j]);
                
            }
        }
    }

    // Copy the mutated individuals back to the old population
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        for (int j = 0; j < NUM_VARIABLES; j++)
        {
            population[i][j] = new_population[i][j];
        }
    }
}

    // int main(int argc, char *argv[])
    // {
    //     srand(time(NULL)); // to make rand num different each time
    //     double min = -5.0;
    //     double max = 5.0;
    //     double random_value = generate_random(min, max);
    //     int random_int_value = generate_int(min, max);
    //     printf("Random value between %.2f and %.2f: %.5f\n", min, max, random_value);
    //     printf("Random integer between %.2f and %.2f: %d\n", min, max, random_int_value);

    //     // Example usage of the genetic algorithm functions
    //     int POPULATION_SIZE = 10;
    //     int NUM_VARIABLES = 2;
    //     double Lbound[] = {-5.0, -5.0};
    //     double Ubound[] = {5.0, 5.0};
    //     double population[POPULATION_SIZE][NUM_VARIABLES];
    //     double new_population[POPULATION_SIZE][NUM_VARIABLES];
    //     double fitness[POPULATION_SIZE];

    //     generate_population(POPULATION_SIZE, NUM_VARIABLES, population, Lbound, Ubound);
    //     compute_objective_function(POPULATION_SIZE, NUM_VARIABLES, population, fitness);

    //     // Perform crossover and mutation
    //     crossover(POPULATION_SIZE, NUM_VARIABLES, fitness, new_population, population, 0.5);
    //     mutate(POPULATION_SIZE, NUM_VARIABLES, new_population, population, Lbound, Ubound, 0.1);

    //     return 0;
    // }
