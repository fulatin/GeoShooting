#include "ShootSpeedBuffBall.h"
#include "GlobalVal.h"
#include <graphics.h>
#include <iostream>
using namespace GeoShooting;
ShootSpeedBuffBall::ShootSpeedBuffBall(float x, float y, float _increasement)
	: BuffBall(x, y), speedIncrease(_increasement) {
	// ��ʼ��Buff�����ɫ�Ͱ뾶
	buffColor = RGB(255, 255, 0); // ��ɫ
	radius = 10.0f; // �뾶
}
void ShootSpeedBuffBall::draw() {
	// ����Buff��Ϊһ��Բ��
	setlinecolor(buffColor);
	setfillcolor(buffColor);
	fillcircle(x, y, radius);
}
void ShootSpeedBuffBall::update() {
	// ����Buff��״̬�������Ҫ��
	// ����������һЩ����Ч�����ƶ��߼�
}
void ShootSpeedBuffBall::applyBuff(Player* _player) {
	// Ӧ��BuffЧ����������ҵ�����ٶ�
	if (_player) {
		_player->fireRate += speedIncrease; // �������Ƶ��
		std::cout << "Shoot speed buff applied. New fire rate: " << _player->fireRate << std::endl;
	}
}