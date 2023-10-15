#ifndef CONTROL_H
#define CONTROL_H

void filenev_beker(char* filename);
bool saveimage(ImageParams *imgdata, PixelData **matrix, char *filename);
int processimage(ImageParams *imgdata, PixelData **matrix, char* filename);


#endif
