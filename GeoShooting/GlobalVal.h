#pragma once
#include <set>
#include "Bullet.h"
#include "Enemy.h"
#include "BuffBall.h"

extern float deltaTime;

extern float realDeltaTime; // 实际上一帧和这一帧的时间差

// 游戏进行的总时间
extern float gameTime;

// 时间系数用来实现慢动作
extern float timeFactor;
// 时间回复系数
extern float timeRestoreFactor;

extern std::set<Bullet*> bullets; // 存储所有子弹的集合
extern std::set<Enemy*> enemies; // 存储所有敌人的集合
extern std::set<BuffBall*> buffBalls; // 存储所有Buff球的集合
extern float score; // 游戏得分
