#pragma once

#include "GameObject.h"
#include "Vector.h"
#include "Player.h"
#include "Bullet.h"
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
	// 被子弹击中时调用
	void getHitBy(Bullet* _bullet);
	Vector direction; // 敌人方向
	float speed; // 敌人速度
	float getHealth() const { return health; } // 获取敌人生命值
	
protected:
	bool isDead = false; // 敌人是否死亡
	Player* targetPlayer; // 敌人的目标玩家
	float health = 100.0f; // 敌人生命值
	COLORREF enemyColor = RGB(255, 0, 0); // 敌人颜色
	float healthBarWidth = 50.0f; // 敌人血条宽度
};