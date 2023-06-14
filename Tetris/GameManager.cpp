#include "StdAfx.h"
#include <stdio.h>
#include "GameManager.h"
#include "DisplayService.h"

#include "Piece.h"
#include "Board.h"

CGameManager* CGameManager::m_Instance = NULL;

CGameManager::CGameManager(void)
{
	m_Board = new CBoard();

	AddPiece();
}


CGameManager::~CGameManager(void)
{
	RemovePiece();
	delete m_Board;
	m_Board = NULL;
}

bool CGameManager::TestCollision(int X, int Y)
{
	if (m_Board != NULL)
		return m_Board->TestCollision(X, Y);
	else
		return false;
}
bool CGameManager::TestCollisionPieces(int X, int Y)
{
	if (pool.size() > 1)
	{
		size_t i;
		size_t len = pool.size();
		for (i = 0; i < len; ++i)
		{
			if (m_currentPiece == i) // skip self check
				continue;
			int l, c;
			for (l = 0; l < MAX_SHAPE_SIZE; l++)
			{
				for ( c = 0; c < MAX_SHAPE_SIZE; c++)
				{
					int s = pool[i].GetShape(c, l);
					if (s != 0)
					{
						int x = pool[i].GetPosX() + c;
						int y = pool[i].GetPosY() + l;

						if(x == X && y == Y)
							return true;
					}
				}
			}



		}
	}

	return false;
}

CPiece* CGameManager::GetCurrentPiece()
{
	//tbh the current piece should always be valid might not need to check
	if (m_currentPiece != InvalidPiece)
		return &pool[m_currentPiece];
	return nullptr;
}

// range_min <= random number < range_max
int RangedRandNumber(int range_min, int range_max)
{
	// Generate random numbers in the half-closed interval
	// [range_min, range_max). In other words,
	// range_min <= random number < range_max
	int r = (int)((double)rand() / (RAND_MAX + 1) * (range_max - range_min) + range_min);
	return r;
}

void CGameManager::AddPiece()
{
	m_currentPiece = pool.size();
	pool.emplace_back();
	//m_currentPiece = new CPiece();
}

void CGameManager::RemovePiece()
{
	m_currentPiece = -1;
}

bool CGameManager::Update(DWORD deltaTime)
{
	if (!GetCurrentPiece()->Update(deltaTime))
	{
		RemovePiece();
		AddPiece();
	}
	return true;
}

void CGameManager::Display(HDC hdc)
{
	m_Board->Display(hdc);
	//m_currentPiece->Display(hdc);
	for (const CPiece& piece : pool)
	{
		piece.Display(hdc);
	}
	CDisplayService::DrawNumber(0, hdc, 400, 450);
}

void CGameManager::OnInput(eInput input)
{
	switch (input)
	{
	case eInputLeft:
	{
		GetCurrentPiece()->Move(-1, 0);
	}
	break;
	case eInputRight:
	{
		GetCurrentPiece()->Move(1, 0);
	}
	break;
	case eInputUp:
	{
		GetCurrentPiece()->Rotate();
	}
	break;
	case eInputSpace:
	{
		GetCurrentPiece()->Move(0, 1);
	}
	break;
	}
}

void CGameManager::StartRecording()
{
}

void CGameManager::StopRecording()
{
}

void CGameManager::Replay()
{
}
