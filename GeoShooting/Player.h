#pragma once
#include "GameObject.h"
#include "Vector.h"

using namespace GeoShooting;
class Player :public GameObject {

public:
	Player(float x, float y, float width, float height);
	void draw() override; // �������
	void update() override; // �������״̬
	void shoot(); // ������ x,y Ϊ���λ��
private:
	Vector speed;
	float mxSpeed = 500.0f; // ����ƶ��ٶ�
	float acc = 2000.0f; // ��Ҽ��ٶ�
	float health; // �������ֵ
	float fireRate; // ������Ƶ�� һ�뼸��
	float lastFireTime; // �ϴ����ʱ��
	float frac = 0.7; // ���ת��ʱ������
	void updateTrangle();
	COLORREF playerColor = RGB(0, 255, 0); // �����ɫ
	Vector trangle[3]; // ��������ζ���
	// ��ҵĻ��ƶ���
	Vector playerDirection; // ��ҷ��� ȷ���ǵ�λ����
	Vector targetDirection; // ���Ŀ�귽��
	IMAGE playerSurface;
};