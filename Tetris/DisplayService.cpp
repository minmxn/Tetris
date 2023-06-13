#include "StdAfx.h"
#include "DisplayService.h"

int CDisplayService::m_SquareSize = 20;
HPEN CDisplayService::m_Pen = NULL;
HPEN LedPen = NULL;

CDisplayService::CDisplayService(void)
{
}

CDisplayService::~CDisplayService(void)
{
}

void CDisplayService::Display(HDC hdc, int X, int Y)
{
	if (m_Pen == NULL)
		m_Pen = CreatePen(PS_SOLID, 1, RGB(0,0,255));
    SelectObject(hdc, m_Pen);
	int XS = X*m_SquareSize;
	int YS = Y*m_SquareSize;
    Rectangle(hdc, XS + 1, YS + 1, XS + m_SquareSize - 2, YS + m_SquareSize - 2);
}

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
// DISPLAY LED
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
void CDisplayService::DisplayLed(HDC hdc, int X, int Y, int N)
{
	if (LedPen == NULL)
    {
        LedPen = CreatePen(PS_SOLID, 1, RGB(0,0,0));
    }

    SelectObject(hdc, LedPen);
    int horiz = 20;
    int verti = 15;
    int h = 5;
    int XS = X;
    int YS = Y;
    switch (N)
    {
    case 1 : Rectangle(hdc, XS+h, YS, XS + horiz + h, YS + h); break;
    case 2 : Rectangle(hdc, XS+h, YS + h + verti, XS + horiz + h, YS + h + verti + h); break;
    case 3 : Rectangle(hdc, XS+h, YS + 2*(h + verti), XS + horiz + h, YS + 2*(h + verti) + h); break;
    case 4 : Rectangle(hdc, XS, YS+h, XS + h, YS + h + verti); break;
    case 5 : Rectangle(hdc, XS+h+horiz, YS+h, XS + h + h + horiz, YS + h + verti); break;
    case 6 : Rectangle(hdc, XS, YS+h + h + verti, XS + h, YS + h + verti + h + verti); break;
    case 7 : Rectangle(hdc, XS+h+horiz, YS+h + h + verti, XS + h + h + horiz, YS + h + verti + h + verti); break;
    }
}

void CDisplayService::DrawDigit(char _digit, HDC hdc, int X, int Y)
{
    switch(_digit)
    {
    case 0: DrawZero(hdc, X, Y);
        break;
    case 1: DrawOne(hdc, X, Y);
        break;
    case 2: DrawTwo(hdc, X, Y);
        break;
    case 3: DrawThree(hdc, X, Y);
        break;
    case 4: DrawFour(hdc, X, Y);
        break;
    case 5: DrawFive(hdc, X, Y);
        break;
    case 6: DrawSix(hdc, X, Y);
        break;
    case 7: DrawSeven(hdc, X, Y);
        break;
    case 8: DrawEight(hdc, X, Y);
        break;
    case 9: DrawNine(hdc, X, Y);
        break;
    }
}

void CDisplayService::DrawNumber(int number, HDC hdc, int X, int Y)
{
    do
    {
        char digit = number % 10;

        DrawDigit(digit, hdc, X, Y);

        number /= 10;
        X -= 37;
    } while (number != 0);
}

void CDisplayService::DrawOne(HDC hdc, int X, int Y)
{
    DisplayLed(hdc, X, Y, 5);
    DisplayLed(hdc, X, Y, 7);
}

void CDisplayService::DrawAllHorizLed(HDC hdc, int X, int Y)
{
    DisplayLed(hdc, X, Y, 1);
    DisplayLed(hdc, X, Y, 2);
    DisplayLed(hdc, X, Y, 3);
}

void CDisplayService::DrawTwo(HDC hdc, int X, int Y)
{
    DrawAllHorizLed(hdc, X, Y);
    DisplayLed(hdc, X, Y, 5);
    DisplayLed(hdc, X, Y, 6);
}

void CDisplayService::DrawThree(HDC hdc, int X, int Y)
{
    DrawOne(hdc, X, Y);
    DrawAllHorizLed(hdc, X, Y);
}

void CDisplayService::DrawFour(HDC hdc, int X, int Y)
{
    DrawOne(hdc, X, Y);
    DisplayLed(hdc, X, Y, 2);
    DisplayLed(hdc, X, Y, 4);
}

void CDisplayService::DrawFive(HDC hdc, int X, int Y)
{
    DrawAllHorizLed(hdc, X, Y);
    DisplayLed(hdc, X, Y, 4);
    DisplayLed(hdc, X, Y, 7);
}

void CDisplayService::DrawSix(HDC hdc, int X, int Y)
{
    DrawAllHorizLed(hdc, X, Y);
    DisplayLed(hdc, X, Y, 4);
    DisplayLed(hdc, X, Y, 6);
    DisplayLed(hdc, X, Y, 7);
}

void CDisplayService::DrawSeven(HDC hdc, int X, int Y)
{
    DrawOne(hdc, X, Y);
    DisplayLed(hdc, X, Y, 1);
}

void CDisplayService::DrawEight(HDC hdc, int X, int Y)
{
    DrawAllHorizLed(hdc, X, Y);
    DrawOne(hdc, X, Y);
    DisplayLed(hdc, X, Y, 4);
    DisplayLed(hdc, X, Y, 6);
}

void CDisplayService::DrawNine(HDC hdc, int X, int Y)
{
    DrawAllHorizLed(hdc, X, Y);
    DrawOne(hdc, X, Y);
    DisplayLed(hdc, X, Y, 4);
}

void CDisplayService::DrawZero(HDC hdc, int X, int Y)
{
    DrawOne(hdc, X, Y);
    DisplayLed(hdc, X, Y, 1);
    DisplayLed(hdc, X, Y, 3);
    DisplayLed(hdc, X, Y, 4);
    DisplayLed(hdc, X, Y, 6);
}
