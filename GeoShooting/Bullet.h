#pragma once

#include "GameObject.h"
#include "Vector.h"
using namespace GeoShooting;
class Bullet : public GameObject {
public:
	Bullet(float x, float y, float width, float height, Vector direction, float speed,GameObject *owner);
	void draw() override; // 绘制子弹
	void update() override; // 更新子弹状态
	bool isOffScreen() const; // 检查子弹是否超出屏幕范围
	bool collideWith(GameObject* other); // 检查子弹是否与其他游戏对象碰撞
	float getDamage() const { return damage; } // 获取子弹伤害
private:
	GameObject* owner; // 子弹的拥有者
	Vector direction; // 子弹方向
	float speed; // 子弹速度
	float damage = 10.0f; // 子弹伤害
	COLORREF bulletColor = RGB(255, 0, 0); // 子弹颜色
};