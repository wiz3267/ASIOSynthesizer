#ifndef __CIRCLE_SLIDER__
#define __CIRCLE_SLIDER__

class CircleSlider 
{
	long	*spriteBuf;
	int		spriteBufLen;
public:
	bool	flagPaint;	//����� �� ������������ ������� ����������
	double	r1, r2;
	int		x,y;		//���������� �������� �� ������

	double cSliderAng;	//����, �� ������� ����������� �����


	//! @breif ������� �������� �������� � �������
	//! @param f - �������� � ��������
	//! @return �������� � ��������
	double toRad( double f );

	//! @brief ������� ������ ������ (������) ����������, ������� �������� ����� � ������� ��������
	//! @param pDat - ������ NxN pixels
	//! @param len - ����������� ������� (����� ������� �������� � ��������)
	//! @param color - ���� ��� ��������� (�������� ���� 255 �� �����)
	//! @param xc, yc - ���������� ������ ����������
	//! @param r1, r2 - ����� � ������� ������� ���� ��������������
	//! @param ang - ��������� ���� �� 0 �� 360
	//! @param angDelta - ������ ���� (���� �������� ������ 0 �� �� ���������)
	//! @return
	void DrawCircleSector( long *pDat, int len, long color, double xc, double yc, double r1, double r2,
						   double ang, double angDelta );

	//! @brief ������� ������ ������� �� ����� (x1, y1) �� ����� (x2, y2) �������� w
	//! @param pDat - ������ NxN pixels
	//! @param len - ����������� ������� (����� ������� �������� � ��������)
	//! @param color - ���� ��� ��������� (�������� ���� 255 �� �����)
	//! @param x1, y1 - ������ �����
	//! @param x2, y2 - ������ �����
	//! @param w - ������� �������
	//! @return
	void DrawEdge( long *pDat, int len, long color, double x1, double y1, double x2, double y2, double w );
public:
	CircleSlider( int len, int x, int y, double arg_cSliderAng );
	~CircleSlider();

	//! @brief ���������� ���� �������� ���������
	//! @brief ����� �������, ��� ���� ������ �������� ������ -1, �� ��� ����������
	//! @param color - ���� ����
	//! @return
	void FillBackground( long color );

	//! @brief ��� ����������� 1 � ����������� �� ����
	//! @param ang - ����
	//! @return 
	void DrawType1( double ang );
	
	//! @brief ��� ����������� 2 � ����������� �� ����
	//! @param ang - ����
	//! @return 
	void DrawType2( double ang );
	
	//! @brief ��� ����������� 3 � ����������� �� ����
	//! @param ang - ����
	//! @return 
	void DrawType3( double ang );

	//! @brief ��� ����������� 4 � ����������� �� ����
	//! @param ang - ����
	//! @return 
	void DrawType4( double ang );

	//! @brief ������� ��������� ����, � ����������� �� ��������� ������� ����
	//! @param xc, yc - ����� �������������� �� ������
	//! @param len - ����� ������� �������������� �� ������
	//! @param mouseX, mouseY - ���������� ������� ����
	//! @return ang - ����
	//! @return ������� - ���� �� ��������
	bool GetAngle( double& ang, double xc, double yc, double len, double mouseX, double mouseY );

	//! @brief ������� ��������� ������� �� ��������
	//! @return ��������� �� ������ �� ��������
	long *GetSpriteBuf( );

	//! @brief ������� ��������� ����������� (�����) ������� �� ��������
	//! @return ����� �������
	int GetSpriteBufLen( );


	//������ ������� ����������
	void Draw( CDC *pDC);

	//������������ ��������� �� �����
	void OnMouseMove(UINT nFlags,CPoint point);
	
};


#endif