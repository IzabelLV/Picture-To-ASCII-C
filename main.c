#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STB_IMAGE_IMPLEMENTATION //To include the implementation of the library.
#include "stb_image.h"


const char* asciiCharacters = "@#%*+=-:. "; //Darkest to lightest

char getAscii(int grayValue)
{
    int index = (grayValue * (strlen(asciiCharacters) - 1)) / 255;
    return asciiCharacters[index];
}

void convertImage(const char* imagePath, const char* outputFile)
{
    int width, height, channels;

    unsigned char* img = stbi_load(imagePath, &width, &height, &channels, 1);
    if (!img)
    {
        printf("Failed to load due to: %s\n", stbi_failure_reason());
        return;
    }

    printf("Image loaded: %dx%d\n", width, height);

    FILE* outFile = fopen(outputFile, "w");
    if (!outFile)
    {
        printf("Failed to open.");
        stbi_image_free(img);
        return;
    }

    for (int i = 0; i < height; i += 2) //To adjust aspect ratio
    {
        for (int y = 0; y < width; ++y)
        {
            int pixelIndex = i * width + y;
            unsigned char grayValue = img[pixelIndex];
            fputc(getAscii(grayValue), outFile);
        }
        fputc('\n', outFile);
    }

    printf("ASCII art saved to: %s\n", outputFile);

    fclose(outFile);
    stbi_image_free(img);
}


int main(int count, char* values[]) //External input (File name)
{
    if (count < 3)
    {
        printf("Usage %s <input_image> <output_file>\n", values[0]);
        return 1;
    }

    const char* imagePath = values[1];
    const char* outputFile = values[2];

    convertImage(imagePath, outputFile);

    return 0;
}