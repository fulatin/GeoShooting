#include "ShootSpeedBuffBall.h"
#include "GlobalVal.h"
#include <graphics.h>
#include <iostream>
using namespace GeoShooting;
ShootSpeedBuffBall::ShootSpeedBuffBall(float x, float y, float _increasement)
	: BuffBall(x, y), speedIncrease(_increasement) {
	// 初始化Buff球的颜色和半径
	buffColor = RGB(255, 255, 0); // 黄色
	radius = 10.0f; // 半径
}
void ShootSpeedBuffBall::draw() {
	// 绘制Buff球为一个圆形
	setlinecolor(buffColor);
	setfillcolor(buffColor);
	fillcircle(x, y, radius);
}
void ShootSpeedBuffBall::update() {
	// 更新Buff球状态（如果需要）
	// 这里可以添加一些动画效果或移动逻辑
}
void ShootSpeedBuffBall::applyBuff(Player* _player) {
	// 应用Buff效果，增加玩家的射击速度
	if (_player) {
		_player->fireRate += speedIncrease; // 增加射击频率
		std::cout << "Shoot speed buff applied. New fire rate: " << _player->fireRate << std::endl;
	}
}