#include "Game.h"
#include "Constants.h"
#include "GlobalVal.h"
#include <iostream>
#include <cmath>
using namespace GeoShooting;
using namespace std;
Game::Game() :player(500,500,50,50) {
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT); // ��ʼ��ͼ�δ���
}
Game::~Game() {

}
void Game::run() {

	float  lastTime = GetTickCount(); // ��ȡ��ǰʱ��
	BeginBatchDraw(); // ��ʼ��������
	while (true) {
		if ((float )GetTickCount() - lastTime - 1000 / 240.0 <= 1.0) {
			Sleep(1);
			continue;
		}
		setbkcolor(RGB(20,20,20));
		cleardevice(); // �������


		deltaTime = (GetTickCount() - lastTime) / 1000.0f; // ������һ֡����һ֡��ʱ���
		lastTime = GetTickCount(); // ������һ֡ʱ��


		player.update(); // �������״̬
		player.draw(); // �������


		// ���������ӵ�
		for (auto it = bullets.begin(); it != bullets.end();) {
			Bullet* bullet = *it;
			bullet->update(); // �����ӵ�״̬
			if (bullet->isOffScreen()) {
				it = bullets.erase(it); // ����ӵ�������Ļ��Χ����ɾ����
				cout << "delete bullet" << endl;
				delete bullet; // �ͷ��ڴ�
			} else {
				bullet->draw(); // �����ӵ�
				++it; // �ƶ�����һ���ӵ�
			}
		}
		FlushBatchDraw(); // ˢ����������
		flushmessage(); // ˢ����Ϣ����
	}
	EndBatchDraw(); // ������������
}