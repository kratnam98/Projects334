/*
 * THIS CODE WILL BE USED TO MANIPULATE THE PPM IAMGES
 * 
 * Kumaran Ratnam
 * SER 334 Acuna
 * 
 * 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PpmProcessor.h"

struct Pixel
{
    char red;
    char blue;
    char green;
};

void readPPMHeader(FILE* file, struct PPM_Header* header)
{
    fscanf(file, "%s", &header->num);
    fscanf(file, "%d", &header->width );
    fscanf(file, "%d", &header->height);
    fscanf(file, "%d", &header->v);
}

void writePPMHeader(FILE* file, struct PPM_Header* header)
{
    fwrite(header ->num, sizeof(char) * 2,1,file);
    fwrite(header->height, sizeof(int), 1,file);
    fwrite(header->width, sizeof(int), 1, file);
    fwrite(header->v, sizeof(int), 1, file);
}

void makePPMHeader(struct PPM_Header* header, int width, int height)
{
    header->width = width;
    header ->height = height;
}

void readPixelsPPM(FILE* file, struct Pixel** pArr, int width, int height)
{
    int total = width * height * 3; //the 3 is for the 3 bytes in each pixel
    char final[total];
    fread(final, sizeof(char), total, file);
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j< width; j++)
        {
            int ele = sizeof(struct Pixel) * i*j*width;
            pArr[i][j].red = final[ele];
            pArr[i][j].blue = final[ele+1];
            pArr[i][j].green = final[ele+2];
        }
    }
}

void writePixelsPPM(FILE* file, struct Pixel** pArr, int width, int height)
{
    for(int i = 0; i<height; i++)
    {
        for(int j = 0; j<width; j++)
        {
            fwrite(&pArr[i][j].red, sizeof(char), 1, file); //take the pArr array, and one by one, write it to the file
            fwrite(&pArr[i][j].blue, sizeof(char), 1, file);
            fwrite(&pArr[i][j].green, sizeof(char), 1, file);
        }
    }
}
