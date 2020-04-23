#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // check for valid file
    char *raw = argv[1];
    FILE *f = fopen(raw, "r");
    if (f == NULL)
    {
        fprintf(stderr, "error %s.\n", raw);
        return 2;
    }

    unsigned char *buffer = malloc(512);
    int count = 0;
    FILE *img;

    while (fread(buffer, sizeof(buffer), 1, f))
    {
        // new jpg 
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // close previous file
            if (count > 0)
            {
                fclose(img);
            }

            // create filename
            char filename[7];
            sprintf(filename, "%03i.jpg", count);

            // open new image file
            img = fopen(filename, "w");

            // check if jpg file is successfully created
            if (img == NULL)
            {
                fclose(f);
                free(buffer);
                fprintf(stderr, "error creating output JPG %s", filename);
                return 3;
            }

            count++;
        }

        // if first jpg is not yet found, skip
        if (!count)
        {
            continue;
        }

        // write jpg info into current file
        fwrite(buffer, 512, 1, img);
    }

    fclose(f);
    fclose(img);

    free(buffer);
    return 0;
}