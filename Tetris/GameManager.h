#pragma once
#include "Piece.h"

class CPiece;
class CBoard;
enum eInput {
	eInputLeft,
	eInputRight,
	eInputUp,
	eInputDown,
	eInputSpace
};
class CGameManager
{
public:
	static constexpr int InvalidPiece = -1;

	CGameManager(void);
	~CGameManager(void);

	void OnInput(eInput input);
	bool Update(DWORD deltaTime);
	void Display(HDC hdc);
	static void Create() { m_Instance = new CGameManager(); }
	static CGameManager* GetInstance() { return m_Instance; }

	CPiece* GetCurrentPiece();
	bool TestCollision(int X, int Y);
	bool TestCollisionPieces(int X, int Y);
	void StartRecording();
	void StopRecording();
	void Replay();

private:
	void AddPiece();
	void RemovePiece();

	std::vector<CPiece> pool; // active pieces
	std::queue<CPiece> queue; // destroyed piece to recycle

	int	m_currentPiece; //avoid ptr how we are using vector and it may reallocate
	CBoard* m_Board;

	static CGameManager* m_Instance;
};

