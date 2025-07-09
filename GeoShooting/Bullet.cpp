#include "Bullet.h"
#include "GlobalVal.h"
#include "Constants.h"
#include <graphics.h>

#include <iostream>
using namespace std;
using namespace GeoShooting;
Bullet::Bullet(float x, float y, float width, float height, Vector direction, float speed, GameObject *_owner)
	: GameObject(x, y, width, height), direction(direction), speed(speed), owner(owner) {
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
