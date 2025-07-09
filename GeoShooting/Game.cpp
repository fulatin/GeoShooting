#include "Game.h"
#include "Constants.h"
#include "GlobalVal.h"
#include "GraphicsHelper.h"
#include <iostream>
#include <cmath>
using namespace GeoShooting;
using namespace std;
Game::Game() :player(500,500,50,50) {
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT); // 初始化图形窗口
	setbkmode(TRANSPARENT);
	canvas = GetImageBuffer();
}
Game::~Game() {

}
void Game::run() {

	float  lastTime = GetTickCount(); // 获取当前时间
	BeginBatchDraw(); // 开始批量绘制
	while (true) {
		if ((float )GetTickCount() - lastTime - 1000 / 240.0 <= 4.0) {
			Sleep(1);
			continue;
		}
		setbkcolor(RGB(255,  255, 255));
		cleardevice(); // 清除画布
		//cout << deltaTime << endl;
		deltaTime = (GetTickCount() - lastTime) / 1000.0f; // 计算上一帧和这一帧的时间差
		lastTime = GetTickCount(); // 更新上一帧时间
		player.update(); // 更新玩家状态
		player.draw(); // 绘制玩家
		FlushBatchDraw(); // 刷新批量绘制
		flushmessage(); // 刷新消息队列
	}
	EndBatchDraw(); // 结束批量绘制
}