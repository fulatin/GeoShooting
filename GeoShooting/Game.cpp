#include "Game.h"
#include "Constants.h"
#include "GlobalVal.h"
#include "GraphicsHelper.h"
#include <iostream>
using namespace GeoShooting;
using namespace std;
Game::Game() :canvas(WINDOW_WIDTH, WINDOW_HEIGHT), glowCanvas(WINDOW_WIDTH, WINDOW_HEIGHT),player(500,500,30,30) {
	
}
Game::~Game() {

}
void Game::run() {
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT); // 初始化图形窗口
	DWORD lastTime = GetTickCount(); // 获取当前时间
	while (true) {
		if (GetTickCount() - lastTime <= 1000 / 60) {
			Sleep(10);
			continue;
		}
		//cout << deltaTime << endl;
		deltaTime = (GetTickCount() - lastTime) / 1000.0f; // 计算上一帧和这一帧的时间差
		lastTime = GetTickCount(); // 更新上一帧时间


		SetWorkingImage(&canvas); // 设置工作图像为画布
		cleardevice(); // 清空画布
		player.update(); // 更新玩家状态
		player.draw(); // 绘制玩家
		SetWorkingImage(&glowCanvas); // 设置工作图像为辉光画布
		cleardevice(); // 清空辉光画布
		player.draw();
		GeoShooting::GraphicsHelper::boxBlur(&glowCanvas, 50);
		GeoShooting::GraphicsHelper::boxBlur(&glowCanvas, 50);
		GeoShooting::GraphicsHelper::boxBlur(&glowCanvas, 50);
		GeoShooting::GraphicsHelper::applyGlow(&canvas, &glowCanvas);
		SetWorkingImage(nullptr);
		putimage(0, 0, &canvas); // 将画布绘制到窗口
		//flushmessage(); // 刷新消息队列
	}
}