#ifndef __DIG_INDICATOR_VALUE__
#define __DIG_INDICATOR_VALUE__

#include "digIndicator.h"

class DigIndicatorValue
{
public:	
	// ����� ������ �����:
	// 1) ���������� ���� ������
	// 2) ���������� ������ ���� �����
	// 3) �� ���������� ������
	enum {
		signTypeShowAlways,
		signTypeShowOnlyMinus,
		signTypeNotShow
	};

	enum {
		maxIndCount = 16
	};

private:
	bool	drawAsIntFlag;
	double	value;
	int		xStart;
	int		yStart;
	long	bColor;
	long	fColor;
	int		befPoint;
	int		aftPoint;
	int		nDigits;
	int		signShowType;
	bool	fixNumberChars;
	int		indSizeType;
	static DigIndicator **digIndList1;	// ������ verySmall ����������� maxIndCount �������
	static DigIndicator **digIndList2;	// ������ small ����������� maxIndCount �������
	static DigIndicator **digIndList3;	// ������ normal ����������� maxIndCount �������

	//! @brief ������� ��������� ASCII-������ ��� ����� ���� int
	//! @return ������
	char *GenerateStringByInt( );
	
	//! @brief ������� ��������� ASCII-������ ��� ����� ���� double
	//! @return ������
	char *GenerateStringByDouble( );

public:
	DigIndicatorValue( int x, int y, long bColor, long fColor, int indSizeType );
	~DigIndicatorValue( );

	//! @brief ������� ������������ ������ (������ ���������� ���� ��� ��� ���������� ������ ���������)
	//! @return
	static void Free( );

	//! @brief ������� ������ �������� ������ ����������� � ��������� ������
	//! @param value - �������� � ������� � ��������� ������
	//! @param befPoint - ���������� ������ �� ������� �����
	//! @param aftPoint - ���������� ������ ����� ������� �����
	//! @param signShowType - ����� ������ ����� (��. enum ����)
	//! @param fixNumberChars - ��������� ���������� ����� ������
	//! @return
	void SetDoubleValue( double value, int befPoint, int aftPoint, int signShowType, bool fixNumberChars );

	//! @brief ������� ������ �������� ������ ����������� ��� ������ �����
	//! @param value - ������������ ��������
	//! @param nDigits - ���������� ���������� ��������
	//! @param signShowType - ����� ������ ����� (��. enum ����)
	//! @param fixNumberChars - ��������� ���������� ����� ������
	//! @return
	void SetIntValue( int value, int nDigits, int signShowType, bool fixNumberChars );

	//! @brief ������� ���������� (�����������) ����������� �� ������
	//! @param pDC - �������� ����������
	//! @param k = 1, ���� 1x1 �������
	//! @param k = 2, ���� 2x2 �������
	//! @return
	void OnPaint(CDC *pDC, int k);
};

#endif