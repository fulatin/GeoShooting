#pragma once
#include "GameObject.h"
#include "Vector.h"

using namespace GeoShooting;
class Player :public GameObject {

public:
	Player(float x, float y, float width, float height);
	void draw() override; // 绘制玩家
	void update() override; // 更新玩家状态
	void shoot(float x, float y); // 玩家射击 x,y 为射击位置
private:
	Vector speed;
	float mxSpeed = 500.0f; // 玩家移动速度
	float acc = 1000.0f; // 玩家加速度
	float health; // 玩家生命值
	float fireRate; // 玩家射击频率
	float lastFireTime; // 上次射击时间
	float fireCooldown; // 射击冷却时间
	float frac = 0.90;
	// 玩家的绘制对象
	IMAGE playerSurface;
};