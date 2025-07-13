#pragma once
#include <set>
#include "Bullet.h"
#include "Enemy.h"
#include "BuffBall.h"

extern float deltaTime;

extern float realDeltaTime; // ʵ����һ֡����һ֡��ʱ���

// ��Ϸ���е���ʱ��
extern float gameTime;

// ʱ��ϵ������ʵ��������
extern float timeFactor;
// ʱ��ظ�ϵ��
extern float timeRestoreFactor;

extern std::set<Bullet*> bullets; // �洢�����ӵ��ļ���
extern std::set<Enemy*> enemies; // �洢���е��˵ļ���
extern std::set<BuffBall*> buffBalls; // �洢����Buff��ļ���
extern float score; // ��Ϸ�÷�
