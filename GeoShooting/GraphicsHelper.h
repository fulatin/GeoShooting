#pragma once
#include <graphics.h>
#define GDIPVER 0x0110 // 定义 GDI+ 版本
// GraphicsHelper 命名空间包含所有自定义的绘图函数
#ifndef ARGB
#define ARGB(a, r, g, b) ((COLORREF)(((BYTE)(a) << 24) | ((BYTE)(r) << 16) | ((BYTE)(g) << 8) | ((BYTE)(b))))
#endif
#define GetAValue(color) ((BYTE)(((color) >> 24) & 0xFF))
namespace GeoShooting {
    namespace GraphicsHelper {
        // 绘制带辉光的矩形 (用于敌人)
        void drawRect(float x, float y, float w, float h, COLORREF color);

        // 绘制带辉光的三角形 (用于玩家)
        void drawTriangle(float x, float y, float size, COLORREF color);

        // 绘制带辉光的线条 (用于子弹)
        void drawLine(float x1, float y1, float x2, float y2, COLORREF color);

        // 绘制用户界面 (UI)，包括分数和生命值
        void drawUI(int score, int playerHp);


        void boxBlur(IMAGE* pImg, int radius);
        void applyGlow(IMAGE* pDst, IMAGE* pSrc);
        void transparentBlend(DWORD* dst, DWORD* src, int alpha);
    }
}
