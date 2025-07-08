#pragma once
#include <graphics.h>

// GraphicsHelper 命名空间包含所有自定义的绘图函数
namespace GeoShooting {
    namespace GraphicsHelper {
        // 绘制带辉光的矩形 (敌人) - 保持简单实现，因为敌人数量多，性能开销大
        void drawGlowRect(float x, float y, float w, float h, COLORREF color);

        // 绘制带辉光的三角形 (玩家) - 保持简单实现
        void drawGlowTriangle(float x, float y, float size, COLORREF color);

        // 绘制带辉光的线条 (子弹) - 保持简单实现
        void drawGlowLine(float x1, float y1, float x2, float y2, COLORREF color);

        // 绘制用户界面 (UI)，包括分数和生命值
        void drawUI(int score, int playerHp);

        // --- 高级辉光效果函数 ---

        // 对一个 IMAGE 对象进行箱式模糊
        void boxBlur(IMAGE* pImg, int radius);

        // 将源图像以“滤色”模式叠加到目标图像上
        void applyGlow(IMAGE* pDst, IMAGE* pSrc);
    }
}
