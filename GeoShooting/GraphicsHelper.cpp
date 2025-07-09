#include "GraphicsHelper.h"
#include "Constants.h"
#include <cmath>
#include <vector>

#include <gdiplus.h>
#include<iostream>
#ifndef ARGB
#define ARGB(a, r, g, b) ((COLORREF)(((BYTE)(a) << 24) | ((BYTE)(r) << 16) | ((BYTE)(g) << 8) | ((BYTE)(b))))
#endif
using namespace std;
using namespace GeoShooting;
#define GetAValue(rgb) ((BYTE)(((DWORD)(rgb) >> 24) & 0xFF))
// �򵥻Թ�Ч�������ڴ������壬����˺��ӵ�����֤���ܣ�

// �򵥻Թ�Ч�������ڴ������壬����˺��ӵ�����֤���ܣ�
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


// �����x,y�������ζ�������Ͻ����꣬size�Ǳ߳�
void GraphicsHelper::drawTriangle(float x, float y, float size, COLORREF color)
{
    BYTE r = GetRValue(color);
    BYTE g = GetGValue(color);
    BYTE b = GetBValue(color);
    POINT pts[3] = { {(int)x,(int)y},{((int)x + size),(int)y},{(int)(x+size/2),(int)y+sqrt(3)*size/2}};
    setlinecolor(color);
	setlinestyle(PS_SOLID, 4);
    line(pts[0].x, pts[0].y, pts[1].x, pts[1].y);
    line(pts[1].x, pts[1].y, pts[2].x, pts[2].y);
    line(pts[2].x, pts[2].y, pts[0].x, pts[0].y);
    setfillcolor(color);
    //solidpolygon(pts, 3);
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

// UI ���ƺ��������䣩
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


// --- �������µ�GDI+�Թ�ʵ�� ---

// ������������EasyX��IMAGE����ת��ΪGDI+��Bitmap����
// ע�⣺�˺����ᴴ���µ�Bitmap���󣬵�������Ҫ����delete��
Gdiplus::Bitmap* CreateBitmapFromImage(IMAGE* pImg)
{
    int width = pImg->getwidth();
    int height = pImg->getheight();
    DWORD* pSrcMem = GetImageBuffer(pImg);

    Gdiplus::Bitmap* pBmp = new Gdiplus::Bitmap(width, height, PixelFormat32bppARGB);
    Gdiplus::BitmapData bmpData;
    Gdiplus::Rect rect(0, 0, width, height);

    pBmp->LockBits(&rect, Gdiplus::ImageLockModeWrite, PixelFormat32bppARGB, &bmpData);

    // EasyX����ɫ��ʽ��BGRA����GDI+��BitmapData��ҪARGB����Ҫ�ֶ�ת����
    BYTE* pDstPixel = (BYTE*)bmpData.Scan0;
    for (int i = 0; i < width * height; i++)
    {
        DWORD srcPixel = pSrcMem[i];
        pDstPixel[i * 4] = GetBValue(srcPixel); 
        pDstPixel[i * 4 + 1] = GetGValue(srcPixel); 
        pDstPixel[i * 4 + 2] = GetRValue(srcPixel); 
        pDstPixel[i * 4 + 3] = srcPixel>>24;              // Alpha (EasyX��Alphaͨ�����ɿ�, ǿ�Ʋ�͸��)
		//cout <<(int) pDstPixel[i * 4] << " " << (int)pDstPixel[i * 4 + 1] << " " << (int)pDstPixel[i * 4 + 2] << " " << (int)pDstPixel[i * 4 + 3] << endl;
    }

    pBmp->UnlockBits(&bmpData);
    return pBmp;
}

// �������������Լ�����Additive Blending����ɫ���
COLORREF AdditiveBlend(COLORREF dest, COLORREF src)
{
    int r = GetRValue(dest) + GetRValue(src);
    int g = GetGValue(dest) + GetGValue(src);
    int b = GetBValue(dest) + GetBValue(src);
	//cout << (int)GetAValue(dest) << " " << (int)GetAValue(src) << endl;
    return RGB(min(r, 255), min(g, 255), min(b, 255));
}


// ʹ��GDI+Ӧ�ûԹ�Ч����������
void GraphicsHelper::applyGlowWithGDI(IMAGE* pDst, IMAGE* pSrc, float radius, bool shadow)
{
    // 1. ��EasyX�ĻԹ�Դͼ��ת��ΪGDI+λͼ
    Gdiplus::Bitmap* pBmp = CreateBitmapFromImage(pSrc);
    if (!pBmp) return;

    // 2. ʹ��GDI+��Blur��Ч���и�˹ģ��
    Gdiplus::Blur blurEffect;
    Gdiplus::BlurParams blurParams;
    blurParams.radius = radius;
    blurParams.expandEdge = false; // ����չ��Ե������ԭ�ߴ�
    blurEffect.SetParameters(&blurParams);

    // Ӧ����Ч������ʵ�ָ�����ģ���ĺ���
    pBmp->ApplyEffect(&blurEffect, NULL);

    // 3. ��ģ�����GDI+λͼ���أ���ϻ�EasyX��Ŀ�껭��
    int width = pDst->getwidth();
    int height = pDst->getheight();
    DWORD* pDstMem = GetImageBuffer(pDst);

    Gdiplus::BitmapData bmpData;
    Gdiplus::Rect rect(0, 0, width, height);
    pBmp->LockBits(&rect, Gdiplus::ImageLockModeRead, PixelFormat32bppARGB, &bmpData);

    BYTE* pSrcPixel = (BYTE*)bmpData.Scan0;
    for (int i = 0; i < width * height; i++)
    {
        // ��GDI+λͼ��ȡģ�������ɫ (ARGB��ʽ)
        BYTE b_s = pSrcPixel[i * 4];
        BYTE g_s = pSrcPixel[i * 4 + 1];
        BYTE r_s = pSrcPixel[i * 4 + 2];
        BYTE a_s = pSrcPixel[i * 4 + 3];
        // ֻ��������ɫ�ĵط��Ž��л��
        if (r_s > 0 || g_s > 0 || b_s > 0)
        {
            COLORREF srcColor = RGB(r_s, g_s, b_s);
            pDstMem[i] = AdditiveBlend(pDstMem[i], srcColor);
        }
    }

    pBmp->UnlockBits(&bmpData);

    // 4. ����GDI+λͼ���󣬷�ֹ�ڴ�й©
    delete pBmp;

}
#include <graphics.h>
#include <conio.h>

// �Զ���͸�����ƺ���
void GraphicsHelper::drawTransparentImage(int x, int y, IMAGE* img, COLORREF transparentColor)
{
    DWORD* dst = GetImageBuffer();       // ���ڻ���������
    DWORD* src = GetImageBuffer(img);    // ͼ�񻺳���
    int winWidth = getwidth();           // ���ڿ��
    int imgWidth = img->getwidth();      // ͼ����
    int imgHeight = img->getheight();    // ͼ��߶�

    // ����ͼ��ÿ������
    for (int iy = 0; iy < imgHeight; iy++)
    {
        for (int ix = 0; ix < imgWidth; ix++)
        {
            // ��������λ��
            int pos = iy * imgWidth + ix;
            COLORREF color = src[pos];

            // �������͸��ɫ�����
            //if (color != transparentColor)
            //{
            //    int dstX = x + ix;
            //    int dstY = y + iy;
            //    if (dstX >= 0 && dstX < winWidth && dstY >= 0 && dstY < getheight())
            //    {
            //        dst[dstY * winWidth + dstX] = color;
            //    }
            //}
            // ������ɫ��ǰ��ɫ���
			int dstX = x + ix;
			int dstY = y + iy;
            dst[dstY*winWidth+dstX] = (color == transparentColor) ? dst[dstY * winWidth + dstX] :
                RGB(
                    (GetRValue(dst[dstY * winWidth + dstX]) * 0.5 + GetRValue(color) * 0.5),
                    (GetGValue(dst[dstY * winWidth + dstX]) * 0.5 + GetGValue(color) * 0.5),
                    (GetBValue(dst[dstY * winWidth + dstX]) * 0.5 + GetBValue(color) * 0.5)
				);
        }
    }
}

