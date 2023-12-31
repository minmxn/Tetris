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

// range_min <= random number < range_max
int RangedRandNumber( int range_min, int range_max)
{
	// Generate random numbers in the half-closed interval
	// [range_min, range_max). In other words,
	// range_min <= random number < range_max
	int r = (int)((double)rand() / (RAND_MAX + 1) * (range_max - range_min) + range_min);
	return r;
}

void CGameManager::AddPiece()
{
	m_currentPiece = new CPiece();
}

void CGameManager::RemovePiece()
{
	m_currentPiece = NULL;
}

bool CGameManager::Update(DWORD deltaTime)
{		
	if (!m_currentPiece->Update(deltaTime))
	{
		RemovePiece();
		AddPiece();
	}
	return true;
}

void CGameManager::Display(HDC hdc)
{
	m_Board->Display(hdc);
	m_currentPiece->Display(hdc);
    CDisplayService::DrawNumber(0, hdc, 400, 450);
}

void CGameManager::OnInput( eInput input )
{
	switch (input)
	{
	case eInputLeft: 
		{
			m_currentPiece->Move(-1, 0);
		}
		break;
	case eInputRight: 
		{
			m_currentPiece->Move(1, 0);
		}
		break;
	case eInputUp:
		{
			m_currentPiece->Rotate();
		}
		break;
	case eInputSpace: 
		{
			m_currentPiece->Move(0, 1);
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
