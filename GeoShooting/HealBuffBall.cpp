#include "HealBuffBall.h"
#include "GlobalVal.h"
using namespace GeoShooting;
HealBuffBall::HealBuffBall(float x, float y, float _increasement)
	: BuffBall(x, y), healthIncrease(_increasement) {
	// ��ʼ��Buff�����ɫ�Ͱ뾶
	buffColor = RGB(0, 128, 128); // ��ɫ
	radius = 10.0f; // �뾶
}
void HealBuffBall::draw() {
	// ����Buff��Ϊһ��Բ��
	setlinecolor(buffColor);
	setfillcolor(buffColor);
	setlinestyle(PS_SOLID, 2);
	fillcircle(x, y, radius + 5.0f * sin(gameTime));
}
void HealBuffBall::update() {

}
void HealBuffBall::applyBuff(Player* _player) {
	// Ӧ��BuffЧ����������ҵ�����ֵ
	if (_player) {
		_player->health += healthIncrease; // ��������ֵ
		if (_player->health > 100.0f) { // ȷ������ֵ������100
			_player->health = 100.0f;
		}
	}
}
