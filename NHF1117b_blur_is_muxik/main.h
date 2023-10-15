#ifndef MAIN_H
#define MAIN_H

typedef enum MainMenu{
    exitprog,
    contrast,
    brightness,
    blur,
    edges
}MainMenu;

typedef enum SubMenu{
    quit,
    saveas,
    save
}SubMenu;

void displaymain();
enum MainMenu selectmain();
//int main();


#endif // MAIN_H


