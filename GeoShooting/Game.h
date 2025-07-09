#pragma once
#include<graphics.h>
#include "GameObject.h"
#include "Player.h"
namespace GeoShooting {
	class Game {
	public:
		Game();
		~Game();
		void run(); // ������Ϸѭ��
	private:
		Player player; // ��Ҷ���

		IMAGE background; // ��Ϸ����ͼ��
		DWORD *canvas; // ��Ϸ����
		
	};
}