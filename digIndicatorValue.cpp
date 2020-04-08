#include <stdafx.h>
#include "digIndicatorValue.h"
#include "digIndicator.h"

DigIndicator **DigIndicatorValue::digIndList1 = NULL;
DigIndicator **DigIndicatorValue::digIndList2 = NULL;
DigIndicator **DigIndicatorValue::digIndList3 = NULL;

DigIndicatorValue::DigIndicatorValue( int x, int y, long bColor, long fColor, int indSizeType )
{
	this->xStart = x;
	this->yStart = y;
	this->bColor = bColor;
	this->fColor = fColor;
	this->indSizeType = indSizeType;

	if (indSizeType == DigIndicator::indTypeVerySmall)
	{
		if (digIndList1 == NULL)
		{
			digIndList1 = new DigIndicator* [maxIndCount];

			for( int i = 0; i < maxIndCount; i++ )
			{
				digIndList1[i] = new DigIndicator( -1, -1, -1, -1, indSizeType );
			}
		}
	}
	if (indSizeType == DigIndicator::indTypeSmall)
	{
		if (digIndList2 == NULL)
		{
			digIndList2 = new DigIndicator* [maxIndCount];

			for( int i = 0; i < maxIndCount; i++ )
			{
				digIndList2[i] = new DigIndicator( -1, -1, -1, -1, indSizeType );
			}
		}
	}
	if (indSizeType == DigIndicator::indTypeNormal)
	{
		if (digIndList3 == NULL)
		{
			digIndList3 = new DigIndicator* [maxIndCount];

			for( int i = 0; i < maxIndCount; i++ )
			{
				digIndList3[i] = new DigIndicator( -1, -1, -1, -1, indSizeType );
			}
		}
	}
}

DigIndicatorValue::~DigIndicatorValue( )
{
}

//! @brief Функция освобождения памяти (должна вызываться один раз при завершении работы программы)
//! @return
void DigIndicatorValue::Free( )
{
	// удаляем массив verySmall индикаторов (если он существует)
	if (digIndList1 != NULL)
	{
		for( int i = 0; i < maxIndCount; i++ )
		{
			if (digIndList1[i] != NULL)
			{
				delete digIndList1[i];
				digIndList1[i] = NULL;
			}
		}
		delete [] digIndList1;
		digIndList1 = NULL;
	}

	// удаляем массив small индикаторов (если он существует)
	if (digIndList2 != NULL)
	{
		for( int i = 0; i < maxIndCount; i++ )
		{
			if (digIndList2[i] != NULL)
			{
				delete digIndList2[i];
				digIndList2[i] = NULL;
			}
		}
		delete [] digIndList2;
		digIndList2 = NULL;
	}

	// удаляем массив normal индикаторов (если он существует)
	if (digIndList3 != NULL)
	{
		for( int i = 0; i < maxIndCount; i++ )
		{
			if (digIndList3[i] != NULL)
			{
				delete digIndList3[i];
				digIndList3[i] = NULL;
			}
		}
		delete [] digIndList3;
		digIndList3 = NULL;
	}
}

//! @brief Функция задает значение панели индикаторов с плавающей точкой
//! @param value - значение в формате с плавающей точкой
//! @param befPoint - количество знаков до дробной точки
//! @param aftPoint - количество знаков после дробной точки
//! @param signShowType - режим показа знака (см. enum выше)
//! @param fixNumberChars - сохранять постоянное число знаков
//! @return
void DigIndicatorValue::SetDoubleValue( double value, int befPoint, int aftPoint, int signShowType, bool fixNumberChars )
{
	this->value = value;
	this->drawAsIntFlag = false;
	this->befPoint = befPoint;
	this->aftPoint = aftPoint;
	this->signShowType = signShowType;
	this->fixNumberChars = fixNumberChars;
}

//! @brief Функция задает значение панели индикаторов для целого числа
//! @param value - целочисленое значение
//! @param nDigits - количество десятичных разрядов
//! @param signShowType - режим показа знака (см. enum выше)
//! @param fixNumberChars - сохранять постоянное число знаков
//! @return
void DigIndicatorValue::SetIntValue( int value, int nDigits, int signShowType, bool fixNumberChars )
{
	this->value = value;
	this->drawAsIntFlag = true;
	this->nDigits = nDigits;
	this->signShowType = signShowType;
	this->fixNumberChars = fixNumberChars;
}

//! @brief Функция генерации ASCII-строки для числа типа int
//! @return строка
char *DigIndicatorValue::GenerateStringByInt( )
{
	int		iValue = (int)value;
	char	tmpFormat[150];
	char	tmpStr1[150];
	char	tmpStr2[150];
	char	*str;
	int		len;

	if (iValue < 0) iValue = -iValue;

	strcpy( tmpFormat, "%0Nd" );
	tmpFormat[2] = '0' + nDigits;

	sprintf( tmpStr1, tmpFormat, iValue );

	if (signShowType == signTypeNotShow)
	{
		strcpy( tmpStr2, tmpStr1 );
	}
	else
	{
		if (value < 0)
			sprintf( tmpStr2, "-%s", tmpStr1 );
		else
		{
			if (signShowType == signTypeShowAlways)
				sprintf( tmpStr2, "+%s", tmpStr1 );
			else
			{
				if (!fixNumberChars)
					strcpy( tmpStr2, tmpStr1 );
				else
					sprintf( tmpStr2, " %s", tmpStr1 );
			}
		}
	}

	len = strlen( tmpStr2 );
	str = new char [len + 1];
	strcpy( str, tmpStr2 );

	return str;
}
	
//! @brief Функция генерации ASCII-строки для чилса типа double
//! @return строка
char *DigIndicatorValue::GenerateStringByDouble( )
{
	double	pval;
	int		iv1;
	int		iv2;
	char	tmpFormat1[150];
	char	tmpFormat2[150];
	char	tmp1[150];
	char	tmp2[150];
	char	tmp3[150];
	char	tmp4[150];
	char	*str;
	int		p = 1;
	int		i;
	int		len;

	pval = value;
	if (pval < 0) pval = -pval;

	strcpy( tmpFormat1, "%0Nd" );
	strcpy( tmpFormat2, "%0Nd" );

	tmpFormat1[2] = '0' + befPoint;
	tmpFormat2[2] = '0' + aftPoint;

	iv1 = (int)pval;
	sprintf( tmp1, tmpFormat1, iv1 );
		
	for( i = 0; i < aftPoint; i++ )
		p *= 10;

	iv2 = ((int)(pval * p)) % p;
	sprintf( tmp2, tmpFormat2, iv2 );

	sprintf( tmp3, "%s.%s", tmp1, tmp2 );


	if (signShowType == signTypeNotShow)
	{
		strcpy( tmp4, tmp3 );
	}
	else
	{
		if (value < 0)
			sprintf( tmp4, "-%s", tmp3 );
		else
		{
			if (signShowType == signTypeShowAlways)
				sprintf( tmp4, "+%s", tmp3 );
			else
			{
				if (!fixNumberChars)
					strcpy( tmp4, tmp3 );
				else
					sprintf( tmp4, " %s", tmp3 );
			}
		}
	}

	len = strlen( tmp4 );
	str = new char [len + 1];
	strcpy( str, tmp4 );

	return str;
}

//! @brief Функция обновления (перерисовки) изображения на экране
//! @param pDC - контекст устройства
//! @param k = 1, если 1x1 пиксель
//! @param k = 2, если 2x2 пикселя
//! @return
void DigIndicatorValue::OnPaint(CDC *pDC, int k)
{
	char	*str;	
	int		len;
	int		i;
	
	if (drawAsIntFlag) 
	{
		str = GenerateStringByInt();
		len = strlen( str );
	}
	else
	{
		str = GenerateStringByDouble();
		len = strlen( str ) - 1;
	}

	int				xSize;

	if (indSizeType == DigIndicator::indTypeVerySmall) xSize = 5;
	if (indSizeType == DigIndicator::indTypeSmall) xSize = 8;
	if (indSizeType == DigIndicator::indTypeNormal) xSize = 24;

	if (k == 2) xSize += xSize;

//	DigIndicator **digIndList = new DigIndicator* [len];
	
//	for( i = 0; i < len; i++ )
//	{
//		digIndList[i] = new DigIndicator( xStart + (xSize + 1) * i, yStart, bColor, fColor, indSizeType );
//	}

	DigIndicator **digIndList = NULL;

	if (indSizeType == DigIndicator::indTypeVerySmall) digIndList = digIndList1;
	if (indSizeType == DigIndicator::indTypeSmall) digIndList = digIndList2;	
	if (indSizeType == DigIndicator::indTypeNormal) digIndList = digIndList3;

	for( i = 0; i < len; i++ )
	{
		digIndList[i]->SetCoord( xStart + (xSize + 1) * i, yStart );
		digIndList[i]->SetColor( bColor, fColor );
	}

	int	 j = 0;
	
	for( i = 0; i < len; i++ )
	{
		if (j + 1 < len + 1 && str[j + 1] == '.')
		{
			digIndList[i]->DrawBuffer( str[j], true );	
			j++;
		}
		else
		{
			digIndList[i]->DrawBuffer( str[j] );
		}
		digIndList[i]->OnPaint( pDC, k );
		j++;
	}

//	if (digIndList != NULL)
//	{
//		for( i = 0; i < len; i++ )
//		{
//			if (digIndList[i] != NULL)
//			{
//				delete digIndList[i];
//				digIndList[i] = NULL;
//			}
//		}
//		delete [] digIndList;
//		digIndList = NULL;
//	}

	if (str != NULL)
	{
		delete [] str;
		str = NULL;
	}
}



