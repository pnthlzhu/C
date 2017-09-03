#ifndef _BMP_H
#define _BMP_H

typedef struct
{
    unsigned short usType;
    unsigned long ulSize;
    unsigned short usReserved1;
    unsigned short usReserved2;
    unsigned long ulOffBits;
}BitMapFileHeader;

typedef struct
{
    unsigned long ulSize;
    long lWidth;
    long lHeight;
    unsigned short usPlanes;
    unsigned short usBitCount;
    unsigned long ulCompression;
    unsigned long ulSizeImage;
    long lXPelsPerMeter;
    long lYPelsPerMeter;
    unsigned long ulClrUsed;
    unsigned long ulClrImportant;
}BitMapInfoHeader;

typedef struct
{
    unsigned char ucRGBBlue;
    unsigned char ucRGBGreen;
    unsigned char ucRGBRed;
    unsigned char ucRGBReserved;
}RGBQuad;

typedef struct
{
    int iWidth;
    int iHeight;
    int iChannels;
    unsigned char *ucpImageData;
}Image;

Image* loadImage(const char *cpImagePath);

#endif
