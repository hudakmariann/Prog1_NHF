#ifndef BRIGHTNESS_H
#define BRIGHTNESS_H

float getpercent();

void setbrightness(ImageParams const *imgdata, HSV  **HSVmatrix);
void setsaturation(ImageParams const *imgdata, HSV  **HSVmatrix);

double maxval(ImageParams const *imgdata, const HSV  **HSVmatrix);
double minval(ImageParams const *imgdata, const HSV  **HSVmatrix);

void setcontrast(ImageParams const *imgdata, HSV  **HSVmatrix);

#endif
