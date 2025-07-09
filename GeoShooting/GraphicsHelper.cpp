#include "GraphicsHelper.h"
#include "Constants.h"
#include <cmath>
#include <vector>


using namespace GeoShooting;
// 简单辉光效果（用于大量物体，如敌人和子弹，保证性能）
void GraphicsHelper::drawRect(float x, float y, float w, float h, COLORREF color)
{
    BYTE r = GetRValue(color);
    BYTE g = GetGValue(color);
    BYTE b = GetBValue(color);
    for (int i = 3; i > 0; --i)
    {
        setlinecolor(ARGB(60 - i * 15, r, g, b));
        setlinestyle(PS_SOLID, i * 2);
        rectangle(int(x - i), int(y - i), int(x + w + i), int(y + h + i));
    }
    setfillcolor(color);
    solidrectangle(int(x), int(y), int(x + w), int(y + h));
}

void GraphicsHelper::drawTriangle(float x, float y, float size, COLORREF color)
{
    BYTE r = GetRValue(color);
    BYTE g = GetGValue(color);
    BYTE b = GetBValue(color);
    POINT pts[3] = { {(int)x, (int)(y - size / 2)}, {(int)(x - size / 2), (int)(y + size / 2)}, {(int)(x + size / 2), (int)(y + size / 2)} };
        setlinecolor(RGB(r, g, b));
        setlinestyle(PS_SOLID, 6);
        line(pts[0].x, pts[0].y, pts[1].x, pts[1].y);
        line(pts[1].x, pts[1].y, pts[2].x, pts[2].y);
        line(pts[2].x, pts[2].y, pts[0].x, pts[0].y);


}

void GraphicsHelper::drawLine(float x1, float y1, float x2, float y2, COLORREF color)
{
    BYTE r = GetRValue(color);
    BYTE g = GetGValue(color);
    BYTE b = GetBValue(color);
    setlinecolor(ARGB(100, r, g, b));
    setlinestyle(PS_SOLID, 5);
    line(int(x1), int(y1), int(x2), int(y2));
    setlinecolor(color);
    setlinestyle(PS_SOLID, 2);
    line(int(x1), int(y1), int(x2), int(y2));
}

// UI 绘制函数（不变）
void GraphicsHelper::drawUI(int score, int playerHp)
{
    setbkmode(TRANSPARENT);
    settextcolor(RGB(0, 255, 255));
    settextstyle(20, 0, _T("Consolas"));
    TCHAR scoreStr[32];
    _stprintf_s(scoreStr, _T("SCORE: %d"), score);
    outtextxy(10, 10, scoreStr);
    settextcolor(RGB(255, 0, 255));
    outtextxy(WINDOW_WIDTH - 150, 10, _T("HP: "));
    for (int i = 0; i < playerHp; ++i)
    {
        drawRect(float(WINDOW_WIDTH - 110 + i * 25), 12, 20, 15, RGB(255, 0, 255));
    }
}


// --- 以下是新的高级辉光实现 ---

// 辅助函数：手动进行颜色叠加（线性减淡/Additive Blending）
COLORREF AdditiveBlend(COLORREF dest, COLORREF src)
{
    int r = GetRValue(dest) + GetRValue(src);
    int g = GetGValue(dest) + GetGValue(src);
    int b = GetBValue(dest) + GetBValue(src);
    return RGB(min(r, 255), min(g, 255), min(b, 255));
}
COLORREF AlphaBlend(COLORREF dest, COLORREF src) {
	COLORREF result;
	int alpha = GetAValue(src);
    result = ARGB(
        0,
        ((256-alpha)*GetRValue(dest)+alpha*GetRValue(src))>>8,
        ((256 - alpha) * GetGValue(dest) + alpha * GetGValue(src)) >> 8,
		((256 - alpha) * GetBValue(dest) + alpha * GetBValue(src)) >> 8

    );
    return result;
}
// 对图像进行箱式模糊（多次迭代近似高斯模糊）
void GraphicsHelper::boxBlur(IMAGE* pImg, int radius)
{
    int width = pImg->getwidth();
    int height = pImg->getheight();
    DWORD* pMem = GetImageBuffer(pImg);

    std::vector<int> r, g, b;
    r.resize(width * height);
    g.resize(width * height);
    b.resize(width * height);

    // 横向模糊
    for (int y = 0; y < height; ++y) {
        int r_sum = 0, g_sum = 0, b_sum = 0;
        for (int x = 0; x < width; ++x) {
            if (x == 0) {
                for (int i = -radius; i <= radius; ++i) {
                    int xi = max(0, min(width - 1, i));
                    COLORREF c = pMem[y * width + xi];
                    r_sum += GetRValue(c);
                    g_sum += GetGValue(c);
                    b_sum += GetBValue(c);
                }
            }
            else {
                COLORREF c_out = pMem[y * width + max(0, x - radius - 1)];
                COLORREF c_in = pMem[y * width + min(width - 1, x + radius)];
                r_sum = r_sum - GetRValue(c_out) + GetRValue(c_in);
                g_sum = g_sum - GetGValue(c_out) + GetGValue(c_in);
                b_sum = b_sum - GetBValue(c_out) + GetBValue(c_in);
            }
            int count = min(width - 1, x + radius) - max(0, x - radius) + 1;
            r[y * width + x] = r_sum / count;
            g[y * width + x] = g_sum / count;
            b[y * width + x] = b_sum / count;
        }
    }

    // 纵向模糊
    for (int x = 0; x < width; ++x) {
        int r_sum = 0, g_sum = 0, b_sum = 0;
        for (int y = 0; y < height; ++y) {
            if (y == 0) {
                for (int i = -radius; i <= radius; ++i) {
                    int yi = max(0, min(height - 1, i));
                    r_sum += r[yi * width + x];
                    g_sum += g[yi * width + x];
                    b_sum += b[yi * width + x];
                }
            }
            else {
                int r_out = r[max(0, y - radius - 1) * width + x];
                int g_out = g[max(0, y - radius - 1) * width + x];
                int b_out = b[max(0, y - radius - 1) * width + x];
                int r_in = r[min(height - 1, y + radius) * width + x];
                int g_in = g[min(height - 1, y + radius) * width + x];
                int b_in = b[min(height - 1, y + radius) * width + x];
                r_sum = r_sum - r_out + r_in;
                g_sum = g_sum - g_out + g_in;
                b_sum = b_sum - b_out + b_in;
            }
            int count = min(height - 1, y + radius) - max(0, y - radius) + 1;
            pMem[y * width + x] = RGB(r_sum / count, g_sum / count, b_sum / count);
        }
    }
}

// 将辉光图像叠加到主绘图设备
void GraphicsHelper::applyGlow(IMAGE* pDst, IMAGE* pSrc)
{
    DWORD* pDstMem = GetImageBuffer(pDst);
    DWORD* pSrcMem = GetImageBuffer(pSrc);
    int width = pDst->getwidth();
    int height = pDst->getheight();

    for (int i = 0; i < width * height; ++i)
    {
        // 使用自定义的颜色叠加函数
        pDstMem[i] = AdditiveBlend(pDstMem[i], pSrcMem[i]);
    }
}
void GraphicsHelper::transparentBlend(DWORD* pDstMem, DWORD* pSrcMem, int alpha) {
    int width = getwidth();
    int height = getheight();

    for (int i = 0; i < width * height; ++i)
    {
        // 使用自定义的颜色叠加函数
        pDstMem[i] = AlphaBlend(pDstMem[i], pSrcMem[i]);
    }
}