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

	//! @brief Функция проверяет используется ли малое изображение индикатора
	//! @return true - если используется малое изображение
	bool isSmallInd( );
};

#endif