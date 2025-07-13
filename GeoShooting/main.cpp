#define WINVER 0x0A00
#define _WIN32_WINNT 0x0A00

#include "Constants.h"
#include "Game.h"
#include <graphics.h>

#include<easyx.h>

#include <ShellScalingApi.h>	
#pragma comment(lib, "Shcore.lib")
#pragma comment(lib, "winmm.lib") // ���� winmm.lib
using namespace std;
using namespace GeoShooting;
int main() {
	// ��ֹϵͳ����
	SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT); // ��ʼ��ͼ�δ���
	bool quit = false; // ��Ϸ�Ƿ��˳�
	while(!quit) {
		Game game; // ������Ϸ����

		quit = !game.run(); // ������Ϸѭ��
	} 

}

