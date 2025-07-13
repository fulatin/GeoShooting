#include "Bullet.h"
#include "GlobalVal.h"
#include "Constants.h"
#include <graphics.h>

using namespace GeoShooting;
Bullet::Bullet(float x, float y, float width, float height, Vector direction, float speed,float damage, GameObject *_owner)
	: GameObject(x, y, width, height), direction(direction), speed(speed), owner(owner),damage(damage) {
	direction.normalize(); // ȷ�������ǵ�λ����
	owner = _owner; // �����ӵ���ӵ����
	bulletColor = RGB(0,0,255); // �����ӵ���ɫΪ��ɫ

}
// �����ӵ�Ϊһ����
void Bullet::draw() {
	setlinecolor(bulletColor);
	setlinestyle(PS_SOLID, 10);
	// �����ӵ�Ϊһ����
	line(x, y, x + direction.x * width, y + direction.y * height);
}
void Bullet::update() {
	// �����ӵ�λ��
	x += direction.x * speed * deltaTime;
	y += direction.y * speed * deltaTime;
}
// ����ӵ��Ƿ񳬳���Ļ��Χ
bool Bullet::isOffScreen() const {
	return x < 0 || x > getwidth() || y < 0 || y > getheight();
}
bool Bullet::collideWith(GameObject* other) {
	// ����ӵ��Ƿ���������Ϸ������ײ
	if (other == owner) return false; // �����ͬһ��ӵ���ߣ��򲻼����ײ
	// �򵥵ľ�����ײ���
	return x < other->x + other->width &&
		   x + width > other->x &&
		   y < other->y + other->height &&
		   y + height > other->y;
}

bool Bullet::collideWith(Enemy* _enemy) {
	// ����ӵ��Ƿ��������ײ
	if (_enemy->isOffScreen()) return false; // ������˳�����Ļ��Χ���򲻼����ײ
	// ���Ӿ�ȷ����ײ���
	Vector bulletCenter(x + width / 2, y + height / 2);
	Vector enemyCenter(_enemy->x , _enemy->y );
	return (bulletCenter - enemyCenter).length() < (width +max( _enemy->width ,_enemy->height)) ; // ����ӵ�������������ĵľ����Ƿ�С�����߰뾶֮��
}

bool Bullet::collideWith(Player* _player) {
	// ����ӵ��Ƿ��������ײ
	// ���Ӿ�ȷ����ײ���
	Vector bulletCenter(x + width / 2, y + height / 2);
	Vector playerCenter(_player->x + _player->width / 2, _player->y + _player->height / 2);
	return (bulletCenter - playerCenter).length() < (width + max(_player->width, _player->height)); // ����ӵ�������������ĵľ����Ƿ�С�����߰뾶֮��
}

