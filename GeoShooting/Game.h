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
		void generateRandomBuffBall(); // �������Buff��
		bool run(); // ������Ϸѭ��
		// ��Ϸ�Ŀ�ʼ���棬���������ʼ��Ϸ
		void beforeStart(); // ��Ϸ��ʼǰ�Ľ���
		bool gameEnd(); // ��Ϸ��������ʾ�����������ѡ���Ƿ����¿�ʼ��Ϸ
	private:
		void drawUI(); // �����û�����
		Player player; // ��Ҷ���

		bool isGameStarted = false; // ��Ϸ�Ƿ�ʼ

		// ��һ��ܵ��˻�÷֣������ӵ�����֣����ʱ���÷֣�����˲��������÷�
		float enermySpawnRate = 0.5f; // ��������Ƶ��
		float lastEnermySpawnTime = 0.0f; // �ϴ����ɵ��˵�ʱ��
		int maxEnermyCount = 100; // ����������
		int inScreenEnermyCount = 0; // ��Ļ�ڵ�������

		int maxBuffBallCount = 10; // ���Buff������
		float lastBuffBallSpawnTime = 0.0f; // �ϴ�����Buff���ʱ��
		float buffBallSpawnRate = 5.0f; // Buff������Ƶ��

		// ���������Ѷ����ӵı���
		float phaseTimeCnt = 0.0f; // �׶ν��е�ʱ�������
		float phaseDuration = 2.0f; // ÿ���׶γ���ʱ��


		IMAGE background; // ��Ϸ����ͼ��
		DWORD *canvas; // ��Ϸ����
		
	};
}