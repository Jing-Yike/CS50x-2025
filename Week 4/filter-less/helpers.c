#include "helpers.h"
#include <math.h>

void boxblur(int a, int b, int height, int width, RGBTRIPLE copy[height][width],
             RGBTRIPLE image[height][width]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take average of red, green, and blue
            int average =
                round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            // Update pixel values
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed, sepiaGreen, sepiaBlue;
            // Comput sepia values
            if (.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                    .189 * image[i][j].rgbtBlue >
                255)
            {
                sepiaRed = 255;
            }
            else
            {
                sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                                 .189 * image[i][j].rgbtBlue);
            }

            if (.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                    .168 * image[i][j].rgbtBlue >
                255)
            {
                sepiaGreen = 255;
            }
            else
            {
                sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                                   .168 * image[i][j].rgbtBlue);
            }

            if (.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                    .131 * image[i][j].rgbtBlue >
                255)
            {
                sepiaBlue = 255;
            }
            else
            {
                sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                                  .131 * image[i][j].rgbtBlue);
            }
            // Update pixel values
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixels
            RGBTRIPLE temp;
            temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    // Blur the pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            boxblur(i, j, height, width, copy, image);
        }
    }
    return;
}

// Function calculates average of box blur
void boxblur(int a, int b, int height, int width, RGBTRIPLE copy[height][width],
             RGBTRIPLE image[height][width])
{
    RGBTRIPLE average;
    int red = 0, green = 0, blue = 0, n = 0;
    for (int row = -1; row <= 1; row++)
    {
        for (int col = -1; col <= 1; col++)
        {
            if (a + row < 0 || a + row > height - 1 || b + col < 0 || b + col > width - 1)
            {
                continue;
            }
            else
            {
                red += copy[a + row][b + col].rgbtRed;
                green += copy[a + row][b + col].rgbtGreen;
                blue += copy[a + row][b + col].rgbtBlue;
                n++;
            }
        }
    }
    image[a][b].rgbtRed = round((float) red / n);
    image[a][b].rgbtGreen = round((float) green / n);
    image[a][b].rgbtBlue = round((float) blue / n);

    return;
}
