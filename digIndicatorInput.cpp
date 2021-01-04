#include <stdafx.h>
#include "digIndicatorInput.h"

bool DigIndicatorInput::isUsed = false;

DigIndicatorInput::DigIndicatorInput( int nInd, int xOrigin, int yOrigin, long bColor, long fColor, long cursorBColor )
{
	int		i;	
	
	indList = new DigIndicator*[nInd];

	for( i = 0; i < nInd; i++ )
	{
//		indSizeX = 24;
//		indList[i] = new DigIndicator( xOrigin + indSizeX * i, yOrigin, bColor, fColor, 2 );
		indSizeX = 8;
		indList[i] = new DigIndicator( xOrigin + indSizeX * i, yOrigin, bColor, fColor, 1 );
	}

	this->xOrigin = xOrigin;
	this->yOrigin = yOrigin;
	this->indCount = nInd;
	this->textString = new char [nInd + 1];
	this->cursorIndex = 0;
	this->bColor = bColor;
	this->fColor = fColor;
	this->cursorBColor = cursorBColor;
	this->isShowCursor = false;

	for( i = 0; i < nInd; i++ )
		textString[i] = '2';
	textString[nInd] = 0;
}

DigIndicatorInput::~DigIndicatorInput( )
{
	if (indList != NULL)
	{
		for( int i = 0; i < indCount; i++ )
		{
			if (indList[i] != NULL)
			{
				delete indList[i];
				indList[i] = NULL;
			}
		}
		delete [] indList;
		indList = NULL;
		indCount = 0;
	}
}

void DigIndicatorInput::HandleKey( int keyPressed )
{
	if (keyPressed == VK_LEFT)
	{
		if (cursorIndex > 0) 
			cursorIndex--;
	}

	if (keyPressed == VK_RIGHT)
	{
		if (cursorIndex < indCount-1)
			cursorIndex++;
	}

	if (keyPressed == VK_HOME)
		cursorIndex = 0;

	if (keyPressed == VK_END)
		cursorIndex = indCount - 1;

	if (keyPressed == VK_BACK && cursorIndex > 0)
	{
		cursorIndex--;

		for( int i = cursorIndex; i < indCount-1; i++ )
		{
			textString[i] = textString[i+1];
		}
		textString[indCount-1] = ' ';
	}

	if (keyPressed == VK_DELETE)
	{
		for( int i = cursorIndex; i < indCount-1; i++ )
		{
			textString[i] = textString[i+1];
		}
		textString[indCount-1] = ' ';
	}

	int		nChar = -1;

	if (keyPressed == '0' || keyPressed == VK_NUMPAD0) nChar = '0';
	if (keyPressed == '1' || keyPressed == VK_NUMPAD1) nChar = '1';
	if (keyPressed == '2' || keyPressed == VK_NUMPAD2) nChar = '2';
	if (keyPressed == '3' || keyPressed == VK_NUMPAD3) nChar = '3';
	if (keyPressed == '4' || keyPressed == VK_NUMPAD4) nChar = '4';
	if (keyPressed == '5' || keyPressed == VK_NUMPAD5) nChar = '5';
	if (keyPressed == '6' || keyPressed == VK_NUMPAD6) nChar = '6';
	if (keyPressed == '7' || keyPressed == VK_NUMPAD7) nChar = '7';
	if (keyPressed == '8' || keyPressed == VK_NUMPAD8) nChar = '8';
	if (keyPressed == '9' || keyPressed == VK_NUMPAD9) nChar = '9';

	if (keyPressed == ' ') nChar = ' ';
	if (keyPressed == VK_DECIMAL || keyPressed == 0xbe)  nChar = 'P';
	if (keyPressed == VK_ADD || keyPressed == 0xbb) nChar = '+';
	if (keyPressed == VK_SUBTRACT || keyPressed == 0xbd) nChar = '-';
	
	if (nChar != -1)
	{
		for( int i = indCount-1; i > cursorIndex; i-- )
			textString[i] = textString[i-1];
		
		textString[cursorIndex] = nChar;
		cursorIndex++;
	}

	if (cursorIndex >= indCount) cursorIndex--;
}

void DigIndicatorInput::OnPaint( CDC *pDC )
{
	int		i;	
	
	for( i = 0; i < indCount; i++ )
	{
		indList[i]->SetColor( bColor, fColor );
		indList[i]->xStart = xOrigin + indSizeX * i;
		indList[i]->yStart = yOrigin;
	}
	
	if (isShowCursor == true)
		indList[cursorIndex]->SetColor( cursorBColor, fColor );
	
	for( i = 0; i < indCount; i++ )
	{
		if (textString[i] == '.')
			indList[i]->DrawBuffer( ' ', true );
		else
			indList[i]->DrawBuffer( textString[i] );	

		indList[i]->OnPaint( pDC, 1 );
	}
}

void DigIndicatorInput::ClearArea( CDC *pDC )
{
	int		i;	
	
	for( i = 0; i < indCount; i++ )
	{
		indList[i]->SetColor( 0xf0f0f0L, 0xf0f0f0L );
		indList[i]->xStart = xOrigin + indSizeX * i;
		indList[i]->yStart = yOrigin;
	}
	
	for( i = 0; i < indCount; i++ )
	{
		indList[i]->DrawBuffer( ' ' );	
		indList[i]->OnPaint( pDC, 1 );
	}
}

char *DigIndicatorInput::GetResult( )
{
	return textString;
}

bool DigIndicatorInput::GetIsUsed( )
{
	return isUsed;
}

void DigIndicatorInput::SetIsUsed( )
{
	isUsed = true;
}

void DigIndicatorInput::ResetIsUsed( )
{
	isUsed = false;
}

void DigIndicatorInput::SetText( char *str )
{
	strcpy( textString, str );
}

void DigIndicatorInput::SetCursorStatus( bool isShowCursor )
{
	this->isShowCursor = isShowCursor;
}

void DigIndicatorInput::SetCursorPos( int cursorPos )
{
	this->cursorIndex = cursorPos;
}

void DigIndicatorInput::SetPosition( int x, int y )
{
	this->xOrigin = x;
	this->yOrigin = y;
}