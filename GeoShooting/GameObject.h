#pragma once

#include<graphics.h>

class GameObject {
public:
	float x, y; // 物体的位置
	float width, height; // 物体的宽度和高度
	GameObject(float x, float y, float width, float height)
		: x(x), y(y), width(width), height(height) {
	}
	virtual ~GameObject() = default;
	// 绘制物体
	virtual void draw() = 0;
	virtual void update() = 0;
	bool need2Delete = false; // 是否需要删除
};