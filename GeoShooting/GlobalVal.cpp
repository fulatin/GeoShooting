#include "GlobalVal.h"

using namespace GeoShooting;
float GeoShooting::deltaTime = 0.0f; // 初始化上一帧和这一帧的时间差为0
std::set<Bullet*> GeoShooting::bullets; // 初始化子弹集合