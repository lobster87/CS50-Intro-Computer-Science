#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

const int SIZE = 512;
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // check number of inputs
    if (argc != 2)
    {
        printf("need filename");
        return 1;
    }

    char *data = argv[1];
    FILE *input = fopen(data, "r");

    if (input == NULL)
    {
        printf("can not open file %s", data);
        return 2;
    }

    // while not end of card
    BYTE buffer[SIZE];
    int count = 0;
    FILE *jpg = NULL;
    char filename[8];

    while (fread(buffer, 1, SIZE, input) == SIZE)
    {
        // if start of new jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if first jpeg
            if (count == 0)
            {
                sprintf(filename, "%03i.jpg", count);
                jpg = fopen(filename, "w");
                count++;
            }
            // else
            else
            {
                fclose(jpg);
                sprintf(filename, "%03i.jpg", count);
                jpg = fopen(filename, "w");
                count++;
            }
        }
        //if already found jpeg
        if (jpg != NULL)
        {
            fwrite(buffer, 1, SIZE, jpg);
        }
    }

    // close remaining files
    fclose(input);
    fclose(jpg);

    return 0;
}