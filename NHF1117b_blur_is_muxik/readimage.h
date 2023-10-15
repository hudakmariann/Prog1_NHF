#ifndef READIMAGE_H
#define READIMAGE_H

typedef struct PixelData{
    short r, g, b;
}PixelData;

typedef struct ImageParams{
    int w; //width
    int h; //height
    int d; //depth
}ImageParams;

void readfilename(char *filename);
PixelData** readfile(char *filename, short* errorcode, ImageParams *imgdata);



#endif
