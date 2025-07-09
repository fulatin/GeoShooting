#include "Game.h"
#include "Constants.h"
#include "GlobalVal.h"
#include "GraphicsHelper.h"
#include <iostream>
#include <cmath>
using namespace GeoShooting;
using namespace std;
Game::Game() :player(500,500,50,50) {
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT); // ��ʼ��ͼ�δ���
	setbkmode(TRANSPARENT);
	canvas = GetImageBuffer();
}
Game::~Game() {

}
void Game::run() {

	float  lastTime = GetTickCount(); // ��ȡ��ǰʱ��
	BeginBatchDraw(); // ��ʼ��������
	while (true) {
		if ((float )GetTickCount() - lastTime - 1000 / 240.0 <= 4.0) {
			Sleep(1);
			continue;
		}
		setbkcolor(RGB(255,  255, 255));
		cleardevice(); // �������
		//cout << deltaTime << endl;
		deltaTime = (GetTickCount() - lastTime) / 1000.0f; // ������һ֡����һ֡��ʱ���
		lastTime = GetTickCount(); // ������һ֡ʱ��
		player.update(); // �������״̬
		player.draw(); // �������
		FlushBatchDraw(); // ˢ����������
		flushmessage(); // ˢ����Ϣ����
	}
	EndBatchDraw(); // ������������
}