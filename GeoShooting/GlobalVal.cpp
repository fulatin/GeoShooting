#include "GlobalVal.h"

using namespace GeoShooting;
float GeoShooting::deltaTime = 0.0f; // 初始化上一帧和这一帧的时间差为0
std::set<Bullet*> GeoShooting::bullets; // 初始化子弹集合
std::set<Enemy*> GeoShooting::enemies; // 初始化敌人集合
std::set<BuffBall*> GeoShooting::buffBalls; // 初始化Buff球集合
float GeoShooting::score = 100.0f; // 初始化游戏得分为100
float GeoShooting::gameTime = 0.0f; // 初始化游戏进行的总时间为0