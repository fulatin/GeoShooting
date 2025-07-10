#include "ShootSpeedBuffBall.h"
#include "GlobalVal.h"
#include <graphics.h>
#include <iostream>
using namespace GeoShooting;
ShootSpeedBuffBall::ShootSpeedBuffBall(float x, float y, float _increasement)
	: BuffBall(x, y), speedIncrease(_increasement) {
	// ��ʼ��Buff�����ɫ�Ͱ뾶
	buffColor = RGB(255, 0, 128); // ��ɫ
	radius = 10.0f; // �뾶
}
void ShootSpeedBuffBall::draw() {
	// ����Buff��Ϊһ��Բ��
	setlinecolor(buffColor);
	setfillcolor(buffColor);
	setlinestyle(PS_SOLID, 2);
	fillcircle(x, y, radius+ 5.0f * sin(gameTime));
}
void ShootSpeedBuffBall::update() {
	// �����ҵķ�ʽ����Buff���λ�úʹ�С




	
}
void ShootSpeedBuffBall::applyBuff(Player* _player) {
	// Ӧ��BuffЧ����������ҵ�����ٶ�
	if (_player) {
		_player->fireRate += speedIncrease; // �������Ƶ��
		std::cout << "Shoot speed buff applied. New fire rate: " << _player->fireRate << std::endl;
	}
}