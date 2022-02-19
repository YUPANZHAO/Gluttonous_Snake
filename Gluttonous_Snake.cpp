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
    // ��ǽ�������
    if(MODE == CLASSICS) {
        nx = (nx - 1 + HEIGHT) % HEIGHT + 1;
        ny = (ny - 1 + WIDTH) % WIDTH + 1;
    }
    // �ж��Ƿ�ײǽ��ײ����
    if(map[nx][ny] == WALL_BLOCK
    || (map[nx][ny] == BODY_BLOCK && !(nx == tail->posx && ny == tail->posy))) {
        gameOver = true;
        return ;
    }
    Node * p = new Node(nx, ny);
    head->nextNode = p;
    head = p;
    // ���û�Ե�ʳ���β��Ҫ�ͷŵ�
    if(map[nx][ny] != FOOD_BLOCK) {
        modifyMap(tail->posx, tail->posy, EMPTY_BLOCK);
        p = tail;
        tail = tail->nextNode;
        delete p;
    }else {
        len++;
        if(len == 5 || len == 10 || len == 15 || len == 20) speed += 15; // ���׶μ���
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
    // ����ͼ�Ƿ��С
    if(WIDTH < 5 || HEIGHT < 5) {
        std::cerr << "��ͼ��С" << std::endl;
        exit(EXIT_FAILURE);
    } 
    // ����ͼ�Ƿ����
    if(WIDTH > 100 || HEIGHT > 100) {
        std::cerr << "��ͼ����" << std::endl;
        exit(EXIT_FAILURE);
    } 
    // ������ʼ״̬���ߣ�����һ����
    int x = (HEIGHT + 1) / 2;
    int y = 2;
    head = tail = new Node(x, y);
    len = 1;
    // ������ͼ��+2����Ϊ�������ҵ�ǽ�岻�����ͼ��С
    map = new BLOCK * [HEIGHT+2];
    for(int i=0; i < HEIGHT+2; i++) 
        map[i] = new BLOCK [WIDTH+2];
    // ��ʼ����ͼԪ��
    for(int i=0; i < HEIGHT+2; i++)
        for(int j=0; j < WIDTH+2; j++)
            if(i == 0 || i == HEIGHT+1 || j == 0 || j == WIDTH+1)
                modifyMap(i, j, WALL_BLOCK);
            else
                modifyMap(i, j, EMPTY_BLOCK);
    modifyMap(x, y, BODY_BLOCK);
    generateFood();
    // ���ع��
    CONSOLE_CURSOR_INFO cci;
    cci.bVisible = FALSE;
    cci.dwSize = sizeof(cci);
    HANDLE handler = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(handler, &cci);
}

Gluttonous_Snake::~Gluttonous_Snake() {
    // �ͷŵ�ͼ�ڴ�
    for(int i=0; i < HEIGHT+2; i++)
        delete [] map[i];
    delete [] map;
    // �ͷ������ڴ�
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
        if(kbhit() && getch() == 224) { // ��ȡ�����ʱ���ȡ���Σ���һ��һ����224
            int ch = getch();
            if(ch == 72 && moveDire != 2) moveDire = 0;      // ��
            else if(ch == 80 && moveDire != 0) moveDire = 2; // ��
            else if(ch == 75 && moveDire != 1) moveDire = 3; // ��
            else if(ch == 77 && moveDire != 3) moveDire = 1; // ��
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