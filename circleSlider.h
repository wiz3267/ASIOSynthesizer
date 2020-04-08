#ifndef __CIRCLE_SLIDER__
#define __CIRCLE_SLIDER__

class CircleSlider 
{
	long	*spriteBuf;
	int		spriteBufLen;
public:
	bool	flagPaint;	//нужно ли перерисовать элемент управления
	double	r1, r2;
	int		x,y;		//координаты элемента на экране

	double	cSliderAng;	//угол, на который установлена ручка
	int		drawType;

	//! @breif Функция перевода градусов в радианы
	//! @param f - значение в градусах
	//! @return значение в радианах
	double toRad( double f );

	//! @brief Функция рисует кольцо (сектор) окружности, которое задается малым и большим радиусом
	//! @param pDat - буффер NxN pixels
	//! @param len - размерность буффера (длина стороны квадрата в пикселях)
	//! @param color - цвет для рисования (например если 255 то синий)
	//! @param xc, yc - координаты центра окружности
	//! @param r1, r2 - малый и большой радиусы дуги соответственно
	//! @param ang - стартовый угол от 0 до 360
	//! @param angDelta - дельта угла (если значение меньше 0 то не учитывать)
	//! @param isNeedSmooth - нужно ли сглаживание
	//! @return
	void DrawCircleSector( long *pDat, int len, long color, double xc, double yc, double r1, double r2,
						   double ang, double angDelta, bool isNeedSmooth = false );

	//! @brief Фукнция рисует отрезок от точки (x1, y1) до точки (x2, y2) толщиной w
	//! @param pDat - буффер NxN pixels
	//! @param len - размерность буффера (длина стороны квадрата в пикселях)
	//! @param color - цвет для рисования (например если 255 то синий)
	//! @param x1, y1 - первая точка
	//! @param x2, y2 - вторая точка
	//! @param w - толщина отрезка
	//! @return
	void DrawEdge( long *pDat, int len, long color, double x1, double y1, double x2, double y2, double w );
public:
	CircleSlider( int len, int x, int y, double arg_cSliderAng );
	~CircleSlider();

	//! @brief Заполнение фона заданным значением
	//! @brief будем считать, что если задано значение равное -1, то фон прозрачный
	//! @param color - цвет фона
	//! @return
	void FillBackground( long color );

	//! @brief Тип перерисовки 1 в зависимости от угла
	//! @param ang - угол
	//! @return 
	void DrawType1( double ang );
	
	//! @brief Тип перерисовки 2 в зависимости от угла
	//! @param ang - угол
	//! @return 
	void DrawType2( double ang );
	
	//! @brief Тип перерисовки 3 в зависимости от угла
	//! @param ang - угол
	//! @return 
	void DrawType3( double ang );

	//! @brief Тип перерисовки 4 в зависимости от угла
	//! @param ang - угол
	//! @return 
	void DrawType4( double ang );

	//! @brief Функция получения угла, в зависимости от координат курсора мыши
	//! @param xc, yc - центр прямоугольника на экране
	//! @param len - длина стороны прямоугольника на экране
	//! @param mouseX, mouseY - координаты курсора мыши
	//! @return ang - угол
	//! @return признак - было ли действие
	bool GetAngle( double& ang, double xc, double yc, double len, double mouseX, double mouseY );

	//! @brief Функция получения буффера со спрайтом
	//! @return указатель на буффер со спрайтом
	long *GetSpriteBuf( );

	//! @brief Функция получения размерности (длины) буффера со спрайтом
	//! @return длина буффера
	int GetSpriteBufLen( );
	
	//! @brief Функция определяет какую функцию перерисовки использовать в дальнейшем
	//! @param drawType - тип перерисовки (1..4)
	//! @return
	void SetDrawType( int drawType );

	//рисует элемент управления
	void Draw( CDC *pDC );

	//обрабатывает сообщение от мышки
	void OnMouseMove(UINT nFlags,CPoint point);

	//! @brief Функция возвращает текущее положение слайдера от 0 до 1
	//! @return положение слайдера
	double GetCurrentValue( );
};


#endif