#define WINVER 0x0A00
#define _WIN32_WINNT 0x0A00

#include "Constants.h"
#include "Game.h"
#include <graphics.h>

#include<easyx.h>

#include <ShellScalingApi.h>	
#pragma comment(lib, "Shcore.lib")
#pragma comment(lib, "winmm.lib") // 链接 winmm.lib
using namespace std;
using namespace GeoShooting;
int main() {
	// 阻止系统缩放
	SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT); // 初始化图形窗口
	bool quit = false; // 游戏是否退出
	while(!quit) {
		Game game; // 创建游戏对象

		quit = !game.run(); // 启动游戏循环
	} 

}

