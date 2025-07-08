#pragma once
#include "Player.h"
#include "GraphicsHelper.h"
#include "GlobalVal.h"
#include "Constants.h"
#include <iostream>
using namespace std;
using namespace GeoShooting;

Player::Player(float x, float y, float width, float height)
	: GameObject(x, y, width, height), speed(80.0f), health(100.0f), fireRate(1.0f), lastFireTime(0.0f), fireCooldown(1.0f) {
}

void Player::draw() {
		// 绘制玩家的矩形
	GraphicsHelper::drawGlowTriangle(x + width / 2, y + height / 2,max( width,height), RGB(0, 255, 0));
}

void Player::update() {
	ExMessage msg;
	if(peekmessage(&msg)) {
		if (msg.message == WM_KEYDOWN) {
			cout << "key down" << msg.vkcode << endl;
			cout << GeoShooting::deltaTime << endl;
			switch (msg.vkcode)
			{
			case VK_LEFT: // 向左移动
			case 'A':
				x -= speed * GeoShooting::deltaTime;
				if (x < 0) x = 0; // 限制在窗口内
				break;
			case VK_RIGHT: // 向右移动
			case 'D':
				x += speed * GeoShooting::deltaTime;
				if (x + width > WINDOW_WIDTH) x = WINDOW_WIDTH - width; // 限制在窗口内
				break;
			case VK_UP: // 向上移动
			case 'W':
				y -= speed * GeoShooting::deltaTime;
				if (y < 0) y = 0; // 限制在窗口内
				break;
			case VK_DOWN: // 向下移动
			case 'S':
				y += speed * GeoShooting::deltaTime;
				if (y + height > WINDOW_HEIGHT) y = WINDOW_HEIGHT - height; // 限制在窗口内
				break;
			default:
				break;
			}
		}
	}
}