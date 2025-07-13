#pragma once
#include "Enemy.h"

class ShootableEnemy : public Enemy {
	public:
		ShootableEnemy(float x, float y, float width, float height, Vector direction, float speed, Player* _target);
	void update() override; // �����������״̬
	void draw() override; // �����������
	void shoot(); // �������
	float getBulletSpeed() const { return bulletSpeed; } // ��ȡ�ӵ��ٶ�
	float getBulletDamage() const { return bulletDamage; } // ��ȡ�ӵ��˺�
private:
	float shootInterval; // ������ʱ��
	float lastShootTime; // �ϴ����ʱ��
	float bulletSpeed; // �ӵ��ٶ�
	float bulletDamage; // �ӵ��˺�
};