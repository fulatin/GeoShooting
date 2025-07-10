#include "BulletSpeedBuffBall.h"
#include "GlobalVal.h"
using namespace GeoShooting;
BulletSpeedBuffBall::BulletSpeedBuffBall(float x, float y, float _increasement)
	: BuffBall(x, y), bulletSpeedIncrease(_increasement) {
	// ��ʼ��Buff�����ɫ�Ͱ뾶
	buffColor = RGB(0, 255, 255); // ��ɫ
	radius = 10.0f; // �뾶
}
void BulletSpeedBuffBall::draw() {
	// ����Buff��Ϊһ��Բ��
	setlinecolor(buffColor);
	setfillcolor(buffColor);
	setlinestyle(PS_SOLID, 2);
	fillcircle(x, y, radius + 5.0f * sin(gameTime));
}
void BulletSpeedBuffBall::update() {
	// �����ҵķ�ʽ����Buff���λ�úʹ�С
	// ����������һЩ����Ч��
}
void BulletSpeedBuffBall::applyBuff(Player* _player) {
	// Ӧ��BuffЧ����������ҵ�����ٶ�
	if (_player) {
		_player->bulletSpeed += bulletSpeedIncrease; // �����ӵ��ٶ�
	}
}
// ����������һЩ��Ч����ʾ
