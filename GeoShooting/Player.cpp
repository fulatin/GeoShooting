#pragma once
#include "Player.h"

#include "GlobalVal.h"
#include "Constants.h"
#include<graphics.h>
#include <iostream>
using namespace std;
using namespace GeoShooting;

Player::Player(float x, float y, float width, float height)
	: GameObject(x, y, width, height), health(100.0f),
	fireRate(1.0f), lastFireTime(0.0f), fireCooldown(1.0f),
	playerSurface(2*width,2*height) {
	playerDirection = { 1,0 }; // 初始方向向右
	updateTrangle(); // 更新三角形顶点
}


// 根据playerDirection的方向更新三角形顶点
void Player::updateTrangle() {
	trangle[0] = Vector(x, y) + playerDirection * width * 2 / 3;
	Vector leftDir = playerDirection.rotate(-PI / 2); // 左侧方向
	trangle[1] = Vector(x, y) - playerDirection * width * 1 / 3 + leftDir * width / 2;
	trangle[2] = Vector(x, y) - playerDirection * width * 1 / 3 - leftDir * width / 2;
}
void Player::draw() {
	setlinecolor(playerColor);
	setlinestyle(PS_SOLID, 2);
	// 绘制玩家三角形
	for(int i = 0; i < 3; i++) {
		line(trangle[i].x, trangle[i].y, trangle[(i + 1) % 3].x, trangle[(i + 1) % 3].y);
	}

}

void Player::update() {
	// 玩家键盘控制位置
	Vector speedDir = {0,0};
	if (GetAsyncKeyState('A') & 0x8000 || GetAsyncKeyState(VK_LEFT) & 0x8000) {
		speedDir.x += -1;
	}
	else if (GetAsyncKeyState('D') & 0x8000 || GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		speedDir.x += 1;
	}
	if (GetAsyncKeyState('W') & 0x8000 || GetAsyncKeyState(VK_UP) & 0x8000) {
		speedDir.y += -1;
	}
	else if (GetAsyncKeyState('S') & 0x8000 || GetAsyncKeyState(VK_DOWN) & 0x8000) {
		speedDir.y += 1;
	}

	speedDir.normalize();

	speed = speed + speedDir * acc * deltaTime; // 更新速度
	if(speed.length()> mxSpeed) {
		speed.normalize();
		speed = speed * mxSpeed; // 限制速度
	}
	x += speed.x * deltaTime;
	y += speed.y * deltaTime;

	// 玩家鼠标控制方向
	POINT mousePos;
	GetCursorPos(&mousePos); // 获取鼠标位置
	ScreenToClient(GetHWnd(), &mousePos); // 转换为窗口坐标
	targetDirection = Vector(mousePos.x, mousePos.y) - Vector(x, y); // 计算目标方向
	targetDirection.normalize(); // 归一化目标方向
	playerDirection = playerDirection * frac + targetDirection * (1 - frac); // 平滑过渡到目标方向
	playerDirection.normalize(); // 确保是单位向量
	updateTrangle(); // 更新三角形顶点
}