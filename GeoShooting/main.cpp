#define WINVER 0x0A00
#define _WIN32_WINNT 0x0A00

#include "Constants.h"
#include "Game.h"
#include <graphics.h>
#include <iostream>
#include<easyx.h>

#include <ShellScalingApi.h>	
#pragma comment(lib, "Shcore.lib")
using namespace std;
using namespace GeoShooting;
int main() {
	// ��ֹϵͳ����
	SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT); // ��ʼ��ͼ�δ���

	Game game; // ������Ϸ����

	game.run(); // ������Ϸѭ��
}

