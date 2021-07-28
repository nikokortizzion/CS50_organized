#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start_population = 0;
    while (start_population < 9)
    {
        start_population = get_int("Start size of population (more or equal to 9): ");
    }
    // TODO: Prompt for end size
    int end_population = 0;
    while (end_population < start_population)
    {
        end_population = get_int("End size of population (more or equal to start size): ");
    }
    // TODO: Calculate number of years until we reach threshold
    int years = 0;
    int population_size = start_population;
    while (true)
    {
        if (population_size >= end_population)
        {
            break;
        }
        population_size += population_size / 3 - population_size / 4;
        years++;
    }
    // TODO: Print number of years
    printf("Years: %i\n", years);
}
