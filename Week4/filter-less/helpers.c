#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            int avg = round((red+green+blue)/3.0);

            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

int limit(int *pixelValue);
// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            int sepiaRed = round(0.393*red + 0.769*green + 0.189 * blue);
            limit(&sepiaRed);

            int sepiaGreen = round(0.349*red + 0.686*green + 0.168 * blue);
            limit(&sepiaGreen);

            int sepiaBlue = round(0.272*red + 0.534*green + 0.131 * blue);
            limit(&sepiaBlue);

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

int limit(int *pixelValue)
{
    if (*pixelValue > 255)
    {
        *pixelValue = 255;
    }
    if (*pixelValue < 0)
    {
        *pixelValue = 0;
    }
    return 0;
}

// Reflect image horizontally
void swap(RGBTRIPLE *pixel1, RGBTRIPLE *pixel2);
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i=0; i<height; i++)
    {
        int start = 0;
        int end = width -1;

        while (start<end)
        {
            swap(&image[i][start], &image[i][end]);
            start++;
            end--;
        }
    }
    return;
}

void swap(RGBTRIPLE *pixel1, RGBTRIPLE *pixel2)
{
    RGBTRIPLE temp = *pixel1;
    *pixel1 = *pixel2;
    *pixel2 = temp;
    return;
}

int check(int row, int column, int height, int width);
int sum(int *red, int *green, int *blue,RGBTRIPLE *pixel);
void checksum(int row, int column, int height, int width, int *red, int *green, int *blue, RGBTRIPLE *pixel, int *count);
// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // make copy of image
    RGBTRIPLE copy[height][width];
    for (int i=0; i<height; i++)
        {
            for (int j=0; j<width; j++)
            {
                // init count red, green, blue values
                int red = 0;
                int green = 0;
                int blue = 0;
                int count = 0;

                sum(&red, &green, &blue , &image[i][j]);
                count += 1;
                // get values from nodes around current node [i][j]
                if (check(i-1, j, height, width)) // see if outside matrix
                {
                    sum(&red, &green, &blue, &image[i-1][j]);
                    count += 1;
                }

                if (check(i-1, j-1, height, width)) // see if outside matrix
                {
                    sum(&red, &green, &blue, &image[i-1][j-1]);
                    count += 1;
                }

                if (check(i, j-1, height, width)) // see if outside matrix
                {
                    sum(&red, &green, &blue, &image[i][j-1]);
                    count += 1;
                }

                if (check(i+1, j-1, height, width)) // see if outside matrix
                {
                    sum(&red, &green, &blue, &image[i+1][j-1]);
                    count += 1;
                }

                if (check(i+1, j, height, width)) // see if outside matrix
                {
                    sum(&red, &green, &blue, &image[i+1][j]);
                    count += 1;
                }

                if (check(i+1, j+1, height, width)) // see if outside matrix
                {
                    sum(&red, &green, &blue, &image[i+1][j+1]);
                    count += 1;
                }

                if (check(i, j+1, height, width)) // see if outside matrix
                {
                    sum(&red, &green, &blue, &image[i][j+1]);
                    count += 1;
                }

                if (check(i-1, j+1, height, width)) // see if outside matrix
                {
                    sum(&red, &green, &blue, &image[i-1][j+1]);
                    count += 1;
                }

                // Apply averages to pixel
                copy[i][j].rgbtRed = round(red/(float)count);
                copy[i][j].rgbtGreen = round(green/(float)count);
                copy[i][j].rgbtBlue = round(blue/(float)count);

                // return image
            }
        }
        for (int i=0; i<height; i++)
        {
            for(int j=0;j<width;j++)
            {
                image[i][j] = copy[i][j];
            }
        }
    return;
}

int check(int row, int column, int height, int width)
{
    if (row < 0 || row >= height || column < 0 || column >= width)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
int sum(int *red, int *green, int *blue,RGBTRIPLE *pixel)
{
    *red += pixel->rgbtRed;
    *green += pixel->rgbtGreen;
    *blue += pixel->rgbtBlue;
    return 0;
}
