#include "BuffBall.h"

#include "GlobalVal.h"
#include <graphics.h>
#include <cmath>
using namespace GeoShooting;
void BuffBall::showEffectUpdFunc() {
	// ����Buff�����ʾЧ��
	if (showEffect.isFinished()) {
		showEffect.reset(); // ���ö���״̬
		need2Delete = true; // ������Ҫɾ����־
	}
}
BuffBall::BuffBall(float x, float y)
	: GameObject(x, y, 50.0f, 50.0f), buffColor(RGB(255, 255, 0)), radius(25.0f), showEffect(2) {
	// ��ʼ��Buff�����ɫ�Ͱ뾶
	wcscpy_s(buffName, L"Buff"); // ����Ĭ��Buff����
	showEffect.setUpdateFunction([=]() {
		// ��buff���λ�û���Ч��
		float durationFactor = showEffect.getElapsedTime() / showEffect.getDuration(); // ���㶯������
		setlinestyle(PS_SOLID, 2);
		settextcolor(RGB(255 *(1- durationFactor), 255 *(1- durationFactor), 255 *(1- durationFactor) ));
		outtextxy(x, y-20*durationFactor, buffName); // ����Buff����
	}); // ���ö������º���
}