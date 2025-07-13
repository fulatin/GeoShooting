#include "SoundManager.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cwchar>

// ����ʵ��
SoundManager& SoundManager::getInstance() {
    static SoundManager instance;
    return instance;
}

SoundManager::SoundManager() : globalVolume(100) {
    // ��ʼ���������
    srand(static_cast<unsigned int>(time(nullptr)));
}

SoundManager::~SoundManager() {
    // �ر����л��Ч
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
    // ʹ��ʱ��������������Ψһ����
    wchar_t buf[32];
    swprintf(buf, 32, L"sound_%lu_%d",
        static_cast<unsigned long>(time(nullptr)),
        rand() % 10000);
    return std::wstring(buf);
}

bool SoundManager::loadSound(const std::wstring filePath, const std::wstring soundName) {
    // ����Ƿ��Ѵ���ͬ����Ч
    if (soundPool.find(soundName) != soundPool.end()) {
        return false;
    }

    // ��ӵ���Ч��

    soundPool[soundName] = filePath;
    return true;
}

void SoundManager::playSound(const std::wstring soundName, int volume, bool loop) {
    // �����Ч�Ƿ����
    auto it = soundPool.find(soundName);

    if (it == soundPool.end()) {
		wprintf(L"Sound not found: %s\n", soundName.c_str());
        return;
    }

    // Ӧ��ȫ������

    volume = volume * globalVolume / 100;
    if (volume > 1000) volume = 1000;
    if (volume < 0) volume = 0;

    // ������Ч
    playSoundInternal(it->second, volume, loop);
}

void SoundManager::playSoundInternal(const std::wstring filePath, int volume, bool loop) {
    // ������ʵ��
    SoundInstance newInstance;
    newInstance.alias = generateUniqueAlias();
    newInstance.filePath = filePath;
    newInstance.state = SOUND_PLAYING;
    newInstance.volume = volume;
    newInstance.startTime = GetTickCount();

    // ����Ƶ�ļ�
    std::wstring cmd = L"open \"" + filePath + L"\" alias " + newInstance.alias;
    if (mciSendCommand(cmd) != 0) {
        return; // ��ʧ��
    }

    // ��������
    cmd = L"setaudio " + newInstance.alias + L" volume to " + std::to_wstring(volume);
    mciSendCommand(cmd);

    // ������Ƶ
    cmd = L"play " + newInstance.alias;
    if (loop) cmd += L" repeat";
    mciSendCommand(cmd);

    // ��ӵ��ʵ���б�
    activeInstances.push_back(newInstance);
}

void SoundManager::update() {
    // ���ÿ��ʵ����״̬
    for (auto it = activeInstances.begin(); it != activeInstances.end(); ) {
        if (it->state == SOUND_STOPPED) {
            // �ر���ֹͣ��ʵ��
            std::wstring cmd = L"close " + it->alias;
            mciSendCommand(cmd);
            it = activeInstances.erase(it);
        }
        else {
            // ��鲥��״̬
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
    // ��������״̬
    update();
}

void SoundManager::stopSound(const std::wstring soundName) {
    for (auto& instance : activeInstances) {
        // ��������ƥ�����Чʵ��
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

    // �������лʵ��������
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

    // ��������ƥ����Чʵ��������
    for (auto& instance : activeInstances) {
        if (soundPool.find(soundName) != soundPool.end() &&
            instance.filePath == soundPool[soundName]) {
            // Ӧ��ȫ������
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