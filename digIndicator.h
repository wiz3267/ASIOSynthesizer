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
	
	static long	*spriteBuffer1;		// буффер для verySmall индикаторов
	static long	*spriteBuffer2;		// буффер для small индикаторов
	static long	*spriteBuffer3;		// буффер для normal индикаторов
	long	*spriteBuffer;
	
	int		spriteBufferW;
	int		spriteBufferH;

	static char	**spriteTemp1;		// строковый массив для small индикаторов
	static char	**spriteTemp2;		// строковый массив для normal индикаторов
	char	**spriteTemp;
	static char	*smallSpriteTemp;	// строковый массив для verySmall индикаторов
	int		indSizeType;

public:
	DigIndicator( int x, int y, long bColor, long fColor, int indSizeType = 0 );
	~DigIndicator();

	//! @brief Функция освобождения памяти (должна вызываться один раз по зарершении программы)
	//! @return
	static void Free( );

	//! @brief Функция установки координат индикатора
	//! @param x, y - новые координаты индикатора
	//! @return
	void SetCoord( int x, int y );

	//! @brief Функция установки цвета индикатора и цвета фона
	//! @param bColor - цвет фона
	//! @param fColor - цвет изображения индикатора
	//! @return
	void SetColor( long bColor, long fColor );

	//! @brief Функция отображения ASCII-символа в буффер индикатора если он маленький
	//! @param c - код символа
	//! @param needPoint - нужна ли точка
	//! @return
	void DrawBufferSmall( char c, bool needPoint = false );

	//! @brief Функция отображения ASCII-символа в буффер индикатора
	//! @param c - код символа
	//! @param needPoint - нужна ли точка
	//! @return
	void DrawBuffer( char c, bool needPoint = false );
	
	//! @brief Функция обновления (перерисовки) изображения на экране
	//! @param pDC - контекст устройства
	//! @param k = 1, если 1x1 пиксель
	//! @param k = 2, если 2x2 пикселя
	//! @return
	void OnPaint(CDC *pDC, int k);

	//! @brief Функция обновления (перерисовки) маленькой дробной точки на экране
	//! @param pDC - контекст устройства
	//! @param k = 1, если 1x1 пиксель
	//! @param k = 2, если 2x2 пикселя
	//! @return
	void OnPaintVerySmallPoint(CDC *pDC, int k);

	//! @brief Функция возвращает размер маленькой (verySmall) дробной точки на экране
	//! @return размер дробной точки
	int GetVerySmallPointSize( );

	//! @brief Функция возвращает тип размера индикатора (порядок малости)
	//! @return тип размера индикатора
	int GetIndSizeType( );
};

#endif