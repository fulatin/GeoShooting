#define WINVER 0x0A00
#define _WIN32_WINNT 0x0A00

#include "Constants.h"
#include "Game.h"
#include <graphics.h>

#include<easyx.h>

#include <ShellScalingApi.h>	
#pragma comment(lib, "Shcore.lib")
#pragma comment(lib, "winmm.lib") // ���� winmm.lib
#pragma comment(linker, "/subsystem:windows /entry:mainCRTStartup") // ������ڵ�Ϊ mainCRTStartup
using namespace std;
using namespace GeoShooting;
int main() {
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT); // ��ʼ��ͼ�δ���
	bool quit = false; // ��Ϸ�Ƿ��˳�
	while(!quit) {
		Game game; // ������Ϸ����

		quit = !game.run(); // ������Ϸѭ��
	} 

}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	// ���ؿ���̨����
	FreeConsole(); // ���ؿ���̨����
	SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE); // ���ý��� DPI ��֪ģʽ
	main(); // ���� main ����
	return 0; // ���� 0 ��ʾ������������
}