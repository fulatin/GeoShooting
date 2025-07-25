﻿#include "Game.h"
#include "Constants.h"
#include "GlobalVal.h"
#include "Enemy.h"
#include "ShootableEnemy.h"

#include "BuffBall.h"
#include "ShootSpeedBuffBall.h"
#include "BulletDamageBuffBall.h"
#include "BulletSpeedBuffBall.h"
#include "HealBuffBall.h"

#include "SoundManager.h"


#include <cmath>
#include <conio.h>
using namespace GeoShooting;

Game::Game() :player(500,500,50,50) {
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT); // 初始化图形窗口

	SoundManager& soundManager = SoundManager::getInstance(); // 获取声音管理器实例
	soundManager.loadSound(L"audio/misc_menu_4.wav", L"startmenu"); // 加载开始菜单音乐
	soundManager.loadSound(L"audio/Mars.wav", L"BGM"); // 加载背景音乐
	SoundManager::getInstance().loadSound(L"audio/enemyShoot.wav", L"enemyShoot"); // 加载射击音效

	wchar_t gotAppliedSound[50]; // Buff应用成功的音效

	wcscpy_s(gotAppliedSound, L"audio/phaserUp1.mp3"); // 设置Buff应用成功的音效
	SoundManager::getInstance().loadSound(gotAppliedSound, L"bulletDamageBuff"); // 加载音效


	wcscpy_s(gotAppliedSound, L"audio/phaserUp2.mp3"); // 设置Buff应用成功的音效
	SoundManager::getInstance().loadSound(gotAppliedSound, L"bulletSpeedBuff"); // 加载音效
	

	wcscpy_s(gotAppliedSound, L"audio/phaserUp3.mp3"); // 设置Buff应用成功的音效
	SoundManager::getInstance().loadSound(gotAppliedSound, L"healBuff"); // 加载音效
	

	wcscpy_s(gotAppliedSound, L"audio/phaserUp4.mp3"); // 设置Buff应用成功的音效
	SoundManager::getInstance().loadSound(gotAppliedSound, L"shootSpeedBuff"); // 加载音效
	
	soundManager.setGlobalVolume(100);
}
Game::~Game() {


}
// 从屏幕外向玩家生成随机敌人
void Game::generateRandomEnermy() {
	// 生成屏幕外的随机位置
	float offsetx = rand() % getwidth()*(rand()%2?-1:1); // 随机生成x偏移量
	float offsety = rand() % getheight() * (rand() % 2 ? -1 : 1); // 随机生成y偏移量
	int x, y;
	if(offsetx < 0) {
		x = offsetx; // 在屏幕外随机生成x坐标
	} else {
		x = getwidth() + offsetx; // 在屏幕外随机生成x坐标
	}
	if(offsety < 0) {
		y = offsety; // 在屏幕外随机生成y坐标
	}
	else {
		y = getheight() + offsety; // 在屏幕外随机生成y坐标
	}
	//cout << x << " " << y << endl; // 输出生成的坐标
	float width = 50.0f + (rand() % 2 ? 1 : -1) *( rand() % 10); // 敌人宽度
	float height = 50.0f + (rand() % 2 ? 1 : -1) * ( rand() % 10); // 敌人高度
	Vector direction(player.x-x+rand()%20, player.y-y+rand()%20); // 指向player的方向
	direction.normalize(); // 确保方向是单位向量
	float speed = 750.0f + rand() % 200*(rand()%2?1:-1)+gameTime; // 随机生成速度
	Enemy* enemy = nullptr; // 初始化敌人指针
	bool generateShootableEnemy = gameTime > 10.0f; // 游戏时间超过10秒后才有可能生成射击敌人
	if(rand()%5==0&&generateShootableEnemy) { // 50%概率生成射击敌人
		enemy = new ShootableEnemy(x, y, width, height, direction, speed, &player); // 创建新的射击敌人对象
	} else {
		enemy = new Enemy(x, y, width, height, direction, speed,&player); // 创建新的普通敌人对象
	}
	
	enemies.insert(enemy); // 将敌人添加到集合中
	//cout << "generate enemy" << endl;
}

void Game::generateRandomBuffBall() {
	// 生成屏幕内的随机位置
	float x = rand() % getwidth(); // 随机生成x坐标
	float y = rand() % getheight(); // 随机生成y坐标
	//cout << x << " " << y << endl; // 输出生成的坐标
	int tp = rand() % BuffBall::buffTypeCnt; // 随机生成Buff球类型
	BuffBall* buffBall = nullptr; // 初始化Buff球指针
	
	// 50%概率生成shoot speed up buff ball
	if(rand()%2){
		buffBall = new ShootSpeedBuffBall(x, y, 0.4); // 创建新的射击速度Buff球对象
		buffBalls.insert(buffBall); // 将Buff球添加到集合中
		return;
	}
	switch (tp)
	{
	case BuffBall::ShootSpeedBuff: // 射击速度Buff
		buffBall = new ShootSpeedBuffBall(x, y, 0.4); // 创建新的射击速度Buff球对象
		break;
	case BuffBall::BulletDamageBuff: // 子弹伤害Buff
		buffBall = new BulletDamageBuffBall(x, y, 8.0f); // 创建新的子弹伤害Buff球对象
		break;
	case BuffBall::BulletSpeedBuff: // 子弹速度Buff
		buffBall = new BulletSpeedBuffBall(x, y, 20.0f); // 创建新的子弹速度Buff球对象
		break;
	case BuffBall::HealBuff: // 治疗Buff
		buffBall = new HealBuffBall(x, y, 10.0f+gameTime/10); // 创建新的治疗Buff球对象
		break;
	default:
		break;
	}
	if(buffBall == nullptr) {
		return; // 如果Buff球创建失败，则返回
	}
	buffBalls.insert(buffBall); // 将Buff球添加到集合中
	//cout << "generate buff ball" << endl;
}

void Game::beforeStart() {
	// 显示游戏开始前的界面
	setbkcolor(RGB(20, 20, 20));
	cleardevice(); // 清除画布
	settextcolor(RGB(255, 255, 255)); // 设置文字颜色为白色
	settextstyle(30, 0, _T("Consolas")); // 设置文字样式
	// 显示文字确保居中
	wchar_t text[] = L"Press any key to start the game!";
	outtextxy((getwidth() - textwidth(text)) / 2, (getheight() - textheight(text)) / 2, text); // 居中显示文字
	ExMessage msg;
	getmessage(&msg, EX_KEY);
	isGameStarted = true; // 设置游戏已开始

	
	SoundManager::getInstance().playSound(L"startmenu",1000); // 播放开始菜单音乐
}

bool Game::gameEnd() {
	// 游戏结束后显示分数并让玩家选择是否重新开始游戏
	setbkcolor(RGB(20, 20, 20));
	cleardevice(); // 清除画布
	settextcolor(RGB(255, 255, 255)); // 设置文字颜色为白色
	settextstyle(30, 0, _T("Consolas")); // 设置文字样式
	wchar_t text[100];
	swprintf(text, 100, L"Game Over! Your score: %.2f", score); // 显示得分
	outtextxy((getwidth() - textwidth(text)) / 2, (getheight() - textheight(text)) / 2, text); // 居中显示文字
	outtextxy((getwidth() - textwidth(L"Press R to restart or Q to quit")) / 2,
		(getheight() - textheight(L"Press R to restart or Q to quit")) / 2 + 50,
		L"Press R to restart or Q to quit"); // 显示重新开始或退出提示
	FlushBatchDraw();
	while (true) {
		ExMessage msg;
		getmessage(&msg,EX_KEY);
		if (msg.message == WM_KEYDOWN) {
			if (msg.vkcode == 'R' || msg.vkcode == 'r') {
				score = 100.0f; // 重置得分
				gameTime = 0.0f; // 重置游戏时间
				enemies.clear(); // 清空敌人集合
				bullets.clear(); // 清空子弹集合
				buffBalls.clear(); // 清空Buff球集合

				return true; // 玩家选择重新开始游戏
			}
			else if (msg.vkcode == 'Q' || msg.vkcode == 'q') {
				return false; // 玩家选择退出游戏
			}
		}
	}
}


bool Game::run() {
	beforeStart(); // 显示游戏开始前的界面

	float  lastTime = GetTickCount(); // 获取当前时间
	BeginBatchDraw(); // 开始批量绘制
	while (true) {
		if ((float )GetTickCount() - lastTime - 1000 / 240.0 <= 1.0) {
			Sleep(1);
			continue;
		}
		setbkcolor(RGB(20,20,20));
		cleardevice(); // 清除画布

		if(!isBGMStarted&& (gameTime >= startBGMTime) ) {
			SoundManager::getInstance().playSound(L"BGM", 10000,true); // 播放背景音乐
			isBGMStarted = true; // 设置BGM已开始播放
		}

		if (SoundManager::getInstance().getTotalSoundInstanceCount() > 10) {
			SoundManager::getInstance().update();
		}

		deltaTime = (GetTickCount() - lastTime) / 1000.0f*timeFactor; // 计算上一帧和这一帧的时间差
		realDeltaTime = (GetTickCount() - lastTime) / 1000.0f; // 计算实际上一帧和这一帧的时间差
		lastTime = GetTickCount(); // 更新上一帧时间
		gameTime += deltaTime; // 更新游戏进行的总时间
		phaseTimeCnt += deltaTime; // 更新阶段进行的时间计数

		if(abs(timeFactor-1)< 0.01) {
			timeFactor = 1.0f; // 重置时间系数为1.0，表示正常速度
		}
		else if (timeFactor > 1.0f) {
			timeFactor = 1.0f; // 如果时间系数大于1.0，则重置为1.0，表示正常速度
		}
		else {
			timeFactor += timeRestoreFactor*deltaTime; // 恢复时间系数

		}

		player.update(); // 更新玩家状态
		player.draw(); // 绘制玩家


		// 更新所有子弹
		for (auto it = bullets.begin(); it != bullets.end();) {
			Bullet* bullet = *it;
			bullet->update(); // 更新子弹状态
			if (bullet->isOffScreen()) {
				it = bullets.erase(it); // 如果子弹超出屏幕范围，则删除它
				delete bullet; // 释放内存
			} else {
				bullet->draw(); // 绘制子弹
				++it; // 移动到下一个子弹
			}
		}




		// 更新所有敌人,并计算屏幕内敌人数量
		inScreenEnermyCount = 0; // 重置屏幕内敌人数量
		for (auto it = enemies.begin(); it != enemies.end();) {
			Enemy* enemy = *it;
			enemy->update(); // 更新敌人状态
			// 超出屏幕范围两倍的敌人将被删除
			if (abs(enemy->x) >= 3 * getwidth() || abs(enemy->y) >= 3 * getheight()) {
				it = enemies.erase(it); // 如果敌人超出屏幕范围，则删除它
				delete enemy; // 释放内存
			}
			else {
				enemy->draw(); // 绘制敌人
				++it; // 移动到下一个敌人
			}
			// 检查敌人是否在屏幕内
			if (enemy->x >= 0 && enemy->x <= getwidth() && enemy->y >= 0 && enemy->y <= getheight()) {
				inScreenEnermyCount++; // 增加屏幕内敌人数量
			}
		}

		// 尝试生成新的敌人
		if (inScreenEnermyCount < maxEnermyCount && (GetTickCount() - lastEnermySpawnTime) / 1000.0f > enermySpawnRate) {
			generateRandomEnermy(); // 生成新的敌人
			lastEnermySpawnTime = GetTickCount(); // 更新上次生成敌人的时间
		}

		// 尝试生成新的Buff球
		if (buffBalls.size() < maxBuffBallCount && (GetTickCount() - lastBuffBallSpawnTime) / 1000.0f > buffBallSpawnRate) {
			generateRandomBuffBall(); // 生成新的Buff球
			lastBuffBallSpawnTime = GetTickCount(); // 更新上次生成Buff球的时间
		}

		// 检查子弹与敌人和玩家碰撞
		for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
			Bullet* bullet = *bulletIt;
			bool bulletDeleted = false; // 标记子弹是否被删除
			if (bullet->getOwner() != &player) {
				if (bullet->collideWith(&player)) {
					player.health -= bullet->getDamage(); // 减少玩家生命值
					bulletDeleted = true; // 标记子弹被删除
				}
			} else {
				for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();) {
					Enemy* enemy = *enemyIt;
					if (bullet->collideWith(enemy)) { // 检查子弹是否与敌人碰撞
						enemy->getHitBy(bullet); // 敌人被子弹击中
						// 增加得分
						if (enemy->getHealth() <= 0) {
							// 如果敌人生命值小于等于0，则敌人死亡
							score += 500.0f; // 击败敌人得分
							enemyIt = enemies.erase(enemyIt); // 删除敌人
							delete enemy; // 释放内存
						}
						else {
							++enemyIt; // 移动到下一个敌人
						}

					}
					else {
						++enemyIt; // 移动到下一个敌人
					}
				}
			}
			if (bulletDeleted) {
				bulletIt = bullets.erase(bulletIt); // 删除子弹
				delete bullet; // 释放内存
			}
			else {
				bullet->draw(); // 绘制子弹
				++bulletIt; // 移动到下一个子弹
			}
		}


		// 检测敌人间的碰撞，如果有就通过动量定理来计算碰撞后的速度
		for (auto it1 = enemies.begin(); it1 != enemies.end(); ++it1) {
			Enemy* enemy1 = *it1;
			for (auto it2 = std::next(it1); it2 != enemies.end();) {
				Enemy* enemy2 = *it2;
				if (enemy1->collideWith(enemy2)) { // 检查敌人是否碰撞
					// 计算碰撞后的速度
					Vector v1(enemy1->direction.x * enemy1->speed, enemy1->direction.y * enemy1->speed);
					Vector v2(enemy2->direction.x * enemy2->speed, enemy2->direction.y * enemy2->speed);
					Vector newV1 = v1 - v2; // 简单的碰撞处理
					Vector newV2 = v2 - v1; // 简单的碰撞处理
					enemy1->direction = newV1 / newV1.length();
					enemy2->direction = newV2 / newV2.length();
					//it2 = enemies.erase(it2); // 删除第二个敌人
					//delete enemy2; // 释放内存
				} 
					++it2; // 移动到下一敌人
				
			}
		}

		// 检测玩家与敌人碰撞
		for (auto it = enemies.begin(); it != enemies.end();) {
			Enemy* enemy = *it;
			if (enemy->collideWith(&player)) { // 检查玩家是否与敌人碰撞
				player.health -= 5.0f+gameTime/10; // 减少玩家生命值
				it = enemies.erase(it); // 删除敌人
				delete enemy; // 释放内存
				if (player.health <= 0) {
					return gameEnd(); // 如果玩家生命值小于等于0，则游戏结束
				}
				timeFactor = 1;
			} else {
				if(( Vector(enemy->x,enemy->y)-Vector(player.x,player.y)).length() < max(enemy->height,enemy->width)*1.5) {
					// 如果敌人靠近玩家，则增加得分
					timeFactor = 0.6f; // 减慢时间系数
					score += 7.0f*deltaTime; // 与敌人擦肩而过得分
				}
			++it; // 移动到下一个敌人
			}
		}

		// 检测玩家与Buff球碰撞 
		for (auto it = buffBalls.begin(); it != buffBalls.end();) {
			BuffBall* buffBall = *it;
			if (buffBall->need2Delete) {
				delete buffBall; // 删除Buff球
				it = buffBalls.erase(it); // 从集合中删除Buff球
				continue; // 跳过当前循环，继续下一个Buff球的处理
			}
			if (player.collideWith(buffBall)) { // 检查玩家是否与Buff球碰撞
				buffBall->applyBuff(&player); // 应用Buff效果
			} else {
				buffBall->draw(); // 绘制Buff球
				buffBall->update(); // 更新Buff球状态
				
			}
			++it; // 移动到下一个Buff球
		}

		// 根据生存时间增加得分
		score += deltaTime * 0.1f; // 每秒增加0.1分
		// 敌人生成速度和总量随着游戏时间增加
		if(phaseTimeCnt> phaseDuration) {
			enermySpawnRate *= 0.93f; // 减少敌人生成间隔
			maxEnermyCount += 4; // 增加最大敌人数量
			maxBuffBallCount += 1; // 增加最大Buff球数量
			buffBallSpawnRate *=0.9f; // 减少Buff球生成间隔
			phaseTimeCnt = 0.0f; // 重置阶段时间计数器
			phaseDuration *= 1.1f; // 增加阶段持续时间

		}

		// 绘制用户界面
		drawUI(); // 绘制用户界面
		FlushBatchDraw(); // 刷新批量绘制
		flushmessage(); // 刷新消息队列
	}
	EndBatchDraw(); // 结束批量绘制
}

void Game::drawUI() {
	// 绘制用户界面
	settextcolor(RGB(255, 255, 255));
	setbkmode(TRANSPARENT);
	wchar_t buffer[100];
	swprintf(buffer,100, L"Health: %.2f", player.health);
	outtextxy(10, 10, buffer ); // 绘制玩家生命值
	swprintf(buffer, 100, L"Score: %.2f", score);
	outtextxy(10, 40, buffer); // 绘制得分
	// 绘制游戏时间
	swprintf(buffer, 100, L"Time: %.2f s", gameTime);
	outtextxy(10, 70, buffer); // 绘制游戏时间
}