#include "Game.h"
#include "Constants.h"
#include "GlobalVal.h"
#include "Enemy.h"
#include <iostream>
#include <cmath>
using namespace GeoShooting;
using namespace std;
Game::Game() :player(500,500,50,50) {
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT); // 初始化图形窗口
}
Game::~Game() {

}
// 从屏幕外向玩家生成随机敌人
void Game::generateRandomEnermy() {
	// 生成屏幕外的随机位置
	float offsetx = rand() % getwidth()*(rand()%2?-1:1); // 随机生成x偏移量
	float offsety = rand() % getheight() * (rand() % 2 ? -1 : 1); // 随机生成y偏移量
	int x, y;
	if(offsetx < 0) {
		x = offsetx; // 在屏幕外随机生成x坐标
	} else {
		x = getwidth() + offsetx; // 在屏幕外随机生成x坐标
	}
	if(offsety < 0) {
		y = offsety; // 在屏幕外随机生成y坐标
	}
	else {
		y = getheight() + offsety; // 在屏幕外随机生成y坐标
	}
	cout << x << " " << y << endl; // 输出生成的坐标
	float width = 50.0f; // 敌人宽度
	float height = 50.0f; // 敌人高度
	Vector direction(player.x-x+rand()%20, player.y-y+rand()%20); // 指向player的方向
	direction.normalize(); // 确保方向是单位向量
	float speed = 750.0f + rand() % 500*(rand()%2?1:-1); // 随机生成速度
	Enemy* enemy = new Enemy(x, y, width, height, direction, speed,&player); // 创建新的敌人对象
	enemies.insert(enemy); // 将敌人添加到集合中
	//cout << "generate enemy" << endl;
}
void Game::run() {
	float  lastTime = GetTickCount(); // 获取当前时间
	BeginBatchDraw(); // 开始批量绘制
	while (true) {
		if ((float )GetTickCount() - lastTime - 1000 / 240.0 <= 1.0) {
			Sleep(1);
			continue;
		}
		setbkcolor(RGB(20,20,20));
		cleardevice(); // 清除画布


		deltaTime = (GetTickCount() - lastTime) / 1000.0f; // 计算上一帧和这一帧的时间差
		lastTime = GetTickCount(); // 更新上一帧时间


		player.update(); // 更新玩家状态
		player.draw(); // 绘制玩家


		// 更新所有子弹
		for (auto it = bullets.begin(); it != bullets.end();) {
			Bullet* bullet = *it;
			bullet->update(); // 更新子弹状态
			if (bullet->isOffScreen()) {
				it = bullets.erase(it); // 如果子弹超出屏幕范围，则删除它
				cout << "delete bullet" << endl;
				delete bullet; // 释放内存
			} else {
				bullet->draw(); // 绘制子弹
				++it; // 移动到下一个子弹
			}
		}
		// 检查子弹与敌人碰撞
		
		for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
			Bullet* bullet = *bulletIt;
			bool bulletDeleted = false; // 标记子弹是否被删除
			for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();) {
				Enemy* enemy = *enemyIt;
				if (bullet->collideWith(enemy)) { // 检查子弹是否与敌人碰撞
					cout << "bullet hit enemy" << endl;
					enemyIt = enemies.erase(enemyIt); // 删除敌人
					delete enemy; // 释放内存
					bulletDeleted = true; // 标记子弹被删除
				} else {
					++enemyIt; // 移动到下一个敌人
				}
			}
			if (bulletDeleted) {
				bulletIt = bullets.erase(bulletIt); // 删除子弹
				delete bullet; // 释放内存
			} else {
				bullet->draw(); // 绘制子弹
				++bulletIt; // 移动到下一个子弹
			}
		}

		// 更新所有敌人,并计算屏幕内敌人数量
		inScreenEnermyCount = 0; // 重置屏幕内敌人数量
		for (auto it = enemies.begin(); it != enemies.end();) {
			Enemy* enemy = *it;
			enemy->update(); // 更新敌人状态
			// 超出屏幕范围两倍的敌人将被删除
			if (abs(enemy->x) >= 3 * getwidth() || abs(enemy->y) >= 3 * getheight()) {
				it = enemies.erase(it); // 如果敌人超出屏幕范围，则删除它
				cout << "delete enemy" << endl;
				delete enemy; // 释放内存
			}
			else {
				enemy->draw(); // 绘制敌人
				++it; // 移动到下一个敌人
			}
			// 检查敌人是否在屏幕内
			if (enemy->x >= 0 && enemy->x <= getwidth() && enemy->y >= 0 && enemy->y <= getheight()) {
				inScreenEnermyCount++; // 增加屏幕内敌人数量
			}
		}

		// 尝试生成新的敌人
		if (inScreenEnermyCount < maxEnermyCount && (GetTickCount() - lastEnermySpawnTime) / 1000.0f > enermySpawnRate) {
			generateRandomEnermy(); // 生成新的敌人
			lastEnermySpawnTime = GetTickCount(); // 更新上次生成敌人的时间
		}
		// 检测敌人间的碰撞，如果有就通过动量定理来计算碰撞后的速度
		for (auto it1 = enemies.begin(); it1 != enemies.end(); ++it1) {
			Enemy* enemy1 = *it1;
			for (auto it2 = std::next(it1); it2 != enemies.end();) {
				Enemy* enemy2 = *it2;
				if (enemy1->collideWith(enemy2)) { // 检查敌人是否碰撞
					cout << "enemy collide" << endl;
					// 计算碰撞后的速度
					Vector v1(enemy1->direction.x * enemy1->speed, enemy1->direction.y * enemy1->speed);
					Vector v2(enemy2->direction.x * enemy2->speed, enemy2->direction.y * enemy2->speed);
					Vector newV1 = v1 - v2; // 简单的碰撞处理
					Vector newV2 = v2 - v1; // 简单的碰撞处理
					enemy1->direction = newV1 / newV1.length();
					enemy2->direction = newV2 / newV2.length();
					//it2 = enemies.erase(it2); // 删除第二个敌人
					//delete enemy2; // 释放内存
				} 
					++it2; // 移动到下一敌人
				
			}
		}
		FlushBatchDraw(); // 刷新批量绘制
		flushmessage(); // 刷新消息队列
	}
	EndBatchDraw(); // 结束批量绘制
}