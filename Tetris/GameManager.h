#pragma once
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
	CGameManager(void);
	~CGameManager(void);

	void OnInput(eInput input);
	bool Update(DWORD deltaTime);
	void Display(HDC hdc);
	static void Create() { m_Instance = new CGameManager(); }
	static CGameManager* GetInstance() { return m_Instance; }
	bool TestCollision(int X, int Y);

	void StartRecording();
	void StopRecording();
	void Replay();

private:
	void AddPiece();
	void RemovePiece();

	CPiece* m_currentPiece;
	CBoard* m_Board;

	static CGameManager* m_Instance;
};

