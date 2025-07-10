#pragma once

// 可以给玩家强化的球
// 是抽象基类
#include "GameObject.h"
#include "Vector.h"
#include "Player.h"
class BuffBall : public GameObject {
public:
	BuffBall(float x, float y): GameObject(x, y, 50.0f, 50.0f), buffColor(RGB(255, 255, 0)), radius(25.0f) {
		// 初始化Buff球的颜色和半径
	}
	virtual ~BuffBall() = default; // 虚析构函数
	virtual void draw() = 0; // 绘制Buff球
	virtual void update() = 0; // 更新Buff球状态
	virtual void applyBuff(Player *_player) = 0; // 应用Buff效果，纯虚函数
protected:
	COLORREF buffColor; // Buff球颜色
	float radius; // Buff球半径
};