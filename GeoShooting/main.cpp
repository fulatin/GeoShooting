#include "GraphicsHelper.h"
#include "Constants.h"
#include "Game.h"
#include <graphics.h>
#include <iostream>
#include<easyx.h>
using namespace std;
using namespace GeoShooting;
#pragma comment(lib, "gdiplus.lib")
int main() {
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT); // ��ʼ��ͼ�δ���

	Game game; // ������Ϸ����

	game.run(); // ������Ϸѭ��
}

