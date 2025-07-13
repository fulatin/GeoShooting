#define WINVER 0x0A00
#define _WIN32_WINNT 0x0A00

#include "Constants.h"
#include "Game.h"
#include <graphics.h>

#include<easyx.h>

#include <ShellScalingApi.h>	
#pragma comment(lib, "Shcore.lib")
#pragma comment(lib, "winmm.lib") // 链接 winmm.lib
#pragma comment(linker, "/subsystem:windows /entry:mainCRTStartup") // 设置入口点为 mainCRTStartup
using namespace std;
using namespace GeoShooting;
int main() {
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT); // 初始化图形窗口
	bool quit = false; // 游戏是否退出
	while(!quit) {
		Game game; // 创建游戏对象

		quit = !game.run(); // 启动游戏循环
	} 

}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	// 隐藏控制台窗口
	FreeConsole(); // 隐藏控制台窗口
	SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE); // 设置进程 DPI 感知模式
	main(); // 调用 main 函数
	return 0; // 返回 0 表示程序正常结束
}