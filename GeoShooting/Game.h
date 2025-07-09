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
		void run(); // 启动游戏循环
	private:
		Player player; // 玩家对象
		float enermySpawnRate = 0.5f; // 敌人生成频率
		float lastEnermySpawnTime = 0.0f; // 上次生成敌人的时间
		int maxEnermyCount = 100; // 最大敌人数量
		int inScreenEnermyCount = 0; // 屏幕内敌人数量
		IMAGE background; // 游戏背景图像
		DWORD *canvas; // 游戏画布
		
	};
}