#ifndef BRIGHTNESS_H
#define BRIGHTNESS_H

void setbrightness(ImageParams const *imgdata, HSV  **HSVmatrix);
void setsaturation(ImageParams const *imgdata, HSV  **HSVmatrix);

double maxval(ImageParams const *imgdata, HSV const **HSVmatrix);
double minval(ImageParams const *imgdata, HSV const **HSVmatrix);

#endif
