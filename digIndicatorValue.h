#ifndef __DIG_INDICATOR_VALUE__
#define __DIG_INDICATOR_VALUE__

#include "digIndicator.h"

class DigIndicatorValue
{
public:	
	// режим показа знака:
	// 1) показывать знак всегда
	// 2) показывать только если минус
	// 3) не показывать вообще
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
	static DigIndicator **digIndList1;	// массив verySmall индикаторов maxIndCount позиций
	static DigIndicator **digIndList2;	// массив small индикаторов maxIndCount позиций
	static DigIndicator **digIndList3;	// массив normal индикаторов maxIndCount позиций

	//! @brief Функция генерации ASCII-строки для числа типа int
	//! @return строка
	char *GenerateStringByInt( );
	
	//! @brief Функция генерации ASCII-строки для чилса типа double
	//! @return строка
	char *GenerateStringByDouble( );

public:
	DigIndicatorValue( int x, int y, long bColor, long fColor, int indSizeType );
	~DigIndicatorValue( );

	//! @brief Функция освобождения памяти (должна вызываться один раз при завершении работы программы)
	//! @return
	static void Free( );

	//! @brief Функция задает значение панели индикаторов с плавающей точкой
	//! @param value - значение в формате с плавающей точкой
	//! @param befPoint - количество знаков до дробной точки
	//! @param aftPoint - количество знаков после дробной точки
	//! @param signShowType - режим показа знака (см. enum выше)
	//! @param fixNumberChars - сохранять постоянное число знаков
	//! @return
	void SetDoubleValue( double value, int befPoint, int aftPoint, int signShowType, bool fixNumberChars );

	//! @brief Функция задает значение панели индикаторов для целого числа
	//! @param value - целочисленое значение
	//! @param nDigits - количество десятичных разрядов
	//! @param signShowType - режим показа знака (см. enum выше)
	//! @param fixNumberChars - сохранять постоянное число знаков
	//! @return
	void SetIntValue( int value, int nDigits, int signShowType, bool fixNumberChars );

	//! @brief Функция обновления (перерисовки) изображения на экране
	//! @param pDC - контекст устройства
	//! @param k = 1, если 1x1 пиксель
	//! @param k = 2, если 2x2 пикселя
	//! @return
	void OnPaint(CDC *pDC, int k);
};

#endif