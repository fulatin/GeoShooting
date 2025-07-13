#include "HealBuffBall.h"
#include "GlobalVal.h"
using namespace GeoShooting;
HealBuffBall::HealBuffBall(float x, float y, float _increasement)
	: BuffBall(x, y), healthIncrease(_increasement) {
	// 初始化Buff球的颜色和半径
	buffColor = RGB(0, 128, 128); // 绿色
	radius = 10.0f; // 半径

	wcscpy_s(buffName, L"Health up"); // 设置Buff名称

}
void HealBuffBall::draw() {
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
void HealBuffBall::update() {

}
void HealBuffBall::applyBuff(Player* _player) {
	// 应用Buff效果，增加玩家的生命值
	if (_player&&!applied) {
		_player->health += healthIncrease; // 增加生命值
		if (_player->health > 100.0f) { // 确保生命值不超过100
			_player->health = 100.0f;
		}
		SoundManager::getInstance().playSound(L"healBuff", 1000); // 播放Buff应用成功的音效
	}
	applied = true; // 设置Buff已应用标志

	showEffect.start(); // 开始显示效果动画

}
