#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

class Texture
{
private:
	SDL_Texture * m_pTexture;

public:
	int m_iWidth, m_iHeight;

	Texture( SDL_Renderer * _pRenderer, const char * _cFileName )
	{
		SDL_Surface * m_pTempSurface;

		m_pTempSurface = IMG_Load( _cFileName );
		if( m_pTempSurface == NULL )
			printf( "TEXTURE CREATE ERROR\n" );
		
		m_iWidth = m_pTempSurface->w;
		m_iHeight = m_pTempSurface->h;

		m_pTexture = SDL_CreateTextureFromSurface( _pRenderer, m_pTempSurface );
		SDL_FreeSurface( m_pTempSurface );
	};

	~Texture()
	{
		SDL_DestroyTexture( m_pTexture );
	};

	SDL_Texture * GetTexture()
	{
		return m_pTexture;
	}

	void RenderWithRotation( SDL_Renderer * _pRenderer, float _fAngle, int _iX, int _iY )
	{
		SDL_Rect m_stRect;
		m_stRect.x = _iX;
		m_stRect.y = _iY;
		m_stRect.w = m_iWidth;
		m_stRect.h = m_iHeight;

		SDL_RenderCopyEx( _pRenderer, m_pTexture, NULL, &m_stRect, (double)_fAngle*180/3.1415f+90, NULL, SDL_FLIP_NONE );
	}

	void Render( SDL_Renderer * _pRenderer )
	{
		SDL_RenderCopy( _pRenderer, m_pTexture, NULL, NULL );
		//SDL_RenderPresent( _pRenderer );
	}

	void Render( SDL_Renderer * _pRenderer, int _iX, int _iY )
	{
		SDL_Rect m_stRect;
		m_stRect.x = _iX;
		m_stRect.y = _iY;
		m_stRect.w = m_iWidth;
		m_stRect.h = m_iHeight;

		SDL_RenderCopy( _pRenderer, m_pTexture, NULL, &m_stRect );
		//SDL_RenderPresent( _pRenderer );
	}

	void Render( SDL_Renderer * _pRenderer, int _iX, int _iY, int _iAlpha )
	{
		SDL_Rect m_stRect;
		m_stRect.x = _iX;
		m_stRect.y = _iY;
		m_stRect.w = m_iWidth;
		m_stRect.h = m_iHeight;

		SDL_SetTextureAlphaMod( m_pTexture, _iAlpha );
		//SDL_SetTextureBlendMode( m_pTexture, SDL_BLENDMODE_BLEND );
		SDL_RenderCopy( _pRenderer, m_pTexture, NULL, &m_stRect );
		SDL_SetTextureAlphaMod( m_pTexture, 255 );
		//SDL_RenderPresent( _pRenderer );
	}

	void Render( SDL_Renderer * _pRenderer, int _iX, int _iY, int _iW, int _iH )
	{
		SDL_Rect m_stRectDest, m_stRectSrc;
		m_stRectDest.x = _iX;
		m_stRectDest.y = _iY;
		m_stRectDest.w = _iW;
		m_stRectDest.h = _iH;

		m_stRectSrc.x = 0;
		m_stRectSrc.y = 0;
		m_stRectSrc.w = _iW;
		m_stRectSrc.h = _iH;

		SDL_RenderCopy( _pRenderer, m_pTexture, &m_stRectSrc, &m_stRectDest );
		//SDL_RenderPresent( _pRenderer );
	}
};

#endif