#pragma once
#include "Enemy.h"

class ShootableEnemy : public Enemy {
	public:
		ShootableEnemy(float x, float y, float width, float height, Vector direction, float speed, Player* _target);
	void update() override; // 更新射击敌人状态
	void draw() override; // 绘制射击敌人
	void shoot(); // 射击方法
	float getBulletSpeed() const { return bulletSpeed; } // 获取子弹速度
	float getBulletDamage() const { return bulletDamage; } // 获取子弹伤害
private:
	float shootInterval; // 射击间隔时间
	float lastShootTime; // 上次射击时间
	float bulletSpeed; // 子弹速度
	float bulletDamage; // 子弹伤害
};