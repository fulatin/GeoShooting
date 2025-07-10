#pragma once

#include "GameObject.h"
#include "Vector.h"
#include "Player.h"
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
	Vector direction; // ���˷���
	float speed; // �����ٶ�
private:
	Player* targetPlayer; // ���˵�Ŀ�����


	COLORREF enemyColor = RGB(255, 0, 0); // ������ɫ
};