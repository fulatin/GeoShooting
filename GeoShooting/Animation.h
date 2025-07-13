#pragma once
#include <functional> // 添加此行以使用 std::function
using namespace GeoShooting;
extern float realDeltaTime; // 实际上一帧和这一帧的时间差
extern float deltaTime; // 上一帧和这一帧的时间差 经过时间系数修正

template <typename T>
class Animation {
    enum class AnimationState {
        Idle, // 空闲状态
        Running, // 运行状态
        Finished // 完成状态
    };
public:
    Animation(float duration);
    void start(); // 开始动画
    void update(); // 更新动画状态
    void reset(); // 重置动画状态
    bool isFinished() const; // 检查动画是否完成
    void setUpdateFunction(T updfunc);
	float getElapsedTime() const { return elapsedTime; } // 获取已过时间
	float getDuration() const { return duration; } // 获取动画持续时间
private:
    AnimationState state; // 动画状态
    std::function<void()> updateFunction; // 使用 std::function 作为更新函数的类型
    float duration; // 动画持续时间
    float elapsedTime; // 已经过的时间
};
template <typename T>
Animation<T>::Animation(float duration)
	: state(AnimationState::Idle), duration(duration), elapsedTime(0.0f) {
}
template <typename T>
void Animation<T>::start() {
	state = AnimationState::Running; // 设置动画状态为运行
	elapsedTime = 0.0f; // 重置已过时间
}
template <typename T>
void Animation<T>::update() {
	if (state == AnimationState::Running) {
		elapsedTime += realDeltaTime; // 增加已过时间
		if (elapsedTime >= duration) {
			state = AnimationState::Finished; // 如果已过时间超过持续时间，设置状态为完成
			elapsedTime = duration; // 确保已过时间不超过持续时间
		}
		updateFunction(); // 调用更新函数
	}
}
template <typename T>
void Animation<T>::reset() {
	state = AnimationState::Idle; // 重置动画状态为空闲
	elapsedTime = 0.0f; // 重置已过时间
}
template <typename T>
bool Animation<T>::isFinished() const {
	return state == AnimationState::Finished; // 检查动画是否完成
}

template <typename T>
void Animation<T>::setUpdateFunction(T updfunc) {
	updateFunction = updfunc; // 设置更新函数
}
