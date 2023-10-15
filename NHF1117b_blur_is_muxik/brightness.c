#include <stdio.h>
#include <stdlib.h>

#include "readimage.h"
#include "HSV_RGB.h"
#include "brightness.h"
#include "debugmalloc.h"


void setbrightness(ImageParams const *imgdata, HSV  **HSVmatrix){
    float percent;
    printf("Please type in the factor of brightness change between -100 and +100.\n");
    scanf("%f", &percent);
    percent /=100;


     for (int i = 0; i < imgdata->h; i++){
        for (int j = 0; j < imgdata->w; j++){
        HSVmatrix[i][j].v = HSVmatrix[i][j].v*(1+percent);

        }//end for j
    }//end for i
}


void setsaturation(ImageParams const *imgdata, HSV  **HSVmatrix){
    float percent;
    printf("Please type in the factor of saturation change between -100 and +100.\n");
    scanf("%f", &percent);
    percent /=100;
     for (int i = 0; i < imgdata->h; i++){
        for (int j = 0; j < imgdata->w; j++){
        HSVmatrix[i][j].s = HSVmatrix[i][j].s*(1+percent);
        }//end for j
    }//end for i
}



double maxval(ImageParams const *imgdata, HSV  const **HSVmatrix){
     double max = 0.0;
     for (int i = 0; i < imgdata->h; i++){
        for (int j = 0; j < imgdata->w; j++){
        if (HSVmatrix[i][j].v > max)
             max = HSVmatrix[i][j].v;
        }//end for j
    }//end for i
    return max;
}

double minval(ImageParams const *imgdata, HSV const **HSVmatrix){
    double min = 255.0;
     for (int i = 0; i < imgdata->h; i++){
        for (int j = 0; j < imgdata->w; j++){
        if (HSVmatrix[i][j].v < min)
             min = HSVmatrix[i][j].v;
        }//end for j
    }//end for i
    return min;
}

void setcontrast(ImageParams const *imgdata, HSV  **HSVmatrix){
    float percent;
    double max = maxval(imgdata, HSVmatrix);
    double min = minval(imgdata, HSVmatrix);
    printf("max = %f\n", max);
    printf("min = %f\n", min);
    printf("Please type in the factor of contrast change between -100 and +100.\n");
    scanf("%f", &percent);
    percent /=100;
     for (int i = 0; i < imgdata->h; i++){
        for (int j = 0; j < imgdata->w; j++){
            HSVmatrix[i][j].v = ((HSVmatrix[i][j].v-min)*(((1+percent)*max)/(max-min))+min*(1-percent));
        }//end for j
    }//end for i
}
