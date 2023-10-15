#include <stdio.h>
#include <stdlib.h>


#include "menu.h"

#include "readimage.h"
#include "HSV_RGB.h"
//#include "debugmalloc.h"

#include "writeimage.h"
#include "filters.h"




void displaymain(){
    printf("Please choose an option!\n");
    printf("0 EXIT\n");
    printf("1 Modify contrast\n");
    printf("2 Modify brightness\n");
    printf("3 Modify saturation\n");
    printf("4 Blur image\n");
    printf("5 Find edges\n");
}

enum MainMenu selectmain(){
    int selected;
    scanf("%d", &selected);
     while (selected < 0 || selected > 5){
        printf("Error: you selected %d - no such option.\nPlease select 0..5 from the menu below\n", selected);
        displaymain();
        scanf("%d", &selected);
     }
     return selected;
}

void displaysubmenu(){
    printf("Please choose an option!\n");
    printf("0 further modification \n");
    printf("1 save as..\n");
    printf("2 save (overwrite original image)\n");

}


enum SubMenu selectsubmenu(){
    int selected;
    scanf("%d", &selected);
     while (selected < 0 || selected > 2){
        printf("Error: you selected %d - no such option.\nPlease select 0..2 from the menu below\n", selected);
        displaysubmenu();
        scanf("%d", &selected);
     }
     return selected;
}



