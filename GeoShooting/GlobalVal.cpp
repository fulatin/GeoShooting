#include "GlobalVal.h"

using namespace GeoShooting;
float GeoShooting::deltaTime = 0.0f; // ��ʼ����һ֡����һ֡��ʱ���Ϊ0
float GeoShooting::realDeltaTime = 0.0f; // ��ʼ��ʵ����һ֡����һ֡��ʱ���Ϊ0
float GeoShooting::timeFactor = 1.0f; // ��ʼ��ʱ��ϵ��Ϊ1.0����ʾ�����ٶ�
float GeoShooting::timeRestoreFactor = 1.2f; // ��ʼ��ʱ��ظ�ϵ��Ϊ1.0����ʾ�����ٶ�
std::set<Bullet* > GeoShooting::bullets; // ��ʼ���ӵ�����
std::set<Enemy* > GeoShooting::enemies; // ��ʼ�����˼���
std::set<BuffBall* > GeoShooting::buffBalls; // ��ʼ��Buff�򼯺�
float GeoShooting::score = 100.0f; // ��ʼ����Ϸ�÷�Ϊ100
float GeoShooting::gameTime = 0.0f; // ��ʼ����Ϸ���е���ʱ��Ϊ0