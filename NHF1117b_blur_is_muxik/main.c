#include <stdio.h>
#include <stdlib.h>


#include "main.h"

#include "readimage.h"
#include "HSV_RGB.h"
#include "debugmalloc.h"

#include "writeimage.h"
#include "filters.h"


void displaymain(){
    printf("Please choose an option!\n");
    printf("0 EXIT\n");
    printf("1 Modify contrast\n");
    printf("2 Modify brightness\n");
    printf("3 Blur image\n");
    printf("4 Find edges\n");
}

enum MainMenu selectmain(){
    int selected;
    scanf("%d", &selected);
     while (selected < 0 || selected > 4){
        printf("Error: you selected %d - no such option.\nPlease select 0..4 from the menu below\n", selected);
        displaymain();
        scanf("%d", &selected);
     }
     return selected;
}

int main(){
    enum MainMenu option;
    short readfileresult;
    ImageParams imgdata;
    //char *filename = "C:\\Users\\terve\\Documents\\Mariann_BME\\Prog_lab\\NHF_V1\\NHFV1\\bin\\Debug\\auto2.ppm";
    char *filename = "papagaj.ppm";
    PixelData **matrix;
    HSV **HSVmatrix;
    HSV ** filteredHSV;
    PixelData **filteredmatrix;

    displaymain();
    option = selectmain();
    printf("The selected option is: %d\n", option);
    matrix = readfile(filename, &readfileresult, &imgdata);
    if (matrix != NULL){
        printf("Image loaded successfully\n");


        HSVmatrix = RGBtoHSV(&imgdata, matrix);
        if (HSVmatrix == NULL){
                printf ("Error: HSV conversion failed!\n");
                return 2;
        }

        //setcontrast(&imgdata, HSVmatrix);
        filteredmatrix = blurimage(&imgdata, matrix);


        //HSVtoRGB(&imgdata, filteredHSV, matrix);

        //matrix_kiir(&imgdata, matrix);  //nyomkovetes celjabol a kepernyore is kiiratoma matrixot szukseg eseten
        writefile("PROBA.ppm", &imgdata, filteredmatrix);
        //matrix_kiir(&imgdata, matrix);  //nyomkovetes celjabol a kepernyore is kiiratoma matrixot szukseg eseten

        free(matrix[0]);
        free(matrix);

    }
    else{
        printf("ERROR loading image\n");
        printf("errorcode = %d\n", readfileresult);
        return 1;
    }

        free(HSVmatrix[0]);
        free(HSVmatrix);
        free(filteredmatrix[0]);
        free(filteredmatrix);
        //free(filteredHSV[0]);
        //free(filteredHSV);
printf("end.\n");
    return 0;
}
