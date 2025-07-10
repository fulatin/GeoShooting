#pragma once
#include "GameObject.h"
#include "Player.h"
#include "BuffBall.h"
class BulletDamageBuffBall : public BuffBall {
public:
	BulletDamageBuffBall(float x, float y, float _increasement = 1.2);
	void draw() override; // 绘制Buff球
	void update() override; // 更新Buff球状态
	void applyBuff(Player* _player) override; // 应用Buff效果
private:
	float damageIncrease; // 子弹伤害增加量
	COLORREF buffColor = RGB(255, 0, 128); // Buff球颜色
	float radius = 10.0f; // Buff球半径
};
