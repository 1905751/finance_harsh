#include "helpers.h"
#include<math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // variables                              
    float avg;
    //main loop to perform grayscale filter           
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // doing average
            avg = round((image[i][j].rgbtGreen + image[i][j].rgbtBlue + image[i][j].rgbtRed) / 3.000);
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // variables                                                 
    float x, y, z;
    // main loop
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //given combination for sepia
            x = 0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue;
            y = 0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue;
            z = 0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue;
            //checking requires conditions
            if (x > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = round(x);
            }
            if (y > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = round(y);
            }
            if (z > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = round(z);
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //temp variables                                             
    int temp1 = 0, temp2 = 0, temp3 = 0;
    // main loop for reflection filter
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // swapping
            temp1 = image[i][j].rgbtGreen;
            temp2 = image[i][j].rgbtBlue;
            temp3 = image[i][j].rgbtRed;

            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;

            image[i][width - 1 - j].rgbtGreen = temp1;
            image[i][width - 1 - j].rgbtBlue = temp2;
            image[i][width - 1 - j].rgbtRed = temp3;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //declaring variables
    int sumg, sumb, sumr;
    float x;
    //temp
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            sumg = 0;
            sumb = 0;
            sumr = 0;
            x = 0.00;
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    if (k < 0 || k > height - 1 || l < 0 || l > width - 1);
                    else
                    {
                        sumg = sumg + image[k][l].rgbtGreen;
                        sumb = sumb + image[k][l].rgbtBlue;
                        sumr = sumr + image[k][l].rgbtRed;
                        x++;
                    }

                }

            }
            //average
            temp[i][j].rgbtGreen = round(sumg / x);
            temp[i][j].rgbtBlue = round(sumb / x);
            temp[i][j].rgbtRed = round(sumr / x);
        }
    }


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //copying
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }
    return;
}
