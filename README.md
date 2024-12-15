# BMP Image Processing Lab

## Overview
This program performs the following operations on a BMP image:
1. Rotates the image 90° clockwise.
2. Rotates the image 90° counter-clockwise.
3. Applies a Gaussian blur filter.

## Files
- **Makefile**: Automates the build process.
- **main.cpp**: The main C++ file containing the image processing logic.
- **input.bmp**: A sample BMP image to process.
- **rotated_clockwise.bmp**: BMP image after 90° clockwise rotation.
- **rotated_counterclockwise.bmp**: BMP image after 90° counter-clockwise rotation.
- **blurred.bmp**: BMP image with Gaussian blur applied.

##How to Compile & Run

#Compile
g++ -o bmp_lab main.cpp

#Run
./bmp_lab