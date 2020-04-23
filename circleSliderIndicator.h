#ifndef __CIRCLE_SLIDER_INDICATOR__
#define __CIRCLE_SLIDER_INDICATOR__

#include "circleSlider.h"
#include "digIndicator.h"
#include "digIndicatorValue.h"

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

	bool	redraw;	//элемент нужно перерисовать
	
public:

	CircleSlider	*pSlider;

	//! @brief ‘ункци€ преобразующа€ значение слайдра [0..1] в нужный формат
	//! @param t - параметр [0..1]
	//! @param emptyFlag - true, если стрелка указывает на пустую часть дуги и значение извлечь не удалось
	//! @return значение
	double ConvertValue( double t, bool &emptyFlag );

public:
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
	CircleSliderIndicator( int x, int y, int typeOfElem, double valueStart, double valueEnd, 
		                   double curValue, bool intFlag, int countOfIndicator, int signShowType );
	
	//! @brief ƒеструктор
	//! @return
	~CircleSliderIndicator( );

	//! @brief ‘ункци€ получени€ текущего значени€
	//! @return текущее значение в формате с плавающей точкой (даже int возвращаетс€ как double)
	double GetValue( );

	//! @brief ‘ункци€ установки текущего значени€
	//! @param value - значение
	//! @return
	void SetValue( double value );

	//! @brief ‘ункци€ обрабатывает сообщение от мышки
	//! @param nFlags - флаги нажатых клавиш
	//! @param point - координаты точки курсора мыши
	//! @return
	void OnMouseMove( UINT nFlags,CPoint point );

	//! @brief ‘ункци€ обновлени€ (перерисовки) изображени€ на экране
	//! @param pDC - контекст устройства
	//! @return
	void OnPaint( CDC *pDC );
};

#endif