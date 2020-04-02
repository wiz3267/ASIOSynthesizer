#include <stdafx.h>
#include <math.h>
#include "digIndicator.h"

DigIndicator::DigIndicator( int x, int y, long bColor, long fColor, bool isSmallInd )
{
	xStart = x;
	yStart = y;
	this->bColor = bColor;
	this->fColor = fColor;

	int		bufLen;

	if (isSmallInd == false)
	{
		spriteBufferW = 24;
		spriteBufferH = 32;
		spriteBuffer = new long [spriteBufferW * spriteBufferH];

		bufLen = spriteBufferW * spriteBufferH;

		for( int i = 0; i < bufLen; i++ )
			spriteBuffer[i] = 0;

		spriteTemp = new char* [spriteBufferH];

		for( i = 0; i < spriteBufferH; i++ )
			spriteTemp[i] = new char [spriteBufferW + 1];

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

		strcpy( spriteTemp[0], s00 );
		strcpy( spriteTemp[1], s01 );
		strcpy( spriteTemp[2], s02 );
		strcpy( spriteTemp[3], s03 );
		strcpy( spriteTemp[4], s04 );
		strcpy( spriteTemp[5], s05 );
		strcpy( spriteTemp[6], s06 );
		strcpy( spriteTemp[7], s07 );

		strcpy( spriteTemp[8], s08 );
		strcpy( spriteTemp[9], s09 );
		strcpy( spriteTemp[10], s10 );
		strcpy( spriteTemp[11], s11 );
		strcpy( spriteTemp[12], s12 );
		strcpy( spriteTemp[13], s13 );
		strcpy( spriteTemp[14], s14 );
		strcpy( spriteTemp[15], s15 );

		strcpy( spriteTemp[16], s16 );
		strcpy( spriteTemp[17], s17 );
		strcpy( spriteTemp[18], s18 );
		strcpy( spriteTemp[19], s19 );
		strcpy( spriteTemp[20], s20 );
		strcpy( spriteTemp[21], s21 );
		strcpy( spriteTemp[22], s22 );
		strcpy( spriteTemp[23], s23 );

		strcpy( spriteTemp[24], s24 );
		strcpy( spriteTemp[25], s25 );
		strcpy( spriteTemp[26], s26 );
		strcpy( spriteTemp[27], s27 );
		strcpy( spriteTemp[28], s28 );
		strcpy( spriteTemp[29], s29 );
		strcpy( spriteTemp[30], s30 );
		strcpy( spriteTemp[31], s31 );

		smallIndFlag = false;
	}
	else
	{
		spriteBufferW = 9;
		spriteBufferH = 10;
		spriteBuffer = new long [spriteBufferW * spriteBufferH];

		bufLen = spriteBufferW * spriteBufferH;

		for( int i = 0; i < bufLen; i++ )
			spriteBuffer[i] = 0;

		spriteTemp = new char* [spriteBufferH];

		for( i = 0; i < spriteBufferH; i++ )
			spriteTemp[i] = new char [spriteBufferW + 1];


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

		strcpy( spriteTemp[0], s00 );
		strcpy( spriteTemp[1], s01 );
		strcpy( spriteTemp[2], s02 );
		strcpy( spriteTemp[3], s03 );
		strcpy( spriteTemp[4], s04 );
		strcpy( spriteTemp[5], s05 );
		strcpy( spriteTemp[6], s06 );
		strcpy( spriteTemp[7], s07 );
		strcpy( spriteTemp[8], s08 );
		strcpy( spriteTemp[9], s09 );

		smallIndFlag = true;
	}
}

DigIndicator::~DigIndicator()
{
	if (spriteTemp != NULL)
	{
		for( int i = 0; i < spriteBufferH; i++ )
		{
			if (spriteTemp[i] != NULL)
			{
				delete [] spriteTemp[i];
				spriteTemp[i] = NULL;
			}
		}
		delete [] spriteTemp;
		spriteTemp = NULL;
	}

	if (spriteBuffer != NULL)
	{
		delete [] spriteBuffer;
		spriteBuffer = NULL;
	}
}

//! @brief Функция проверяет используется ли малое изображение индикатора
//! @return true - если используется малое изображение
bool DigIndicator::isSmallInd( )
{
	return smallIndFlag;
}

//! @brief Функция отображения ASCII-символа в буффер индикатора
//! @param c - код символа
//! @param needPoint - нужна ли точка
//! @return
void DigIndicator::DrawBuffer( char c, bool needPoint )
{
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


