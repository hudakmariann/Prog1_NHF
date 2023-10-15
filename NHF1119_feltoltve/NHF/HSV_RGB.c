#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "readimage.h"
#include "debugmalloc.h"
#include "HSV_RGB.h"



double minRGB(double r, double g, double b){
    double rgb[3] = {r,g,b};
    double min = 255;
    for (int i = 0; i<3; ++i){
        if (rgb[i] < min)
            min = rgb[i];
    }
    return min;
}

double maxRGB(double r, double g, double b){
    double rgb[3] = {r,g,b};
    double max = 0;
    for (int i = 0; i<3; ++i){
        if (rgb[i] > max)
            max = rgb[i];
    }
    return max;
}


//az rgb-hsv es hsv-rgb konverzio algoritmusa adaptalva a https://www.geeksforgeeks.org/program-change-rgb-color-model-hsv-color-model/?tab=article -rol
HSV** RGBtoHSV(const ImageParams*  imgdata, const PixelData**  matrix){
    double min, max, diff;
    HSV** HSVmatrix;
    double r, g, b;

    /* foglalás */
    debugmalloc_max_block_size(imgdata->w * imgdata->h * sizeof(HSV)); //ha ezt nem allitom be, a debugmalloc sir mar egy 512*512-es keptol is

    HSVmatrix = (HSV**) malloc(imgdata->h * sizeof(HSV*));
    HSVmatrix[0] = (HSV*) malloc(imgdata->w * imgdata->h * sizeof(HSV));

    for (int y = 1; y < imgdata->h; ++y)
        HSVmatrix[y] = HSVmatrix[0] + y * imgdata->w;

    for (int i = 0; i < imgdata->h; i++){
        for (int j = 0; j < imgdata->w; j++){

            r = (double)matrix[i][j].r/256;
            g = (double)matrix[i][j].g/256;
            b = (double)matrix[i][j].b/256;

            max = maxRGB(r,g,b);
            min = minRGB(r,g,b);
            diff = max - min;

            if (max == 0)
                HSVmatrix[i][j].s = 0;
            else
                HSVmatrix[i][j].s = diff / max;

            if (diff == 0){
                HSVmatrix[i][j].h = 0;
                HSVmatrix[i][j].s = 0;
            }

            if (max == r)
                     HSVmatrix[i][j].h = (g - b) /diff;
            else
            if (max == g)
                HSVmatrix[i][j].h = 2 + (b - r) / diff;
            else
                HSVmatrix[i][j].h = 4 + (r - g) / diff;

            if (HSVmatrix[i][j].h < 0)
                HSVmatrix[i][j].h=0;
            HSVmatrix[i][j].h /= 6;
            HSVmatrix[i][j].v = max;
        }//end for j
    }//end for i
    return HSVmatrix;
}



void HSVtoRGB(ImageParams const *imgdata,  const HSV **HSVmatrix,  PixelData** matrix){
    //double max, min;
    double h, s, v;
    double r, g, b;

    for (int i = 0; i < imgdata->h; i++){
        for (int j = 0; j < imgdata->w; j++){

    // RGB-HSV konverziohoz hasznalt forras: https://lodev.org/cgtutor/color.html

            h = HSVmatrix[i][j].h;
            s = HSVmatrix[i][j].s;
            v = HSVmatrix[i][j].v;

            if(s == 0)
                r = g = b = v;
            else
            {
                float f, p, q, t;
                int i;
                h *= 6;
                i = (int)(floor(h));
                f = h - i;
                p = v * (1 - s);
                q = v * (1 - (s * f));
                t = v * (1 - (s * (1 - f)));
                switch(i)
                {
                    case 0:{
                        r = v;
                        g = t;
                        b = p;
                        break;
                    }
                    case 1: {
                        r = q;
                        g = v;
                        b = p;
                        break;
                    }
                    case 2: {
                        r = p;
                        g = v;
                        b = t;
                        break;
                    }
                    case 3: {
                        r = p;
                        g = q;
                        b = v;
                        break;
                    }
                    case 4: {
                        r = t;
                        g = p;
                        b = v;
                        break;
                    }
                    case 5: {
                        r = v;
                        g = p;
                        b = q;
                        break;
                    } //end case
                } //end switch
            } // end else

            if (r < 0) r = 0;
            if (r>1)  r = 1;
            if (g < 0) g = 0;
            if (g>1)  g = 1;
            if (b < 0) b = 0;
            if (b>1)  b = 1;


            matrix[i][j].r = (int)(r * 255);
            matrix[i][j].g = (int)(g * 255);
            matrix[i][j].b = (int)(b * 255);


            }//end for j
        }//end for i
//printf("***********************************RGBtoHSV***************************\n");
}

void HSVmatrix_kiir(ImageParams const *imgdata, HSV  **HSVmatrix){
    for (int i = 0; i < imgdata->h; i++){
        for (int j = 0; j < imgdata->w; j++){
            for (int k = 0; k<3; k++){
                 switch (k%3) {
                     case 0: {
                        printf(" [%d][%d].h=%.2f ",i, j, HSVmatrix[i][j].h);
                        break;
                     }
                     case 1: {
                        printf(" [%d][%d].s=%.2f ", i, j, HSVmatrix[i][j].s);
                        break;
                     }
                     case 2: {
                        printf(" [%d][%d].v=%.2f ", i, j, HSVmatrix[i][j].v);
                        break;
                     }
                }//end case
            }// end for k
            printf("\n");
        }//end for j
    printf ("\n");
    }//end for i

    printf("\n");
    printf(" a %d. sor %d-edik pixelenek h erteke = %.2f \n", 117, 51, HSVmatrix[117][51].h);
    //free(matrix[0]);
    //free(matrix);
}


