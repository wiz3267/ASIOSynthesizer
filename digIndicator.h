#ifndef __DIG_INDICATOR__
#define __DIG_INDICATOR__

class DigIndicator 
{
public:
	enum {
		indTypeVerySmall = 0,
		indTypeSmall = 1,
		indTypeNormal = 2
	};

	int		xStart, yStart;
private:	
	long	bColor;
	long	fColor;
	
	static long	*spriteBuffer1;		// ������ ��� verySmall �����������
	static long	*spriteBuffer2;		// ������ ��� small �����������
	static long	*spriteBuffer3;		// ������ ��� normal �����������
	long	*spriteBuffer;
	
	int		spriteBufferW;
	int		spriteBufferH;

	static char	**spriteTemp1;		// ��������� ������ ��� small �����������
	static char	**spriteTemp2;		// ��������� ������ ��� normal �����������
	char	**spriteTemp;
	static char	*smallSpriteTemp;	// ��������� ������ ��� verySmall �����������
	int		indSizeType;

public:
	DigIndicator( int x, int y, long bColor, long fColor, int indSizeType = 0 );
	~DigIndicator();

	//! @brief ������� ������������ ������ (������ ���������� ���� ��� �� ���������� ���������)
	//! @return
	static void Free( );

	//! @brief ������� ��������� ��������� ����������
	//! @param x, y - ����� ���������� ����������
	//! @return
	void SetCoord( int x, int y );

	//! @brief ������� ��������� ����� ���������� � ����� ����
	//! @param bColor - ���� ����
	//! @param fColor - ���� ����������� ����������
	//! @return
	void SetColor( long bColor, long fColor );

	//! @brief ������� ����������� ASCII-������� � ������ ���������� ���� �� ���������
	//! @param c - ��� �������
	//! @param needPoint - ����� �� �����
	//! @return
	void DrawBufferSmall( char c, bool needPoint = false );

	//! @brief ������� ����������� ASCII-������� � ������ ����������
	//! @param c - ��� �������
	//! @param needPoint - ����� �� �����
	//! @return
	void DrawBuffer( char c, bool needPoint = false );
	
	//! @brief ������� ���������� (�����������) ����������� �� ������
	//! @param pDC - �������� ����������
	//! @param k = 1, ���� 1x1 �������
	//! @param k = 2, ���� 2x2 �������
	//! @return
	void OnPaint(CDC *pDC, int k);

	//! @brief ������� ���������� (�����������) ��������� ������� ����� �� ������
	//! @param pDC - �������� ����������
	//! @param k = 1, ���� 1x1 �������
	//! @param k = 2, ���� 2x2 �������
	//! @return
	void OnPaintVerySmallPoint(CDC *pDC, int k);

	//! @brief ������� ���������� ������ ��������� (verySmall) ������� ����� �� ������
	//! @return ������ ������� �����
	int GetVerySmallPointSize( );

	//! @brief ������� ���������� ��� ������� ���������� (������� �������)
	//! @return ��� ������� ����������
	int GetIndSizeType( );
};

#endif