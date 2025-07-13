#include "Bullet.h"
#include "GlobalVal.h"
#include "Constants.h"
#include <graphics.h>

using namespace GeoShooting;
Bullet::Bullet(float x, float y, float width, float height, Vector direction, float speed,float damage, GameObject *_owner)
	: GameObject(x, y, width, height), direction(direction), speed(speed), owner(owner),damage(damage) {
	direction.normalize(); // 确保方向是单位向量
	owner = _owner; // 设置子弹的拥有者
	bulletColor = RGB(0,0,255); // 设置子弹颜色为红色

}
// 绘制子弹为一条线
void Bullet::draw() {
	setlinecolor(bulletColor);
	setlinestyle(PS_SOLID, 10);
	// 绘制子弹为一条线
	line(x, y, x + direction.x * width, y + direction.y * height);
}
void Bullet::update() {
	// 更新子弹位置
	x += direction.x * speed * deltaTime;
	y += direction.y * speed * deltaTime;
}
// 检查子弹是否超出屏幕范围
bool Bullet::isOffScreen() const {
	return x < 0 || x > getwidth() || y < 0 || y > getheight();
}
bool Bullet::collideWith(GameObject* other) {
	// 检查子弹是否与其他游戏对象碰撞
	if (other == owner) return false; // 如果是同一个拥有者，则不检测碰撞
	// 简单的矩形碰撞检测
	return x < other->x + other->width &&
		   x + width > other->x &&
		   y < other->y + other->height &&
		   y + height > other->y;
}

bool Bullet::collideWith(Enemy* _enemy) {
	// 检查子弹是否与敌人碰撞
	if (_enemy->isOffScreen()) return false; // 如果敌人超出屏幕范围，则不检测碰撞
	// 更加精确的碰撞检测
	Vector bulletCenter(x + width / 2, y + height / 2);
	Vector enemyCenter(_enemy->x , _enemy->y );
	return (bulletCenter - enemyCenter).length() < (width +max( _enemy->width ,_enemy->height)) ; // 检查子弹中心与敌人中心的距离是否小于两者半径之和
}

bool Bullet::collideWith(Player* _player) {
	// 检查子弹是否与玩家碰撞
	// 更加精确的碰撞检测
	Vector bulletCenter(x + width / 2, y + height / 2);
	Vector playerCenter(_player->x + _player->width / 2, _player->y + _player->height / 2);
	return (bulletCenter - playerCenter).length() < (width + max(_player->width, _player->height)); // 检查子弹中心与玩家中心的距离是否小于两者半径之和
}

