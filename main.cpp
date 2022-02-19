#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Gluttonous_Snake.h"

int main() {
    COORD coord;
    HANDLE handler = GetStdHandle(STD_OUTPUT_HANDLE);
    bool flag = true;
    while(true) {
        std::cout << "选择游戏模式:" << std::endl;
        int mode = 0;
        std::cout << "> 可穿墙      不可穿墙:" << std::endl;
        coord.X = 0;
        coord.Y = 16;
        if(flag) {
            coord.Y = 1;
            flag = false;
        }
        while(true) {
            if(kbhit()) {
                if(getch() == 13) break;
                int key = getch();
                if(key == 75) mode = std::max(mode-1, 0);
                else if(key == 77) mode = std::min(mode+1, 1);
                SetConsoleCursorPosition(handler, coord);
                std::cout.put(' ');
                if(mode == 0) coord.X = 0;
                else coord.X = 12;
                SetConsoleCursorPosition(handler, coord);
                std::cout.put('>');
            }
            Sleep(10);
        }
        system("cls");
        Gluttonous_Snake game(15,10);
        game.setMode(mode);
        game.start();
        std::cout << "游戏结束!" << std::endl;
        std::cout << "是否继续?(Y/N)" << std::endl;
        char ch = std::cin.get();
        while(std::cin.get() != '\n');
        if(ch != 'Y' && ch != 'y') break;
    }
    return 0;
}