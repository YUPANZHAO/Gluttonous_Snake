#include "Gluttonous_Snake.h"

void Gluttonous_Snake::modifyMap(int x, int y, const BLOCK & ch) {
    COORD coord;
    coord.X = y * 2;
    coord.Y = x;
    HANDLE handler = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handler, coord);
    map[x][y] = ch;
    std::cout << ch << std::flush;
}

void Gluttonous_Snake::move() {
    static int dire[4][2] = {-1, 0, 0, 1, 1, 0, 0, -1};
    int nx = head->posx + dire[moveDire][0];
    int ny = head->posy + dire[moveDire][1];
    // 穿墙后的坐标
    if(MODE == CLASSICS) {
        nx = (nx - 1 + HEIGHT) % HEIGHT + 1;
        ny = (ny - 1 + WIDTH) % WIDTH + 1;
    }
    // 判断是否撞墙或撞身体
    if(map[nx][ny] == WALL_BLOCK
    || (map[nx][ny] == BODY_BLOCK && !(nx == tail->posx && ny == tail->posy))) {
        gameOver = true;
        return ;
    }
    Node * p = new Node(nx, ny);
    head->nextNode = p;
    head = p;
    // 如果没吃到食物，蛇尾巴要释放掉
    if(map[nx][ny] != FOOD_BLOCK) {
        modifyMap(tail->posx, tail->posy, EMPTY_BLOCK);
        p = tail;
        tail = tail->nextNode;
        delete p;
    }else {
        len++;
        if(len == 5 || len == 10 || len == 15 || len == 20) speed += 15; // 按阶段加速
        generateFood();
    }
    modifyMap(nx, ny, BODY_BLOCK);
}

void Gluttonous_Snake::generateFood() {
    srand(time(0));
    int x, y;
    do {
        x = rand() % HEIGHT + 1;
        y = rand() % WIDTH + 1;
    }while(map[x][y] != EMPTY_BLOCK);
    modifyMap(x, y, FOOD_BLOCK);
}

Gluttonous_Snake::Gluttonous_Snake(int w, int h) : WIDTH(w), HEIGHT(h), MODE(CLASSICS) {
    // 检测地图是否过小
    if(WIDTH < 5 || HEIGHT < 5) {
        std::cerr << "地图过小" << std::endl;
        exit(EXIT_FAILURE);
    } 
    // 检测地图是否过大
    if(WIDTH > 100 || HEIGHT > 100) {
        std::cerr << "地图过大" << std::endl;
        exit(EXIT_FAILURE);
    } 
    // 构建初始状态的蛇，仅有一个块
    int x = (HEIGHT + 1) / 2;
    int y = 2;
    head = tail = new Node(x, y);
    len = 1;
    // 构建地图，+2是以为上下左右的墙体不算入地图大小
    map = new BLOCK * [HEIGHT+2];
    for(int i=0; i < HEIGHT+2; i++) 
        map[i] = new BLOCK [WIDTH+2];
    // 初始化地图元素
    for(int i=0; i < HEIGHT+2; i++)
        for(int j=0; j < WIDTH+2; j++)
            if(i == 0 || i == HEIGHT+1 || j == 0 || j == WIDTH+1)
                modifyMap(i, j, WALL_BLOCK);
            else
                modifyMap(i, j, EMPTY_BLOCK);
    modifyMap(x, y, BODY_BLOCK);
    generateFood();
    // 隐藏光标
    CONSOLE_CURSOR_INFO cci;
    cci.bVisible = FALSE;
    cci.dwSize = sizeof(cci);
    HANDLE handler = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(handler, &cci);
}

Gluttonous_Snake::~Gluttonous_Snake() {
    // 释放地图内存
    for(int i=0; i < HEIGHT+2; i++)
        delete [] map[i];
    delete [] map;
    // 释放蛇身内存
    while(tail != nullptr) {
        Node * p = tail;
        tail = tail->nextNode;
        delete p;
    }
}

bool Gluttonous_Snake::setMode(int MODE) {
    if(MODE > 1) return false;
    this->MODE = MODE;
    return true;
}

bool Gluttonous_Snake::setSpeed(int speed) {
    if(speed <= 0) return false;
    this->speed = speed;
    return true;
}

void Gluttonous_Snake::start() {
    while(!gameOver) {
        if(kbhit() && getch() == 224) { // 读取方向键时需读取两次，第一次一定是224
            int ch = getch();
            if(ch == 72 && moveDire != 2) moveDire = 0;      // 上
            else if(ch == 80 && moveDire != 0) moveDire = 2; // 下
            else if(ch == 75 && moveDire != 1) moveDire = 3; // 左
            else if(ch == 77 && moveDire != 3) moveDire = 1; // 右
        }
        move();
        Sleep(10000/speed);
    }
    COORD coord;
    coord.X = 0;
    coord.Y = HEIGHT+2;
    HANDLE handler = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handler, coord);
}