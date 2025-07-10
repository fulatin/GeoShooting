#pragma once

#include "GameObject.h"
#include "Player.h"
#include "BuffBall.h"
// �̳���BuffBall��HealBuffBall�࣬���������������ֵ��Buff��
class HealBuffBall : public BuffBall {
public:
	HealBuffBall(float x, float y, float _increasement = 20.0f);
	void draw() override; // ����Buff��
	void update() override; // ����Buff��״̬
	void applyBuff(Player* _player) override; // Ӧ��BuffЧ��
private:
	float healthIncrease; // ����ֵ������
	COLORREF buffColor = RGB(0, 255, 0); // Buff����ɫ
	float radius = 10.0f; // Buff��뾶
};