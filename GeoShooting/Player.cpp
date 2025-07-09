#pragma once
#include "Player.h"
#include "GlobalVal.h"
#include "Constants.h"
#include "Bullet.h"
#include<graphics.h>
#include <iostream>
using namespace std;
using namespace GeoShooting;

Player::Player(float x, float y, float width, float height)
	: GameObject(x, y, width, height), health(100.0f),
	fireRate(2), lastFireTime(0.0f),
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
	// ����Ƿ񳬳���Ļ��Χ ���ĳһ�㳬�������ٶȷ���
	if (trangle[0].x < 0 || trangle[0].x > getwidth() ||
		trangle[0].y < 0 || trangle[0].y > getheight()) {
		speed.x = -speed.x; // �����ٶ�
		speed.y = -speed.y;
	}
	if (trangle[1].x < 0 || trangle[1].x > getwidth() ||
		trangle[1].y < 0 || trangle[1].y > getheight()) {
		speed.x = -speed.x; // �����ٶ�
		speed.y = -speed.y;
	}
	if (trangle[2].x < 0 || trangle[2].x > getwidth() ||
		trangle[2].y < 0 || trangle[2].y > getheight()) {
		speed.x = -speed.x; // �����ٶ�
		speed.y = -speed.y;
	}


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
	if(speedDir.length() < 0.1f) {
		speed = speed * 0.96f; // ���û�а��������
	}
	else {
		speed = speed + speedDir * acc * deltaTime; // �����ٶ�
	}
	if(speed.length()> mxSpeed) {
		speed.normalize();
		speed = speed * mxSpeed; // �����ٶ�
	}
	// ����λ��
	
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

	// �첽��ȡ��ҵ���¼��Է����ӵ�
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
		if(GetTickCount()/1000.0-lastFireTime > 1.0 / fireRate) {
			shoot(); // �����ӵ�
			lastFireTime = GetTickCount() / 1000.0; // �����ϴ����ʱ��
		}

	}
	updateTrangle(); // ���������ζ���
}
void Player::shoot() {
	// �����µ��ӵ�����
	Bullet* bullet = new Bullet(trangle[0].x,trangle[0].y, width , height , playerDirection, 1000.0f, this);
	bullets.insert(bullet); // ���ӵ���ӵ�ȫ���ӵ�������
}