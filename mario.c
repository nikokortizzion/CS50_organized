#include <stdio.h>
#include <cs50.h>
#include <string.h>

int GetHeight(void);

int main(void)
{
    int height = GetHeight();
    // Loop for making pyramid
    for (int h = 0; h < height; h++)
    {
        char brick[9] = "#";
        strncat(brick, "########", h); //make step
        printf("%*s  %-s\n", height, brick, brick);
    }

}

int GetHeight(void)
// Get number from 1 to 8
{
    while (1)
    {
        int h = get_int("Height: ");
        if ((h > 0) && (h <= 8))
        {
            return h;
        }
    }

}
