#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

Image* loadImage(const char *cpImagePath)
{
    Image *tpBmpImage;
    FILE *fpBmpFile;
    BitMapFileHeader tBmpFileHeader;
    BitMapInfoHeader tBmpInfoHeader;
    int iChannels = 1;
    int iWidth = 0;
    int iHeight = 0;
    int iOffset = 0;
    int iStep = 0;
    unsigned char ucPixVal;
    RGBQuad *tpRGBQuad;
    int i,j,k;

    if((fpBmpFile = fopen(cpImagePath, "rb")) == NULL)
    {
	perror("fopen failed");
	return NULL;
    }

    fprintf(stdout, "sizeof(BitMapFileHeader) is %ld\n", sizeof(BitMapFileHeader));
    fprintf(stdout, "sizeof(BitMapInfoHeader) is %ld\n", sizeof(BitMapInfoHeader));
    fprintf(stdout, "sizeof(RGBQuad) is %ld\n", sizeof(RGBQuad));

    tpBmpImage = (Image*)malloc(sizeof(Image));
    fread(&tBmpFileHeader, sizeof(BitMapFileHeader), 1, fpBmpFile);
    if(tBmpFileHeader.bfType == 0x4D42)
    {
	fprintf(stdout, "this is a bmp file!\n");
	fprintf(stdout, "===================\n");
	fprintf(stdout, "bmp文件头信息:\n");
	fprintf(stdout, "文件大小:%dB\n", tBmpFileHeader.bfSize);
	fprintf(stdout, "保留字1:%d\n", tBmpFileHeader.bfReserved1);
	fprintf(stdout, "保留字2:%d\n", tBmpFileHeader.bfReserved2);
	fprintf(stdout, "位图数据偏移字节数:%dB\n", tBmpFileHeader.bfOffBits);

	fread(&tBmpInfoHeader, sizeof(BitMapInfoHeader), 1, fpBmpFile);
	fprintf(stdout, "===================\n");
	fprintf(stdout, "bmp位图头信息:\n");
	fprintf(stdout, "结构体长度:%d\n", tBmpInfoHeader.biSize);
	fprintf(stdout, "位图宽度:%d\n", tBmpInfoHeader.biWidth);
	fprintf(stdout, "位图高度:%d\n", tBmpInfoHeader.biHeight);
	fprintf(stdout, "位图平面数:%d\n", tBmpInfoHeader.biPlanes);
	fprintf(stdout, "颜色位数:%d\n", tBmpInfoHeader.biBitCount);
	fprintf(stdout, "压缩方式:%d\n", tBmpInfoHeader.biCompression);
	fprintf(stdout, "实际位图数据占用的字节数:%d\n", tBmpInfoHeader.biSizeImage);
	fprintf(stdout, "X方向分辨率:%d\n", tBmpInfoHeader.biXPelsPerMeter);
	fprintf(stdout, "Y方向分辨率:%d\n", tBmpInfoHeader.biYPelsPerMeter);
	fprintf(stdout, "使用的颜色数:%d\n", tBmpInfoHeader.biClrUsed);
	fprintf(stdout, "重要颜色数:%d\n", tBmpInfoHeader.biClrImportant);

	if(tBmpInfoHeader.biBitCount == 8)
	{
	    fprintf(stdout, "该文件有调色板，即该位图为非真彩色\n");
	    iChannels = 1;
	    iWidth = tBmpInfoHeader.biWidth;
	    iHeight = tBmpInfoHeader.biHeight;
	    iOffset = (iChannels * iWidth) % 4;

	    if(iOffset != 0)
	    {
		iOffset = 4 - iOffset;
	    }

	    tpBmpImage->iWidth = iWidth;
	    tpBmpImage->iHeight = iHeight;
	    tpBmpImage->iChannels = iChannels;
	    tpBmpImage->ucpImageData = (unsigned char*)malloc(sizeof(unsigned char)*iWidth*iHeight);
	    iStep = iChannels * iWidth;

	    tpRGBQuad = (RGBQuad*)malloc(sizeof(RGBQuad));
	    fread(tpRGBQuad, sizeof(RGBQuad), 256, fpBmpFile);
	    free(tpRGBQuad);
	
	    for(i = 0;i < iHeight;i++)
	    {
		for(j = 0;j < iWidth;j++)
		{
		    fread(&ucPixVal, sizeof(unsigned char), 1, fpBmpFile);
		    tpBmpImage->ucpImageData[(iHeight-1-i)*iStep+j] = ucPixVal;
		}
		if(iOffset != 0)
		{
		    for(j = 0;j < iOffset;j++)
		    {
			fread(&ucPixVal, sizeof(unsigned char), 1, fpBmpFile);
		    }
		}
	    }
	}
	else if(tBmpInfoHeader.biBitCount == 24)
	{
	    fprintf(stdout, "该位图为真彩色\n");
	    iChannels = 3;
            iWidth = tBmpInfoHeader.biWidth;
            iHeight = tBmpInfoHeader.biHeight;

	    tpBmpImage->iWidth = iWidth;
            tpBmpImage->iHeight = iHeight;
            tpBmpImage->iChannels = iChannels;
	    tpBmpImage->ucpImageData = (unsigned char*)malloc(sizeof(unsigned char)*iWidth*iHeight*3);
            iStep = iChannels * iWidth;
	    iOffset = (iChannels * iWidth) % 4;

            if(iOffset != 0)
            {
                iOffset = 4 - iOffset;
            }

	    for(i = 0;i < iHeight;i++)
            {
                for(j = 0;j < iWidth;j++)
                {
		    for(k = 0;k < 3;k++)
		    {
                        fread(&ucPixVal, sizeof(unsigned char), 1, fpBmpFile);
                        tpBmpImage->ucpImageData[(iHeight-1-i)*iStep+j*3+k] = ucPixVal;
		    }
                }
                if(iOffset != 0)
                {
                    for(j = 0;j < iOffset;j++)
                    {
                        fread(&ucPixVal, sizeof(unsigned char), 1, fpBmpFile);
                    }
                }
            }

	}
    }
    else
    {
	fprintf(stdout, "this is not a bmp file\n");
    }

    return tpBmpImage;
}

BOOL saveImage(const char *cpImagePath, const Image *ipImage)
{
    FILE *fpImageFile;
    WORD fileType;
    BitMapFileHeader tBmpFileHeader;
    BitMapInfoHeader tBmpInfoHeader;
    int iStep;
    int iOffset;
    BYTE bPixVal = '\0';
    int i, j;
    RGBQuad *pRGBQuad;

    if((fpImageFile = fopen(cpImagePath, "wb")) == NULL)
    {
	perror("fopen failed");
	return FALSE;
    }

    //24位，通道，彩图
    if(ipImage->iChannels == 3)
    {
	iStep = ipImage->iChannels * ipImage->iWidth;
	iOffset = iStep % 4;
	if(iOffset != 4)
	{
	    iStep += 4 - iOffset;
	}

	tBmpFileHeader.bfType = 0x4D42;
	tBmpFileHeader.bfSize = ipImage->iHeight*iStep + 54;  
	tBmpFileHeader.bfReserved1 = 0;  
	tBmpFileHeader.bfReserved2 = 0;  
	tBmpFileHeader.bfOffBits = 54;  
	fwrite(&tBmpFileHeader, sizeof(BitMapFileHeader), 1, fpImageFile);

	tBmpInfoHeader.biSize = 40;  
	tBmpInfoHeader.biWidth = ipImage->iWidth;  
	tBmpInfoHeader.biHeight = ipImage->iHeight;  
	tBmpInfoHeader.biPlanes = 1;  
	tBmpInfoHeader.biBitCount = 24;  
	tBmpInfoHeader.biCompression = 0;  
	tBmpInfoHeader.biSizeImage = ipImage->iHeight*iStep;  
	tBmpInfoHeader.biXPelsPerMeter = 0;  
	tBmpInfoHeader.biYPelsPerMeter = 0;  
	tBmpInfoHeader.biClrUsed = 0;  
	tBmpInfoHeader.biClrImportant = 0;  
	fwrite(&tBmpInfoHeader, sizeof(BitMapInfoHeader), 1, fpImageFile);

	for (i=ipImage->iHeight-1; i>-1; i--)  
	{  
	    for (j=0; j<ipImage->iWidth; j++)  
	    {  
		bPixVal = ipImage->ucpImageData[i*ipImage->iWidth*3+j*3];  
		fwrite(&bPixVal, sizeof(BYTE), 1, fpImageFile);  
		bPixVal = ipImage->ucpImageData[i*ipImage->iWidth*3+j*3+1];  
		fwrite(&bPixVal, sizeof(BYTE), 1, fpImageFile);  
		bPixVal = ipImage->ucpImageData[i*ipImage->iWidth*3+j*3+2];  
		fwrite(&bPixVal, sizeof(BYTE), 1, fpImageFile);  
	    }  
	    if (iOffset!=0)  
	    {  
		for (j=0; j<iOffset; j++)  
		{  
		    bPixVal = 0;  
		    fwrite(&bPixVal, sizeof(BYTE), 1, fpImageFile);  
		}	 
	    }  
	}
    }

    fclose(fpImageFile);

    return TRUE;
}

int main(int argc, char *argv[])
{
    char *cpImagePath;
    char *cpSaveImagePath;
    Image *ipImage;

    if(argc != 3)
    {
	perror("argument error");
        exit(1);
    }

    cpImagePath = argv[1];
    cpSaveImagePath = argv[2];

    ipImage = loadImage(cpImagePath);

    BOOL flag = saveImage(cpSaveImagePath, ipImage);
    if(flag)
    {
	fprintf(stdout, "save image success\n");
    }

    return 0;
}
