#pragma once
#include "Buffball.h"

class ShootSpeedBuffBall : public BuffBall {
public:
	ShootSpeedBuffBall(float x, float y,float _increasement = 1.2);
	void draw() override; // 绘制Buff球
	void update() override; // 更新Buff球状态
	void applyBuff(Player* _player) override; // 应用Buff效果
private:
	float speedIncrease; // 射击速度增加量

};
