#pragma once
#include "GameObject.h"
#include "Vector.h"

using namespace GeoShooting;
class Player :public GameObject {

public:
	Player(float x, float y, float width, float height);
	void draw() override; // �������
	void update() override; // �������״̬
	void shoot(float x, float y); // ������ x,y Ϊ���λ��
private:
	Vector speed;
	float mxSpeed = 500.0f; // ����ƶ��ٶ�
	float acc = 1000.0f; // ��Ҽ��ٶ�
	float health; // �������ֵ
	float fireRate; // ������Ƶ��
	float lastFireTime; // �ϴ����ʱ��
	float fireCooldown; // �����ȴʱ��
	float frac = 0.90;
	// ��ҵĻ��ƶ���
	IMAGE playerSurface;
};