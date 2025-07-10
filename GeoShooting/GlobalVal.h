#pragma once
#include <set>
#include "Bullet.h"
#include "Enemy.h"
#include "BuffBall.h"
namespace GeoShooting {
	// ȫ�ֱ���
	// ��һ֡����һ֡��ʱ���
	extern float deltaTime;
	// ��Ϸ���е���ʱ��
	extern float gameTime;
	extern std::set<Bullet*> bullets; // �洢�����ӵ��ļ���
	extern std::set<Enemy*> enemies; // �洢���е��˵ļ���
	extern std::set<BuffBall*> buffBalls; // �洢����Buff��ļ���
	extern float score; // ��Ϸ�÷�
	
} // namespace GeoShooting