#pragma once
#include<graphics.h>
#include "GameObject.h"
#include "Player.h"
namespace GeoShooting {
	class Game {
	public:
		Game();
		~Game();
		void generateRandomEnermy(); // 生成随机敌人
		void generateRandomBuffBall(); // 生成随机Buff球
		bool run(); // 启动游戏循环
		// 游戏的开始界面，按任意键开始游戏
		void beforeStart(); // 游戏开始前的界面
		bool gameEnd(); // 游戏结束后显示分数并让玩家选择是否重新开始游戏
	private:
		void drawUI(); // 绘制用户界面
		Player player; // 玩家对象

		bool isGameStarted = false; // 游戏是否开始

		// 玩家击败敌人会得分，发射子弹会减分，坚持时间会得分，与敌人擦肩而过会得分
		float enermySpawnRate = 0.7f; // 敌人生成频率
		float lastEnermySpawnTime = 0.0f; // 上次生成敌人的时间
		int maxEnermyCount = 70; // 最大敌人数量
		int inScreenEnermyCount = 0; // 屏幕内敌人数量

		int maxBuffBallCount = 10; // 最大Buff球数量
		float lastBuffBallSpawnTime = 0.0f; // 上次生成Buff球的时间
		float buffBallSpawnRate = 7.0f; // Buff球生成频率

		// 用来进行难度增加的变量
		float phaseTimeCnt = 0.0f; // 阶段进行的时间计数器
		float phaseDuration = 3.0f; // 每个阶段持续时间


		float startBGMTime = 5.0f; // 开始BGM的时间
		bool isBGMStarted = false; // BGM是否开始播放
		
	};
}