#include <stdio.h>
#include <stdlib.h>

// File divide on blocks with size of 512 bites
const int BLOCK = 512;

int search_jpeg(unsigned char *chank);
int main(int argc, char *argv[])
{
    // Initialize variables
    int start = 0, end = 0, counter = 0;
    FILE *image = NULL;
    char *filename = NULL;
    // Check correct way to execute program
    if (argc != 2)
    {
        printf("Usage: ./recover file\n");
        return 1;
    }
    // Open file for reading
    FILE *mem = fopen(argv[1], "rb");
    if (mem == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    // Create pointer for each block and allocate memory for it
    unsigned char *buffer = malloc(BLOCK);
    while (fread(buffer, BLOCK, 1, mem))
    {
        // Check if buffer contain header of jpeg
        if (search_jpeg(buffer))
        {
            // If file opened close it
            if (start)
            {
                start = 0;
                printf("Image %s saved.\n", filename);
                fclose(image);
                counter++;
                free(filename);
            }
            // Create filename for image
            if (counter >= 0 && counter <= 999)
            {
                filename = malloc(10);
                sprintf(filename, "./%03d.jpg", counter);
            }
            // open file image for writing
            image = fopen(filename, "wb");
            if (image == NULL)
            {
                printf("Coould not open file.\n");
                return 1;
            }
            start = 1;

            // Start writing bytes in file image
            fwrite(buffer, BLOCK, 1, image);

        }
        else
        {
            // If file opened continue writing
            if (start)
            {
                fwrite(buffer, BLOCK, 1, image);
            }
        }

    }

    free(buffer);
    fclose(mem);
    fclose(image);
}

int search_jpeg(unsigned char *chank)
{
    /** If first four bytes contain:
     * first byte - 0xff
     * second - 0xd8
     * third - 0xff
     * fourth - either 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8,
     * 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xefs
     * then it's header of jpeg file.
     **/
    if (chank == NULL)
    {
        return 0;
    }
    return (chank[0] == 0xff && chank[1] == 0xd8 && chank[2] == 0xff && (
                chank[3] & 0xf0) == 0xe0);
}
