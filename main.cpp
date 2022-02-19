#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Gluttonous_Snake.h"

int main() {
    COORD coord;
    HANDLE handler = GetStdHandle(STD_OUTPUT_HANDLE);
    bool flag = true;
    while(true) {
        std::cout << "ѡ����Ϸģʽ:" << std::endl;
        int mode = 0;
        std::cout << "> �ɴ�ǽ      ���ɴ�ǽ:" << std::endl;
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
        std::cout << "��Ϸ����!" << std::endl;
        std::cout << "�Ƿ����?(Y/N)" << std::endl;
        char ch = std::cin.get();
        while(std::cin.get() != '\n');
        if(ch != 'Y' && ch != 'y') break;
    }
    return 0;
}