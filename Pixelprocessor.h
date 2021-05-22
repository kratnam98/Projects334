/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Pixelprocessor.h
 * Author: kumaran
 *
 * Created on September 18, 2019, 7:45 PM
 */
#include <stdio.h>
#include <stdlib.h>
#ifndef PIXELPROCESSOR_H
#define PIXELPROCESSOR_H

struct Pixel;

struct PPM_Header;

void colorShiftPixels(struct Pixel** pArr, int width, int height, int rShift, int gShift, int bShift);

#endif /* PIXELPROCESSOR_H */
