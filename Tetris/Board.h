#pragma once

#define MAX_COL	12
#define MAX_LINE 25

class CPiece;

class CBoard
{
public:
	CBoard(void);
	~CBoard(void);

	bool TestCollision(int X, int Y);
	void Display(HDC hdc);

private:
	HPEN m_Pen;
};

