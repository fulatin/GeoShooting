#pragma once

#include "GameObject.h"
#include "Vector.h"
using namespace GeoShooting;
class Bullet : public GameObject {
public:
	Bullet(float x, float y, float width, float height, Vector direction, float speed,GameObject *owner);
	void draw() override; // �����ӵ�
	void update() override; // �����ӵ�״̬
	bool isOffScreen() const; // ����ӵ��Ƿ񳬳���Ļ��Χ
	bool collideWith(GameObject* other); // ����ӵ��Ƿ���������Ϸ������ײ
private:
	GameObject* owner; // �ӵ���ӵ����
	Vector direction; // �ӵ�����
	float speed; // �ӵ��ٶ�
	COLORREF bulletColor = RGB(255, 0, 0); // �ӵ���ɫ
};