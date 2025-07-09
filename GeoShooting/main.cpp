#include "GraphicsHelper.h"
#include "Constants.h"
#include "Game.h"
#include <graphics.h>
#include <iostream>
#include<easyx.h>
using namespace std;
using namespace GeoShooting;
#pragma comment(lib, "gdiplus.lib")
int main() {
	Game game; // 创建游戏对象
	game.run(); // 启动游戏循环
}

