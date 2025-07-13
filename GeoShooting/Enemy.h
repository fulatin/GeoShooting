#pragma once

#include "GameObject.h"
#include "Vector.h"
#include "Player.h"
#include "Bullet.h"
using namespace GeoShooting;
class Enemy : public GameObject {
public:
	Enemy(float x, float y, float width, float height, Vector direction, float speed,Player *_target);
	void draw() override; // ���Ƶ���
	void update() override; // ���µ���״̬
	bool isOffScreen() const; // �������Ƿ񳬳���Ļ��Χ
	bool collideWith(GameObject* other); // �������Ƿ���������Ϸ������ײ
	// Ϊ����ṩ�ĸ��Ӿ�ȷ����ײ���
	bool collideWith(Player* _player);
	// ���ӵ�����ʱ����
	void getHitBy(Bullet* _bullet);
	Vector direction; // ���˷���
	float speed; // �����ٶ�
	float getHealth() const { return health; } // ��ȡ��������ֵ
	
protected:
	bool isDead = false; // �����Ƿ�����
	Player* targetPlayer; // ���˵�Ŀ�����
	float health = 100.0f; // ��������ֵ
	COLORREF enemyColor = RGB(255, 0, 0); // ������ɫ
	float healthBarWidth = 50.0f; // ����Ѫ�����
};