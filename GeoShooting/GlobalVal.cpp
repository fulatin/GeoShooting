#include "GlobalVal.h"


float deltaTime = 0.0f; // ��ʼ����һ֡����һ֡��ʱ���Ϊ0
float realDeltaTime = 0.0f; // ��ʼ��ʵ����һ֡����һ֡��ʱ���Ϊ0
float timeFactor = 1.0f; // ��ʼ��ʱ��ϵ��Ϊ1.0����ʾ�����ٶ�
float timeRestoreFactor = 1.2f; // ��ʼ��ʱ��ظ�ϵ��Ϊ1.0����ʾ�����ٶ�
std::set<Bullet* > bullets; // ��ʼ���ӵ�����
std::set<Enemy* > enemies; // ��ʼ�����˼���
std::set<BuffBall* > buffBalls; // ��ʼ��Buff�򼯺�
float score = 100.0f; // ��ʼ����Ϸ�÷�Ϊ100
float gameTime = 0.0f; // ��ʼ����Ϸ���е���ʱ��Ϊ0