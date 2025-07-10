#include "Enemy.h"
#include "GlobalVal.h"
#include "Constants.h"
#include <graphics.h>
#include <iostream>
using namespace std;

Enemy::Enemy(float x, float y, float width, float height, Vector direction, float speed,Player *_target)
	: GameObject(x, y, width, height), direction(direction), speed(speed) 
	, targetPlayer(_target) 
{
	direction.normalize(); // 确保方向是单位向量
	enemyColor = RGB(255, 0, 0); // 设置敌人颜色为红色
}

// 绘制敌人为一个矩形, x , y 为矩形中心
void Enemy::draw() {
	setlinecolor(enemyColor);
	setlinestyle(PS_SOLID, 2);
	// 绘制敌人为一个矩形
	rectangle(x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}
void Enemy::update() {
	// 更新敌人位置,并将direction些许向玩家移动
	Vector modifiedDirection = direction; // 复制方向
	if (targetPlayer) {
		// 计算敌人和玩家之间的距离
		float distanceToPlayer = direction.distance(Vector(targetPlayer->x, targetPlayer->y));
		if (distanceToPlayer > 0) {
			// 如果敌人与玩家之间有距离，则向玩家移动
			modifiedDirection.x += (targetPlayer->x - x) / distanceToPlayer * 0.6f; // 向玩家方向微调
			modifiedDirection.y += (targetPlayer->y - y) / distanceToPlayer * 0.6f; // 向玩家方向微调
			modifiedDirection.normalize(); // 确保方向是单位向量
		}
	}
	x += direction.x * speed * deltaTime;
	y += direction.y * speed * deltaTime;
	//cout << "Enemy position: " << x << ", " << y << endl; // 输出敌人位置
}
// 检查敌人是否超出屏幕范围
bool Enemy::isOffScreen() const {
	return x < 0 || x > getwidth() || y < 0 || y > getheight();
}
bool Enemy::collideWith(GameObject* other) {
	// 检查敌人是否与其他游戏对象碰撞
	// 简单的矩形碰撞检测
	return x - width / 2 < other->x + other->width &&
		   x + width / 2 > other->x &&
		   y - height / 2 < other->y + other->height &&
		   y + height / 2 > other->y;
}

bool Enemy::collideWith(Player* _player) {

	// 检测三角形顶点与矩形的碰撞

	for (int i = 0; i < 3; ++i) {
		Vector curr = targetPlayer->trangle[i];

		if ((curr.x >= x - width / 2) && (curr.x <= x + width / 2) &&
			(curr.y >= y - height / 2) && (curr.y <= y + height / 2) ) {
			return true; // 如果三角形顶点在敌人矩形内，则发生碰撞
		}
	}
	return false; // 没有碰撞
}