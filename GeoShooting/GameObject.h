#pragma once

#include<graphics.h>

class GameObject {
public:
	float x, y; // �����λ��
	float width, height; // ����Ŀ�Ⱥ͸߶�
	GameObject(float x, float y, float width, float height)
		: x(x), y(y), width(width), height(height) {
	}
	virtual ~GameObject() = default;
	// ��������
	virtual void draw() = 0;
	virtual void update() = 0;
	bool need2Delete = false; // �Ƿ���Ҫɾ��
};