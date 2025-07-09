#pragma once
#include <set>
#include "Bullet.h"
#include "Enemy.h"
namespace GeoShooting {
	// 全局变量
	// 上一帧和这一帧的时间差
	extern float deltaTime;
	extern std::set<Bullet*> bullets; // 存储所有子弹的集合
	extern std::set<Enemy*> enemies; // 存储所有敌人的集合
} // namespace GeoShooting