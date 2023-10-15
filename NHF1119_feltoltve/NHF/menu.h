#ifndef MENU_H
#define MENU_H

typedef enum MainMenu{
    exitprog,
    contrast,
    brightness,
    saturation,
    blur,
    edges
}MainMenu;

typedef enum SubMenu{
    further_modification,
    saveas,
    save
}SubMenu;



void displaymain();
enum MainMenu selectmain();
void displaysubmenu();
enum SubMenu selectsubmenu();

#endif


