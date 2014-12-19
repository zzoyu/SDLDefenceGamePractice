#ifndef __GUI_DIALOGUE_H__
#define __GUI_DIALOGUE_H__

#include "Texture.h"
#include <string>

//class GameManager;

class GUIDialogue
{
private:
	bool m_bIsVisible;
	bool m_bIsEffectShown;
	int m_iBaseX, m_iBaseY, m_iStandingX, m_iStandingY;
	std::wstring m_strCharacter, m_strQuote;
	Texture * m_pBaseTexture, *m_pStandingTexture;

public:
	GUIDialogue()
	{}

	GUIDialogue( std::wstring &_strCharacter, std::wstring &_strQuote,
		Texture *_pBaseTexture, Texture *_pStandingTexture,
		int _iBaseX, int _iBaseY, int _iStandingX, int _iStandingY )
	{
		m_strCharacter = _strCharacter;
		m_strQuote = _strQuote;

		m_pBaseTexture = _pBaseTexture;
		m_pStandingTexture = _pStandingTexture;

		m_iBaseX = _iBaseX;
		m_iBaseY = _iBaseY;
		m_iStandingX = _iStandingX;
		m_iStandingY = _iStandingY;

		m_bIsVisible = true;
		m_bIsEffectShown = false;
	}

	void Render( SDL_Renderer *_pRenderer );

	void SetVisible( bool _bIsVisible )
	{
		m_bIsVisible = _bIsVisible;
	}

	bool GetVisible()
	{
		return m_bIsVisible;
	}
};

#endif