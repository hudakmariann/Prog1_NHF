#include <stdio.h>
#include <stdlib.h>

#include "readimage.h"
#include "debugmalloc.h"

void readfilename(char *filename){
    printf("Please type in the filename of the image to modify. it should be a *.ppm file.");
    scanf("%s", filename);
}


PixelData** readfile(char *filename, short* errorcode, ImageParams *imgdata){

    FILE *inputfile;
    char c;
    char filetype[3];
    char size[10];
    char depth[5];
    PixelData **matrix;
    unsigned char p;
    short v;

    //word tipus: 1 byte a merete pont, lehet, hogy azt jobb lenne hasznalni --nem biztos!

    inputfile = fopen(filename, "rb");
    printf("The selected file is %s\n", filename);
    if (inputfile == NULL){
        printf("Error opening file\n");
        *errorcode = 1;
        return NULL;
    }
    else
        printf("File opened successfully\n");

   for (int i = 0; i<3; ++i){
       fread(&filetype[i], sizeof(char), 1, inputfile);
   }
   if (filetype[0] != 'P' || filetype[1] !='6'){
        printf("Error: not a valid *.ppm file (identifier = %c%c)\n", filetype[0], filetype[1]);
        *errorcode = 2;
        return NULL;
    }
    else
        printf("Successful identification as valid *.ppm file (identifier = %c%c)\n", filetype[0], filetype[1]);

    //comment kiszurese
    fread(&c, sizeof(char), 1, inputfile);
    //printf("c = %c",c);
    if (c == '#'){
        while (c != '\n')
            fread(&c, sizeof(char), 1, inputfile);
    }

// kep meretenek beolvasasa
     size[0] = c; //ha nem volt komment, a kep  merete mar itt kezodik, ezert be kell irni a size tombbe. Ha volt, akkor a \n kerul a size tomb elejere, de azt a sscanf ugysem fogja szamkent beolvasni, ugyhogy nem baj.
     fread(&c, sizeof(char), 1, inputfile);
     if (isdigit(c)){
        size[1] = c;
        int i = 2;
        while (c != '\n'){
        //while (!isspace(c)){
            fread(&c, sizeof(char), 1, inputfile);
            size[i] = c;
            i++;
        }

    sscanf(size, "%d %d", &imgdata->w, &imgdata->h);

    printf("width = %d, height = %d\n", imgdata->w, imgdata->h);
    }
    else{
        printf("Error: file contains invalid resolution data\n");
        *errorcode = 3;
        return NULL;
    }

    //bitmelyseg beolvasasa
     fread(&c, sizeof(char), 1, inputfile);
     if (isdigit(c)){
        depth[0] = c;
        int j = 1;
        while (c != '\n'){
            fread(&c, sizeof(char), 1, inputfile);
            depth[j] = c;
            j++;
        }
        sscanf(depth, "%d", &imgdata->d);
        printf("bitdepth = %d\n", imgdata->d);
    }
    else{
        printf("Error: file contains invalid color data\n");
        *errorcode = 4;
        return NULL;
    }

    //pixel adatok beolvasasa a heap-re

/* foglalás */
    debugmalloc_max_block_size(imgdata->w * imgdata->h * sizeof(PixelData));

    matrix = (PixelData**) malloc(imgdata->h * sizeof(PixelData*));
    matrix[0] = (PixelData*) malloc(imgdata->w * imgdata->h * sizeof(PixelData));
    for (int y = 1; y < imgdata->h; ++y)
        matrix[y] = matrix[0] + y * imgdata->w;


    for (int i = 0; i < imgdata->h; i++){
        for (int j = 0; j < imgdata->w; j++){
            for (int k = 0; k<3; k++){
                 fread(&p,  sizeof(unsigned char), 1, inputfile) ;
                 v = (short) p;
                 switch (k%3) {
                     case 0: {
                        matrix[i][j].r = v;
                        break;
                     }
                     case 1: {
                        matrix[i][j].g = v;
                        break;
                     }
                     case 2: {
                        matrix[i][j].b = v;
                        break;
                     }
                }//end case
            }// end for k
        }//end for j
    }//end for i

fclose(inputfile);
errorcode = 0;

return matrix;
}
