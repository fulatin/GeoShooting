#include "BuffBall.h"

#include "GlobalVal.h"
#include <graphics.h>
#include <cmath>
using namespace GeoShooting;
void BuffBall::showEffectUpdFunc() {
	// 更新Buff球的显示效果
	if (showEffect.isFinished()) {
		showEffect.reset(); // 重置动画状态
		need2Delete = true; // 设置需要删除标志
	}
}
BuffBall::BuffBall(float x, float y)
	: GameObject(x, y, 50.0f, 50.0f), buffColor(RGB(255, 255, 0)), radius(25.0f), showEffect(2) {
	// 初始化Buff球的颜色和半径
	wcscpy_s(buffName, L"Buff"); // 设置默认Buff名称
	showEffect.setUpdateFunction([=]() {
		// 在buff球的位置绘制效果
		float durationFactor = showEffect.getElapsedTime() / showEffect.getDuration(); // 计算动画进度
		setlinestyle(PS_SOLID, 2);
		settextcolor(RGB(255 *(1- durationFactor), 255 *(1- durationFactor), 255 *(1- durationFactor) ));
		outtextxy(x, y-20*durationFactor, buffName); // 绘制Buff名称
	}); // 设置动画更新函数
}