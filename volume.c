// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file

    // Create Array header with size HEADER_SIZE
    uint8_t header[HEADER_SIZE];

    // Read array of bytes from input to header
    fread(&header, HEADER_SIZE, 1, input);

    // Write array of bytes from header to output
    fwrite(&header, HEADER_SIZE, 1,  output);

    // TODO: Read samples from input file and write updated data to output file

    // Create pointer buffer and allocate memory for it
    int16_t *buffer = malloc(sizeof(int16_t));
    if (buffer == NULL)
    {
        return 1;
    }
    while (fread(buffer, sizeof(int16_t), 1, input))
    {
        *buffer *= factor;
        fwrite(buffer, sizeof(int16_t), 1, output);
    }
    // Free allocated memory
    free(buffer);

    // Close files
    fclose(input);
    fclose(output);
}
