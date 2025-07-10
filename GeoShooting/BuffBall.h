#pragma once

// ���Ը����ǿ������

#include "GameObject.h"
#include "Vector.h"
#include "Player.h"
class BuffBall : public GameObject {
public:
	enum BuffType {
		ShootSpeedBuff, // ����ٶ�Buff
		BulletDamageBuff, // �ӵ��˺�Buff
		BulletSpeedBuff, // �ӵ��ٶ�Buff
		HealBuff, // ����Buff
		// ������Ӹ����Buff����
	};
	const static int buffTypeCnt = 4; // Buff�������� 
	BuffBall(float x, float y): GameObject(x, y, 50.0f, 50.0f), buffColor(RGB(255, 255, 0)), radius(25.0f) {
		// ��ʼ��Buff�����ɫ�Ͱ뾶
	}
	virtual ~BuffBall() = default; // ����������
	virtual void draw() = 0; // ����Buff��
	virtual void update() = 0; // ����Buff��״̬
	virtual void applyBuff(Player *_player) = 0; // Ӧ��BuffЧ�������麯��
protected:
	COLORREF buffColor; // Buff����ɫ
	float radius; // Buff��뾶
	bool applied = false; // Buff�Ƿ���Ӧ��
	wchar_t buffName[20]; // Buff����




};