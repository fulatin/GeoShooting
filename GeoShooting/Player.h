#pragma once
#include "GameObject.h"
#include "Vector.h"

using namespace GeoShooting;
class Player :public GameObject {

public:
	float health; // 玩家生命值
	Vector trangle[3]; // 玩家三角形顶点
	Player(float x, float y, float width, float height);
	void draw() override; // 绘制玩家
	void update() override; // 更新玩家状态
	void shoot(); // 玩家射击 x,y 为射击位置
	Vector getPosition() const { return Vector(x, y); } // 获取玩家位置
	// 检测玩家是否与其他游戏对象碰撞
	bool collideWith(GameObject* other) {
		// 简单的矩形碰撞检测
		return x < other->x + other->width &&
			   x + width > other->x &&
			   y < other->y + other->height &&
			   y + height > other->y;
	}
	Vector speed;
	float mxSpeed = 600.0f; // 玩家移动速度
	float acc = 1500.0f; // 玩家加速度
	float fireRate; // 玩家射击频率 一秒几次
	float lastFireTime; // 上次射击时间
	float frac = 0.7; // 玩家转动时的阻尼
	float bulletDamage = 10.0f; // 子弹伤害
	float bulletSpeed = 1000.0f; // 子弹速度
	void updateTrangle();
	COLORREF playerColor = RGB(0, 255, 0); // 玩家颜色
	// 玩家的绘制对象
	Vector playerDirection; // 玩家方向 确保是单位向量
	Vector targetDirection; // 玩家目标方向
	IMAGE playerSurface;
};