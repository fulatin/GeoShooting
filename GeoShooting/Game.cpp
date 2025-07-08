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
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT); // ��ʼ��ͼ�δ���
	DWORD lastTime = GetTickCount(); // ��ȡ��ǰʱ��
	while (true) {
		if (GetTickCount() - lastTime <= 1000 / 60) {
			Sleep(10);
			continue;
		}
		//cout << deltaTime << endl;
		deltaTime = (GetTickCount() - lastTime) / 1000.0f; // ������һ֡����һ֡��ʱ���
		lastTime = GetTickCount(); // ������һ֡ʱ��


		SetWorkingImage(&canvas); // ���ù���ͼ��Ϊ����
		cleardevice(); // ��ջ���
		player.update(); // �������״̬
		player.draw(); // �������
		SetWorkingImage(&glowCanvas); // ���ù���ͼ��Ϊ�Թ⻭��
		cleardevice(); // ��ջԹ⻭��
		player.draw();
		GeoShooting::GraphicsHelper::boxBlur(&glowCanvas, 50);
		GeoShooting::GraphicsHelper::boxBlur(&glowCanvas, 50);
		GeoShooting::GraphicsHelper::boxBlur(&glowCanvas, 50);
		GeoShooting::GraphicsHelper::applyGlow(&canvas, &glowCanvas);
		SetWorkingImage(nullptr);
		putimage(0, 0, &canvas); // ���������Ƶ�����
		//flushmessage(); // ˢ����Ϣ����
	}
}