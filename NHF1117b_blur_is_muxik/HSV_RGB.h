#ifndef HSV_RGB_H
#define HSV_RGB_H


typedef struct HSV{
    double h, s, v;
}HSV;


double minRGB(double r, double g, double b);
double maxRGB(double r, double g, double b);

HSV** RGBtoHSV(const ImageParams*  imgdata, const PixelData**   matrix);
void HSVtoRGB(ImageParams const *imgdata, HSV const **HSVmatrix, PixelData** matrix);


#endif
