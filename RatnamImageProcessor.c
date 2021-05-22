/*THIS IS THE MAIN METHIOD HERE. IT WILL TAKE INPUT FROM THE USER, SUCH AS SHUFT VALUES, FILE NAME,
 * SAVE FILE NAME ETC, AND IMPLEMENT THEM WITH THE OTHER .C AND .H FILES.
 * 
 * KUMARAN RATNAM
 * 334 Acuna
 * 
 * Completion time total: ~30 hours
 * 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: kumaran
 *
 * Created on September 18, 2019, 7:43 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BmpProcessor.h"
#include "Pixelprocessor.h"
#include "PpmProcessor.h"

/*
 * 
 */
int main(int argc, char** argv) {
    //printf("hi");
    char* name;
    char* fileName;
    char *dupli;
    char* oldName;
    char *newName;
    char *newType;
    char* oldType;
    char* re;
    char* bl;
    char* gr;
    unsigned int red = 0; //red pixel
    unsigned int green = 0; //green pixel
    unsigned int blue = 0; //blue pixel
    for(int i = 0; i < argc; ++i) //the idea is to iterate through all arguments presented
    {
        if(strcmp(argv[i], "-r")== 0)//if the argument is for a red shift...
        {
            re = argv[i+1];
            red = (int)re;
        }
        if(strcmp(argv[i], "-g")== 0)//if the argument is for a green shift...
        {
            
            gr = argv[i+1];
            green = (int)gr;
        }
        if(strcmp(argv[i], "-b")== 0)//if the argument is for a blue shift...
        {
            bl = argv[i+1];
            blue = (int)bl;
        }
        if(strcmp(argv[i], "-t")== 0) //output file type
        {
            if(strcmp(argv[i], "ppm")== 0)
            {
                strcpy(newType, "ppm");
            }
            if(strcmp(argv[i], "bmp")== 0)
            {
                strcpy(newType, "bmp");
            }
        }
        if(strcmp(argv[i], "-n") == 0) //name of output
        {
            strcpy(name, argv[i+1]); //grab the new file name from next argument over.
        }
        strcpy(oldName, argv[2]); //second argument should be file name to open
    }
    if(strstr(oldName, "bmp") != NULL)
    {
        strcpy(oldType, "bmp");
    }
    else
    {
        strcpy(oldType, "ppm");
    }
    //it looks like argv[] is an array with all arguments or something.
    FILE* file = fopen(argv[1], "rb");
    FILE *newFile;
    if(file == NULL)
    {
        printf("whoops, null file. try again");
        return 0;
    }
    struct Pixel** pArr;
    if(strcmp(oldType, "bmp") == 0) //we start with a bmp file...
    {
        float hiss = sizeof(struct Pixel*);
        struct BMP_Header header;
        struct Pixel* helpme;
        struct DIB_Header dibHeader;
        readDIBHeader(file, &dibHeader);
        struct Pixel** theFilenameType;
        float snek = sizeof(struct Pixel);
        readBMPHeader(file, &header);
        int bwahaha = dibHeader.height;
        int bosque = dibHeader.width;
        pArr = (struct Pixel**) malloc(1 *  hiss * bwahaha); //malloc some memore for our pixel array
        for(int a = 0; a < bwahaha; a++)
        {
            pArr[a] = (struct Pixel*) malloc(bosque * snek); //depending on size of image, malloc memory for each byte
        }
        bwahaha = dibHeader.height;
        bosque = dibHeader.width;
        readPixelsBMP(file, pArr, bosque, bwahaha);
        theFilenameType = (struct Pixel**) malloc(1 * bwahaha * hiss);
        colorShiftPixels(pArr, bosque, bwahaha, red, green, blue);
        int tired = strcmp(newType, "bmp"); //use this as the new byte
        if(newType == NULL || tired == 0) //if they don't want to set a new type, then just use the old type
        {
            dupli = strtok(argv[1], ".");
            newName = strcat(dupli, "secondOne.bmp");
            newFile = fopen(newName, "ab");
            writeBMPHeader(newFile, &header);
            writeDIBHeader(newFile, &dibHeader);
            bwahaha = dibHeader.height;
            bosque = dibHeader.width;
            writePixelsBMP(newFile, pArr, bosque, bwahaha);
        }
        else
        {
            dupli = strtok(argv[1], ".");
            newName = strcat(dupli, "secondOne.ppm");
            newFile = fopen(newName, "ab");
            struct PPM_Header* ppmh = malloc(sizeof(struct PPM_Header));
            bwahaha = dibHeader.height;
            bosque = dibHeader.width;
            makePPMHeader(ppmh, bosque, bwahaha);
            writePPMHeader(newFile, ppmh);
            bwahaha = dibHeader.height;
            bosque = dibHeader.width;
            writePixelsPPM(newFile, pArr, bosque, bwahaha);
            free(ppmh);
        }
        free(theFilenameType);
    }
    else
    {
        char *dodo;
        char* fn;
        struct PPM_Header ppmheader;
        struct Pixel* what;
        readPPMHeader(file, &ppmheader);
        float coal = sizeof(struct Pixel*);
        int leo = ppmheader.height;
        int qwerty = ppmheader.width;
        pArr = (struct Pixel**) malloc(leo * coal);
        for(int a = 0; a<leo; a++)
        {
            pArr[a] = (struct Pixel*) malloc(sizeof(struct Pixel)* qwerty);
        }
        leo = ppmheader.height;
        qwerty = ppmheader.width;
        readPixelsPPM(file, pArr, qwerty, leo);
        colorShiftPixels(pArr, qwerty, leo, red, green, blue);
        if(newType == NULL || strcmp(newType, "ppm") == 0)
        {
            dodo = strtok(argv[1], "ppm");
            fn = strcat(dodo, "secondOne.ppm");
            newFile = fopen(fn, "ab");
            writePPMHeader(newFile, &ppmheader);
            int leo = ppmheader.height;
            int qwerty = ppmheader.width;
            writePixelsPPM(newFile, pArr, qwerty, leo);
        }
        else
        {
            dodo = strtok(argv[1], "ppm");
            fn = strcat(dodo, "secondOne.ppm");
            newFile = fopen(fn, "ab");
            struct BMP_Header* idek = malloc(sizeof(struct BMP_Header));
            struct DIB_Header* thisisdumb = malloc(sizeof(struct DIB_Header));
            int leo = ppmheader.height;
            int qwerty = ppmheader.width;
            makeBMPHeader(idek, qwerty, leo);
            makeDIBHeader(thisisdumb, qwerty, leo);
            writeBMPHeader(newFile, idek);
            writeDIBHeader(newFile, thisisdumb);
            leo = ppmheader.height;
            qwerty = ppmheader.width;
            writePixelsBMP(newFile, pArr, qwerty, leo);
            free(idek);
            free(thisisdumb);
        }
        for(int k = 0; leo; k++)
        {
            free(pArr[k]);
        }
        free(pArr);
        fclose(newFile);
    }
    fclose(file);
}

