// Including everything necessary here
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "functions.h"
//#include "OF.h"

#ifndef M_PI
#define M_PI 3.141592653589793238462643383279502884197
#endif

int main(int argc, char *argv[])
{

    
    // ###################################################################################
    // YOUR CODE: Handle the possible errors in input data given by the user and say how to execute the code

    // YOUR CODE: Assign all inputs given by the user argv[i] like:
    // POPULATION_SIZE, MAX_GENERATIONS, crossover_rate, mutate_rate, stop_criteria

    if (argc != 6)
    {
        printf("Usage: %s <Pop Size> <Max Generations> <Crossover Rate> <Mutation Rate> <Stop Criteria>\n", argv[0]);
        printf("Please use proper amount of arguments \n");
        return 1;
    }


    int Pop_size = atoi(argv[1]);
    int Max_gen = atoi(argv[2]);
    double Cross_rate = atof(argv[3]);
    double Mut_rate = atof(argv[4]);
    double Stop_crit = atof(argv[5]);

    // ###################################################################################
    /* YOUR CODE: You must change this part based on the lower and upper bounds
    1. based on what function is going to be minimized (let's say Levy)
    2. given bound in https://www.sfu.ca/~ssurjano/optimization.html for each function.*/

    // the number of variables (d)

    srand(time(NULL)); // to make different num for rand each time

    int NUM_VARIABLES = 10;
    // the lower bounds of variables (x_1, x_2, ..., x_d) where d=NUM_VARIABLES
    double Lbound[] = {-5, -5, -5, -5, -5, -5, -5, -5, -5, -5};
    // the upper bounds of variable
    double Ubound[] = {+5, +5, +5, +5, +5, +5, +5, +5, +5, +5 };

    /*For example: in Levy function x_i ∈ [-10, 10], for all i = 1, …, d. This means:
    lower bound = -10 for all x_i
    upper bound = +10 for all x_i
    if d =10 (or NUM_VARIABLES = 10) then:
    double Lbound[] = {-5.0, -5.0, -5.0, -5.0, -5.0, -5.0, -5.0, -5.0, -5.0, -5.0};
    double Ubound[] = {+5.0, +5.0, +5.0, +5.0, +5.0, +5.0, +5.0, +5.0, +5.0, +5.0};

    Another example: in Griewank() if NUM_VARIABLES = 7, then:
    // double Lbound[] = {-600.0, -600.0, -600.0, -600.0, -600.0, -600.0, -600.0};
    // double Ubound[] = {+600.0, +600.0, +600.0, +600.0, +600.0, +600.0, +600.0};
    */

    // ###################################################################################

    // YOUR CODE: Here make all the initial print outs

    printf("Genetic Algorithm Parameters:\n");
    printf("Population Size: %d\n", Pop_size);
    printf("Max Generations: %d\n", Max_gen);
    printf("Crossover Rate: %.2f\n", Cross_rate);
    printf("Mutation Rate: %.2f\n", Mut_rate);
    printf("Stop Criteria: %.2f\n", Stop_crit);

    clock_t start_time, end_time;
    double cpu_time_used;
    start_time = clock();

    // <YOUR CODE: Declare all the arrays you need here>

    double population[Pop_size][NUM_VARIABLES];
    double new_population[Pop_size][NUM_VARIABLES];
    double fitness[Pop_size];
    double best_solution[NUM_VARIABLES]; //
    double best_fitness = INFINITY; // 
    double best_fitness_bef;
    int gen_counter = 0;
    int maxgen_count = 3000; // change as you go


    // <YOUR CODE: Call generate_population function to initialize the "population"> like:
    // generate_population(POPULATION_SIZE, NUM_VARIABLES, population, Lbound, Ubound);
    generate_population(Pop_size, NUM_VARIABLES, population, Lbound, Ubound);

    // iteration starts here. The loop continues until MAX_GENERATIONS is reached
    // Or stopping criteria is met
    for (int generation = 0; generation < Max_gen; generation++)
    {
        // <YOUR CODE: Compute the fitness values using objective function for
        // each row in "population" (each set of variables)> like:
        compute_objective_function(Pop_size, NUM_VARIABLES, population, fitness);

        // <YOUR CODE: Here implement the logic of finding best solution with minimum fitness value
        // and the stopping criteria>

        for (int i = 0; i < Pop_size; i++)
        {
            if (fitness[i] < best_fitness)
            {
                best_fitness_bef = best_fitness;
                best_fitness = fitness[i];
                for (int j = 0; j < NUM_VARIABLES; j++)
                {
                    best_solution[j] = population[i][j];
                }
                gen_counter = 0;
            }
        }

        gen_counter+=1;

        // Check stopping criteria
        if (fabs(best_fitness - best_fitness_bef) < Stop_crit)
        {
            printf("Stopping criteria met at generation %d.\n", generation);
            break;
        }

        if (gen_counter >= maxgen_count)
        {
            break;
        }


        // <YOUR CODE: Here call the crossover function>
        crossover(Pop_size, NUM_VARIABLES, fitness, new_population, population, Cross_rate);
        // <YOUR CODE: Here call the mutation function>
        mutate(Pop_size, NUM_VARIABLES, new_population, population, Lbound, Ubound, Mut_rate);
        // Now you have the a new population, and it goes to the beginning of loop to re-compute all again
    }

    // ###################################################################################
    // You dont need to change anything here
    // Here we print the CPU time taken for your code
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("CPU time: %f seconds\n", cpu_time_used);
    // ###################################################################################

    // <Your CODE: Here print out the best solution and objective function value for the best solution like the format>

    printf("Best solution found:\n");
    for (int j = 0; j < NUM_VARIABLES; j++)
    {
        printf("x[%d] = %f\n", j, best_solution[j]);
    }
    printf("Objective function value: %f\n", best_fitness);
    printf("\n");
    printf("Best fitness: %e\n", best_fitness);

    return 0;
}
