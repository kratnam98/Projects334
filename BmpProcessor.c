/*THIS PROGRAM WILL BE USED TO MANIPULATE THE BMP, GET HEADER INFO, DIMENSIONS, ETC.
 * 
 * KUMARAN RATNAM
 * 
 * SER334 ACUNA
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <stdlib.h>
#include "BmpProcessor.h"


void readBMPHeader(FILE* file, struct BMP_Header* header)
{
    printf("hu");
    file = fopen("test2.bmp", "rb");
    fread(header->signature, sizeof(char)*2, 1,file);
    fread(&header->size, sizeof(int), 1,file);
    fread(&header->reserved1, sizeof(short), 1,file);
    fread(&header->reserved2, sizeof(short), 1,file);
    fread(&header->offset_pixel_array, sizeof(int), 1,file);
    
    printf("signature: %c%c\n", header->signature[0],header->signature[1]);
    printf("size: %d\n", header->size);
    printf("reserved1: %hd\n", header->reserved1);
    printf("reserved2: %hd\n", header->reserved2);
    printf("offset_pixel_array: %d\n", header->offset_pixel_array);
    
    fclose(file);
}

void writeBMPHeader(FILE* file, struct BMP_Header* header)
{
    fwrite(&header->signature, sizeof(int),1,file);
    fwrite(&header ->size, sizeof(int),1,file);
    fwrite(&header ->reserved1, sizeof(short),1,file);
    fwrite(&header ->reserved2, sizeof(short),1,file);
    fwrite(&header ->offset_pixel_array, sizeof(int),1,file);
}

void readDIBHeader(FILE* file, struct DIB_Header* header)
{
    file = fopen("test2.bmp", "rb");
    //struct Dib_Header header;
    fread(&header->width, sizeof(int), 1,file); //this is the important part
    fread(&header->height, sizeof(int), 1,file);
    fread(&header->color_planes, sizeof(unsigned int), 1,file);
    fread(&header->bpp, sizeof(unsigned int), 1,file);
    fread(&header->compression, sizeof(int), 1,file);
    fread(&header->size, sizeof(int), 1,file);
    fread(&header->xppm, sizeof(int), 1,file);
    fread(&header->yppm, sizeof(int), 1,file);
    fread(&header->color, sizeof(int), 1,file);
    fread(&header->important_cc, sizeof(int), 1,file);
    fclose(file);
}

void writeDIBHeader(FILE* file, struct DIB_Header* header)
{
    fwrite(&header->width, sizeof(int), 1,file); //this is the important part
    fwrite(&header->height, sizeof(int), 1,file);
    fwrite(&header->color_planes, sizeof(unsigned int), 1,file);
    fwrite(&header->bpp, sizeof(unsigned int), 1,file);
    fwrite(&header->compression, sizeof(int), 1,file);
    fwrite(&header->size, sizeof(int), 1,file);
    fwrite(&header->xppm, sizeof(int), 1,file);
    fwrite(&header->yppm, sizeof(int), 1,file);
    fwrite(&header->color, sizeof(int), 1,file);
    fwrite(&header->important_cc, sizeof(int), 1,file);
}

void makeBMPHeader(struct BMP_Header* header, int width, int height)
{
    header->size = width*height;
    header->reserved1 = 0;
    header->reserved2 = 0;
    header->offset_pixel_array = 40; //idk what this is supposed to be hahahahahaha help
   // header->signature = "BM";
    strcpy(header->signature, "BM");
}

void makeDIBHeader(struct DIB_Header* header, int width, int height)
{
    header->size = 40;
    header->important_cc = 0;
    header->compression = 0;
    header->xppm = 1920; //????
    header->yppm = 1080; //????
    header->color_planes = 1;
    header->color = 0;
    header->bpp = 24; //its 24 bit pixel array or something
    header ->height = height;
    header->width = width;
}

void readPixelsBMP(FILE* file, struct Pixel** pArr, int width, int height)
{
    fseek(file, 54, SEEK_SET);
    int sss = 3 * height;
    unsigned char wippity[sss];
    fread(wippity, sizeof(unsigned char), sss, file);
    //this is because 54 is how we skip over stuff we don't need
    int pad = width % 4; //4 becuase 32 bit system
    int width_pad = width * 3 + pad;
    pad = width%4;
    //use the width to add up hoe much padding is now needed
    int size = width_pad * height;
    int weee = width_pad*pad*width_pad;
    unsigned char info[size];
    //this has to be unsigned for it to work properly
    fread(info, sizeof(unsigned char), size, file);
    //read up on all the values you will now need here
    int howMuchPad = 0;
    for(int i =0; i<height; i++)
    {
        for(int j = 0; j< width; j++)
        {
            int ele = sizeof(struct Pixel) * i * j * width;
            //since we are reading, we need to go up(trial and error lol)
            pArr[i][j].red = info[ele + 2 + howMuchPad];
            pArr[i][j].blue = info[ele + 1 + howMuchPad];
            pArr[i][j].green = info[ele + 0 + howMuchPad];
        }
    }
    
}

void writePixelsBMP(FILE* file, struct Pixel** pArr, int width, int height)
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j< height; j++)
        {
            fwrite(&pArr[i][j].blue, sizeof(char), 1, file);
            fwrite(&pArr[i][j].green, sizeof(char), 1, file);
            fwrite(&pArr[i][j].red, sizeof(char), 1, file);
        }
    }
}