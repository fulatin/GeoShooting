#include "GlobalVal.h"

using namespace GeoShooting;
float GeoShooting::deltaTime = 0.0f; // ��ʼ����һ֡����һ֡��ʱ���Ϊ0
std::set<Bullet*> GeoShooting::bullets; // ��ʼ���ӵ�����
std::set<Enemy*> GeoShooting::enemies; // ��ʼ�����˼���
std::set<BuffBall*> GeoShooting::buffBalls; // ��ʼ��Buff�򼯺�
float GeoShooting::score = 100.0f; // ��ʼ����Ϸ�÷�Ϊ100
float GeoShooting::gameTime = 0.0f; // ��ʼ����Ϸ���е���ʱ��Ϊ0