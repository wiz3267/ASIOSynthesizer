#ifndef __CIRCLE_SLIDER_INDICATOR__
#define __CIRCLE_SLIDER_INDICATOR__

#include "circleSlider.h"
#include "digIndicator.h"
#include "digIndicatorValue.h"
#include "digIndicatorInput.h"

class CircleSliderIndicator 
{
public:
	enum {
		typeOfElem1,
		typeOfElem2,
		typeOfElem3,
		typeOfElem4,
		typeOfElem5,
		typeOfElem6,
		typeOfElem7,
		typeOfElem8,
		typeOfElem9,
	};
//private:	
public:
	int		xSliderStart;
	int		ySliderStart;
	int		sliderDrawType;
	
	int		xIndStart;
	int		yIndStart;
	int		indSizeType;
	bool	doubleIndFlag;

	double	doubleValue1;
	double	doubleValue2;

	long	bColorInd;
	long	fColorInd;

	bool	showAsDoubleFlag;

	int		befPoint;
	int		aftPoint;
	int		countOfIndicator;
	int		signShowType;

	int		typeOfElem;

	bool	redraw;	//������� ����� ������������
	bool	textInputCaptured;
	DigIndicatorInput *digInput;
	
public:

	CircleSlider	*pSlider;

	//! @brief ������� ������������� �������� ������� [0..1] � ������ ������
	//! @param t - �������� [0..1]
	//! @param emptyFlag - true, ���� ������� ��������� �� ������ ����� ���� � �������� ������� �� �������
	//! @return ��������
	double ConvertValue( double t, bool &emptyFlag );

public:
	//! @brief ������� ������� � ������ �� �����������, ����� ��������, ��������� � �������� ���������
	//! @param x, y - ���������� �����, � ������� ����� �������� �������
	//! @param typeOfElem - ���� �� ���������������� ����� �������� (��. enum)
	//! @param valueStart - ������ ����� �������� (int ��� double)
	//! @param valueEnd - ������� ����� �������� (int ��� double)
	//! @param curValue - ��������� ��������
	//! @param intFlag - true, ���� ����� ���������� ������ ����� ��������
	//! @param countOfIndicator - ����� �����������, �� ������� ����� ���������� ��������
	//! @param signShowType - �������� ����� ����������� ������ "+" � "-" ����� ������
	//! @return
	CircleSliderIndicator( int x, int y, int typeOfElem, double valueStart, double valueEnd, 
		                   double curValue, bool intFlag, int countOfIndicator, int signShowType );
	
	//! @brief ����������
	//! @return
	~CircleSliderIndicator( );

	//! @brief ������� ��������� �������� ��������
	//! @return ������� �������� � ������� � ��������� ������ (���� int ������������ ��� double)
	double GetValue( );

	//! @brief ������� ��������� �������� ��������
	//! @param value - ��������
	//! @return
	void SetValue( double value );

	//! @brief ������� ������������ ��������� �� �����
	//! @param nFlags - ����� ������� ������
	//! @param point - ���������� ����� ������� ����
	//! @return
	void OnMouseMove( UINT nFlags,CPoint point );

	//! @brief ������� ������������ ������ ������ ������ ����
	//! @param nFlags - ����� ������� ������
	//! @param point - ���������� ����� ������� ����
	//! @return
	void OnRButtonUp( UINT nFlags,CPoint point );

	//! @brief ������� ������������ ������� ������ ����� ������� ����
	//! @param nFlags - ����� ������� ������
	//! @param point - ���������� ����� ������� ����
	//! @return
	void OnLButtonDoubleClick( UINT nFlags,CPoint point );

	//! @brief ������� ���������� (�����������) ����������� �� ������
	//! @param pDC - �������� ����������
	//! @return
	void OnPaint( CDC *pDC );

	//! @brief �������� ���������� (����������) ���������� ���� �����
	//! @param pDC - �������� ����������
	//! @return
	void OnPaintDigInput( CDC *pDC );

	//! @brief ������� �������� ���������� ���� �����
	//! @param pDC - �������� ����������
	//! @return
	void OnClearArea( CDC *pDC );

	//! @brief ��������� ������� �� ������� (����� ��� ���������� ���� �����)
	//! @param keyPressed - ������� �������
	//! @return ������ �� ������� �����
	bool HandleKey( int keyPressed );

	//! @brief ��������, �������� �� ����� ���������� �����
	//! @return true - ���� ����� ��������, ����� false
	bool IsTextInputCaptured( );
};

#endif