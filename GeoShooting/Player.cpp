#pragma once
#include "Player.h"
#include "GlobalVal.h"
#include "Constants.h"
#include "Bullet.h"
#include "SoundManager.h"
#include<graphics.h>

using namespace GeoShooting;

Player::Player(float x, float y, float width, float height)
	: GameObject(x, y, width, height), health(100.0f),
	fireRate(2), lastFireTime(0.0f),
	playerSurface(2*width,2*height) {
	playerDirection = { 1,0 }; // 初始方向向右
	updateTrangle(); // 更新三角形顶点
	SoundManager::getInstance().loadSound(L"audio/laser.wav", L"playerShoot"); // 加载射击音效
}


// 根据playerDirection的方向更新三角形顶点
void Player::updateTrangle() {
	trangle[0] = Vector(x, y) + playerDirection * width * 2 / 3;
	Vector leftDir = playerDirection.rotate(-PI / 2); // 左侧方向
	trangle[1] = Vector(x, y) - playerDirection * width * 1 / 3 + leftDir * width / 2;
	trangle[2] = Vector(x, y) - playerDirection * width * 1 / 3 - leftDir * width / 2;
	// 检测是否超出屏幕范围 如果某一点超出就让速度反向
	if (trangle[0].x < 0 || trangle[0].x > getwidth() ||
		trangle[0].y < 0 || trangle[0].y > getheight()) {
		speed.x = -speed.x; // 反向速度
		speed.y = -speed.y;
	}
	if (trangle[1].x < 0 || trangle[1].x > getwidth() ||
		trangle[1].y < 0 || trangle[1].y > getheight()) {
		speed.x = -speed.x; // 反向速度
		speed.y = -speed.y;
	}
	if (trangle[2].x < 0 || trangle[2].x > getwidth() ||
		trangle[2].y < 0 || trangle[2].y > getheight()) {
		speed.x = -speed.x; // 反向速度
		speed.y = -speed.y;
	}


}
void Player::draw() {
	setlinecolor(playerColor);
	setlinestyle(PS_SOLID, 2);
	// 绘制玩家三角形
	for(int i = 0; i < 3; i++) {
		line(trangle[i].x, trangle[i].y, trangle[(i + 1) % 3].x, trangle[(i + 1) % 3].y);
	}

	// 绘制玩家的血量条


		float healthBarWidth = width * (health / 100.0f); // 血条宽度根据生命值计算
		setfillcolor(RGB(0, 255, 0)); // 设置血条颜色为红色
		// 血条为矩形，位于玩家三角形下方
		setlinecolor(RGB(0, 255, 0)); // 设置血条边框颜色为红色
		setlinestyle(PS_SOLID, 1); // 设置血条边框样式
		rectangle(x - width / 2, y + height / 2 + 10, x + width / 2, y + height / 2 + 20);
		fillrectangle(x - width / 2, y + height / 2 + 10, x - width/2 + healthBarWidth, y + height / 2 + 20);

}

void Player::update() {
	// 玩家键盘控制位置
	Vector speedDir = {0,0};
	if (GetAsyncKeyState('A') & 0x8000 || GetAsyncKeyState(VK_LEFT) & 0x8000) {
		speedDir.x += -1;
	}
	else if (GetAsyncKeyState('D') & 0x8000 || GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		speedDir.x += 1;
	}
	if (GetAsyncKeyState('W') & 0x8000 || GetAsyncKeyState(VK_UP) & 0x8000) {
		speedDir.y += -1;
	}
	else if (GetAsyncKeyState('S') & 0x8000 || GetAsyncKeyState(VK_DOWN) & 0x8000) {
		speedDir.y += 1;
	}

	speedDir.normalize();

	// 如果speedDir和速度反向就加大减速效果
	if (speedDir.dot(speed) < 0) {
		speedDir = speedDir * 3.0f;
	} 
	else if (speedDir.length() < 0.1f) {
		speed = speed * 0.97f; // 如果没有按键则减速
	}
	
	speed = speed + speedDir * acc * realDeltaTime; // 更新速度
	
	
	if(speed.length()> mxSpeed) {
		speed.normalize();
		speed = speed * mxSpeed; // 限制速度
	}
	// 更新位置
	
	x += speed.x * realDeltaTime;
	y += speed.y * realDeltaTime;
	
	// 玩家鼠标控制方向
	POINT mousePos;
	GetCursorPos(&mousePos); // 获取鼠标位置
	ScreenToClient(GetHWnd(), &mousePos); // 转换为窗口坐标
	targetDirection = Vector(mousePos.x, mousePos.y) - Vector(x, y); // 计算目标方向
	targetDirection.normalize(); // 归一化目标方向
	playerDirection = playerDirection * frac + targetDirection * (1 - frac); // 平滑过渡到目标方向
	playerDirection.normalize(); // 确保是单位向量

	// 异步获取玩家点击事件以发射子弹
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
		if(GetTickCount()/1000.0-lastFireTime > 1.0 / fireRate) {
			shoot(); // 发射子弹
			lastFireTime = GetTickCount() / 1000.0; // 更新上次射击时间
			// 射速越快减的分越少
			score -= 1.0f / fireRate; // 减少分数
		}

	}
	updateTrangle(); // 更新三角形顶点
}
void Player::shoot() {
	// 创建新的子弹对象
	Bullet* bullet = new Bullet(trangle[0].x,trangle[0].y, width , height , playerDirection, bulletSpeed,bulletDamage, this);
	bullets.insert(bullet); // 将子弹添加到全局子弹集合中
	SoundManager::getInstance().playSound(L"playerShoot", 1000); // 播放射击音效

}
