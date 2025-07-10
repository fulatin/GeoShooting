#include "ShootSpeedBuffBall.h"
#include "GlobalVal.h"
using namespace GeoShooting;
ShootSpeedBuffBall::ShootSpeedBuffBall(float x, float y, float _increasement)
	: BuffBall(x, y), speedIncrease(_increasement) {
	// 初始化Buff球的颜色和半径
	buffColor = RGB(255, 0, 128); // 黄色
	radius = 10.0f; // 半径
}
void ShootSpeedBuffBall::draw() {
	// 绘制Buff球为一个圆形
	setlinecolor(buffColor);
	setfillcolor(buffColor);
	setlinestyle(PS_SOLID, 2);
	fillcircle(x, y, radius+ 5.0f * sin(gameTime));
}
void ShootSpeedBuffBall::update() {
	// 以正弦的方式更新Buff球的位置和大小




	
}
void ShootSpeedBuffBall::applyBuff(Player* _player) {
	// 应用Buff效果，增加玩家的射击速度
	if (_player) {
		_player->fireRate += speedIncrease; // 增加射击频率
	}
}