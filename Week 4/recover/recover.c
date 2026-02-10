#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCKSIZE 512

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");

    // Check if the file is opened properly
    if (card == NULL)
    {
        perror("Failed to open the file");
    }

    // Create a buffer for a block of data
    uint8_t buffer[BLOCKSIZE];

    // Create a counter to count the JPEGs
    int count = 0;
    FILE *img = NULL;

    // While there's still data left to read from the memory card
    while (fread(buffer, 1, BLOCKSIZE, card) == BLOCKSIZE)
    {
        // Create a buffer for the file name
        char filename[8];

        // If start of new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3]) == 0xe0)
        {
            // If first JPEG
            if (count == 0)
            {
                sprintf(filename, "%03i.jpg", count);
                img = fopen(filename, "w");
                if (img == NULL)
                {
                    perror("Failed to open the file");
                }
                fwrite(buffer, 1, BLOCKSIZE, img);
                count++;
            }

            // Else
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", count);
                img = fopen(filename, "w");
                if (img == NULL)
                {
                    perror("Failed to open the file");
                }
                fwrite(buffer, 1, BLOCKSIZE, img);
                count++;
            }
        }

        // Else
        else
        {
            // If already found JPEG
            if (count != 0)
            {
                fwrite(buffer, 1, BLOCKSIZE, img);
            }
        }
    }

    fclose(img);
    fclose(card);
}
