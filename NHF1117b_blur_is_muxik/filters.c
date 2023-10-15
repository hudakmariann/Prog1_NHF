#include <stdio.h>
#include <stdlib.h>

#include "readimage.h"
#include "HSV_RGB.h"
#include "brightness.h"
#include "debugmalloc.h"
#include "filters.h"


HSV** findedges(ImageParams const *imgdata, HSV  **HSVmatrix){
    double surround[8];
    double szele = 1;

    HSV** filteredHSV = (HSV**) malloc(imgdata->h * sizeof(HSV*));
    filteredHSV[0] = (HSV*) malloc(imgdata->w * imgdata->h * sizeof(HSV));
    for (int y = 1; y < imgdata->h; ++y)
        filteredHSV[y] = filteredHSV[0] + y * imgdata->w;


    if (filteredHSV == NULL)
        return NULL;

    for (int y = 0; y < imgdata->h; y++){
        for (int x = 0; x < imgdata->w; x++){

            if ((y != 0) && (x != 0) && (y != imgdata->h-1) && (x != imgdata->w-1) ){
                surround[0] = HSVmatrix[y-1][x-1].v;
                surround[1] = HSVmatrix[y-1][x].v;
                surround[2] = HSVmatrix[y-1][x+1].v;
                surround[3] = HSVmatrix[y][x-1].v;
                surround[4] = HSVmatrix[y][x+1].v;
                surround[5] = HSVmatrix[y+1][x-1].v;
                surround[6] = HSVmatrix[y+1][x].v;
                surround[7] = HSVmatrix[y+1][x+1].v;
            }
            else
                for (int i = 0; i < 8; i++) //kep szelenek lekezelese a tulindexeles elkerulese vegett
                    surround[i] = szele;

            double sum = 0;
            for (int i = 0; i < 8; i++){
                sum+=surround[i];
            }
            filteredHSV[y][x].h = HSVmatrix[y][x].h;
            filteredHSV[y][x].s = 0;//HSVmatrix[y][x].s;
            filteredHSV[y][x].v = (-8)*HSVmatrix[y][x].v + sum;

        }//end for x
    }//end for y
    return filteredHSV;
}

PixelData** blurimage(ImageParams const *imgdata, PixelData  **matrix){
    int filtersize;

    double szele = 127;
    int kozepe;
    double centerweight;

    printf("Please provide the factor of blur between 1 and 100.\n");
    scanf("%d", &filtersize);
    if (filtersize < 3)
        filtersize = 3;
    else if (filtersize > 100)
        filtersize = 101;
    if (filtersize%2 == 0)
        filtersize++;

    kozepe = (filtersize-1)/2 ;
    centerweight = (filtersize+1)/2;


    PixelData** filteredIMG = (PixelData**) malloc(imgdata->h * sizeof(PixelData*));
    filteredIMG[0] = (PixelData*) malloc(imgdata->w * imgdata->h * sizeof(PixelData));
    for (int y = 1; y < imgdata->h; ++y)
        filteredIMG[y] = filteredIMG[0] + y * imgdata->w;
    if (filteredIMG == NULL)
        return NULL;

    double** filter = (double**) malloc(filtersize * sizeof(double*));
    filter[0] = (double*) malloc(filtersize * filtersize * sizeof(double));
    for (int y = 1; y < filtersize; ++y)
        filter[y] = filter[0] + y * filtersize;

    double filtersum = 0;
    for (int i = 0; i < filtersize; i++){
        for (int j = 0; j < filtersize; j++){
                filter[i][j] = centerweight - ((abs(kozepe-i))+ abs(kozepe-j));
            if (filter[i][j]< 1)
                filter[i][j] = 1;
            //printf("%2.f ", filter[i][j]);
            filtersum += filter[i][j];
        }
    //printf("\n");
    }


    printf("Processing 0%% ");
    for (int y = 0; y < imgdata->h; y++){
        for (int x = 0; x < imgdata->w; x++){

            PixelData** window = (PixelData**) malloc(filtersize * sizeof(PixelData*));
            window[0] = (PixelData*) malloc(filtersize * filtersize * sizeof(PixelData));
            for (int y = 1; y < filtersize; ++y)
                window[y] = window[0] + y * filtersize;


            double windowsum_r = 0;
            double windowsum_g = 0;
            double windowsum_b = 0;
            for (int i = 0; i< filtersize; ++i){
                for (int j = 0; j< filtersize; ++j){
                    if ((y+i > imgdata->h-1) || (x+j > imgdata->w-1)){
                        window[i][j].r = szele;
                        window[i][j].g = szele;
                        window[i][j].b = szele;
                    }
                    else{
                        window[i][j].r = matrix[y+i][x+j].r;
                        window[i][j].g = matrix[y+i][x+j].g;
                        window[i][j].b = matrix[y+i][x+j].b;
                    }
                windowsum_r += window[i][j].r*filter[i][j];
                windowsum_g += window[i][j].g*filter[i][j];
                windowsum_b += window[i][j].b*filter[i][j];
               // printf("%.2f ",  window[i][j] );

                }// end for j
               // printf("\n");
            }//end for i
        /*if (windowsum_h/filtersum > 0.99)
            filteredHSV[y][x].h = 0.99;
        else if (windowsum_h/filtersum < 0.01)
            filteredHSV[y][x].h = 0.01;
        else*/
        filteredIMG[y][x].r =  windowsum_r/filtersum;
        filteredIMG[y][x].g =  windowsum_g/filtersum;
        filteredIMG[y][x].b = windowsum_b/filtersum;
        free(window[0]);
        free(window);
       // printf("i j ciklus vege\n");
        }//end for x
        if (y%20 == 0)
            printf("|");
    }//end for y
    printf("100%%\nReady.\n");
    free(filter[0]);
    free(filter);

    return filteredIMG;
}
