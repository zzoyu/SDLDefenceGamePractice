#include "GUIDialogue.h"
#include "manager_game.h"

void GUIDialogue::Render( SDL_Renderer *_pRenderer )
{
	SDL_Color m_stColor = { 255, 255, 255 };
	if( m_pStandingTexture )
		m_pStandingTexture->Render( _pRenderer, m_iStandingX, m_iStandingY );
	if( m_pBaseTexture )
		m_pBaseTexture->Render( _pRenderer, m_iBaseX, m_iBaseY );

	if( !m_bIsEffectShown )
		GameManager::Instance()->SetEffectFlag( false );
	GameManager::Instance()->DrawText( m_strCharacter, m_iBaseX+10, m_iBaseY+10, m_stColor );

	int m_iNewLine, i = 0;
	std::wstring m_strTemp = m_strQuote;

	while( true )
	{
		if( !m_bIsEffectShown )
			GameManager::Instance()->SetEffectFlag( false );
		m_iNewLine = ( m_strTemp.find( L"$n" ) == -1 ) ? m_strTemp.length() : m_strTemp.find( L"$n" );
		GameManager::Instance()->DrawText( m_strTemp.substr( 0, m_iNewLine ), m_iBaseX+10, m_iBaseY+30+(20*i), m_stColor );

		if( m_iNewLine == m_strTemp.length() )
			break;

		m_strTemp = m_strTemp.substr( m_iNewLine+2, m_strTemp.length() );
		i++;
	}
	m_bIsEffectShown = true;
	m_bIsVisible = true;
}