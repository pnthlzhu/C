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
	return NULL;
    }

    tpBmpImage = (Image*)malloc(sizeof(Image));
    fread(&tBmpFileHeader, sizeof(BitMapFileHeader), 1, fpBmpFile);
    if(tBmpFileHeader.usType == 0x4D42)
    {
	fprintf(stdout, "this is a bmp file!\n");
	fprintf(stdout, "===================\n");
	fprintf(stdout, "bmp文件头信息:\n");
	fprintf(stdout, "文件大小:%ldB\n", tBmpFileHeader.ulSize);
	fprintf(stdout, "保留字1:%d\n", tBmpFileHeader.usReserved1);
	fprintf(stdout, "保留字2:%d\n", tBmpFileHeader.usReserved2);
	fprintf(stdout, "位图数据偏移字节数:%ldB\n", tBmpFileHeader.ulOffBits);

	fread(&tBmpInfoHeader, sizeof(BitMapInfoHeader), 1, fpBmpFile);
	fprintf(stdout, "===================\n");
	fprintf(stdout, "bmp位图头信息:\n");
	fprintf(stdout, "结构体长度:%ld\n", tBmpInfoHeader.ulSize);
	fprintf(stdout, "位图宽度:%ld\n", tBmpInfoHeader.lWidth);
	fprintf(stdout, "位图高度:%ld\n", tBmpInfoHeader.lHeight);
	fprintf(stdout, "位图平面数:%d\n", tBmpInfoHeader.usPlanes);
	fprintf(stdout, "颜色位数:%d\n", tBmpInfoHeader.usBitCount);
	fprintf(stdout, "压缩方式:%ld\n", tBmpInfoHeader.ulCompression);
	fprintf(stdout, "实际位图数据占用的字节数:%ld\n", tBmpInfoHeader.ulSizeImage);
	fprintf(stdout, "X方向分辨率:%ld\n", tBmpInfoHeader.lXPelsPerMeter);
	fprintf(stdout, "Y方向分辨率:%ld\n", tBmpInfoHeader.lYPelsPerMeter);
	fprintf(stdout, "使用的颜色数:%ld\n", tBmpInfoHeader.ulClrUsed);
	fprintf(stdout, "重要颜色数:%ld\n", tBmpInfoHeader.ulClrImportant);

	if(tBmpInfoHeader.usBitCount == 8)
	{
	    fprintf(stdout, "该文件有调色板，即该位图为非真彩色\n");
	    iChannels = 1;
	    iWidth = tBmpInfoHeader.lWidth;
	    iHeight = tBmpInfoHeader.lHeight;
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
	else if(tBmpInfoHeader.usBitCount == 24)
	{
	    fprintf(stdout, "该位图为真彩色\n");
	    iChannels = 3;
            iWidth = tBmpInfoHeader.lWidth;
            iHeight = tBmpInfoHeader.lHeight;

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

int main(int argc, char *argv[])
{
    char *cpImagePath;

    if(argc != 2)
    {
	perror("argument error");
        exit(1);
    }

    cpImagePath = argv[1];

    loadImage(cpImagePath);
    return 0;
}
