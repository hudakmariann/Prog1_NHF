#ifndef WRITEIMAGE_H
#define WRITEIMAGE_H


void matrix_kiir(ImageParams const *imgdata, PixelData  **matrix);
void writefile(char const *filename, ImageParams const *imgdata, PixelData  **matrix);

#endif // WRITEIMAGE_H
