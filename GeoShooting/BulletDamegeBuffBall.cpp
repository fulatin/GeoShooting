#include "BulletDamageBuffBall.h"
#include "GlobalVal.h"
using namespace GeoShooting;
BulletDamageBuffBall::BulletDamageBuffBall(float x, float y, float _increasement)
	: BuffBall(x, y), damageIncrease(_increasement) {
	// ��ʼ��Buff�����ɫ�Ͱ뾶
	buffColor = RGB(255, 128,0);
	radius = 10.0f; // �뾶
	wcscpy_s(buffName, L"Damage"); // ����Buff����
}
void BulletDamageBuffBall::draw() {
	// ����Buff��Ϊһ��Բ��
	setlinecolor(buffColor);
	setfillcolor(buffColor);
	setlinestyle(PS_SOLID, 2);
	fillcircle(x, y, radius + 2.0f * sin(gameTime));
}
void BulletDamageBuffBall::update() {
	// �����ҵķ�ʽ����Buff���λ�úʹ�С
	// ����������һЩ����Ч��
}
void BulletDamageBuffBall::applyBuff(Player* _player) {
	// Ӧ��BuffЧ����������ҵ��ӵ��˺�
	if (_player) {
		_player->bulletDamage += damageIncrease; // �����ӵ��˺�
	}
}
