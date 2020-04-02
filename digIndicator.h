#ifndef __DIG_INDICATOR__
#define __DIG_INDICATOR__

class DigIndicator 
{
	int		xStart, yStart;
	long	bColor;
	long	fColor;
	
	long	*spriteBuffer;
	int		spriteBufferW;
	int		spriteBufferH;

	char	**spriteTemp;
	bool	smallIndFlag;

public:
	DigIndicator( int x, int y, long bColor, long fColor, bool isSmallInd = false );
	~DigIndicator();

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

	//! @brief ������� ��������� ������������ �� ����� ����������� ����������
	//! @return true - ���� ������������ ����� �����������
	bool isSmallInd( );
};

#endif