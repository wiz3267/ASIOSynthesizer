#ifndef __DIG_INDICATOR_INPUT__
#define __DIG_INDICATOR_INPUT__

#include "digIndicator.h"

class DigIndicatorInput
{
	DigIndicator	**indList;
	int				indCount;
	int				xOrigin;
	int				yOrigin;
	char			*textString;
	int				cursorIndex;
	long			bColor;
	long			fColor;
	long			cursorBColor;
	static bool		isUsed;
	bool			isShowCursor;
	int				indSizeX;

public:
	DigIndicatorInput( int nInd, int xOrigin, int yOrigin, long bColor, long fColor, long cursorBColor );
	~DigIndicatorInput( );

	void HandleKey( int keyPressed );
	void OnPaint( CDC *pDC );
	void ClearArea( CDC *pDC );
	char *GetResult( );
	void SetText( char *str );

	bool GetIsUsed( );
	void SetIsUsed( );
	void ResetIsUsed( );
	void SetCursorStatus( bool isShowCursor );
	void SetCursorPos( int cursorPos );
	void SetPosition( int x, int y );
};

#endif