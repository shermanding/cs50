#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK 512
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    else
    {
        // remember infile
        char *infile = argv[1];

        // open input file. If file does not exist, return error.
        FILE *inptr = fopen(infile, "r");
        if (inptr == NULL)
        {
            printf("File not found\n");
            return 2;
        }

        // create buffer with 512 size
        BYTE buffer[BLOCK];

        // initialise the jpeg counter, set outfile to null, declare filename with 8 characters. 7 for naming convention + 1 for null character at end of string.
        int jpg_counter = 0;
        FILE *outptr = NULL;
        char filename[8];

        // reading through the whole file, 1 byte at a time. Loop will keep reading until there are no more btyes to be read which is the end of the file.
        while (fread(&buffer, BLOCK, 1, inptr) == 1)
        {
            // if conditions of jpeg are met, where first 4 bytes match the conditions
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                // checks if first JPEG is found, closes file if it is not.
                // if first JPEG has already been found, the counter will be 1 and when the distinct 4 bytes of JPEG are found again this means the end of the JPEG(and start of new JPEG)
                // has been reached. Closes the file that program is writing.
                if (jpg_counter != 0)
                {
                    // close the file
                    fclose(outptr);

                }
                // prints the indexed file name to the output file, opens a new file and adds to the counter each time a new file is created.
                sprintf(filename, "%03i.jpg", jpg_counter);
                outptr = fopen(filename, "w");
                jpg_counter++;

            }
            // condition where if JPEG file is found (JPG counter), starts writing to file
            if (jpg_counter != 0)
            {
                fwrite(&buffer, BLOCK, 1, outptr);
            }

        }
        // closes input and output files
        fclose(inptr);
        fclose(outptr);

        return 0;
    }

}