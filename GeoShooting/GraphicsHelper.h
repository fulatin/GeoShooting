#pragma once
#include <graphics.h>
#define GDIPVER 0x0110 // ���� GDI+ �汾
// GraphicsHelper �����ռ���������Զ���Ļ�ͼ����
#ifndef ARGB
#define ARGB(a, r, g, b) ((COLORREF)(((BYTE)(a) << 24) | ((BYTE)(r) << 16) | ((BYTE)(g) << 8) | ((BYTE)(b))))
#endif
#define GetAValue(color) ((BYTE)(((color) >> 24) & 0xFF))
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


        void boxBlur(IMAGE* pImg, int radius);
        void applyGlow(IMAGE* pDst, IMAGE* pSrc);
        void transparentBlend(DWORD* dst, DWORD* src, int alpha);
    }
}
