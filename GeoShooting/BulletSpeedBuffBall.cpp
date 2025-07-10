#include "BulletSpeedBuffBall.h"
#include "GlobalVal.h"
using namespace GeoShooting;
BulletSpeedBuffBall::BulletSpeedBuffBall(float x, float y, float _increasement)
	: BuffBall(x, y), bulletSpeedIncrease(_increasement) {
	// 初始化Buff球的颜色和半径
	buffColor = RGB(0, 255, 255); // 青色
	radius = 10.0f; // 半径
}
void BulletSpeedBuffBall::draw() {
	// 绘制Buff球为一个圆形
	setlinecolor(buffColor);
	setfillcolor(buffColor);
	setlinestyle(PS_SOLID, 2);
	fillcircle(x, y, radius + 5.0f * sin(gameTime));
}
void BulletSpeedBuffBall::update() {
	// 以正弦的方式更新Buff球的位置和大小
	// 这里可以添加一些动画效果
}
void BulletSpeedBuffBall::applyBuff(Player* _player) {
	// 应用Buff效果，增加玩家的射击速度
	if (_player) {
		_player->bulletSpeed += bulletSpeedIncrease; // 增加子弹速度
	}
}
// 这里可以添加一些特效或提示
