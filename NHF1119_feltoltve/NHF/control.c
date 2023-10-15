#include <stdbool.h>
#include <string.h>


#include "menu.h"
#include "readimage.h"
#include "HSV_RGB.h"
#include "brightness.h"
#include "debugmalloc.h"
#include "writeimage.h"
#include "filters.h"
#include "control.h"

void filenev_beker(char* filename){
    char* ppm = NULL;
    char const extension[4] = ".ppm";

    do{
    printf("Please type in the filename of the image!\n");
    scanf(" %s", filename);
    printf("FILENAME = %s\n", filename);
    ppm = strstr(filename, extension);
    if (ppm == NULL)
        printf("The file extension is not *.ppm!\n");
    }while (ppm == NULL);
}


bool saveimage(ImageParams *imgdata, PixelData **matrix, char *filename){
    enum SubMenu suboption;
    char yesno;

    displaysubmenu();

    suboption = selectsubmenu();
    printf("The selected option is: %d\n", suboption);

    switch(suboption){
        case 0:{
            writefile("TEST.ppm", imgdata, matrix); //egy biztonsagi mentest a teszt kedveert ebben az esetben is csinalok
           // processimage(imgdata, matrix, filename);
            return false;

        }
        case 1: {
            filenev_beker(filename);
            writefile(filename, imgdata, matrix);
            break;;
        }
        case 2: {
            printf("WARNING: are you sure you want to overwrite %s? (y/n) \n", filename);
            scanf(" %c", &yesno); //szokoz kell, kulonben atugorja. Az elozo entert karakternek veszi!
            if ((yesno == 'y') || (yesno == 'Y'))
                writefile(filename, imgdata, matrix);
            else{
                filenev_beker(filename);
                writefile(filename, imgdata, matrix);
            }
            break;
        }
    }
return true;
}


int processimage(ImageParams *imgdata, PixelData **matrix, char* filename){
    enum MainMenu option;
    HSV **HSVmatrix;

    displaymain();
    option = selectmain();
    printf("The selected option is: %d\n", option);

    switch(option){
        case 0:{
            free(matrix[0]);
            free(matrix);
            exit(0);
        }
        case 1: {
            HSVmatrix = RGBtoHSV(imgdata, matrix);
            if (HSVmatrix == NULL){
                printf ("Error: HSV conversion failed!\n");
                return 2;
            }
            setcontrast(imgdata, HSVmatrix);
            HSVtoRGB(imgdata, HSVmatrix, matrix);
            free(HSVmatrix[0]);
            free(HSVmatrix);
            break;
        }
        case 2: {
            HSVmatrix = RGBtoHSV(imgdata, matrix);
            if (HSVmatrix == NULL){
                printf ("Error: HSV conversion failed!\n");
                return 2;
            }
            setbrightness(imgdata, HSVmatrix);
            HSVtoRGB(imgdata, HSVmatrix, matrix);
            free(HSVmatrix[0]);
            free(HSVmatrix);
            break;
        }
        case 3: {
            HSVmatrix = RGBtoHSV(imgdata, matrix);
            if (HSVmatrix == NULL){
                printf ("Error: HSV conversion failed!\n");
                return 2;
            }
            setsaturation(imgdata, HSVmatrix);
            HSVtoRGB(imgdata, HSVmatrix, matrix);
            free(HSVmatrix[0]);
            free(HSVmatrix);
            break;
        }
        case 4: {
            blurimage(imgdata, matrix);
            break;
        }
        case 5: {
            HSVmatrix = RGBtoHSV(imgdata, matrix);
            if (HSVmatrix == NULL){
                printf ("Error: HSV conversion failed!\n");
                return 2;
            }
            findedges(imgdata, HSVmatrix);
            HSVtoRGB(imgdata, HSVmatrix, matrix);
            free(HSVmatrix[0]);
            free(HSVmatrix);
            break;
        }
    }//end switch

    return 0;
}



