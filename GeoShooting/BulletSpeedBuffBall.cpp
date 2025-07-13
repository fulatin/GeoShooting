#include "BulletSpeedBuffBall.h"
#include "GlobalVal.h"
using namespace GeoShooting;
BulletSpeedBuffBall::BulletSpeedBuffBall(float x, float y, float _increasement)
	: BuffBall(x, y), bulletSpeedIncrease(_increasement) {
	// 初始化Buff球的颜色和半径
	buffColor = RGB(0, 255, 255); // 青色
	radius = 10.0f; // 半径

	wcscpy_s(buffName, L"Bullet Speed up"); // 设置Buff名称

}
void BulletSpeedBuffBall::draw() {
	if (applied) {
		showEffect.update(); // 更新Buff球的显示效果
		if (showEffect.isFinished()) {
			need2Delete = true; // 设置需要删除标志
		}
		return;
	}
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
	if (_player&&!applied) {
		_player->bulletSpeed += bulletSpeedIncrease; // 增加子弹速度
		SoundManager::getInstance().playSound(L"bulletSpeedBuff", 1000); // 播放Buff应用成功的音效
	}
	applied = true; // 设置Buff已应用标志

	showEffect.start(); // 开始显示效果动画
}
// 这里可以添加一些特效或提示
