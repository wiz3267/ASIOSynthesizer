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

	bool	redraw;	//элемент нужно перерисовать
	bool	textInputCaptured;
	DigIndicatorInput *digInput;
	
public:

	CircleSlider	*pSlider;

	//! @brief Функция преобразующая значение слайдра [0..1] в нужный формат
	//! @param t - параметр [0..1]
	//! @param emptyFlag - true, если стрелка указывает на пустую часть дуги и значение извлечь не удалось
	//! @return значение
	double ConvertValue( double t, bool &emptyFlag );

public:
	//! @brief Создать элемент с такими то координатми, типом элемента, начальным и конечным значением
	//! @param x, y - координаты места, в котором будет размещен элемент
	//! @param typeOfElem - один из предопределенных типов элемента (см. enum)
	//! @param valueStart - нижний порог значения (int или double)
	//! @param valueEnd - верхний порог значения (int или double)
	//! @param curValue - стартовое значение
	//! @param intFlag - true, если нужно отображать только целые значения
	//! @param countOfIndicator - число индикаторов, на которых будет отображено значение
	//! @param signShowType - выбирает режим отображения знаков "+" и "-" перед числом
	//! @return
	CircleSliderIndicator( int x, int y, int typeOfElem, double valueStart, double valueEnd, 
		                   double curValue, bool intFlag, int countOfIndicator, int signShowType );
	
	//! @brief Деструктор
	//! @return
	~CircleSliderIndicator( );

	//! @brief Функция получения текущего значения
	//! @return текущее значение в формате с плавающей точкой (даже int возвращается как double)
	double GetValue( );

	//! @brief Функция установки текущего значения
	//! @param value - значение
	//! @return
	void SetValue( double value );

	//! @brief Функция обрабатывает сообщение от мышки
	//! @param nFlags - флаги нажатых клавиш
	//! @param point - координаты точки курсора мыши
	//! @return
	void OnMouseMove( UINT nFlags,CPoint point );

	//! @brief Функция обрабатывает щелчок правой кнопки мыши
	//! @param nFlags - флаги нажатых клавиш
	//! @param point - координаты точки курсора мыши
	//! @return
	void OnRButtonUp( UINT nFlags,CPoint point );

	//! @brief Функция обрабатывает двойной щелчок левой кнопкой мыши
	//! @param nFlags - флаги нажатых клавиш
	//! @param point - координаты точки курсора мыши
	//! @return
	void OnLButtonDoubleClick( UINT nFlags,CPoint point );

	//! @brief Функция обновления (перерисовки) изображения на экране
	//! @param pDC - контекст устройства
	//! @return
	void OnPaint( CDC *pDC );

	//! @brief Фукнкция обновления (перерисоки) текстового поля ввода
	//! @param pDC - контекст устройства
	//! @return
	void OnPaintDigInput( CDC *pDC );

	//! @brief Функция стирания текстового поля ввода
	//! @param pDC - контекст устройства
	//! @return
	void OnClearArea( CDC *pDC );

	//! @brief Обработка нажатия на клавишу (нужна для текстового поля ввода)
	//! @param keyPressed - нажатая клавиша
	//! @return нажата ли клавиша ввода
	bool HandleKey( int keyPressed );

	//! @brief Проверка, захвачен ли фокус текстового ввода
	//! @return true - если фокус захвачен, иначе false
	bool IsTextInputCaptured( );
};

#endif