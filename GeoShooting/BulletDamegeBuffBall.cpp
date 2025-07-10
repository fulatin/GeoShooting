#include "BulletDamageBuffBall.h"
#include "GlobalVal.h"
using namespace GeoShooting;
BulletDamageBuffBall::BulletDamageBuffBall(float x, float y, float _increasement)
	: BuffBall(x, y), damageIncrease(_increasement) {
	// 初始化Buff球的颜色和半径
	buffColor = RGB(255, 128,0);
	radius = 10.0f; // 半径
	wcscpy_s(buffName, L"Damage"); // 设置Buff名称
}
void BulletDamageBuffBall::draw() {
	// 绘制Buff球为一个圆形
	setlinecolor(buffColor);
	setfillcolor(buffColor);
	setlinestyle(PS_SOLID, 2);
	fillcircle(x, y, radius + 2.0f * sin(gameTime));
}
void BulletDamageBuffBall::update() {
	// 以正弦的方式更新Buff球的位置和大小
	// 这里可以添加一些动画效果
}
void BulletDamageBuffBall::applyBuff(Player* _player) {
	// 应用Buff效果，增加玩家的子弹伤害
	if (_player) {
		_player->bulletDamage += damageIncrease; // 增加子弹伤害
	}
}
