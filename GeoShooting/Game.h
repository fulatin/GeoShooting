#pragma once
#include<graphics.h>
#include "GameObject.h"
#include "Player.h"
namespace GeoShooting {
	class Game {
	public:
		Game();
		~Game();
		void generateRandomEnermy(); // �����������
		void run(); // ������Ϸѭ��
	private:
		Player player; // ��Ҷ���
		float enermySpawnRate = 0.5f; // ��������Ƶ��
		float lastEnermySpawnTime = 0.0f; // �ϴ����ɵ��˵�ʱ��
		int maxEnermyCount = 100; // ����������
		int inScreenEnermyCount = 0; // ��Ļ�ڵ�������
		IMAGE background; // ��Ϸ����ͼ��
		DWORD *canvas; // ��Ϸ����
		
	};
}