#include "ShootableEnemy.h"
#include "GlobalVal.h"
#include "SoundManager.h"
#include "constants.h"
using namespace GeoShooting;
ShootableEnemy::ShootableEnemy(float x, float y, float width, float height, Vector direction, float speed, Player* _target)
	: Enemy(x, y, width, height, direction, speed, _target) {
	// ��ʼ��������˵�����
	shootInterval = 2.0f; // ������ʱ��
	lastShootTime = 0.0f; // �ϴ����ʱ��
	bulletSpeed = 800.0f+gameTime; // �ӵ��ٶ�
	bulletDamage = 5.0f+gameTime/10; // �ӵ��˺�
	enemyColor = RGB(255, 165, 0); // ���������ɫ

}
void ShootableEnemy::update() {
	// �����������״̬
	Enemy::update(); // ���û���ĸ��·���
	// ����Ƿ�������
	if (gameTime - lastShootTime >= shootInterval&&!isOffScreen()) {
		shoot(); // ���
		lastShootTime = gameTime; // �����ϴ����ʱ��
	}

}
void ShootableEnemy::draw() {
	// �����������
	Enemy::draw(); // ���û���Ļ��Ʒ���

	// ��һ��ָ����ҵĵȱ�С������
	Vector playerPosition = targetPlayer->getPosition(); // ��ȡ���λ��
	Vector directionToPlayer = playerPosition - Vector(x, y); // ����ָ����ҵķ���
	directionToPlayer.normalize(); // ȷ�������ǵ�λ����
	float triangleSize = 10.0f; // �����δ�С
	int offset = max(width, height); // ƫ������ȷ�������β�������ص�
	Vector trangleCenter = Vector(x,y)+directionToPlayer*offset; // ����������λ��
	Vector center2vert = directionToPlayer * triangleSize; // �����ζ��㵽���ĵ�����

	setlinecolor(enemyColor); // ������������ɫ
	Vector vertex1 = center2vert + trangleCenter; // ��һ������
	Vector vertex2 = center2vert.rotate(2 * PI / 3) + trangleCenter; // �ڶ�������
	Vector vertex3 = center2vert.rotate(4 * PI / 3) + trangleCenter; // ����������
	line(vertex1.x, vertex1.y, vertex2.x, vertex2.y); // ���Ƶ�һ����
	line(vertex2.x, vertex2.y, vertex3.x, vertex3.y); // ���Ƶڶ�����
	line(vertex3.x, vertex3.y, vertex1.x, vertex1.y); // ���Ƶ�������
}
void ShootableEnemy::shoot() {
	// �����ӵ�����ӵ���Ϸ�����б���
	Vector playerPosition = targetPlayer->getPosition(); // ��ȡ���λ��
	Vector direction = playerPosition - Vector(x, y); // ����ָ����ҵķ���
	float distanceToPlayer = direction.length(); // ������������֮��ľ���

	Vector playerSpeed = targetPlayer->speed; // ��ȡ����ٶ�
	// ��������ҵľ������ҵ��ٶȼ����ӵ�����

	direction = direction + playerSpeed * (distanceToPlayer / bulletSpeed + 0.3 ); // ���������Կ�����ҵ��ƶ�
	  
	direction.normalize(); // ȷ�������ǵ�λ����
	Bullet* bullet = new Bullet(x, y, 10.0f, 10.0f, direction, bulletSpeed, bulletDamage, this); // �����ӵ�
	bullet->setBulletColor(RGB(255, 123, 0)); // �����ӵ���ɫΪ��ɫ

	bullets.insert(bullet); // ���ӵ���ӵ���Ϸ�����б���


	SoundManager::getInstance().playSound(L"enemyShoot", 1000); // ���������Ч
}