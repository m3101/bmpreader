#include "bmpreader.h"
#include <stdio.h>
#include <stdlib.h>

/*
Copyright (c) 2020 Amélia O. F. da S.
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

long int sizebmp(const char* fname)
{
    FILE* fp=fopen(fname,"r");
    char c;
    int sx,sy;
    if(!fp)return 0;
    c=fgetc(fp);
    if(c!='B')return 0;
    c=fgetc(fp);
    if(c!='M')return 0;
    fseek(fp,0x12,SEEK_SET);
    ((char*)&sx)[0]=fgetc(fp);
    ((char*)&sx)[1]=fgetc(fp);
    ((char*)&sx)[2]=fgetc(fp);
    ((char*)&sx)[3]=fgetc(fp);
    ((char*)&sy)[0]=fgetc(fp);
    ((char*)&sy)[1]=fgetc(fp);
    ((char*)&sy)[2]=fgetc(fp);
    ((char*)&sy)[3]=fgetc(fp);  
    return (((long int)sx)<<32)+sy;
}

char* readbmp(const char* fname)
{
    FILE* fp=fopen(fname,"r");
    char* image=NULL;
    char c;
    int x,y,sx,sy,start;
    if(!fp)return NULL;
    c=fgetc(fp);
    if(c!='B')return NULL;
    c=fgetc(fp);
    if(c!='M')return NULL;
    /*First we check whether it is a 32bit image or not (we'll use the 'start' int so we don't waste memory)*/
    fseek(fp,0x1C,SEEK_SET);
    ((char*)&start)[0]=fgetc(fp);
    ((char*)&start)[1]=fgetc(fp);
    ((char*)&start)[2]=0;
    ((char*)&start)[3]=0;
    if(start!=32)return NULL;
    hwfromsize(sizebmp(fname),sx,sy);
    /*Then we find the start of the stream*/
    fseek(fp,0x0A,SEEK_SET);
    ((char*)&start)[0]=fgetc(fp);
    ((char*)&start)[1]=fgetc(fp);
    ((char*)&start)[2]=fgetc(fp);
    ((char*)&start)[3]=fgetc(fp);
    /*Then we allocate the buffer and read the image*/
    image=malloc(4*sx*sy);
    fseek(fp,start,SEEK_SET);
    for(y=0;y<sy;y++)
        for(x=0;x<sx;x++)
            for(c=0;c<4;c++)
                image[(3-c)+4*(x+(sx*(sy-(y+1))))]=fgetc(fp);
    fclose(fp);
    return image;
}