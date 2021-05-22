/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BmpProcessor.h
 * Author: kumaran
 *
 * Created on September 18, 2019, 7:44 PM
 */

#include <stdio.h>
#include <stdlib.h>
#ifndef BMPPROCESSOR_H
#define BMPPROCESSOR_H

struct BMP_Header{
    char signature [ 2 ] ;
    int size;
    short reserved1 ;
    short reserved2 ;
    int offset_pixel_array;
};

struct DIB_Header{
    int width;
    int height;
    unsigned int color_planes;
    unsigned int bpp;
    int compression;
    int size;
    int xppm;
    int yppm;
    int color;
    int important_cc;
    
};

struct Pixel
{
    char red;
    char blue;
    char green;
};

void readBMPHeader(FILE* file, struct BMP_Header* header);

void writeBMPHeader(FILE* file, struct BMP_Header* header);

void readDIBHeader(FILE* file, struct DIB_Header* header);

void writeDIBHeader(FILE* file, struct DIB_Header* header);

void makeBMPHeader(struct BMP_Header* header, int width, int height);

void makeDIBHeader(struct DIB_Header* header, int width, int height);

void readPixelsBMP(FILE* file, struct Pixel** pArr, int width, int height);

void writePixelsBMP(FILE* file, struct Pixel** pArr, int width, int height);



#endif /* BMPPROCESSOR_H */

