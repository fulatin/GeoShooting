#include "Game.h"
#include "Constants.h"
#include "GlobalVal.h"
#include "Enemy.h"
#include <iostream>
#include <cmath>
using namespace GeoShooting;
using namespace std;
Game::Game() :player(500,500,50,50) {
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT); // ��ʼ��ͼ�δ���
}
Game::~Game() {

}
// ����Ļ������������������
void Game::generateRandomEnermy() {
	// ������Ļ������λ��
	float offsetx = rand() % getwidth()*(rand()%2?-1:1); // �������xƫ����
	float offsety = rand() % getheight() * (rand() % 2 ? -1 : 1); // �������yƫ����
	int x, y;
	if(offsetx < 0) {
		x = offsetx; // ����Ļ���������x����
	} else {
		x = getwidth() + offsetx; // ����Ļ���������x����
	}
	if(offsety < 0) {
		y = offsety; // ����Ļ���������y����
	}
	else {
		y = getheight() + offsety; // ����Ļ���������y����
	}
	cout << x << " " << y << endl; // ������ɵ�����
	float width = 50.0f; // ���˿��
	float height = 50.0f; // ���˸߶�
	Vector direction(player.x-x+rand()%20, player.y-y+rand()%20); // ָ��player�ķ���
	direction.normalize(); // ȷ�������ǵ�λ����
	float speed = 750.0f + rand() % 500*(rand()%2?1:-1); // ��������ٶ�
	Enemy* enemy = new Enemy(x, y, width, height, direction, speed,&player); // �����µĵ��˶���
	enemies.insert(enemy); // ��������ӵ�������
	//cout << "generate enemy" << endl;
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
		// ����ӵ��������ײ
		
		for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
			Bullet* bullet = *bulletIt;
			bool bulletDeleted = false; // ����ӵ��Ƿ�ɾ��
			for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();) {
				Enemy* enemy = *enemyIt;
				if (bullet->collideWith(enemy)) { // ����ӵ��Ƿ��������ײ
					cout << "bullet hit enemy" << endl;
					enemyIt = enemies.erase(enemyIt); // ɾ������
					delete enemy; // �ͷ��ڴ�
					bulletDeleted = true; // ����ӵ���ɾ��
				} else {
					++enemyIt; // �ƶ�����һ������
				}
			}
			if (bulletDeleted) {
				bulletIt = bullets.erase(bulletIt); // ɾ���ӵ�
				delete bullet; // �ͷ��ڴ�
			} else {
				bullet->draw(); // �����ӵ�
				++bulletIt; // �ƶ�����һ���ӵ�
			}
		}

		// �������е���,��������Ļ�ڵ�������
		inScreenEnermyCount = 0; // ������Ļ�ڵ�������
		for (auto it = enemies.begin(); it != enemies.end();) {
			Enemy* enemy = *it;
			enemy->update(); // ���µ���״̬
			// ������Ļ��Χ�����ĵ��˽���ɾ��
			if (abs(enemy->x) >= 3 * getwidth() || abs(enemy->y) >= 3 * getheight()) {
				it = enemies.erase(it); // ������˳�����Ļ��Χ����ɾ����
				cout << "delete enemy" << endl;
				delete enemy; // �ͷ��ڴ�
			}
			else {
				enemy->draw(); // ���Ƶ���
				++it; // �ƶ�����һ������
			}
			// �������Ƿ�����Ļ��
			if (enemy->x >= 0 && enemy->x <= getwidth() && enemy->y >= 0 && enemy->y <= getheight()) {
				inScreenEnermyCount++; // ������Ļ�ڵ�������
			}
		}

		// ���������µĵ���
		if (inScreenEnermyCount < maxEnermyCount && (GetTickCount() - lastEnermySpawnTime) / 1000.0f > enermySpawnRate) {
			generateRandomEnermy(); // �����µĵ���
			lastEnermySpawnTime = GetTickCount(); // �����ϴ����ɵ��˵�ʱ��
		}

		FlushBatchDraw(); // ˢ����������
		flushmessage(); // ˢ����Ϣ����
	}
	EndBatchDraw(); // ������������
}