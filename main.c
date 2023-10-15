#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#include "menu.h"
#include "readimage.h"
#include "HSV_RGB.h"
//#include "debugmalloc.h"
#include "writeimage.h"
#include "filters.h"
#include "control.h"

int main(){
    PixelData **matrix;
    short readfileresult;
    ImageParams imgdata;
    char filename[100];
    bool onemore = false;
    char yesno;
    int processcompleted = 1;


    do{
        bool finished = false;
        filenev_beker(filename);

        matrix = readfile(filename, &readfileresult, &imgdata);
        if (matrix != NULL)
            printf("Image loaded successfully\n");
        else{
            printf("ERROR loading image\n");
            printf("errorcode = %d\n", readfileresult);
            return 1;
        }

        while(!finished){
            processcompleted = processimage(&imgdata, matrix, filename);
            if (processcompleted != 0){
                    printf("ERROR: Image processing failed.\n");
                return 2;
            }
            finished = saveimage(&imgdata, matrix, filename);
        }

        free(matrix[0]);
        free(matrix);

        printf("Would you like to process another image? (y/n)\n");
        scanf(" %c", &yesno); //szokoz kell, kulonben atugorja. Az elozo entert karakternek veszi!


        if ((yesno == 'y') || (yesno == 'Y'))
            onemore = true;
        else
            onemore = false;

    }while(onemore);

    printf("end.\n");
    return 0;
}
