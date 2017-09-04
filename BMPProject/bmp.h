#ifndef _BMP_H
#define _BMP_H

#pragma pack(1)

typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef unsigned char BYTE;
typedef int BOOL;

#define TRUE 1
#define FALSE 0

typedef struct
{
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
}BitMapFileHeader;

typedef struct
{
    DWORD biSize;
    DWORD biWidth;
    DWORD biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    DWORD biXPelsPerMeter;
    DWORD biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
}BitMapInfoHeader;

typedef struct
{
    BYTE rgbBlue;
    BYTE rgbGreen;
    BYTE rgbRed;
    BYTE rgbReserved;
}RGBQuad;

#pragma pack()

typedef struct
{
    int iWidth;
    int iHeight;
    int iChannels;
    unsigned char *ucpImageData;
}Image;

Image* loadImage(const char *cpImagePath);
BOOL saveImage(const char *cpImagePath, const Image *ipImage);

#endif
