#pragma once

#include "GameObject.h"
#include "Vector.h"
#include "Player.h"
using namespace GeoShooting;
class Enemy : public GameObject {
public:
	Enemy(float x, float y, float width, float height, Vector direction, float speed,Player *_target);
	void draw() override; // 绘制敌人
	void update() override; // 更新敌人状态
	bool isOffScreen() const; // 检查敌人是否超出屏幕范围
	bool collideWith(GameObject* other); // 检查敌人是否与其他游戏对象碰撞
	// 为玩家提供的更加精确的碰撞检测
	bool collideWith(Player* _player);
	Vector direction; // 敌人方向
	float speed; // 敌人速度
private:
	Player* targetPlayer; // 敌人的目标玩家


	COLORREF enemyColor = RGB(255, 0, 0); // 敌人颜色
};