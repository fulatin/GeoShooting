#include "GlobalVal.h"

using namespace GeoShooting;
float GeoShooting::deltaTime = 0.0f; // 初始化上一帧和这一帧的时间差为0
float GeoShooting::realDeltaTime = 0.0f; // 初始化实际上一帧和这一帧的时间差为0
float GeoShooting::timeFactor = 1.0f; // 初始化时间系数为1.0，表示正常速度
float GeoShooting::timeRestoreFactor = 1.2f; // 初始化时间回复系数为1.0，表示正常速度
std::set<Bullet* > GeoShooting::bullets; // 初始化子弹集合
std::set<Enemy* > GeoShooting::enemies; // 初始化敌人集合
std::set<BuffBall* > GeoShooting::buffBalls; // 初始化Buff球集合
float GeoShooting::score = 100.0f; // 初始化游戏得分为100
float GeoShooting::gameTime = 0.0f; // 初始化游戏进行的总时间为0