#pragma once
#include <set>
#include "Bullet.h"
#include "Enemy.h"
#include "BuffBall.h"
namespace GeoShooting {
	// 全局变量
	// 上一帧和这一帧的时间差
	extern float deltaTime;
	// 游戏进行的总时间
	extern float gameTime;
	extern std::set<Bullet*> bullets; // 存储所有子弹的集合
	extern std::set<Enemy*> enemies; // 存储所有敌人的集合
	extern std::set<BuffBall*> buffBalls; // 存储所有Buff球的集合
	extern float score; // 游戏得分
	
} // namespace GeoShooting