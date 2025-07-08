#pragma once
#include "GameObject.h"

class Player :public GameObject {

public:
	Player(float x, float y, float width, float height);
	void draw() override; // �������
	void update() override; // �������״̬
	void shoot(float x, float y); // ������ x,y Ϊ���λ��
private:
	float speed; // ����ƶ��ٶ�
	float health; // �������ֵ
	float fireRate; // ������Ƶ��
	float lastFireTime; // �ϴ����ʱ��
	float fireCooldown; // �����ȴʱ��

};