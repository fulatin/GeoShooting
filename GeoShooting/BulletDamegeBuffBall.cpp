#include "BulletDamageBuffBall.h"
#include "GlobalVal.h"

using namespace GeoShooting;
BulletDamageBuffBall::BulletDamageBuffBall(float x, float y, float _increasement)
	: BuffBall(x, y), damageIncrease(_increasement) {
	// 初始化Buff球的颜色和半径
	buffColor = RGB(255, 128,0);
	radius = 10.0f; // 半径
	wcscpy_s(buffName, L"Damage up"); // 设置Buff名称
}
void BulletDamageBuffBall::draw() {
	// 绘制Buff球为一个圆形
	if (applied) {
		showEffect.update(); // 更新Buff球的显示效果
		if(showEffect.isFinished()) {
			need2Delete = true; // 设置需要删除标志
		}
		return;
	}
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
	if (_player&&!applied) {
		_player->bulletDamage += damageIncrease; // 增加子弹伤害
		SoundManager::getInstance().playSound(L"bulletDamageBuff", 1000); // 播放Buff应用成功的音效
	}
	applied = true; // 设置Buff已应用标志

	showEffect.start(); // 开始显示效果动画

}
