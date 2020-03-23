#include <stdafx.h>
#include <math.h>
#include "circleSlider.h"

	
CircleSlider::CircleSlider( int len, int _x,int _y, double Arg_cSliderAng )
{
	cSliderAng=Arg_cSliderAng;
	x=_x;
	y=_y;
	spriteBuf = new long [len * len];
	spriteBufLen = len;

	r1 = len / 2 * 0.7;
	r2 = len / 2 * 0.8;
}

CircleSlider::~CircleSlider()
{
	delete [] spriteBuf;
}

//! @breif Функция перевода градусов в радианы
//! @param f - значение в градусах
//! @return значение в радианах
double CircleSlider::toRad( double f )
{
	double	mPi = 3.1415926;

	return f * (mPi / 180);
}

//! @brief Функция рисует кольцо (сектор) окружности, которое задается малым и большим радиусом
//! @param pDat - буффер NxN pixels
//! @param len - размерность буффера (длина стороны квадрата в пикселях)
//! @param color - цвет для рисования (например если 255 то синий)
//! @param xc, yc - координаты центра окружности
//! @param r1, r2 - малый и большой радиусы дуги соответственно
//! @param ang - стартовый угол от 0 до 360
//! @param angDelta - дельта угла (если значение меньше 0 то не учитывать)
//! @return
void CircleSlider::DrawCircleSector( long *pDat, int len, long color, double xc, double yc, double r1, double r2,
									 double ang, double angDelta )
{
	double	vx = cos(ang);
	double	vy = sin(ang);
	int		gx, gy;
	double	cosAngDelta = cos(angDelta);

	if (angDelta < 0) cosAngDelta = -1.1;

	for( gy = 0; gy < len; gy++ )
	{
		for( gx = 0; gx < len; gx++ )
		{
			long	curPixelColor = *pDat;
			
			double	curX = gx;
			double	curY = len-1 - gy;
			double	dx = curX - xc;
			double	dy = curY - yc;
			double	d2 = dx * dx + dy * dy;
			double	d = sqrt( d2 );

			if (d >= r1 && d <= r2)
			{
				double	ux = dx / d;
				double	uy = dy / d;
				double	sm = ux * vx + uy * vy;

				if (sm > cosAngDelta)
				{
					curPixelColor = color;
				}
			}
			*pDat++ = curPixelColor;
		}
	}
}

//! @brief Фукнция рисует отрезок от точки (x1, y1) до точки (x2, y2) толщиной w
//! @param pDat - буффер NxN pixels
//! @param len - размерность буффера (длина стороны квадрата в пикселях)
//! @param color - цвет для рисования (например если 255 то синий)
//! @param x1, y1 - первая точка
//! @param x2, y2 - вторая точка
//! @param w - толщина отрезка
//! @return
void CircleSlider::DrawEdge( long *pDat, int len, long color, double x1, double y1, double x2, double y2, double w )
{
	int		gx, gy;

	for( gy = 0; gy < len; gy++ )
	{
		for( gx = 0; gx < len; gx++ )
		{
			long	curPixelColor = *pDat;
			
			double	curX = gx;
			double	curY = len-1 - gy;

			// (p + ab' * t - a, ab') = 0
			// (p - a, ab') + (ab', ab') * t = 0
			// t = (a - p, ab) / (ab', ab')
			// |ab'| * t
			double	ax = x1;
			double	ay = y1;
			double	bx = x2;
			double	by = y2;
			double	px = curX;
			double	py = curY;
			double	t1 = (ax - px) * (ay - by)  + (ay - py) * (bx - ax);
			double	t2 = (bx - ax) * (bx - ax) + (by - ay) * (by - ay);
			double	t = t1 / t2;

			if (t < 0) t = -t;

			double	d = sqrt( (bx - ax) * (bx - ax) + (by - ay) * (by - ay) ) * t;

			if (d < w)
			{
				// (a + ab * t - p, ab) = 0
				// (a - p, ab) + (ab, ab) * t = 0
				// t = (p - a, ab) / (ab, ab)
				t1 = (px - ax) * (bx - ax) + (py - ay) * (by - ay);
				t2 = (bx - ax) * (bx - ax) + (by - ay) * (by - ay);
				t = t1 / t2;

				if (t >= 0 && t <= 1)
				{
					curPixelColor = color;
				}
			}

			*pDat++ = curPixelColor;
		}
	}
}

//! @brief Заполнение фона заданным значением
//! @brief будем считать, что если задано значение равное -1, то фон прозрачный
//! @param color - цвет фона
//! @return
void CircleSlider::FillBackground( long color )
{
	int		count = spriteBufLen * spriteBufLen;	
	
	for( int i = 0; i < count; i++ )
	{
		spriteBuf[i] = color;
	}
}

//! @brief Тип перерисовки 1 в зависимости от угла
//! @param ang - угол
//! @return 
void CircleSlider::DrawType1( double ang )
{
	int		len = spriteBufLen;	
	long	color1 = 0xff0000L;
	long	color2 = 0xffff00L;
	double	xc = len / 2;
	double	yc = len / 2;
	
	DrawCircleSector( spriteBuf, spriteBufLen, color1, xc, yc, r1, r2, 0, -1 );
	DrawCircleSector( spriteBuf, spriteBufLen, color2, xc, yc, r1, r2, ang, toRad(10) );
}
	
//! @brief Тип перерисовки 2 в зависимости от угла
//! @param ang - угол
//! @return 
void CircleSlider::DrawType2( double ang )
{
	int		len = spriteBufLen;	
	long	color1 = 0xff0000L;
	long	color2 = 0xff00ffL;
	double	xc = len / 2;
	double	yc = len / 2;
	double	r = (r1 + r2) / 2;
	double	xo = xc + r * cos(ang);
	double	yo = yc + r * sin(ang);

	DrawCircleSector( spriteBuf, spriteBufLen, color1, xc, yc, r1, r2, 0, -1 );
	DrawCircleSector( spriteBuf, spriteBufLen, color2, xo, yo, 0, 5, 0, -1 );
}
	
//! @brief Тип перерисовки 3 в зависимости от угла
//! @param ang - угол
//! @return 
void CircleSlider::DrawType3( double ang )
{
	int		len = spriteBufLen;	
	long	color1 = 0xff0000L;
	long	color2 = 0xffff00L;
	double	xc = len / 2;
	double	yc = len / 2;
	
	DrawCircleSector( spriteBuf, spriteBufLen, color1, xc, yc, r1, r2, 0, -1 );
	DrawCircleSector( spriteBuf, spriteBufLen, color2, xc, yc, 0, r2, ang, toRad(10) );
}

//! @brief Тип перерисовки 4 в зависимости от угла
//! @param ang - угол
//! @return 
void CircleSlider::DrawType4( double ang )
{
	int		len = spriteBufLen;	
	long	color1 = RGB(0,0,0);
	long	color2 = RGB(0,0,0);
	long	color3 = RGB(0xF0,0xF0,0xF0);
	DWORD	color4 = RGB(0,0,0);	//цвет стрелки
			
	double	xc = len / 2;
	double	yc = len / 2;
	double	r = (r1 + r2) / 2;
	double	x1 = xc + r * 0.1 * cos(ang);
	double	y1 = yc + r * 0.1 * sin(ang);
	double	x2 = xc + r * 0.9 * cos(ang);
	double	y2 = yc + r * 0.9 * sin(ang);

	DrawCircleSector( spriteBuf, spriteBufLen, color1, xc, yc, r1, r2, 0, -1 );
	DrawCircleSector( spriteBuf, spriteBufLen, color3, xc, yc, r1, r2, toRad(270), toRad(45) );
	
	//DrawEdge( spriteBuf, spriteBufLen, 0xff00ffL, x1, y1, x2, y2, 3 );
	DrawEdge( spriteBuf, spriteBufLen, RGB(0,0,0), x1, y1, x2, y2, 1 );
}

//! @brief Функция получения угла, в зависимости от координат курсора мыши
//! @param xc, yc - центр прямоугольника на экране
//! @param len - длина стороны прямоугольника на экране
//! @param mouseX, mouseY - координаты курсора мыши
//! @return ang - угол
//! @return признак - было ли действие
bool CircleSlider::GetAngle( double& ang, double xc, double yc, double len, double mouseX, double mouseY )
{
	double	dx = mouseX - xc;
	double	dy = -(mouseY - yc);
	double	d2 = dx * dx + dy * dy;
	double	d = sqrt( d2 );

	if (!(d >= r1 - 5 && d <= r2 + 5)) return false;
	
	double	f = 0;

	ang = 0;
	for( f = 0; f < 6.29; f += 0.001 )
	{
		double	ux = cos(f);
		double	uy = sin(f);
		double	vx = dx / d;
		double	vy = dy / d;
		double	sm = ux * vx + uy * vy;

		if (sm > 0.99) ang = f;
	}
	return true;
}

//! @brief Функция получения буффера со спрайтом
//! @return указатель на буффер со спрайтом
long *CircleSlider::GetSpriteBuf( )
{
	return spriteBuf;
}

//! @brief Функция получения размерности (длины) буффера со спрайтом
//! @return длина буффера
int CircleSlider::GetSpriteBufLen( )
{
	return spriteBufLen;
}


void CircleSlider::Draw( CDC *pDC)
{

	int C=0xF0;
	FillBackground( RGB(C,C,C) );

	DrawType4( cSliderAng );

	long *pDat=spriteBuf;

	int len=spriteBufLen;

	int		gx, gy;


	for( gy = 0; gy < len; gy++ )
	{
		for( gx = 0; gx < len; gx++ )
		{
			long	color = *pDat;			
			
			if (color != -1)
			{
				pDC->SetPixel( x + gx, y + gy, color );
			}
			pDat++;
		}
	}
}

void CircleSlider::OnMouseMove(UINT nFlags,CPoint point)
{
	if (!(nFlags & MK_LBUTTON))
	{
		return;
	}

	flagPaint = false;
	
	int xo = x;
	int yo = y;

	int		len = GetSpriteBufLen();
	int		xc = xo + len / 2;
	int		yc = yo + len / 2;
	int		mouseX = point.x;
	int		mouseY = point.y;

	double	ang;
		
	if (GetAngle( ang, xc, yc, len, mouseX, mouseY ))
	{
		cSliderAng = ang;
		flagPaint = true;
	}

}