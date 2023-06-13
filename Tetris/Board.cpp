#include "StdAfx.h"
#include "Board.h"
#include "DisplayService.h"
#include "Piece.h"

CBoard::CBoard(void)
{
	m_Pen = CreatePen(PS_SOLID, 1, RGB(0,0,0));
}


CBoard::~CBoard(void)
{
}

bool CBoard::TestCollision(int X, int Y)
{
	if ((X >= MAX_COL) || (Y >= MAX_LINE) || (X < 0))
		return true;

	return false;
}

void CBoard::Display(HDC hdc)
{
	SelectObject(hdc,m_Pen);
	Rectangle(hdc, 0, 0, MAX_COL * CDisplayService::m_SquareSize + 4, MAX_LINE * CDisplayService::m_SquareSize + 4);
}