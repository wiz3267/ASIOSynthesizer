#include <stdafx.h>
#include <math.h>
#include "digIndicator.h"

char *DigIndicator::smallSpriteTemp = NULL;
char **DigIndicator::spriteTemp1 = NULL;
char **DigIndicator::spriteTemp2 = NULL;
long *DigIndicator::spriteBuffer1 = NULL;
long *DigIndicator::spriteBuffer2 = NULL;
long *DigIndicator::spriteBuffer3 = NULL;

DigIndicator::DigIndicator( int x, int y, long bColor, long fColor, int indSizeType )
{
	xStart = x;
	yStart = y;
	this->bColor = bColor;
	this->fColor = fColor;

	int		bufLen;

	if (indSizeType == indTypeNormal)
	{
		spriteBufferW = 24;
		spriteBufferH = 32;

		bufLen = spriteBufferW * spriteBufferH;

		if (spriteBuffer3 == NULL) 
			spriteBuffer3 = new long [spriteBufferW * spriteBufferH];

		spriteBuffer = spriteBuffer3;

		for( int i = 0; i < bufLen; i++ )
			spriteBuffer[i] = 0;

		if (spriteTemp2 == NULL)
		{
			spriteTemp2 = new char* [spriteBufferH];

			for( i = 0; i < spriteBufferH; i++ )
				spriteTemp2[i] = new char [spriteBufferW + 1];

			char	*s00 = "000022222222222222220000";
			char	*s01 = "000222222222222222222000";
			char	*s02 = "000022222222222222220000";
			char	*s03 = "003000000000000000000100";
			char	*s04 = "003300000000000000001100";
			char	*s05 = "003330000009000000011100";
			char	*s06 = "003330000099900000011100";
			char	*s07 = "003330000099900000011100";	
			char	*s08 = "003330000099900000011100";	
			char	*s09 = "003330000099900000011100";
			char	*s10 = "003330000099900000011100";
			char	*s11 = "003300000099900000001100";
			char	*s12 = "003000000099900000000100";
			char	*s13 = "000077777777777777770000";
			char	*s14 = "000777777777777777777000";
			char	*s15 = "000077777777777777770000";
			char	*s16 = "004000000099900000000600";
			char	*s17 = "004400000099900000006600";
			char	*s18 = "004440000099900000066600";
			char	*s19 = "004440000099900000066600";
			char	*s20 = "004440000099900000066600";
			char	*s21 = "004440000099900000066600";
			char	*s22 = "004440000099900000066600";
			char	*s23 = "004440000009000000066600";
			char	*s24 = "004440000000000000066600";
			char	*s25 = "004400000000000000006600";
			char	*s26 = "004000000000000000000600";
			char	*s27 = "000055555555555555550000";
			char	*s28 = "000555555555555555555088";
			char	*s29 = "000055555555555555550088";
			char	*s30 = "000000000000000000000000";
			char	*s31 = "000000000000000000000000";

			strcpy( spriteTemp2[0], s00 );
			strcpy( spriteTemp2[1], s01 );
			strcpy( spriteTemp2[2], s02 );
			strcpy( spriteTemp2[3], s03 );
			strcpy( spriteTemp2[4], s04 );
			strcpy( spriteTemp2[5], s05 );
			strcpy( spriteTemp2[6], s06 );
			strcpy( spriteTemp2[7], s07 );

			strcpy( spriteTemp2[8], s08 );
			strcpy( spriteTemp2[9], s09 );
			strcpy( spriteTemp2[10], s10 );
			strcpy( spriteTemp2[11], s11 );
			strcpy( spriteTemp2[12], s12 );
			strcpy( spriteTemp2[13], s13 );
			strcpy( spriteTemp2[14], s14 );
			strcpy( spriteTemp2[15], s15 );

			strcpy( spriteTemp2[16], s16 );
			strcpy( spriteTemp2[17], s17 );
			strcpy( spriteTemp2[18], s18 );
			strcpy( spriteTemp2[19], s19 );
			strcpy( spriteTemp2[20], s20 );
			strcpy( spriteTemp2[21], s21 );
			strcpy( spriteTemp2[22], s22 );
			strcpy( spriteTemp2[23], s23 );

			strcpy( spriteTemp2[24], s24 );
			strcpy( spriteTemp2[25], s25 );
			strcpy( spriteTemp2[26], s26 );
			strcpy( spriteTemp2[27], s27 );
			strcpy( spriteTemp2[28], s28 );
			strcpy( spriteTemp2[29], s29 );
			strcpy( spriteTemp2[30], s30 );
			strcpy( spriteTemp2[31], s31 );
		}
		spriteTemp = spriteTemp2;

		this->indSizeType = indTypeNormal;
	}
	
	if (indSizeType == indTypeSmall)
	{
		spriteBufferW = 9;
		spriteBufferH = 10;
		
		if (spriteBuffer2 == NULL)
			spriteBuffer2 = new long [spriteBufferW * spriteBufferH];

		spriteBuffer = spriteBuffer2;

		bufLen = spriteBufferW * spriteBufferH;

		for( int i = 0; i < bufLen; i++ )
			spriteBuffer[i] = 0;

		if (spriteTemp1 == NULL)
		{
			spriteTemp1 = new char* [spriteBufferH];

			for( i = 0; i < spriteBufferH; i++ )
				spriteTemp1[i] = new char [spriteBufferW + 1];


			char	*s00 = "002222200";
			char	*s01 = "030000010";
			char	*s02 = "030090010";
			char	*s03 = "030090010";
			char	*s04 = "007777700";		
			char	*s05 = "040090060";
			char	*s06 = "040090060";
			char	*s07 = "040000060";
			char	*s08 = "005555500";
			char	*s09 = "000000008";

			strcpy( spriteTemp1[0], s00 );
			strcpy( spriteTemp1[1], s01 );
			strcpy( spriteTemp1[2], s02 );
			strcpy( spriteTemp1[3], s03 );
			strcpy( spriteTemp1[4], s04 );
			strcpy( spriteTemp1[5], s05 );
			strcpy( spriteTemp1[6], s06 );
			strcpy( spriteTemp1[7], s07 );
			strcpy( spriteTemp1[8], s08 );
			strcpy( spriteTemp1[9], s09 );
		}
		spriteTemp = spriteTemp1;
		this->indSizeType = indTypeSmall;
	}

	if (indSizeType == indTypeVerySmall)
	{
		int		nChars = 14;

		spriteBufferW = 5;
		spriteBufferH = 7;
		
		if (spriteBuffer1 == NULL)
			spriteBuffer1 = new long [spriteBufferW * spriteBufferH];

		spriteBuffer = spriteBuffer1;

		bufLen = spriteBufferW * spriteBufferH;

		for( int i = 0; i < bufLen; i++ )
			spriteBuffer[i] = 0;

		if (smallSpriteTemp == NULL)
		{
			char	*s00 = "00000";
			char	*s01 = "01111";
			char	*s02 = "01001";
			char	*s03 = "01001";
			char	*s04 = "01001";
			char	*s05 = "01111";
			char	*s06 = "00000";		
	
			char	*s10 = "00000";
			char	*s11 = "00001";
			char	*s12 = "00001";
			char	*s13 = "00001";
			char	*s14 = "00001";
			char	*s15 = "00001";
			char	*s16 = "00000";		
	
			char	*s20 = "00000";
			char	*s21 = "01111";
			char	*s22 = "00001";
			char	*s23 = "01111";
			char	*s24 = "01000";
			char	*s25 = "01111";
			char	*s26 = "00000";		
	
			char	*s30 = "00000";
			char	*s31 = "01111";
			char	*s32 = "00001";
			char	*s33 = "01111";
			char	*s34 = "00001";
			char	*s35 = "01111";
			char	*s36 = "00000";		
	
			char	*s40 = "00000";
			char	*s41 = "01001";
			char	*s42 = "01001";
			char	*s43 = "01111";
			char	*s44 = "00001";
			char	*s45 = "00001";
			char	*s46 = "00000";		

			char	*s50 = "00000";
			char	*s51 = "01111";
			char	*s52 = "01000";
			char	*s53 = "01111";
			char	*s54 = "00001";
			char	*s55 = "01111";
			char	*s56 = "00000";		

			char	*s60 = "00000";
			char	*s61 = "01111";
			char	*s62 = "01000";
			char	*s63 = "01111";
			char	*s64 = "01001";
			char	*s65 = "01111";
			char	*s66 = "00000";		

			char	*s70 = "00000";
			char	*s71 = "01111";
			char	*s72 = "00001";
			char	*s73 = "00001";
			char	*s74 = "00001";
			char	*s75 = "00001";
			char	*s76 = "00000";		

			char	*s80 = "00000";
			char	*s81 = "01111";
			char	*s82 = "01001";
			char	*s83 = "01111";
			char	*s84 = "01001";
			char	*s85 = "01111";
			char	*s86 = "00000";		

			char	*s90 = "00000";
			char	*s91 = "01111";
			char	*s92 = "01001";
			char	*s93 = "01111";
			char	*s94 = "00001";
			char	*s95 = "01111";
			char	*s96 = "00000";		

			char	*sP0 = "00000";
			char	*sP1 = "00100";
			char	*sP2 = "00100";
			char	*sP3 = "01110";
			char	*sP4 = "00100";
			char	*sP5 = "00100";
			char	*sP6 = "00000";		

			char	*sM0 = "00000";
			char	*sM1 = "00000";
			char	*sM2 = "00000";
			char	*sM3 = "01111";
			char	*sM4 = "00000";
			char	*sM5 = "00000";
			char	*sM6 = "00000";
		
			char	*sE0 = "00000";
			char	*sE1 = "00000";
			char	*sE2 = "00000";
			char	*sE3 = "00000";
			char	*sE4 = "00000";
			char	*sE5 = "00000";
			char	*sE6 = "00000";	

			char	*sR0 = "00000";
			char	*sR1 = "00000";
			char	*sR2 = "00000";
			char	*sR3 = "00000";
			char	*sR4 = "00000";
			char	*sR5 = "01100";
			char	*sR6 = "01100";	

			smallSpriteTemp = new char [nChars * spriteBufferW * spriteBufferH];
			char *pdat = smallSpriteTemp;

			for( int k = 0; k < nChars; k++ )
			{
				for( int gy = 0; gy < spriteBufferH; gy++ )
				{
					char	str[7];

					if (k == 0 && gy == 0) strcpy( str, s00 );
					if (k == 0 && gy == 1) strcpy( str, s01 );
					if (k == 0 && gy == 2) strcpy( str, s02 );
					if (k == 0 && gy == 3) strcpy( str, s03 );
					if (k == 0 && gy == 4) strcpy( str, s04 );
					if (k == 0 && gy == 5) strcpy( str, s05 );
					if (k == 0 && gy == 6) strcpy( str, s06 );

					if (k == 1 && gy == 0) strcpy( str, s10 );
					if (k == 1 && gy == 1) strcpy( str, s11 );
					if (k == 1 && gy == 2) strcpy( str, s12 );
					if (k == 1 && gy == 3) strcpy( str, s13 );
					if (k == 1 && gy == 4) strcpy( str, s14 );
					if (k == 1 && gy == 5) strcpy( str, s15 );
					if (k == 1 && gy == 6) strcpy( str, s16 );
			
					if (k == 2 && gy == 0) strcpy( str, s20 );
					if (k == 2 && gy == 1) strcpy( str, s21 );
					if (k == 2 && gy == 2) strcpy( str, s22 );
					if (k == 2 && gy == 3) strcpy( str, s23 );
					if (k == 2 && gy == 4) strcpy( str, s24 );
					if (k == 2 && gy == 5) strcpy( str, s25 );
					if (k == 2 && gy == 6) strcpy( str, s26 );
				 
					if (k == 3 && gy == 0) strcpy( str, s30 );
					if (k == 3 && gy == 1) strcpy( str, s31 );
					if (k == 3 && gy == 2) strcpy( str, s32 );
					if (k == 3 && gy == 3) strcpy( str, s33 );
					if (k == 3 && gy == 4) strcpy( str, s34 );
					if (k == 3 && gy == 5) strcpy( str, s35 );
					if (k == 3 && gy == 6) strcpy( str, s36 );
			
					if (k == 4 && gy == 0) strcpy( str, s40 );
					if (k == 4 && gy == 1) strcpy( str, s41 );
					if (k == 4 && gy == 2) strcpy( str, s42 );
					if (k == 4 && gy == 3) strcpy( str, s43 );
					if (k == 4 && gy == 4) strcpy( str, s44 );
					if (k == 4 && gy == 5) strcpy( str, s45 );
					if (k == 4 && gy == 6) strcpy( str, s46 );
			 
					if (k == 5 && gy == 0) strcpy( str, s50 );
					if (k == 5 && gy == 1) strcpy( str, s51 );
					if (k == 5 && gy == 2) strcpy( str, s52 );
					if (k == 5 && gy == 3) strcpy( str, s53 );
					if (k == 5 && gy == 4) strcpy( str, s54 );
					if (k == 5 && gy == 5) strcpy( str, s55 );
					if (k == 5 && gy == 6) strcpy( str, s56 );
			
					if (k == 6 && gy == 0) strcpy( str, s60 );
					if (k == 6 && gy == 1) strcpy( str, s61 );
					if (k == 6 && gy == 2) strcpy( str, s62 );
					if (k == 6 && gy == 3) strcpy( str, s63 );
					if (k == 6 && gy == 4) strcpy( str, s64 );
					if (k == 6 && gy == 5) strcpy( str, s65 );
					if (k == 6 && gy == 6) strcpy( str, s66 );

					if (k == 7 && gy == 0) strcpy( str, s70 );
					if (k == 7 && gy == 1) strcpy( str, s71 );
					if (k == 7 && gy == 2) strcpy( str, s72 );
					if (k == 7 && gy == 3) strcpy( str, s73 );
					if (k == 7 && gy == 4) strcpy( str, s74 );
					if (k == 7 && gy == 5) strcpy( str, s75 );
					if (k == 7 && gy == 6) strcpy( str, s76 );

					if (k == 8 && gy == 0) strcpy( str, s80 );
					if (k == 8 && gy == 1) strcpy( str, s81 );
					if (k == 8 && gy == 2) strcpy( str, s82 );
					if (k == 8 && gy == 3) strcpy( str, s83 );
					if (k == 8 && gy == 4) strcpy( str, s84 );
					if (k == 8 && gy == 5) strcpy( str, s85 );
					if (k == 8 && gy == 6) strcpy( str, s86 );

					if (k == 9 && gy == 0) strcpy( str, s90 );
					if (k == 9 && gy == 1) strcpy( str, s91 );
					if (k == 9 && gy == 2) strcpy( str, s92 );
					if (k == 9 && gy == 3) strcpy( str, s93 );
					if (k == 9 && gy == 4) strcpy( str, s94 );
					if (k == 9 && gy == 5) strcpy( str, s95 );
					if (k == 9 && gy == 6) strcpy( str, s96 );

					if (k == 10 && gy == 0) strcpy( str, sP0 );
					if (k == 10 && gy == 1) strcpy( str, sP1 );
					if (k == 10 && gy == 2) strcpy( str, sP2 );
					if (k == 10 && gy == 3) strcpy( str, sP3 );
					if (k == 10 && gy == 4) strcpy( str, sP4 );
					if (k == 10 && gy == 5) strcpy( str, sP5 );
					if (k == 10 && gy == 6) strcpy( str, sP6 );

					if (k == 11 && gy == 0) strcpy( str, sM0 );
					if (k == 11 && gy == 1) strcpy( str, sM1 );
					if (k == 11 && gy == 2) strcpy( str, sM2 );
					if (k == 11 && gy == 3) strcpy( str, sM3 );
					if (k == 11 && gy == 4) strcpy( str, sM4 );
					if (k == 11 && gy == 5) strcpy( str, sM5 );
					if (k == 11 && gy == 6) strcpy( str, sM6 );

					if (k == 12 && gy == 0) strcpy( str, sE0 );
					if (k == 12 && gy == 1) strcpy( str, sE1 );
					if (k == 12 && gy == 2) strcpy( str, sE2 );
					if (k == 12 && gy == 3) strcpy( str, sE3 );
					if (k == 12 && gy == 4) strcpy( str, sE4 );
					if (k == 12 && gy == 5) strcpy( str, sE5 );
					if (k == 12 && gy == 6) strcpy( str, sE6 );

					if (k == 13 && gy == 0) strcpy( str, sR0 );
					if (k == 13 && gy == 1) strcpy( str, sR1 );
					if (k == 13 && gy == 2) strcpy( str, sR2 );
					if (k == 13 && gy == 3) strcpy( str, sR3 );
					if (k == 13 && gy == 4) strcpy( str, sR4 );
					if (k == 13 && gy == 5) strcpy( str, sR5 );
					if (k == 13 && gy == 6) strcpy( str, sR6 );

					for( int gx = 0; gx < spriteBufferW; gx++ )
					{
						if (str[gx] == '0') *pdat = 0;
						if (str[gx] == '1') *pdat = 1;
						pdat++;
					}
				}
			}
		}
		this->indSizeType = indTypeVerySmall;	
	}
}

DigIndicator::~DigIndicator()
{
}

//! @brief Функция освобождения памяти (должна вызываться один раз по зарершении программы)
//! @return
void DigIndicator::Free( )
{
	if (spriteBuffer1 != NULL)
	{
		delete [] spriteBuffer1;
		spriteBuffer1 = NULL;
	}

	if (spriteBuffer2 != NULL)
	{
		delete [] spriteBuffer2;
		spriteBuffer2 = NULL;
	}

	if (spriteBuffer3 != NULL)
	{
		delete [] spriteBuffer3;
		spriteBuffer3 = NULL;
	}
	
	if (spriteTemp1 != NULL)
	{
		for( int i = 0; i < 10; i++ )
		{
			if (spriteTemp1[i] != NULL)
			{
				delete [] spriteTemp1[i];
				spriteTemp1[i] = NULL;
			}
		}
		delete [] spriteTemp1;
		spriteTemp1 = NULL;
	}

	if (spriteTemp2 != NULL)
	{
		for( int i = 0; i < 32; i++ )
		{
			if (spriteTemp2[i] != NULL)
			{
				delete [] spriteTemp2[i];
				spriteTemp2[i] = NULL;
			}
		}
		delete [] spriteTemp2;
		spriteTemp2 = NULL;
	}

	if (smallSpriteTemp != NULL)
	{
		delete [] smallSpriteTemp;
		smallSpriteTemp = NULL;
	}
}

//! @brief Функция установки координат индикатора
//! @param x, y - новые координаты индикатора
//! @return
void DigIndicator::SetCoord( int x, int y )
{
	xStart = x;
	yStart = y;
}

//! @brief Функция установки цвета индикатора и цвета фона
//! @param bColor - цвет фона
//! @param fColor - цвет изображения индикатора
//! @return
void DigIndicator::SetColor( long bColor, long fColor )
{
	this->bColor = bColor;
	this->fColor = fColor;
}

//! @brief Функция возвращает тип размера индикатора (порядок малости)
//! @return тип размера индикатора
int DigIndicator::GetIndSizeType( )
{
	return indSizeType;
}

//! @brief Функция отображения ASCII-символа в буффер индикатора если он маленький
//! @param c - код символа
//! @param needPoint - нужна ли точка
//! @return
void DigIndicator::DrawBufferSmall( char c, bool needPoint )
{
	int		charOffset;

	if (c == '+') charOffset = 10;
	if (c == '-') charOffset = 11;
	if (c == ' ') charOffset = 12;
	if (c == '.') charOffset = 13;
	if (c >= '0' && c <= '9') charOffset = c - '0';

	char	*pSource = smallSpriteTemp + charOffset * spriteBufferW * spriteBufferH;
	long	*pDest = spriteBuffer;
	int		gx, gy;

	for( gy = 0; gy < spriteBufferH; gy++ )
	{
		for( gx = 0; gx < spriteBufferW; gx++ )
		{
			long	color = bColor;

			if ((*pSource) == 1)
				color = fColor;
		
			if (needPoint && gx == spriteBufferW - 1 && gy == spriteBufferH - 1)
				color = fColor;

			pSource++;
			*pDest++ = color;		
		}
	}
}

//! @brief Функция отображения ASCII-символа в буффер индикатора
//! @param c - код символа
//! @param needPoint - нужна ли точка
//! @return
void DigIndicator::DrawBuffer( char c, bool needPoint )
{
	if (indSizeType == indTypeVerySmall)
	{
		DrawBufferSmall( c, needPoint );
		return;
	}
	
	int		gx, gy;
	int		binCode = 0;
	long	*pDat;
									// 987654321
	if (c == '0') binCode = 0x3f;	// 000111111
	if (c == '1') binCode = 0x21;	// 000100001
	if (c == '2') binCode = 0x5b;	// 001011011
	if (c == '3') binCode = 0x73;	// 001110011
	if (c == '4') binCode = 0x65;	// 001100101
	if (c == '5') binCode = 0x76;	// 001110110
	if (c == '6') binCode = 0x7e;	// 001111110
	if (c == '7') binCode = 0x23;	// 000100011
	if (c == '8') binCode = 0x7f;	// 001111111
	if (c == '9') binCode = 0x77;	// 001110111
	if (c == '-') binCode = 0x40;	// 001000000	
	if (c == '+') binCode = 0x140;	// 101000000
	if (c == ' ') binCode = 0x00;	// 000000000

	if (needPoint) binCode |= 0x80;

	pDat = spriteBuffer;
	for( gy = 0; gy < spriteBufferH; gy++ )
	{
		for( gx = 0; gx < spriteBufferW; gx++ )
		{
			long	color = bColor;
			char	c = spriteTemp[gy][gx];

			if ((binCode & 0x01) != 0 && c == '1') color = fColor;
			if ((binCode & 0x02) != 0 && c == '2') color = fColor;		
			if ((binCode & 0x04) != 0 && c == '3') color = fColor;
			if ((binCode & 0x08) != 0 && c == '4') color = fColor;		
			if ((binCode & 0x10) != 0 && c == '5') color = fColor;
			if ((binCode & 0x20) != 0 && c == '6') color = fColor;		
			if ((binCode & 0x40) != 0 && c == '7') color = fColor;
			if ((binCode & 0x80) != 0 && c == '8') color = fColor;
			if ((binCode & 0x100) != 0 && c == '9') color = fColor;
		
			*pDat++ = color;
		}
	}
}
	
//! @brief Функция обновления (перерисовки) изображения на экране
//! @param pDC - контекст устройства
//! @param k = 1, если 1x1 пиксель
//! @param k = 2, если 2x2 пикселя
//! @return
void DigIndicator::OnPaint(CDC *pDC, int k)
{
	CDC		memDC;
	CBitmap memBM;
	CClientDC *dc = (CClientDC*)pDC;

	long	*buf;
	if (k == 1) buf = new long [spriteBufferW * spriteBufferH];
	if (k == 2) buf = new long [spriteBufferW * spriteBufferH * 4];	

    memDC.CreateCompatibleDC( dc );
	
	long	*pDat = spriteBuffer;
	int		gx, gy;

	for( gy = 0; gy < spriteBufferH; gy++ )
	{
		for( gx = 0; gx < spriteBufferW; gx++ )
		{
			long	color = *pDat;
			char	*colorData = (char*)&color;
			char	tmpByte;
	
			tmpByte = colorData[0];
			colorData[0] = colorData[2];
			colorData[2] = tmpByte;

			if (k == 1)
				buf[gy * spriteBufferW + gx] = color;
			else
			{
				buf[(gy * 2 + 0) * spriteBufferW * 2 + (gx * 2 + 0)] = color;
				buf[(gy * 2 + 0) * spriteBufferW * 2 + (gx * 2 + 1)] = color;
				buf[(gy * 2 + 1) * spriteBufferW * 2 + (gx * 2 + 0)] = color;
				buf[(gy * 2 + 1) * spriteBufferW * 2 + (gx * 2 + 1)] = color;
			}
		
			pDat++;	
		}
	}

    if (k == 1) memBM.CreateBitmap( spriteBufferW, spriteBufferH, 1, 32, buf );
    if (k == 2) memBM.CreateBitmap( spriteBufferW * 2, spriteBufferH * 2, 1, 32, buf );	
	delete [] buf;
    memDC.SelectObject( &memBM );
    if (k == 1) pDC->BitBlt( xStart, yStart, spriteBufferW, spriteBufferH, &memDC, 0, 0, SRCCOPY );
    if (k == 2) pDC->BitBlt( xStart, yStart, spriteBufferW * 2, spriteBufferH * 2, &memDC, 0, 0, SRCCOPY );
}

//! @brief Функция обновления (перерисовки) маленькой дробной точки на экране
//! @param pDC - контекст устройства
//! @param k = 1, если 1x1 пиксель
//! @param k = 2, если 2x2 пикселя
//! @return
void DigIndicator::OnPaintVerySmallPoint(CDC *pDC, int k)
{
	int		spriteW = 3;
	int		spriteH = 7;
	long	*sprite = new long [spriteW * spriteH];
	long	*pDat = sprite;
	int		gx, gy;
	
	for( gy = 0; gy < spriteH; gy++ )
	{
		for( gx = 0; gx < spriteW; gx++ )
		{
			bool	isPaint = false;
			long	color = bColor;

			if (gx == 1 && gy == 5) isPaint = true;

			if (isPaint) color = fColor;
			
			*pDat++ = color;		
		}
	}

	CDC		memDC;
	CBitmap memBM;
	CClientDC *dc = (CClientDC*)pDC;

	long	*buf;
	if (k == 1) buf = new long [spriteW * spriteH];
	if (k == 2) buf = new long [spriteW * spriteH * 4];	

    memDC.CreateCompatibleDC( dc );
	
	pDat = sprite;

	for( gy = 0; gy < spriteH; gy++ )
	{
		for( gx = 0; gx < spriteW; gx++ )
		{
			long	color = *pDat;
			char	*colorData = (char*)&color;
			char	tmpByte;
	
			tmpByte = colorData[0];
			colorData[0] = colorData[2];
			colorData[2] = tmpByte;

			if (k == 1)
				buf[gy * spriteW + gx] = color;
			else
			{
				buf[(gy * 2 + 0) * spriteW * 2 + (gx * 2 + 0)] = color;
				buf[(gy * 2 + 0) * spriteW * 2 + (gx * 2 + 1)] = color;
				buf[(gy * 2 + 1) * spriteW * 2 + (gx * 2 + 0)] = color;
				buf[(gy * 2 + 1) * spriteW * 2 + (gx * 2 + 1)] = color;
			}
		
			pDat++;	
		}
	}

    if (k == 1) memBM.CreateBitmap( spriteW, spriteH, 1, 32, buf );
    if (k == 2) memBM.CreateBitmap( spriteW * 2, spriteH * 2, 1, 32, buf );	
	delete [] buf;
    memDC.SelectObject( &memBM );
    if (k == 1) pDC->BitBlt( xStart, yStart, spriteW, spriteH, &memDC, 0, 0, SRCCOPY );
    if (k == 2) pDC->BitBlt( xStart, yStart, spriteW * 2, spriteH * 2, &memDC, 0, 0, SRCCOPY );

	delete [] sprite;
}

//! @brief Функция возвращает размер маленькой (verySmall) дробной точки на экране
//! @return размер дробной точки
int DigIndicator::GetVerySmallPointSize( )
{
	return 3;
}
