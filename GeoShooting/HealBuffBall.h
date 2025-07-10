#pragma once

#include "GameObject.h"
#include "Player.h"
#include "BuffBall.h"
// 继承自BuffBall的HealBuffBall类，用于增加玩家生命值的Buff球
class HealBuffBall : public BuffBall {
public:
	HealBuffBall(float x, float y, float _increasement = 20.0f);
	void draw() override; // 绘制Buff球
	void update() override; // 更新Buff球状态
	void applyBuff(Player* _player) override; // 应用Buff效果
private:
	float healthIncrease; // 生命值增加量
	COLORREF buffColor = RGB(0, 255, 0); // Buff球颜色
	float radius = 10.0f; // Buff球半径
};