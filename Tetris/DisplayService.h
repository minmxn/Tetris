#pragma once

//QUESTION : Why did we used static in this class ?
//QUESTION : Is there another way to do it ?
class CDisplayService
{
public:
	//QUESTION : What is the purpose of these two functions (constructor and destructor) ?
	CDisplayService(void);
	~CDisplayService(void);

	static void Display(HDC hdc, int X, int Y);
    static void DisplayLed(HDC hdc, int X, int Y, int N);
    static void DrawAllHorizLed(HDC hdc, int X, int Y);
    static void DrawOne(HDC hdc, int X, int Y);
    static void DrawTwo(HDC hdc, int X, int Y);
    static void DrawThree(HDC hdc, int X, int Y);
    static void DrawFour(HDC hdc, int X, int Y);
    static void DrawFive(HDC hdc, int X, int Y);
    static void DrawSix(HDC hdc, int X, int Y);
    static void DrawSeven(HDC hdc, int X, int Y);
    static void DrawEight(HDC hdc, int X, int Y);
    static void DrawNine(HDC hdc, int X, int Y);
    static void DrawZero(HDC hdc, int X, int Y);
    static void DrawDigit(char digit, HDC hdc, int X, int Y);
    static void DrawNumber(int number, HDC hdc, int X, int Y);

public:
	static int m_SquareSize; // In Pixel.
	static HPEN m_Pen; // Pen
};

