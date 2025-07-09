#pragma once
#include "Player.h"
#include "GraphicsHelper.h"
#include "GlobalVal.h"
#include "Constants.h"
#include<graphics.h>
#include <iostream>
using namespace std;
using namespace GeoShooting;

Player::Player(float x, float y, float width, float height)
	: GameObject(x, y, width, height), health(100.0f),
	fireRate(1.0f), lastFireTime(0.0f), fireCooldown(1.0f),playerSurface(2*width,2*height) {
	IMAGE tmp(playerSurface);

	// 创建有辉光效果的玩家

	SetWorkingImage(&playerSurface);
	GraphicsHelper::drawTriangle(width / 2, height / 2, width, RGB(255, 0, 0));
	//setbkcolor(RGB(255, 255, 255));
	//cleardevice();
	SetWorkingImage(&tmp);
	GraphicsHelper::drawTriangle(width/2, height/2, width, RGB(255, 0, 0));
	GraphicsHelper::applyGlowWithGDI(&playerSurface, &tmp, 10, false);
	SetWorkingImage(nullptr);
}

void Player::draw() {
	GraphicsHelper::drawTransparentImage(x, y, &playerSurface, BLACK);
	//putimage(x, y, &playerSurface);
}

void Player::update() {
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
}