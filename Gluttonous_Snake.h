#ifndef GLUTTONOUS_SNAKE_H
#define GLUTTONOUS_SNAKE_H

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <random>

typedef char * BLOCK;
class Gluttonous_Snake {
private:
    const int WIDTH; // 地图宽度
    const int HEIGHT; // 地图高度
    const BLOCK WALL_BLOCK  = (BLOCK) "■"; // 墙体字符块 该特殊字符是两个字节
    const BLOCK BODY_BLOCK  = (BLOCK) "□"; // 蛇身字符块
    const BLOCK EMPTY_BLOCK = (BLOCK) "  "; // 空白字符块 要保证是两个字节 所以是两个空格
    const BLOCK FOOD_BLOCK  = (BLOCK) "★"; // 食物字符块
    int MODE; // 游戏模式
    int speed = 30; // 速度
    bool gameOver = false; // 游戏状态: false 游戏未结束 true 游戏结束
    int moveDire = 1; // 当前移动方向: 0 上 1 右 2 下 3 左
    int len = 0; // 蛇的长度
    BLOCK ** map = nullptr; // 地图指针
    struct Node { 
        int posx, posy; // 记录蛇身体块的位置
        Node * nextNode; // 指向下一个块的位置 从蛇的尾部一直指到头部
        Node(int x, int y) : posx(x), posy(y), nextNode(nullptr) {}
    };
    Node * head = nullptr, * tail = nullptr; // head 指向蛇的头部 tail 指向蛇的尾部

    // 将光标移动到指定位置，然后输出指定字符ch，并修改地图数据
    void modifyMap(int x, int y, const BLOCK & ch);
    // 蛇想moveDire方向移动一步
    void move();
    // 生成新食物
    void generateFood();
public:
    enum { CLASSICS /*经典可穿墙*/, DIFFICULTY /*不可穿墙*/};
    Gluttonous_Snake(int w = 30, int h = 15);
    ~Gluttonous_Snake();
    // 设置模式
    bool setMode(int MODE);
    // 设置速度
    bool setSpeed(int speed);
    // 开始游戏
    void start();
};

#endif