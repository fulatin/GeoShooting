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
		// ������ҵľ���
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
			case VK_LEFT: // �����ƶ�
			case 'A':
				x -= speed * GeoShooting::deltaTime;
				if (x < 0) x = 0; // �����ڴ�����
				break;
			case VK_RIGHT: // �����ƶ�
			case 'D':
				x += speed * GeoShooting::deltaTime;
				if (x + width > WINDOW_WIDTH) x = WINDOW_WIDTH - width; // �����ڴ�����
				break;
			case VK_UP: // �����ƶ�
			case 'W':
				y -= speed * GeoShooting::deltaTime;
				if (y < 0) y = 0; // �����ڴ�����
				break;
			case VK_DOWN: // �����ƶ�
			case 'S':
				y += speed * GeoShooting::deltaTime;
				if (y + height > WINDOW_HEIGHT) y = WINDOW_HEIGHT - height; // �����ڴ�����
				break;
			default:
				break;
			}
		}
	}
}