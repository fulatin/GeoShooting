#include "SoundManager.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cwchar>

// 单例实例
SoundManager& SoundManager::getInstance() {
    static SoundManager instance;
    return instance;
}

SoundManager::SoundManager() : globalVolume(100) {
    // 初始化随机种子
    srand(static_cast<unsigned int>(time(nullptr)));
}

SoundManager::~SoundManager() {
    // 关闭所有活动音效
    for (auto& instance : activeInstances) {
        std::wstring cmd = L"close " + instance.alias;
        mciSendString(cmd.c_str(), nullptr, 0, nullptr);
    }
    activeInstances.clear();
}

MCIERROR SoundManager::mciSendCommand(const std::wstring command) const {
    return mciSendString(command.c_str(), nullptr, 0, nullptr);
}

std::wstring SoundManager::generateUniqueAlias() {
    // 使用时间戳和随机数生成唯一别名
    wchar_t buf[32];
    swprintf(buf, 32, L"sound_%lu_%d",
        static_cast<unsigned long>(time(nullptr)),
        rand() % 10000);
    return std::wstring(buf);
}

bool SoundManager::loadSound(const std::wstring filePath, const std::wstring soundName) {
    // 检查是否已存在同名音效
    if (soundPool.find(soundName) != soundPool.end()) {
        return false;
    }

    // 添加到音效池

    soundPool[soundName] = filePath;
    return true;
}

void SoundManager::playSound(const std::wstring soundName, int volume, bool loop) {
    // 检查音效是否存在
    auto it = soundPool.find(soundName);

    if (it == soundPool.end()) {
		wprintf(L"Sound not found: %s\n", soundName.c_str());
        return;
    }

    // 应用全局音量

    volume = volume * globalVolume / 100;
    if (volume > 1000) volume = 1000;
    if (volume < 0) volume = 0;

    // 播放音效
    playSoundInternal(it->second, volume, loop);
}

void SoundManager::playSoundInternal(const std::wstring filePath, int volume, bool loop) {
    // 创建新实例
    SoundInstance newInstance;
    newInstance.alias = generateUniqueAlias();
    newInstance.filePath = filePath;
    newInstance.state = SOUND_PLAYING;
    newInstance.volume = volume;
    newInstance.startTime = GetTickCount();

    // 打开音频文件
    std::wstring cmd = L"open \"" + filePath + L"\" alias " + newInstance.alias;
    if (mciSendCommand(cmd) != 0) {
        return; // 打开失败
    }

    // 设置音量
    cmd = L"setaudio " + newInstance.alias + L" volume to " + std::to_wstring(volume);
    mciSendCommand(cmd);

    // 播放音频
    cmd = L"play " + newInstance.alias;
    if (loop) cmd += L" repeat";
    mciSendCommand(cmd);

    // 添加到活动实例列表
    activeInstances.push_back(newInstance);
}

void SoundManager::update() {
    // 检查每个实例的状态
    for (auto it = activeInstances.begin(); it != activeInstances.end(); ) {
        if (it->state == SOUND_STOPPED) {
            // 关闭已停止的实例
            std::wstring cmd = L"close " + it->alias;
            mciSendCommand(cmd);
            it = activeInstances.erase(it);
        }
        else {
            // 检查播放状态
            std::wstring statusCmd = L"status " + it->alias + L" mode";

            wchar_t status[32] = { 0 };
            if (mciSendString(statusCmd.c_str(), status, 32, nullptr) == 0) {
                if (wcscmp(status, L"playing") != 0 &&
                    wcscmp(status, L"paused") != 0) {
                    it->state = SOUND_STOPPED;
                }
                else {
                    it->state = (wcscmp(status, L"paused") == 0) ?
                        SOUND_PAUSED : SOUND_PLAYING;
                }
            }
            ++it;
        }
    }
}

void SoundManager::stopAllSounds() {
    for (auto& instance : activeInstances) {
        if (instance.state == SOUND_PLAYING || instance.state == SOUND_PAUSED) {
            std::wstring cmd = L"stop " + instance.alias;
            mciSendCommand(cmd);
            instance.state = SOUND_STOPPED;
        }
    }
    // 立即更新状态
    update();
}

void SoundManager::stopSound(const std::wstring soundName) {
    for (auto& instance : activeInstances) {
        // 查找所有匹配的音效实例
        if (soundPool.find(soundName) != soundPool.end() &&
            instance.filePath == soundPool[soundName]) {
            if (instance.state == SOUND_PLAYING || instance.state == SOUND_PAUSED) {
                std::wstring cmd = L"stop " + instance.alias;
                mciSendCommand(cmd);
                instance.state = SOUND_STOPPED;
            }
        }
    }
}

void SoundManager::pauseAllSounds() {
    for (auto& instance : activeInstances) {
        if (instance.state == SOUND_PLAYING) {
            std::wstring cmd = L"pause " + instance.alias;
            mciSendCommand(cmd);
            instance.state = SOUND_PAUSED;
        }
    }
}

void SoundManager::resumeAllSounds() {
    for (auto& instance : activeInstances) {
        if (instance.state == SOUND_PAUSED) {
            std::wstring cmd = L"resume " + instance.alias;
            mciSendCommand(cmd);
            instance.state = SOUND_PLAYING;
        }
    }
}

void SoundManager::setGlobalVolume(int volume) {
    if (volume < 0) volume = 0;
    if (volume > 100) volume = 100;

    globalVolume = volume;

    // 更新所有活动实例的音量
    for (auto& instance : activeInstances) {
        int newVolume = instance.volume * globalVolume / 100;
        std::wstring cmd = L"setaudio " + instance.alias +
            L" volume to " + std::to_wstring(newVolume);
        mciSendCommand(cmd);
    }
}

void SoundManager::setSoundVolume(const std::wstring soundName, int volume) {
    if (volume < 0) volume = 0;
    if (volume > 100) volume = 100;

    // 更新所有匹配音效实例的音量
    for (auto& instance : activeInstances) {
        if (soundPool.find(soundName) != soundPool.end() &&
            instance.filePath == soundPool[soundName]) {
            // 应用全局音量
            int newVolume = volume * globalVolume / 100;
            instance.volume = newVolume;

            std::wstring cmd = L"setaudio " + instance.alias +
                L" volume to " + std::to_wstring(newVolume);
            mciSendCommand(cmd);
        }
    }
}

int SoundManager::getPlayingCount() const {
    int count = 0;
    for (const auto& instance : activeInstances) {
        if (instance.state == SOUND_PLAYING) {
            count++;
        }
    }
    return count;
}

int SoundManager::getSoundInstanceCount(const std::wstring soundName) const {
    int count = 0;
    if (soundPool.find(soundName) != soundPool.end()) {
        const std::wstring& filePath = soundPool.at(soundName);
        for (const auto& instance : activeInstances) {
            if (instance.filePath == filePath) {
                count++;
            }
        }
    }
    return count;
}