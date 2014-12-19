#ifndef	__GUI_BUTTON_H__
#define __GUI_BUTTON_H__

#include "Texture.h"

class GameManager;

typedef struct _tagEvent
{
	int iType;
	int iData;
} EVENT_MESSAGE;

typedef struct _tagButtonTexture
{
	Texture * idle;
	Texture * hover;
} BUTTON_TEXTURE;
class GUIButton
{
private:
	int m_iX;
	int m_iY;
	int m_iW;
	int m_iH;

	bool m_bEnable;
	bool m_bIsHover;

	//Texture * m_pTexture;
	BUTTON_TEXTURE m_stTexture;

	void ( GameManager::*m_fp ) ( EVENT_MESSAGE );
	EVENT_MESSAGE m_stMessage;

public:
	GUIButton( int _iX, int _iY, BUTTON_TEXTURE &_stTexture, void (GameManager::*_fp)(EVENT_MESSAGE), void *_stMessage )
	{
		m_iX = _iX;
		m_iY = _iY;
		m_iW = _stTexture.idle->m_iWidth;
		m_iH = _stTexture.idle->m_iHeight;
		m_fp = _fp;
		m_stTexture = _stTexture;
		if( _stMessage )
			m_stMessage = *( EVENT_MESSAGE * )_stMessage;

		m_bEnable = true;
		m_bIsHover = false;
	}

	~GUIButton()
	{
	}

	void SetEnable( bool _bEnable )
	{
		m_bEnable = _bEnable;
	}

	void Render( SDL_Renderer * _pRenderer )
	{
		if( !m_bIsHover )
			m_stTexture.idle->Render( _pRenderer, m_iX, m_iY );
		else
			m_stTexture.hover->Render( _pRenderer, m_iX, m_iY );
	}

	bool Check( int _iX, int _iY )
	{
		if( ( _iX >= m_iX ) && ( _iX <= (m_iX+m_iW) ) )
			if( ( _iY >= m_iY ) && ( _iY <= (m_iY+m_iH) ) )
				return true;
		return false;
	}

	void SetHover( bool _bIsHover )
	{
		m_bIsHover = _bIsHover;
	}

	void Work()
	{
		if( m_fp )
			((GameManager* const)this->*m_fp)( m_stMessage );
	}
};

#endif