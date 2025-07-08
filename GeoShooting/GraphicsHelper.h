#pragma once
#include <graphics.h>

// GraphicsHelper �����ռ���������Զ���Ļ�ͼ����
namespace GeoShooting {
    namespace GraphicsHelper {
        // ���ƴ��Թ�ľ��� (����) - ���ּ�ʵ�֣���Ϊ���������࣬���ܿ�����
        void drawGlowRect(float x, float y, float w, float h, COLORREF color);

        // ���ƴ��Թ�������� (���) - ���ּ�ʵ��
        void drawGlowTriangle(float x, float y, float size, COLORREF color);

        // ���ƴ��Թ������ (�ӵ�) - ���ּ�ʵ��
        void drawGlowLine(float x1, float y1, float x2, float y2, COLORREF color);

        // �����û����� (UI)����������������ֵ
        void drawUI(int score, int playerHp);

        // --- �߼��Թ�Ч������ ---

        // ��һ�� IMAGE ���������ʽģ��
        void boxBlur(IMAGE* pImg, int radius);

        // ��Դͼ���ԡ���ɫ��ģʽ���ӵ�Ŀ��ͼ����
        void applyGlow(IMAGE* pDst, IMAGE* pSrc);
    }
}
