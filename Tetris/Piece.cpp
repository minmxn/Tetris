#include "StdAfx.h"
#include "Piece.h"
#include "DisplayService.h"
#include "GameManager.h"

const CPiece::SShapeDefinition& CPiece::GetCurrentRotation() const noexcept
{
	return m_availableRotation[m_currentRotation];
}

CPiece::CPiece()
{
	m_X = 0;
	m_Y = 0;
	m_currentRotation = 0;
	m_fY = 0;

	// Define a square Piece (no need to take care of rotation :) )
	SShapeDefinition newShape;

	newShape.Reset();
	newShape.AddLine(0,0,0,0);
	newShape.AddLine(0,1,1,0);
	newShape.AddLine(0,1,1,0);
	newShape.AddLine(0,0,0,0);
	AddAvailableRotation(newShape);
}


CPiece::~CPiece()
{
}

int CPiece::GetShape(int c, int l)
{
	if (!m_availableRotation.empty())
	{
		if (m_availableRotation[m_currentRotation].IsValid())
		{
 			if ((c < MAX_SHAPE_SIZE) || (l < MAX_SHAPE_SIZE))
				return m_availableRotation[m_currentRotation].m_lines[l][c];
		}
	}
	return 0;
}

void CPiece::Display(HDC hdc) const noexcept
{
	if (!m_availableRotation.empty())
	{
		if (m_availableRotation[m_currentRotation].IsValid())
		{
			for (int l = 0; l < MAX_SHAPE_SIZE; l++)
			{// For each line
				for (int c = 0; c < MAX_SHAPE_SIZE; c++)
				{
					if (m_availableRotation[m_currentRotation].m_lines[l][c] != 0)
						CDisplayService::Display(hdc, m_X + c, m_Y + l);
				}
			}
		}
	}
}

bool CPiece::Update(DWORD deltaTime)
{
	float m_fSpeedY = 0.005f;
	m_fY += deltaTime * m_fSpeedY;
	if (m_fY > 1)
	{// You move only when we have an integer value.
		m_fY = 0;
		if (CollisionTest(0, 1, m_currentRotation))
		{// Stop the piece
			return false;
		}
		else
		{
			m_Y += 1;
		}
	}
	return true;
}

bool CPiece::CollisionTest(int DX, int DY, int Rotation)
{
	if (!m_availableRotation.empty())
	{
		if (m_availableRotation[Rotation].IsValid())
		{
			for (int l = 0; l < MAX_SHAPE_SIZE; l++)
			{// For each line
				for (int c = 0; c < MAX_SHAPE_SIZE; c++)
				{
					if (m_availableRotation[Rotation].m_lines[l][c] != 0)
					{
						//this test for board collision
						if (CGameManager::GetInstance()->TestCollision(m_X + c + DX, m_Y + l + DY))
							return true;

						//this test for piece to piece collision
						if (CGameManager::GetInstance()->TestCollisionPieces(m_X + c + DX, m_Y + l + DY))
							return true;
					}
				}
			}
		}
	}
	return false;
}

void CPiece::Move( int DX, int DY )
{
	if (CollisionTest(DX, DY, m_currentRotation))
		return;
	m_X += DX;
	m_Y += DY;
}

void CPiece::Rotate()
{
	int CurrRot = m_currentRotation;
	
	if (!CollisionTest(0, 0, CurrRot))
	{// We can do the rotation.
		m_currentRotation = CurrRot;
	}
}

bool CPiece::AddAvailableRotation(const SShapeDefinition & shapeDefinition)
{
	if (shapeDefinition.IsValid())
	{
		m_availableRotation.push_back(shapeDefinition);
		return true;
	}
	return false;
}

bool CPiece::SShapeDefinition::AddLine( int c1,int c2, int c3, int c4 )
{
	if (m_lineCount < MAX_SHAPE_SIZE)
	{
		m_lines[m_lineCount][0] = c1;
		m_lines[m_lineCount][1] = c2;
		m_lines[m_lineCount][2] = c3;
		m_lines[m_lineCount][3] = c4;
		m_lineCount++;
		return true;
	}
	return false;
}
