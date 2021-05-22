/*THIS CODE WILL BE USED TO PROCESS THE PIXELS, AND SHIFT THEM OVER THE GIVEN VALUES
 * YOU INOUT A PIXEL STRUCT, DIMENSIONS, AND SHIFT VALUES
 * 
 * KUMARAN RATNAM
 * SER334 ACUNA
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
//#include "PpmProcessor.h"
#include "Pixelprocessor.h"

struct Pixel
{
    char red;
    char blue;
    char green;
};

void colorShiftPixels(struct Pixel** pArr, int width, int height, int rShift, int gShift, int bShift)
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j< width; j++)
        {
            pArr[i][j].red = pArr[i][j].red + rShift;
            pArr[i][j].blue = pArr[i][j].blue + bShift;
            pArr[i][j].green = pArr[i][j].green + gShift;
        }
    }
}
