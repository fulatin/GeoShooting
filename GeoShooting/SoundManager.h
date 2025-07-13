#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

// ��Чʵ��״̬
enum SoundState {
    SOUND_PLAYING,
    SOUND_STOPPED,
    SOUND_PAUSED
};

// ��Чʵ���ṹ
struct SoundInstance {
    std::wstring alias;      // MCI����
    std::wstring filePath;   // �ļ�·��
    SoundState state;        // ��ǰ״̬
    int volume;              // ���� (0-1000)
    DWORD startTime;         // ��ʼ����ʱ��
};

class SoundManager {
public:
    // ��ȡ����ʵ��
    static SoundManager& getInstance();

    // ��ֹ�����͸�ֵ
    SoundManager(const SoundManager&) = delete;
    void operator=(const SoundManager&) = delete;

    // ������Ч
    bool loadSound(const std::wstring filePath, const std::wstring soundName);

    // ������Ч
    void playSound(const std::wstring soundName, int volume = 1000, bool loop = false);

    // ֹͣ������Ч
    void stopAllSounds();

    // ֹͣ�ض���Ч������ʵ��
    void stopSound(const std::wstring soundName);

    // ��ͣ������Ч
    void pauseAllSounds();

    // �ָ�������Ч
    void resumeAllSounds();

    // ����ȫ������ (0-100)
    void setGlobalVolume(int volume);

    // �����ض���Ч������ (0-100)
    void setSoundVolume(const std::wstring soundName, int volume);

    // ������Ч״̬ (��������ɵ�ʵ��)
    void update();

    // ��ȡ���ڲ��ŵ���Ч����
    int getPlayingCount() const;

    // ��ȡȫ������
    int getGlobalVolume() const { return globalVolume; }

    // ��ȡ�ض���Ч��ʵ������
    int getSoundInstanceCount(const std::wstring soundName) const;

	// ��ȡ������Ч��ʵ������
	int getTotalSoundInstanceCount() const { return static_cast<int>(activeInstances.size()); }

private:
    SoundManager();  // ˽�й��캯��
    ~SoundManager(); // ��������

    // ����Ψһ����
    std::wstring generateUniqueAlias();

    // �ڲ����ź���
    void playSoundInternal(const std::wstring filePath, int volume, bool loop);

    // ����MCI���� (���ַ��汾)
    MCIERROR mciSendCommand(const std::wstring command) const;

    // ��Ч��
    std::map<std::wstring, std::wstring> soundPool; // <��Ч����, �ļ�·��>

    // ���Чʵ��
    std::vector<SoundInstance> activeInstances;

    // ȫ������ (0-100)
    int globalVolume;
};

#endif // SOUNDMANAGER_H