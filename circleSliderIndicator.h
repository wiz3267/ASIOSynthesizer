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
private:	
	int		xSliderStart;
	int		ySliderStart;
	int		sliderDrawType;
	
	int		xIndStart;
	int		yIndStart;
	bool	smallIndFlag;
	bool	doubleIndFlag;

	double	doubleValue1;
	double	doubleValue2;

	long	bColorInd;
	long	fColorInd;

	bool	showAsDoubleFlag;

	int		befPoint;
	int		aftPoint;
	int		countOfIndicator;

	int		typeOfElem;
public:

	CircleSlider	*pSlider;

	//! @brief Функция преобразующая значение слайдра [0..1] в нужный формат
	//! @param t - параметр [0..1]
	//! @return значение
	double ConvertValue( double t );

public:
	//! @brief Создать элемент с такими то координатми, типом элемента, начальным и конечным значением
	//! @param x, y - координаты места, в котором будет размещен элемент
	//! @param typeOfElem - один из предопределенных типов элемента (см. enum)
	//! @param valueStart - нижний порог значения (int или double)
	//! @param valueEnd - верхний порог значения (int или double)
	//! @param curValue - стартовое значение
	//! @param intFlag - true, если нужно отображать только целые значения
	//! @param countOfIndicator - число индикаторов, на которых будет отображено значение
	//! @return
	CircleSliderIndicator( int x, int y, int typeOfElem, double valueStart, double valueEnd, 
		                   double curValue, bool intFlag, int countOfIndicator );
	
	//! @brief Деструктор
	//! @return
	~CircleSliderIndicator( );

	//! @brief Функция получения текущего значения
	//! @return текущее значение в формате с плавающей точкой (даже int возвращается как double)
	double GetValue( );

	//! @brief Функция обрабатывает сообщение от мышки
	//! @param nFlags - флаги нажатых клавиш
	//! @param point - координаты точки курсора мыши
	//! @return
	void OnMouseMove( UINT nFlags,CPoint point );

	//! @brief Функция обновления (перерисовки) изображения на экране
	//! @param pDC - контекст устройства
	//! @return
	void OnPaint( CDC *pDC );
};

#endif