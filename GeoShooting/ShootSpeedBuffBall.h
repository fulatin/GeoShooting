#pragma once
#include "Buffball.h"

class ShootSpeedBuffBall : public BuffBall {
public:
	ShootSpeedBuffBall(float x, float y,float _increasement = 1.2);
	void draw() override; // ����Buff��
	void update() override; // ����Buff��״̬
	void applyBuff(Player* _player) override; // Ӧ��BuffЧ��
private:
	float speedIncrease; // ����ٶ�������

};
