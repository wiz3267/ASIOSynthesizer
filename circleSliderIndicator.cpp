#include <stdafx.h>
#include "circleSliderIndicator.h"

//! @brief —оздать элемент с такими то координатми, типом элемента, начальным и конечным значением
//! @param x, y - координаты места, в котором будет размещен элемент
//! @param typeOfElem - один из предопределенных типов элемента (см. enum)
//! @param valueStart - нижний порог значени€ (int или double)
//! @param valueEnd - верхний порог значени€ (int или double)
//! @param curValue - стартовое значение
//! @param intFlag - true, если нужно отображать только целые значени€
//! @param countOfIndicator - число индикаторов, на которых будет отображено значение
//! @param signShowType - выбирает режим отображени€ знаков "+" и "-" перед числом
//! @return
CircleSliderIndicator::CircleSliderIndicator( int x, int y, int typeOfElem, double valueStart, double valueEnd, 
											  double curValue, bool intFlag, int countOfIndicator, int signShowType )
{
	if (typeOfElem == typeOfElem1)
	{
		xSliderStart = x;
		ySliderStart = y;

		pSlider = new CircleSlider( 32, x, y, -1 );

		xIndStart = xSliderStart + 32 / 2 - (countOfIndicator * 10) / 2;
		yIndStart = ySliderStart + 32;
		
		doubleValue1 = valueStart;
		doubleValue2 = valueEnd;

		if (intFlag)
			showAsDoubleFlag = false;
		else
			showAsDoubleFlag = true;

		this->typeOfElem = typeOfElem;		
		SetValue( curValue );
		
		doubleIndFlag = false;
		indSizeType = DigIndicator::indTypeSmall;

		sliderDrawType = 4;

		bColorInd = RGB( 0xf0, 0xf0, 0xf0 );
		fColorInd = RGB( 0x00, 0x00, 0x00 );

		this->countOfIndicator = countOfIndicator;
		this->signShowType = signShowType;
	}

	if (typeOfElem == typeOfElem2)
	{
		xSliderStart = x;
		ySliderStart = y;

		pSlider = new CircleSlider( 32, x, y, -1 );

		xIndStart = xSliderStart + 32 / 2 - (countOfIndicator * 10) / 2;
		yIndStart = ySliderStart + 32;
		
		doubleValue1 = valueStart;
		doubleValue2 = valueEnd;

		if (intFlag)
			showAsDoubleFlag = false;
		else
			showAsDoubleFlag = true;

		this->typeOfElem = typeOfElem;
		SetValue( curValue );
		
		doubleIndFlag = false;
		indSizeType = DigIndicator::indTypeSmall;

		sliderDrawType = 1;

		bColorInd = RGB( 0xf0, 0xf0, 0xf0 );
		fColorInd = RGB( 0x00, 0x00, 0x00 );

		this->countOfIndicator = countOfIndicator;
		this->signShowType = signShowType;
	}

	if (typeOfElem == typeOfElem3)
	{
		xSliderStart = x;
		ySliderStart = y;

		pSlider = new CircleSlider( 64, x, y, -1 );

		xIndStart = xSliderStart + 64 / 2 - (countOfIndicator * 20) / 2;
		yIndStart = ySliderStart + 64;
		
		doubleValue1 = valueStart;
		doubleValue2 = valueEnd;
	
		if (intFlag)
			showAsDoubleFlag = false;
		else
			showAsDoubleFlag = true;
		
		this->typeOfElem = typeOfElem;		
		SetValue( curValue );
		
		doubleIndFlag = false;
		indSizeType = DigIndicator::indTypeSmall;

		sliderDrawType = 3;

		bColorInd = RGB( 0xf0, 0xf0, 0xf0 );
		fColorInd = RGB( 0x00, 0xff, 0x00 );

		this->countOfIndicator = countOfIndicator;
		this->signShowType = signShowType;
	}

	if (typeOfElem == typeOfElem4)
	{
		xSliderStart = x;
		ySliderStart = y;

		pSlider = new CircleSlider( 32, x, y, -1 );

		xIndStart = xSliderStart + 32 / 2 - (countOfIndicator * 6) / 2;
		yIndStart = ySliderStart + 32;
		
		doubleValue1 = valueStart;
		doubleValue2 = valueEnd;

		if (intFlag)
			showAsDoubleFlag = false;
		else
			showAsDoubleFlag = true;

		this->typeOfElem = typeOfElem;
		SetValue( curValue );
		
		doubleIndFlag = false;
		indSizeType = DigIndicator::indTypeVerySmall;

		sliderDrawType = 4;

		bColorInd = RGB( 0xf0, 0xf0, 0xf0 );
		fColorInd = RGB( 0x00, 0x00, 0x00 );

		this->countOfIndicator = countOfIndicator;
		this->signShowType = signShowType;
	}

	if (typeOfElem == typeOfElem5)
	{
		xSliderStart = x;
		ySliderStart = y;

		pSlider = new CircleSlider( 64, x, y, -1 );

		xIndStart = xSliderStart + 64 / 2 - (countOfIndicator * 20) / 2;
		yIndStart = ySliderStart + 64;
		
		doubleValue1 = valueStart;
		doubleValue2 = valueEnd;

		if (intFlag)
			showAsDoubleFlag = false;
		else
			showAsDoubleFlag = true;

		this->typeOfElem = typeOfElem;		
		SetValue( curValue );
		
		doubleIndFlag = false;
		indSizeType = DigIndicator::indTypeNormal;

		sliderDrawType = 3;

		bColorInd = RGB( 0xf0, 0xf0, 0xf0 );
		fColorInd = RGB( 0x00, 0xff, 0x00 );

		this->countOfIndicator = countOfIndicator;
		this->signShowType = signShowType;
	}
}

//! @brief ƒеструктор
//! @return
CircleSliderIndicator::~CircleSliderIndicator( )
{
}

//! @brief ‘ункци€ преобразующа€ значение слайдра [0..1] в нужный формат
//! @param t - параметр [0..1]
//! @param emptyFlag - true, если стрелка указывает на пустую часть дуги и значение извлечь не удалось
//! @return значение
double CircleSliderIndicator::ConvertValue( double t, bool &emptyFlag )
{
	double	res;

	emptyFlag = false;

	if (typeOfElem == typeOfElem1 || typeOfElem == typeOfElem4)
	{
		double	t1 = (270 - 45) / 360.0;
		double	t2 = (270 + 45) / 360.0;
		double	res = 0;

		if (t >= t1 && t <= t2)
		{
			res = 0;
			emptyFlag = true;
		}
		else
		{
			if (t >= 0 && t <= t1) res = t + (1 - t2);
			if (t >= t2) res = t - t2;
			res = res / ((360 - 90) / 360.0);
		}

		t = res;
		t = 1 - t;
	}

	res = doubleValue1 + (doubleValue2 - doubleValue1) * t;

	double	eps = (doubleValue2 - doubleValue1) / 1000;	
	double	d1 = res - doubleValue1;
	double	d2 = res - doubleValue2;

	if (d1 >= -eps && d1 <= eps) res = doubleValue1;
	if (d2 >= -eps && d2 <= eps) res = doubleValue2;

	if (showAsDoubleFlag)
		return res;
	else
		return (int)res;
}

//! @brief ‘ункци€ получени€ текущего значени€
//! @return текущее значение в формате с плавающей точкой (даже int возвращаетс€ как double)
double CircleSliderIndicator::GetValue( )
{
	bool	emptyFlag;	
	
	return ConvertValue( pSlider->GetCurrentValue( ), emptyFlag );
}

//! @brief ‘ункци€ обрабатывает сообщение от мышки
//! @param nFlags - флаги нажатых клавиш
//! @param point - координаты точки курсора мыши
//! @return
void CircleSliderIndicator::OnMouseMove( UINT nFlags,CPoint point )
{
	pSlider->OnMouseMove( nFlags, point );
}

//! @brief ‘ункци€ обновлени€ (перерисовки) изображени€ на экране
//! @param pDC - контекст устройства
//! @return
void CircleSliderIndicator::OnPaint( CDC *pDC )
{
	bool	emptyFlag;	
	
	pSlider->SetDrawType( sliderDrawType );
	pSlider->Draw( pDC );

	DigIndicatorValue *pIndValue = new DigIndicatorValue( xIndStart, yIndStart, bColorInd, fColorInd, indSizeType );

	double	t = ConvertValue( pSlider->GetCurrentValue( ), emptyFlag );
	int		intT = (int)t;

	int		befPoint = (countOfIndicator - 1) / 2;
	int		aftPoint = (countOfIndicator - 1) / 2;

	if (showAsDoubleFlag)
		pIndValue->SetDoubleValue( t, befPoint, aftPoint, signShowType, true );
	else
		pIndValue->SetIntValue( intT, countOfIndicator, signShowType, true );

	if (doubleIndFlag)
		pIndValue->OnPaint( pDC, 2);
	else
		pIndValue->OnPaint( pDC, 1);

	if (pIndValue != NULL)
		delete pIndValue;
}

//! @brief ‘ункци€ установки текущего значени€
//! @param value - значение
//! @return
void CircleSliderIndicator::SetValue( double value )
{
	double	m_pi = 3.14159;
	bool	wholeCircleFlag;
	double	t;

	if (typeOfElem == typeOfElem1) wholeCircleFlag = false;
	if (typeOfElem == typeOfElem2) wholeCircleFlag = true;	
	if (typeOfElem == typeOfElem3) wholeCircleFlag = true;
	if (typeOfElem == typeOfElem4) wholeCircleFlag = false;
	if (typeOfElem == typeOfElem5) wholeCircleFlag = true;	

	if (wholeCircleFlag)
	{
		t = (value - doubleValue1) / (doubleValue2 - doubleValue1);
		pSlider->SetAngle( t * 2 * m_pi );
	}
	else
	{
		double	k = 1 - (value - doubleValue1) / (doubleValue2 - doubleValue1);
		double	t1 = (270 - 45) / 360.0;
		double	t2 = (270 + 45) / 360.0;
		double	len = k * ((360 - 90) / 360.0);

		if (len < 1 - t2)
			t = t2 + len;
		else
			t = len - (1 - t2);

		double	ta = t;
		double	tb = t;
		double	dt = 0.0001;
		double	va;
		double	vb;
		bool	emptyFlagA;
		bool	emptyFlagB;
		
		while( true )
		{
			pSlider->SetAngle( ta * 2 * m_pi );
			va = ConvertValue( pSlider->GetCurrentValue(), emptyFlagA );
			pSlider->SetAngle( tb * 2 * m_pi );
			vb = ConvertValue( pSlider->GetCurrentValue(), emptyFlagB );

			if (!emptyFlagA)
			{
				t = ta;
				break;
			}

			if (!emptyFlagB)
			{
				t = tb;
				break;
			}

			ta -= dt;
			tb += dt;
		}
		
		pSlider->SetAngle( t * 2 * m_pi );
	}
}

