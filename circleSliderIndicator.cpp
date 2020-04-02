#include <stdafx.h>
#include "circleSliderIndicator.h"

//! @brief Создать элемент с такими то координатми, типом элемента, начальным и конечным значением
//! @param x, y - координаты места, в котором будет размещен элемент
//! @param typeOfElem - один из предопределенных типов элемента (см. enum)
//! @param valueStart - нижний порог значения (int или double)
//! @param valueEnd - верхний порог значения (int или double)
//! @param curValue - стартовое значение
//! @param intFlag - true, если нужно отображать только целые значения
//! @param countOfIndicator - число индикаторов, на которых будет отображено значение
//! @return
CircleSliderIndicator::CircleSliderIndicator( int x, int y, int typeOfElem, double valueStart, double valueEnd, 
											  double curValue, bool intFlag, int countOfIndicator )
{
	if (typeOfElem == typeOfElem1)
	{
		xSliderStart = x;
		ySliderStart = y;

		double	m_pi = 3.14159;
		double	k = ((curValue - valueStart) / (valueEnd - valueStart));
		double	t1 = (270 - 45) / 360.0;
		double	t2 = (270 + 45) / 360.0;
		double	len = k * ((360 - 90) / 360.0);
		double	t;

		if (len < 1 - t2)
			t = t2 + len;
		else
			t = len - (1 - t2);

		t = t * 2 * m_pi;

		pSlider = new CircleSlider( 32, x, y, t );

		xIndStart = xSliderStart + 32 / 2 - (countOfIndicator * 10) / 2;
		yIndStart = ySliderStart + 32;
		
		doubleValue1 = valueStart;
		doubleValue2 = valueEnd;
		
		doubleIndFlag = false;
		smallIndFlag = true;

		sliderDrawType = 4;

		bColorInd = RGB( 0xf0, 0xf0, 0xf0 );
		fColorInd = RGB( 0x00, 0x00, 0x00 );

		if (intFlag)
			showAsDoubleFlag = false;
		else
			showAsDoubleFlag = true;

		this->countOfIndicator = countOfIndicator;
		this->typeOfElem = typeOfElem;
	}

	if (typeOfElem == typeOfElem2)
	{
		xSliderStart = x;
		ySliderStart = y;

		double	m_pi = 3.14159;
		double	t = ((curValue - valueStart) / (valueEnd - valueStart)) * 2 * m_pi;

		pSlider = new CircleSlider( 32, x, y, t );

		xIndStart = xSliderStart + 32 / 2 - (countOfIndicator * 10) / 2;
		yIndStart = ySliderStart + 32;
		
		doubleValue1 = valueStart;
		doubleValue2 = valueEnd;
		
		doubleIndFlag = false;
		smallIndFlag = true;

		sliderDrawType = 1;

		bColorInd = RGB( 0xf0, 0xf0, 0xf0 );
		fColorInd = RGB( 0x00, 0x00, 0x00 );

		if (intFlag)
			showAsDoubleFlag = false;
		else
			showAsDoubleFlag = true;

		this->countOfIndicator = countOfIndicator;
		this->typeOfElem = typeOfElem;
	}

	if (typeOfElem == typeOfElem3)
	{
		xSliderStart = x;
		ySliderStart = y;

		double	m_pi = 3.14159;
		double	t = ((curValue - valueStart) / (valueEnd - valueStart)) * 2 * m_pi;

		pSlider = new CircleSlider( 64, x, y, t );

		xIndStart = xSliderStart + 64 / 2 - (countOfIndicator * 20) / 2;
		yIndStart = ySliderStart + 64;
		
		doubleValue1 = valueStart;
		doubleValue2 = valueEnd;
		
		doubleIndFlag = true;
		smallIndFlag = true;

		sliderDrawType = 3;

		bColorInd = RGB( 0xf0, 0xf0, 0xf0 );
		fColorInd = RGB( 0x00, 0xff, 0x00 );

		if (intFlag)
			showAsDoubleFlag = false;
		else
			showAsDoubleFlag = true;

		this->countOfIndicator = countOfIndicator;
		this->typeOfElem = typeOfElem;
	}
}

//! @brief Деструктор
//! @return
CircleSliderIndicator::~CircleSliderIndicator( )
{
}

//! @brief Функция преобразующая значение слайдра [0..1] в нужный формат
//! @param t - параметр [0..1]
//! @return значение
double CircleSliderIndicator::ConvertValue( double t )
{
	double	res;

	if (typeOfElem == typeOfElem1)
	{
		double	t1 = (270 - 45) / 360.0;
		double	t2 = (270 + 45) / 360.0;
		double	res = 0;

		if (t >= t1 && t <= t2)
			res = 0;
		else
		{
			if (t >= 0 && t <= t1) res = t + (1 - t2);
			if (t >= t2) res = t - t2;
			res = res / ((360 - 90) / 360.0);
		}

		t = res;
		t = 1-t;
	}

	res = doubleValue1 + (doubleValue2 - doubleValue1) * t;

	if (showAsDoubleFlag)
		return res;
	else
		return (int)res;
}

//! @brief Функция получения текущего значения
//! @return текущее значение в формате с плавающей точкой (даже int возвращается как double)
double CircleSliderIndicator::GetValue( )
{
	return ConvertValue( pSlider->GetCurrentValue( ) );
}

//! @brief Функция обрабатывает сообщение от мышки
//! @param nFlags - флаги нажатых клавиш
//! @param point - координаты точки курсора мыши
//! @return
void CircleSliderIndicator::OnMouseMove( UINT nFlags,CPoint point )
{
	pSlider->OnMouseMove( nFlags, point );
}

//! @brief Функция обновления (перерисовки) изображения на экране
//! @param pDC - контекст устройства
//! @return
void CircleSliderIndicator::OnPaint( CDC *pDC )
{
	pSlider->SetDrawType( sliderDrawType );
	pSlider->Draw( pDC );

	DigIndicatorValue *pIndValue = new DigIndicatorValue( xIndStart, yIndStart, bColorInd, fColorInd, smallIndFlag );

	double	t = ConvertValue( pSlider->GetCurrentValue( ) );
	int		intT = (int)t;

	int		befPoint = (countOfIndicator - 1) / 2;
	int		aftPoint = (countOfIndicator - 1) / 2;

	if (showAsDoubleFlag)
		pIndValue->SetDoubleValue( t, befPoint, aftPoint, DigIndicatorValue::signTypeShowAlways, true );
	else
		pIndValue->SetIntValue( intT, countOfIndicator, DigIndicatorValue::signTypeShowAlways, true );

	if (doubleIndFlag)
		pIndValue->OnPaint( pDC, 2);
	else
		pIndValue->OnPaint( pDC, 1);

	if (pIndValue != NULL)
		delete pIndValue;
}

