#pragma once
#include <set>
#include "Bullet.h"
namespace GeoShooting {
	// ȫ�ֱ���
	// ��һ֡����һ֡��ʱ���
	extern float deltaTime;
	extern std::set<Bullet*> bullets; // �洢�����ӵ��ļ���
} // namespace GeoShooting