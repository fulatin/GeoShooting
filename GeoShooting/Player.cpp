#pragma once
#include "Player.h"
#include "GlobalVal.h"
#include "Constants.h"
#include "Bullet.h"
#include "SoundManager.h"
#include<graphics.h>

using namespace GeoShooting;

Player::Player(float x, float y, float width, float height)
	: GameObject(x, y, width, height), health(100.0f),
	fireRate(2), lastFireTime(0.0f),
	playerSurface(2*width,2*height) {
	playerDirection = { 1,0 }; // ��ʼ��������
	updateTrangle(); // ���������ζ���
	SoundManager::getInstance().loadSound(L"audio/laser.wav", L"playerShoot"); // ���������Ч
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

	// ������ҵ�Ѫ����


		float healthBarWidth = width * (health / 100.0f); // Ѫ����ȸ�������ֵ����
		setfillcolor(RGB(0, 255, 0)); // ����Ѫ����ɫΪ��ɫ
		// Ѫ��Ϊ���Σ�λ������������·�
		setlinecolor(RGB(0, 255, 0)); // ����Ѫ���߿���ɫΪ��ɫ
		setlinestyle(PS_SOLID, 1); // ����Ѫ���߿���ʽ
		rectangle(x - width / 2, y + height / 2 + 10, x + width / 2, y + height / 2 + 20);
		fillrectangle(x - width / 2, y + height / 2 + 10, x - width/2 + healthBarWidth, y + height / 2 + 20);

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

	// ���speedDir���ٶȷ���ͼӴ����Ч��
	if (speedDir.dot(speed) < 0) {
		speedDir = speedDir * 3.0f;
	} 
	else if (speedDir.length() < 0.1f) {
		speed = speed * 0.97f; // ���û�а��������
	}
	
	speed = speed + speedDir * acc * realDeltaTime; // �����ٶ�
	
	
	if(speed.length()> mxSpeed) {
		speed.normalize();
		speed = speed * mxSpeed; // �����ٶ�
	}
	// ����λ��
	
	x += speed.x * realDeltaTime;
	y += speed.y * realDeltaTime;
	
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
			// ����Խ����ķ�Խ��
			score -= 1.0f / fireRate; // ���ٷ���
		}

	}
	updateTrangle(); // ���������ζ���
}
void Player::shoot() {
	// �����µ��ӵ�����
	Bullet* bullet = new Bullet(trangle[0].x,trangle[0].y, width , height , playerDirection, bulletSpeed,bulletDamage, this);
	bullets.insert(bullet); // ���ӵ���ӵ�ȫ���ӵ�������
	SoundManager::getInstance().playSound(L"playerShoot", 1000); // ���������Ч

}
