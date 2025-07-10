#include "Enemy.h"
#include "GlobalVal.h"
#include "Constants.h"
#include <graphics.h>
#include <iostream>
using namespace std;

Enemy::Enemy(float x, float y, float width, float height, Vector direction, float speed,Player *_target)
	: GameObject(x, y, width, height), direction(direction), speed(speed) 
	, targetPlayer(_target) 
{
	direction.normalize(); // ȷ�������ǵ�λ����
	enemyColor = RGB(255, 0, 0); // ���õ�����ɫΪ��ɫ
}

// ���Ƶ���Ϊһ������, x , y Ϊ��������
void Enemy::draw() {
	setlinecolor(enemyColor);
	setlinestyle(PS_SOLID, 2);
	// ���Ƶ���Ϊһ������
	rectangle(x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}
void Enemy::update() {
	// ���µ���λ��,����directionЩ��������ƶ�
	Vector modifiedDirection = direction; // ���Ʒ���
	if (targetPlayer) {
		// ������˺����֮��ľ���
		float distanceToPlayer = direction.distance(Vector(targetPlayer->x, targetPlayer->y));
		if (distanceToPlayer > 0) {
			// ������������֮���о��룬��������ƶ�
			modifiedDirection.x += (targetPlayer->x - x) / distanceToPlayer * 0.6f; // ����ҷ���΢��
			modifiedDirection.y += (targetPlayer->y - y) / distanceToPlayer * 0.6f; // ����ҷ���΢��
			modifiedDirection.normalize(); // ȷ�������ǵ�λ����
		}
	}
	x += direction.x * speed * deltaTime;
	y += direction.y * speed * deltaTime;
	//cout << "Enemy position: " << x << ", " << y << endl; // �������λ��
}
// �������Ƿ񳬳���Ļ��Χ
bool Enemy::isOffScreen() const {
	return x < 0 || x > getwidth() || y < 0 || y > getheight();
}
bool Enemy::collideWith(GameObject* other) {
	// �������Ƿ���������Ϸ������ײ
	// �򵥵ľ�����ײ���
	return x - width / 2 < other->x + other->width &&
		   x + width / 2 > other->x &&
		   y - height / 2 < other->y + other->height &&
		   y + height / 2 > other->y;
}

bool Enemy::collideWith(Player* _player) {

	// ��������ζ�������ε���ײ

	for (int i = 0; i < 3; ++i) {
		Vector curr = targetPlayer->trangle[i];

		if ((curr.x >= x - width / 2) && (curr.x <= x + width / 2) &&
			(curr.y >= y - height / 2) && (curr.y <= y + height / 2) ) {
			return true; // ��������ζ����ڵ��˾����ڣ�������ײ
		}
	}
	return false; // û����ײ
}