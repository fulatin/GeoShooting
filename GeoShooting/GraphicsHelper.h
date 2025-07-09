#pragma once
#include <graphics.h>
#define GDIPVER 0x0110 // ���� GDI+ �汾
// GraphicsHelper �����ռ���������Զ���Ļ�ͼ����
namespace GeoShooting {
    namespace GraphicsHelper {
        // ���ƴ��Թ�ľ��� (���ڵ���)
        void drawRect(float x, float y, float w, float h, COLORREF color);

        // ���ƴ��Թ�������� (�������)
        void drawTriangle(float x, float y, float size, COLORREF color);

        // ���ƴ��Թ������ (�����ӵ�)
        void drawLine(float x1, float y1, float x2, float y2, COLORREF color);

        // �����û����� (UI)����������������ֵ
        void drawUI(int score, int playerHp);

        // ������ʹ��GDI+Ӧ�ø������Թ�Ч���ĺ���
        void applyGlowWithGDI(IMAGE* pDst, IMAGE* pSrc, float radius, bool shadow);
        
		void drawTransparentImage(int x, int y, IMAGE* img, COLORREF transparentColor);
    }
}
