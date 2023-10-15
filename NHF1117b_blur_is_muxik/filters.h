#ifndef FILTERS_H
#define FILTERS_H

HSV** findedges(ImageParams const *imgdata, HSV  **HSVmatrix);
PixelData** blurimage(ImageParams const *imgdata, PixelData  **matrix);
#endif

