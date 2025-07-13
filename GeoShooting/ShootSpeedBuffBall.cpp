#include "ShootSpeedBuffBall.h"
#include "GlobalVal.h"
using namespace GeoShooting;
ShootSpeedBuffBall::ShootSpeedBuffBall(float x, float y, float _increasement)
	: BuffBall(x, y), speedIncrease(_increasement) {
	// ��ʼ��Buff�����ɫ�Ͱ뾶
	buffColor = RGB(255, 0, 128); // ��ɫ
	radius = 10.0f; // �뾶

	wcscpy_s(buffName, L"Shoot Speed up"); // ����Buff����

}
void ShootSpeedBuffBall::draw() {
	if (applied) {
		showEffect.update(); // ����Buff�����ʾЧ��
		if (showEffect.isFinished()) {
			need2Delete = true; // ������Ҫɾ����־
		}
		return;
	}
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
	if (_player&&!applied) {
		_player->fireRate += speedIncrease; // �������Ƶ��
		if (_player->fireRate > 7.0f) {
			_player->fireRate = 7.0f;
		}
		SoundManager::getInstance().playSound(L"shootSpeedBuff", 1000); // ����BuffӦ�óɹ�����Ч
	}
	applied = true; // ����Buff��Ӧ�ñ�־

	showEffect.start(); // ��ʼ��ʾЧ������
}