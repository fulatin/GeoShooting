#pragma once

#include "GameObject.h"
#include "Vector.h"
class Enemy; // ǰ������Enemy��
class Player; // ǰ������Player��
using namespace GeoShooting;
class Bullet : public GameObject {
public:
	Bullet(float x, float y, float width, float height, Vector direction, float speed,float damage,GameObject *owner);
	void draw() override; // �����ӵ�
	void update() override; // �����ӵ�״̬
	bool isOffScreen() const; // ����ӵ��Ƿ񳬳���Ļ��Χ
	bool collideWith(GameObject* other); // ����ӵ��Ƿ���������Ϸ������ײ
	bool collideWith(Enemy* _enemy); // ����ӵ��Ƿ��������ײ ���Ӿ�ȷ�İ汾
	bool collideWith(Player* _player); // ����ӵ��Ƿ��������ײ
	float getDamage() const { return damage; } // ��ȡ�ӵ��˺�
	void setBulletColor(COLORREF color) { bulletColor = color; } // �����ӵ���ɫ
	GameObject* getOwner() const { return owner; } // ��ȡ�ӵ���ӵ����
private:
	GameObject* owner; // �ӵ���ӵ����
	Vector direction; // �ӵ�����
	float speed; // �ӵ��ٶ�
	float damage = 10.0f; // �ӵ��˺�
	COLORREF bulletColor = RGB(255, 0, 0); // �ӵ���ɫ
};