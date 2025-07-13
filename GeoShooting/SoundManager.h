#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

// 音效实例状态
enum SoundState {
    SOUND_PLAYING,
    SOUND_STOPPED,
    SOUND_PAUSED
};

// 音效实例结构
struct SoundInstance {
    std::wstring alias;      // MCI别名
    std::wstring filePath;   // 文件路径
    SoundState state;        // 当前状态
    int volume;              // 音量 (0-1000)
    DWORD startTime;         // 开始播放时间
};

class SoundManager {
public:
    // 获取单例实例
    static SoundManager& getInstance();

    // 禁止拷贝和赋值
    SoundManager(const SoundManager&) = delete;
    void operator=(const SoundManager&) = delete;

    // 加载音效
    bool loadSound(const std::wstring filePath, const std::wstring soundName);

    // 播放音效
    void playSound(const std::wstring soundName, int volume = 1000, bool loop = false);

    // 停止所有音效
    void stopAllSounds();

    // 停止特定音效的所有实例
    void stopSound(const std::wstring soundName);

    // 暂停所有音效
    void pauseAllSounds();

    // 恢复所有音效
    void resumeAllSounds();

    // 设置全局音量 (0-100)
    void setGlobalVolume(int volume);

    // 设置特定音效的音量 (0-100)
    void setSoundVolume(const std::wstring soundName, int volume);

    // 更新音效状态 (清理已完成的实例)
    void update();

    // 获取正在播放的音效数量
    int getPlayingCount() const;

    // 获取全局音量
    int getGlobalVolume() const { return globalVolume; }

    // 获取特定音效的实例数量
    int getSoundInstanceCount(const std::wstring soundName) const;

	// 获取所有音效的实例数量
	int getTotalSoundInstanceCount() const { return static_cast<int>(activeInstances.size()); }

private:
    SoundManager();  // 私有构造函数
    ~SoundManager(); // 析构函数

    // 生成唯一别名
    std::wstring generateUniqueAlias();

    // 内部播放函数
    void playSoundInternal(const std::wstring filePath, int volume, bool loop);

    // 发送MCI命令 (宽字符版本)
    MCIERROR mciSendCommand(const std::wstring command) const;

    // 音效池
    std::map<std::wstring, std::wstring> soundPool; // <音效名称, 文件路径>

    // 活动音效实例
    std::vector<SoundInstance> activeInstances;

    // 全局音量 (0-100)
    int globalVolume;
};

#endif // SOUNDMANAGER_H