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
	playerDirection = { 1,0 }; // ��ʼ��������
	updateTrangle(); // ���������ζ���
}


// ����playerDirection�ķ�����������ζ���
void Player::updateTrangle() {
	trangle[0] = Vector(x, y) + playerDirection * width * 2 / 3;
	Vector leftDir = playerDirection.rotate(-PI / 2); // ��෽��
	trangle[1] = Vector(x, y) - playerDirection * width * 1 / 3 + leftDir * width / 2;
	trangle[2] = Vector(x, y) - playerDirection * width * 1 / 3 - leftDir * width / 2;
}
void Player::draw() {
	setlinecolor(playerColor);
	setlinestyle(PS_SOLID, 2);
	// �������������
	for(int i = 0; i < 3; i++) {
		line(trangle[i].x, trangle[i].y, trangle[(i + 1) % 3].x, trangle[(i + 1) % 3].y);
	}

}

void Player::update() {
	// ��Ҽ��̿���λ��
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

	speed = speed + speedDir * acc * deltaTime; // �����ٶ�
	if(speed.length()> mxSpeed) {
		speed.normalize();
		speed = speed * mxSpeed; // �����ٶ�
	}
	x += speed.x * deltaTime;
	y += speed.y * deltaTime;

	// ��������Ʒ���
	POINT mousePos;
	GetCursorPos(&mousePos); // ��ȡ���λ��
	ScreenToClient(GetHWnd(), &mousePos); // ת��Ϊ��������
	targetDirection = Vector(mousePos.x, mousePos.y) - Vector(x, y); // ����Ŀ�귽��
	targetDirection.normalize(); // ��һ��Ŀ�귽��
	playerDirection = playerDirection * frac + targetDirection * (1 - frac); // ƽ�����ɵ�Ŀ�귽��
	playerDirection.normalize(); // ȷ���ǵ�λ����
	updateTrangle(); // ���������ζ���
}