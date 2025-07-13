#pragma once
#include <functional> // ��Ӵ�����ʹ�� std::function
using namespace GeoShooting;
extern float realDeltaTime; // ʵ����һ֡����һ֡��ʱ���
extern float deltaTime; // ��һ֡����һ֡��ʱ��� ����ʱ��ϵ������

template <typename T>
class Animation {
    enum class AnimationState {
        Idle, // ����״̬
        Running, // ����״̬
        Finished // ���״̬
    };
public:
    Animation(float duration);
    void start(); // ��ʼ����
    void update(); // ���¶���״̬
    void reset(); // ���ö���״̬
    bool isFinished() const; // ��鶯���Ƿ����
    void setUpdateFunction(T updfunc);
	float getElapsedTime() const { return elapsedTime; } // ��ȡ�ѹ�ʱ��
	float getDuration() const { return duration; } // ��ȡ��������ʱ��
private:
    AnimationState state; // ����״̬
    std::function<void()> updateFunction; // ʹ�� std::function ��Ϊ���º���������
    float duration; // ��������ʱ��
    float elapsedTime; // �Ѿ�����ʱ��
};
template <typename T>
Animation<T>::Animation(float duration)
	: state(AnimationState::Idle), duration(duration), elapsedTime(0.0f) {
}
template <typename T>
void Animation<T>::start() {
	state = AnimationState::Running; // ���ö���״̬Ϊ����
	elapsedTime = 0.0f; // �����ѹ�ʱ��
}
template <typename T>
void Animation<T>::update() {
	if (state == AnimationState::Running) {
		elapsedTime += realDeltaTime; // �����ѹ�ʱ��
		if (elapsedTime >= duration) {
			state = AnimationState::Finished; // ����ѹ�ʱ�䳬������ʱ�䣬����״̬Ϊ���
			elapsedTime = duration; // ȷ���ѹ�ʱ�䲻��������ʱ��
		}
		updateFunction(); // ���ø��º���
	}
}
template <typename T>
void Animation<T>::reset() {
	state = AnimationState::Idle; // ���ö���״̬Ϊ����
	elapsedTime = 0.0f; // �����ѹ�ʱ��
}
template <typename T>
bool Animation<T>::isFinished() const {
	return state == AnimationState::Finished; // ��鶯���Ƿ����
}

template <typename T>
void Animation<T>::setUpdateFunction(T updfunc) {
	updateFunction = updfunc; // ���ø��º���
}
