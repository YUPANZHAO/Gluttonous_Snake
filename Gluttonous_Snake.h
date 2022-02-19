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
    const int WIDTH; // ��ͼ���
    const int HEIGHT; // ��ͼ�߶�
    const BLOCK WALL_BLOCK  = (BLOCK) "��"; // ǽ���ַ��� �������ַ��������ֽ�
    const BLOCK BODY_BLOCK  = (BLOCK) "��"; // �����ַ���
    const BLOCK EMPTY_BLOCK = (BLOCK) "  "; // �հ��ַ��� Ҫ��֤�������ֽ� �����������ո�
    const BLOCK FOOD_BLOCK  = (BLOCK) "��"; // ʳ���ַ���
    int MODE; // ��Ϸģʽ
    int speed = 30; // �ٶ�
    bool gameOver = false; // ��Ϸ״̬: false ��Ϸδ���� true ��Ϸ����
    int moveDire = 1; // ��ǰ�ƶ�����: 0 �� 1 �� 2 �� 3 ��
    int len = 0; // �ߵĳ���
    BLOCK ** map = nullptr; // ��ͼָ��
    struct Node { 
        int posx, posy; // ��¼��������λ��
        Node * nextNode; // ָ����һ�����λ�� ���ߵ�β��һֱָ��ͷ��
        Node(int x, int y) : posx(x), posy(y), nextNode(nullptr) {}
    };
    Node * head = nullptr, * tail = nullptr; // head ָ���ߵ�ͷ�� tail ָ���ߵ�β��

    // ������ƶ���ָ��λ�ã�Ȼ�����ָ���ַ�ch�����޸ĵ�ͼ����
    void modifyMap(int x, int y, const BLOCK & ch);
    // ����moveDire�����ƶ�һ��
    void move();
    // ������ʳ��
    void generateFood();
public:
    enum { CLASSICS /*����ɴ�ǽ*/, DIFFICULTY /*���ɴ�ǽ*/};
    Gluttonous_Snake(int w = 30, int h = 15);
    ~Gluttonous_Snake();
    // ����ģʽ
    bool setMode(int MODE);
    // �����ٶ�
    bool setSpeed(int speed);
    // ��ʼ��Ϸ
    void start();
};

#endif