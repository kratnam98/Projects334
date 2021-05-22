/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PpmProcessor.h
 * Author: kumaran
 *
 * Created on September 18, 2019, 7:45 PM
 */

#ifndef PPMPROCESSOR_H
#define PPMPROCESSOR_H

/*
struct Pixel
{
    char red;
    char blue;
    char green;
};
*/
struct PPM_Header
{
    char num[2];
    int height;
    int width;
    int v;
};

struct Pixel;

void readPPMHeader(FILE* file, struct PPM_Header* header);

void writePPMHeader(FILE* file, struct PPM_Header* header);

void makePPMHeader(struct PPM_Header* header, int width, int height);

void readPixelsPPM(FILE* file, struct Pixel** pArr, int width, int height);

void writePixelsPPM(FILE* file, struct Pixel** pArr, int width, int height);


#endif /* PPMPROCESSOR_H */

