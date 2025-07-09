#pragma once
#include<graphics.h>
#include "GameObject.h"
#include "Player.h"
namespace GeoShooting {
	class Game {
	public:
		Game();
		~Game();
		void run(); // 启动游戏循环
	private:
		Player player; // 玩家对象

		IMAGE background; // 游戏背景图像
		DWORD *canvas; // 游戏画布
		
	};
}