#pragma once
#include <set>
#include "Bullet.h"
#include "Enemy.h"
namespace GeoShooting {
	// ȫ�ֱ���
	// ��һ֡����һ֡��ʱ���
	extern float deltaTime;
	extern std::set<Bullet*> bullets; // �洢�����ӵ��ļ���
	extern std::set<Enemy*> enemies; // �洢���е��˵ļ���
} // namespace GeoShooting