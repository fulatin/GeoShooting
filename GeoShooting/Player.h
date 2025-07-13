#pragma once
#include "GameObject.h"
#include "Vector.h"

using namespace GeoShooting;
class Player :public GameObject {

public:
	float health; // �������ֵ
	Vector trangle[3]; // ��������ζ���
	Player(float x, float y, float width, float height);
	void draw() override; // �������
	void update() override; // �������״̬
	void shoot(); // ������ x,y Ϊ���λ��
	Vector getPosition() const { return Vector(x, y); } // ��ȡ���λ��
	// �������Ƿ���������Ϸ������ײ
	bool collideWith(GameObject* other) {
		// �򵥵ľ�����ײ���
		return x < other->x + other->width &&
			   x + width > other->x &&
			   y < other->y + other->height &&
			   y + height > other->y;
	}
	Vector speed;
	float mxSpeed = 600.0f; // ����ƶ��ٶ�
	float acc = 1500.0f; // ��Ҽ��ٶ�
	float fireRate; // ������Ƶ�� һ�뼸��
	float lastFireTime; // �ϴ����ʱ��
	float frac = 0.7; // ���ת��ʱ������
	float bulletDamage = 10.0f; // �ӵ��˺�
	float bulletSpeed = 1000.0f; // �ӵ��ٶ�
	void updateTrangle();
	COLORREF playerColor = RGB(0, 255, 0); // �����ɫ
	// ��ҵĻ��ƶ���
	Vector playerDirection; // ��ҷ��� ȷ���ǵ�λ����
	Vector targetDirection; // ���Ŀ�귽��
	IMAGE playerSurface;
};