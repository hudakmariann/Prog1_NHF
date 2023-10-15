#ifndef FILTERS_H
#define FILTERS_H

void findedges(ImageParams const *imgdata, HSV  **HSVmatrix);
void blurimage(ImageParams const *imgdata, PixelData  **matrix);



#endif

