#pragma once
#include "GameObject.h"
#include "Player.h"
#include "BuffBall.h"
class BulletSpeedBuffBall : public BuffBall {
public:
	BulletSpeedBuffBall(float x, float y, float _increasement = 142);
	void draw() override; // ����Buff��
	void update() override; // ����Buff��״̬
	void applyBuff(Player* _player) override; // Ӧ��BuffЧ��
private:
	float bulletSpeedIncrease; // �ӵ��˺�������
	COLORREF buffColor = RGB(255, 0, 128); // Buff����ɫ
	float radius = 10.0f; // Buff��뾶
};

