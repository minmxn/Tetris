#pragma once
#define MAX_SHAPE_SIZE 4

class CPiece
{
public:
	CPiece(void);
	~CPiece(void);

	// return false if the piece had a collision and has to be stopped.
 	bool Update(DWORD deltaTime);
	void Move(int DX, int DY);
	void Rotate();
	void Display(HDC hdc);
	int GetShape(int c, int l);
	int GetPosX() { return m_X; }
	int GetPosY() { return m_Y; }

protected:
	bool CollisionTest(int DX, int DY, int Rotation);

	struct SShapeDefinition
	{
		SShapeDefinition() { Reset(); }

		bool AddLine(int c1,int c2, int c3, int c4);
		bool IsValid() const	{ return m_lineCount == MAX_SHAPE_SIZE; }
		void Reset()	{ m_lineCount = 0; }

		int m_lineCount;
		int m_lines[MAX_SHAPE_SIZE][MAX_SHAPE_SIZE];
	};

	bool AddAvailableRotation(const SShapeDefinition & shapeDefinition); //QUESTION : why did we use a 'const &' here instead of simply AddAvailableRotation(SShapeDefinition shapeDefinition)

	std::vector<SShapeDefinition> m_availableRotation;

	unsigned int m_currentRotation;

	int m_X; // In Square unit
	int m_Y; // In Square unit

	float m_fY;
};

