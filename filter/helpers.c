#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // loop through height(rows) of image
    for (int i = 0; i < height; i++)
    {
        // loop through width(columns) of image
        for (int j = 0; j < width; j++)
        {
            // getting the RGBTriple values for each variable
            float b = image[i][j].rgbtBlue;
            float g = image[i][j].rgbtGreen;
            float r = image[i][j].rgbtRed;

            // calculating and declaring average variable
            // set all pixels to grayscale which is rounded average of sum of RGB values
            int average = round((b + g + r) / 3.0);
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = average;

        }
    }
    return;
}


// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // loop through height(rows) of image
    for (int i = 0; i < height; i++)
    {
        //loop through width(columns) of image
        for (int j = 0; j < width; j++)
        {
            // get the RGBTriple values for each variable
            float b = image[i][j].rgbtBlue;
            float g = image[i][j].rgbtGreen;
            float r = image[i][j].rgbtRed;

            // plugging original RGBTriple values into sepia variables
            // declaring maximum value 255 which is end of spectrum
            int max = 255;
            int sepia_b = round((0.272 * r) + (0.534 * g) + (0.131 * b));
            if (sepia_b > max)
            {
                sepia_b = max;
            }

            int sepia_g = round((0.349 * r) + (0.686 * g) + (0.168 * b));
            if (sepia_g > max)
            {
                sepia_g = max;
            }

            int sepia_r = round((0.393 * r) + (0.769 * g) + (0.189 * b));
            if (sepia_r > max)
            {
                sepia_r = max;
            }

            // assigning sepia values to each pixel
            image[i][j].rgbtBlue = sepia_b;
            image[i][j].rgbtGreen = sepia_g;
            image[i][j].rgbtRed = sepia_r;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // loop through height(rows) of image
    for (int i = 0; i < height; i++)
    {
        //loop through half of the width(columns) of image
        for (int j = 0; j < width / 2; j++)
        {
            // declaring a temp array variable
            // storing the first left half of the array into the temp array
            RGBTRIPLE Temp = image[i][j];

            // below formula works as assigning rightmost element to leftmost element. array[j] = array[width - j - 1]
            // e.g array of 10 elements: array[0] = array[10 - 0 - 1] which gives a swapped array[0] = array[9]
            // e.g array of 11 elements: array[5] = array[11 - 5 - 1] which gives swapped array[5] = array[5]
            image[i][j] = image[i][width - j - 1];

            // after assigning original right half of array to left half of array, we use the original stored left half
            // array in Temp variable to assign to right half of array for each element incremental
            // works as such: for 10 element array, highest j will be 4, and width variable will be (10 - 4 - 1) = 5
            image[i][width - j - 1] = Temp;

        }

    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // declaring a temp array variable to store original pixel values that loops through height and width of image
    RGBTRIPLE temp_value[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // assigning original values to temp array
            temp_value[i][j] = image[i][j];
        }

    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // declaring blue, green and red variables, also creating a pixel_count variable to calculate the available valid pixels around the pixel to be changed.
            // initialise all variables below to 0
            int blue_value = 0;
            int green_value = 0;
            int red_value = 0;
            float pixel_count = 0;

            for (int row = -1; row < 2; row++)
            {
                for (int col = -1; col < 2; col++)
                {
                    // ensuring that we do not exceed height and width 0.
                    if ((row + i >= 0 && row + i < height) && (col + j >= 0 && col + j < width))
                    {
                        blue_value = blue_value + temp_value[row + i][col + j].rgbtBlue;
                        green_value = green_value + temp_value[row + i][col + j].rgbtGreen;
                        red_value = red_value + temp_value[row + i][col + j].rgbtRed;
                        pixel_count++;

                    }
                }
            }
            // finding the rounded average colour value of each pixel by dividing  by the valid surrounding pixels
            image[i][j].rgbtBlue = round(blue_value / pixel_count);
            image[i][j].rgbtGreen = round(green_value / pixel_count);
            image[i][j].rgbtRed = round(red_value / pixel_count);
        }
    }
    return;
}
