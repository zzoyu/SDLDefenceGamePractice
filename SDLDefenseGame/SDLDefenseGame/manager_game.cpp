#include "manager_game.h"

GameManager* GameManager::m_pInstance = NULL;

GameManager* GameManager::Instance()
{
	if( !m_pInstance )	// 인스턴스 할당
		m_pInstance = new GameManager;

	return m_pInstance;
}

bool GameManager::Initialize()
{
	m_uiWidth = 500, m_uiHeight = 500;

	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
		return false;
	else if( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) )
		return false;
	else if( TTF_Init() == -1 )
		return false;
	else if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
		return false;
	else
	{
		m_pWindow = SDL_CreateWindow(
			"Touhou Defence", 100, 100, m_uiWidth, m_uiHeight, SDL_WINDOW_SHOWN );
		SDL_Surface * m_surfaceIco = IMG_Load( "./res/image/character_sprite/kedama.png" );	// 아이콘 변경
		SDL_SetWindowIcon( m_pWindow, m_surfaceIco );
		SDL_FreeSurface( m_surfaceIco );
		m_pRenderer = SDL_CreateRenderer( m_pWindow, -1, SDL_RENDERER_ACCELERATED );
		SDL_SetRenderDrawColor( m_pRenderer, 0, 0, 0, 0 );
		SDL_RenderPresent( m_pRenderer );

		m_pFont = TTF_OpenFont( "./res/NanumBarunGothic.ttf", 18 );
		if( m_pFont == NULL )
			return false;
	}

	//기타 로딩작업
	m_vTexture.push_back( new Texture( m_pRenderer, "./res/image/UI/title_bg.png" ) );
	m_vTexture.push_back( new Texture( m_pRenderer, "./res/image/UI/title_letter.png" ) );
	m_vTexture.push_back( new Texture( m_pRenderer, "./res/image/UI/gui_start_idle.png" ) );
	m_vTexture.push_back( new Texture( m_pRenderer, "./res/image/UI/gui_start_hover.png" ) );
	m_vTexture.push_back( new Texture( m_pRenderer, "./res/image/UI/gui_quit_idle.png" ) );
	m_vTexture.push_back( new Texture( m_pRenderer, "./res/image/UI/gui_quit_hover.png" ) );
	m_vTexture.push_back( new Texture( m_pRenderer, "./res/image/UI/character_slot.png" ) );
	m_vTexture.push_back( new Texture( m_pRenderer, "./res/image/UI/base.png" ) );
	m_vTexture.push_back( new Texture( m_pRenderer, "./res/image/UI/town.png" ) );
	m_vTexture.push_back( new Texture( m_pRenderer, "./res/image/UI/gameover.png" ) );
	m_vTexture.push_back( new Texture( m_pRenderer, "./res/image/UI/loading.png" ) );
	m_vTexture.push_back( new Texture( m_pRenderer, "./res/image/UI/end.png" ) );
	m_vTexture.push_back( new Texture( m_pRenderer, "./res/image/UI/ten_25.png" ) );

	m_mStanding[GameManager::MARISA].push_back( new Texture( m_pRenderer, "./res/image/character_standing/marisa_normal.png" ) );
	m_mStanding[GameManager::MARISA].push_back( new Texture( m_pRenderer, "./res/image/character_standing/marisa_smile.png" ) );
	m_mStanding[GameManager::MARISA].push_back( new Texture( m_pRenderer, "./res/image/character_standing/marisa_angry.png" ) );

	m_mStanding[GameManager::NITORI].push_back( new Texture( m_pRenderer, "./res/image/character_standing/nitori_normal.png" ) );
	m_mStanding[GameManager::NITORI].push_back( new Texture( m_pRenderer, "./res/image/character_standing/nitori_smile.png" ) );
	m_mStanding[GameManager::NITORI].push_back( new Texture( m_pRenderer, "./res/image/character_standing/nitori_angry.png" ) );

	m_mStanding[GameManager::KEDAMA].push_back( new Texture( m_pRenderer, "./res/image/character_standing/kedama_normal.png" ) );

	m_mSprite[GameManager::MARISA].push_back( new Texture( m_pRenderer, "./res/image/character_sprite/marisa_idle1.png" ) );
	m_mSprite[GameManager::MARISA].push_back( new Texture( m_pRenderer, "./res/image/character_sprite/marisa_idle2.png" ) );

	m_mSprite[GameManager::NITORI].push_back( new Texture( m_pRenderer, "./res/image/character_sprite/nitori_idle1.png" ) );
	m_mSprite[GameManager::NITORI].push_back( new Texture( m_pRenderer, "./res/image/character_sprite/nitori_idle2.png" ) );

	m_mSprite[GameManager::KEDAMA].push_back( new Texture( m_pRenderer, "./res/image/character_sprite/kedama_idle1.png" ) );
	m_mSprite[GameManager::KEDAMA].push_back( new Texture( m_pRenderer, "./res/image/character_sprite/kedama_idle2.png" ) );

	m_mSprite[GameManager::BULLET].push_back( new Texture( m_pRenderer, "./res/image/object/bullet1.png" ) );
	m_mSprite[GameManager::BULLET].push_back( new Texture( m_pRenderer, "./res/image/object/cucumber.png" ) );

	m_mSprite[GameManager::HP_GAUGE].push_back( new Texture( m_pRenderer, "./res/image/UI/health_base.png" ) );
	m_mSprite[GameManager::HP_GAUGE].push_back( new Texture( m_pRenderer, "./res/image/UI/health_bar.png" ) );

	m_mSprite[GameManager::BUBBLE].push_back( new Texture( m_pRenderer, "./res/image/UI/bubble_1.png" ) );
	m_mSprite[GameManager::BUBBLE].push_back( new Texture( m_pRenderer, "./res/image/UI/bubble_2.png" ) );
	m_mSprite[GameManager::BUBBLE].push_back( new Texture( m_pRenderer, "./res/image/UI/bubble_3.png" ) );
	m_mSprite[GameManager::BUBBLE].push_back( new Texture( m_pRenderer, "./res/image/UI/bubble_4.png" ) );

	m_vTile.push_back( new Texture( m_pRenderer, "./res/image/tile/grass.png" ) );
	m_vTile.push_back( new Texture( m_pRenderer, "./res/image/tile/road.png" ) );

	m_vScene.push_back( new Scene( TITLE, NULL, &GameManager::Scene_Title ) );
	m_vScene.push_back( new Scene( TITLE, NULL, &GameManager::Scene_GameOver ) );
	m_vScene.push_back( new Scene( TITLE, NULL, &GameManager::Scene_GameEnd ) );
	m_vScene.push_back( new Scene( TITLE, NULL, &GameManager::Scene_Loading ) );

	m_pCurrentScene = m_vScene.at(0);

	//Texture * m_pTempTexture = ;
	BUTTON_TEXTURE stTexture;

	stTexture.idle = m_vTexture.at(2);
	stTexture.hover = m_vTexture.at(3);
	GUIButton * m_tempButton = new GUIButton( 187, 250, stTexture, (&GameManager::StartGame), (void*)NULL );
	m_pCurrentScene->AddGUI( m_tempButton );

	stTexture.idle = m_vTexture.at(4);
	stTexture.hover = m_vTexture.at(5);
	m_tempButton = new GUIButton( 187, 330, stTexture, (&GameManager::QuitGame), (void*)NULL );
	m_pCurrentScene->AddGUI( m_tempButton );

	stTexture.idle = m_vTexture.at(GameManager::GAME_OVER);
	stTexture.hover = m_vTexture.at(GameManager::GAME_OVER);
	m_tempButton = new GUIButton( 0, 0, stTexture, (&GameManager::GameOver), (void*)NULL );
	m_vScene.at(1)->AddGUI( m_tempButton );

	stTexture.idle = m_vTexture.at(GameManager::GAME_END);
	stTexture.hover = m_vTexture.at(GameManager::GAME_END);
	m_tempButton = new GUIButton( 0, 0, stTexture, (&GameManager::GameOver), (void*)NULL );
	m_vScene.at(2)->AddGUI( m_tempButton );

	m_bGameFlag = true;
	m_bDialogFlag = false;
	m_bIsStageEnded = false;
	m_bIsEffectShown = false;
	m_bIsAddCharMode = false;
	m_bIsFuncExecuted = false;
	m_uiScore = 0;
	return true;
}

void GameManager::Destroy()
{
	m_vTexture.clear();
	m_lSFX.clear();
	m_lBGM.clear();
	TTF_CloseFont( m_pFont );

	SDL_DestroyRenderer( m_pRenderer );
	SDL_DestroyWindow( m_pWindow );

	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool GameManager::IsGameRunning()
{
	return m_bGameFlag;
}

void GameManager::Work()
{
	Instance()->Event();

	if( Instance()->GetDialogFlag() != true )
		m_pCurrentScene->Work();
}

void GameManager::Event()
{
	while( SDL_PollEvent( &m_stSDLEvent ) != 0 )
	{
		if( m_stSDLEvent.type == SDL_QUIT )
			m_bGameFlag = false;

		if( m_bGameFlag == false )
			break;

		else if( m_stSDLEvent.type == SDL_KEYDOWN )
		{	
			if( m_stSDLEvent.key.keysym.sym == SDLK_PRINTSCREEN )
				ScreenCapture();
			else if( m_stSDLEvent.key.keysym.sym == SDLK_RETURN )
			{
				if( GameManager::Instance()->GetStageEndFlag() == false )
					m_pCurrentScene->m_lDialogOnStart.clear();
				else
					m_pCurrentScene->m_lDialogOnEnd.clear();
				m_bDialogFlag = false;
			}

			/*switch( m_stSDLEvent.key.keysym.sym )
			{

			}*/
		}
		else if( m_stSDLEvent.type == SDL_MOUSEMOTION )
		{
			m_pCurrentScene->CheckButton( m_stSDLEvent.motion.x, m_stSDLEvent.motion.y, false );
		}
		else if( m_stSDLEvent.type == SDL_MOUSEBUTTONDOWN )
		{
			if( m_stSDLEvent.button.button == SDL_BUTTON_LEFT )
			{
				if( GameManager::Instance()->GetDialogFlag() == true )
					m_bDialogFlag = m_pCurrentScene->CheckDialogue();
				else if( GameManager::Instance()->GetAddCharFlag() )
				{
					if(
						( (GameManager::Instance()->GetMap())[0][m_stSDLEvent.motion.y/50][m_stSDLEvent.motion.x/50] == 2 ) ||
						( (GameManager::Instance()->GetMap())[1][m_stSDLEvent.motion.y/50][m_stSDLEvent.motion.x/50] != 0 )
						)
					{
						return;
					}
					m_pCurrentScene->m_vCharacter.push_back( new Character( m_stTempMessage.iData, new BulletShooter( Instance()->GetMapSpriteTexture()->at(GameManager::BULLET).at(m_stTempMessage.iData), 10, 10, 5, false ), (m_stSDLEvent.motion.x/50)*50, (m_stSDLEvent.motion.y/50)*50, 100, 1000, 10 ) );
					m_bIsAddCharMode = false;
				}
				else
					m_pCurrentScene->CheckButton( m_stSDLEvent.button.x, m_stSDLEvent.button.y, true );
				//m_pCurrentScene->
			}
			/*switch( m_stSDLEvent.key.keysym.sym )
			{

			}*/
		}
	}
}

void GameManager::DrawText( std::wstring &_strDisplay, SDL_Color _stColor )
{
	SDL_Surface * m_pFontSurface = TTF_RenderUNICODE_Blended( m_pFont, (Uint16*)_strDisplay.data(), _stColor );
	SDL_Texture * m_pFontTexture = SDL_CreateTextureFromSurface( m_pRenderer, m_pFontSurface );
	SDL_Rect m_stRect;
	m_stRect.h = m_pFontSurface->h;
	m_stRect.w = m_pFontSurface->w;
	m_stRect.x = ( m_uiWidth - m_stRect.w ) / 2;
	m_stRect.y = ( m_uiHeight - m_stRect.h ) / 2 + 50 -1;
	SDL_FreeSurface( m_pFontSurface );
	SDL_RenderCopy( m_pRenderer, m_pFontTexture, NULL, &m_stRect );
	SDL_RenderPresent( m_pRenderer );
	SDL_DestroyTexture( m_pFontTexture );
}

void GameManager::DrawText( std::wstring &_strDisplay, int _iX, int _iY, SDL_Color _stColor )
{
	SDL_Surface * m_pFontSurface = TTF_RenderUNICODE_Blended( m_pFont, (Uint16*)_strDisplay.data(), _stColor );
	SDL_Texture * m_pFontTexture = SDL_CreateTextureFromSurface( m_pRenderer, m_pFontSurface );
	SDL_Rect m_stRect;
	m_stRect.h = m_pFontSurface->h;
	m_stRect.w = m_pFontSurface->w;
	m_stRect.x = _iX;
	m_stRect.y = _iY;
	SDL_FreeSurface( m_pFontSurface );

	if( m_bIsEffectShown == false )
	{
		ShowEffect( FADE_IN, m_pFontTexture, &m_stRect );
		m_bIsEffectShown = true;
	}
	SDL_RenderCopy( m_pRenderer, m_pFontTexture, NULL, &m_stRect );
	//SDL_RenderPresent( m_pRenderer );
	SDL_DestroyTexture( m_pFontTexture );
}

void GameManager::ShowEffect( int _iEffect )
{
	SDL_Rect m_stRect;

	m_stRect.w = Instance()->m_uiWidth;
	m_stRect.h = Instance()->m_uiHeight;
	m_stRect.x = 0;
	m_stRect.y = 0;

	SDL_Surface *m_screenImg = SDL_CreateRGBSurface( 0, m_stRect.w, m_stRect.h, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF );
	SDL_RenderReadPixels( Instance()->GetGlobalRenderer(), NULL, SDL_PIXELFORMAT_RGBA8888, m_screenImg->pixels, m_screenImg->pitch );
	SDL_Texture *m_texture = SDL_CreateTextureFromSurface( Instance()->GetGlobalRenderer(), m_screenImg );
	SDL_FreeSurface( m_screenImg );

	SDL_Texture *m_effect = SDL_CreateTexture( Instance()->GetGlobalRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Instance()->m_uiWidth, Instance()->m_uiHeight );
	SDL_SetRenderTarget( Instance()->GetGlobalRenderer(), m_effect );

	SDL_RenderClear( Instance()->GetGlobalRenderer() );

	SDL_SetRenderDrawColor( Instance()->GetGlobalRenderer(), 0x00, 0x00, 0x00, 0xFF );
	SDL_RenderFillRect( Instance()->GetGlobalRenderer(), &m_stRect );

	SDL_SetRenderTarget( Instance()->GetGlobalRenderer(), NULL );

	switch( _iEffect )
	{
	case FADE_IN:
		for( int i=255; i>=0; i-- )
		{
			SDL_RenderClear( Instance()->GetGlobalRenderer() );
			SDL_SetTextureAlphaMod( m_effect, i );
			SDL_SetTextureBlendMode( m_effect, SDL_BLENDMODE_BLEND );
			SDL_RenderCopy( Instance()->GetGlobalRenderer(), m_texture, NULL, NULL );
			SDL_RenderCopy( Instance()->GetGlobalRenderer(), m_effect, NULL, NULL );
			SDL_RenderPresent( Instance()->GetGlobalRenderer() );
			SDL_Delay( 5 );
		}
		break;
	case FADE_OUT:
		for( int i=0; i<256; i++ )
		{
			SDL_RenderClear( Instance()->GetGlobalRenderer() );
			SDL_SetTextureAlphaMod( m_effect, i );
			SDL_SetTextureBlendMode( m_effect, SDL_BLENDMODE_BLEND );
			SDL_RenderCopy( Instance()->GetGlobalRenderer(), m_texture, NULL, NULL );
			SDL_RenderCopy( Instance()->GetGlobalRenderer(), m_effect, NULL, NULL );
			SDL_RenderPresent( Instance()->GetGlobalRenderer() );
			SDL_Delay( 5 );
		}
		break;
	}
}

void GameManager::ShowEffect( int _iEffect, SDL_Texture *_pSrcTexture )
{
	SDL_Rect m_stRect;

	m_stRect.w = Instance()->m_uiWidth;
	m_stRect.h = Instance()->m_uiHeight;
	m_stRect.x = 0;
	m_stRect.y = 0;

	SDL_Surface *m_screenImg = SDL_CreateRGBSurface( 0, m_stRect.w, m_stRect.h, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF );
	SDL_RenderReadPixels( Instance()->GetGlobalRenderer(), NULL, SDL_PIXELFORMAT_RGBA8888, m_screenImg->pixels, m_screenImg->pitch );
	SDL_Texture *m_texture = SDL_CreateTextureFromSurface( Instance()->GetGlobalRenderer(), m_screenImg );
	SDL_FreeSurface( m_screenImg );

	SDL_RenderClear( Instance()->GetGlobalRenderer() );

	SDL_SetRenderDrawColor( Instance()->GetGlobalRenderer(), 0x00, 0x00, 0x00, 0xFF );
	SDL_RenderFillRect( Instance()->GetGlobalRenderer(), &m_stRect );

	SDL_SetRenderTarget( Instance()->GetGlobalRenderer(), NULL );

	switch( _iEffect )
	{
	case FADE_IN:
		for( int i=0; i<256; i+=2 )
		{
			SDL_RenderClear( Instance()->GetGlobalRenderer() );
			SDL_SetTextureAlphaMod( _pSrcTexture, i );
			SDL_SetTextureBlendMode( _pSrcTexture, SDL_BLENDMODE_BLEND );
			SDL_RenderCopy( Instance()->GetGlobalRenderer(), m_texture, NULL, NULL );
			SDL_RenderCopy( Instance()->GetGlobalRenderer(), _pSrcTexture, NULL, NULL );
			SDL_RenderPresent( Instance()->GetGlobalRenderer() );
			SDL_Delay( 1 );
		}
		break;
	case FADE_OUT:
		for( int i=256; i<0; i+=2 )
		{
			SDL_RenderClear( Instance()->GetGlobalRenderer() );
			SDL_SetTextureAlphaMod( _pSrcTexture, i );
			SDL_SetTextureBlendMode( _pSrcTexture, SDL_BLENDMODE_BLEND );
			SDL_RenderCopy( Instance()->GetGlobalRenderer(), m_texture, NULL, NULL );
			SDL_RenderCopy( Instance()->GetGlobalRenderer(), _pSrcTexture, NULL, NULL );
			SDL_RenderPresent( Instance()->GetGlobalRenderer() );
			SDL_Delay( 1 );
		}
		break;
	}
}

void GameManager::ShowEffect( int _iEffect, SDL_Texture *_pSrcTexture, SDL_Rect *_stpRect )
{
	SDL_Rect m_stRect;

	m_stRect.w = Instance()->m_uiWidth;
	m_stRect.h = Instance()->m_uiHeight;
	m_stRect.x = 0;
	m_stRect.y = 0;

	SDL_Surface *m_screenImg = SDL_CreateRGBSurface( 0, m_stRect.w, m_stRect.h, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF );
	SDL_RenderReadPixels( Instance()->GetGlobalRenderer(), NULL, SDL_PIXELFORMAT_RGBA8888, m_screenImg->pixels, m_screenImg->pitch );
	SDL_Texture *m_texture = SDL_CreateTextureFromSurface( Instance()->GetGlobalRenderer(), m_screenImg );
	SDL_FreeSurface( m_screenImg );

	SDL_RenderClear( Instance()->GetGlobalRenderer() );

	SDL_SetRenderDrawColor( Instance()->GetGlobalRenderer(), 0x00, 0x00, 0x00, 0xFF );
	SDL_RenderFillRect( Instance()->GetGlobalRenderer(), &m_stRect );

	SDL_SetRenderTarget( Instance()->GetGlobalRenderer(), NULL );

	switch( _iEffect )
	{
	case FADE_IN:
		for( int i=0; i<256; i+=2 )
		{
			SDL_RenderClear( Instance()->GetGlobalRenderer() );
			SDL_SetTextureAlphaMod( _pSrcTexture, i );
			SDL_SetTextureBlendMode( _pSrcTexture, SDL_BLENDMODE_BLEND );
			SDL_RenderCopy( Instance()->GetGlobalRenderer(), m_texture, NULL, NULL );
			SDL_RenderCopy( Instance()->GetGlobalRenderer(), _pSrcTexture, NULL, _stpRect );
			SDL_RenderPresent( Instance()->GetGlobalRenderer() );
			SDL_Delay( 1 );
		}
		break;
	case FADE_OUT:
		/*for( int i=0; i<256; i++ )
		{
			SDL_RenderClear( Instance()->GetGlobalRenderer() );
			SDL_SetTextureAlphaMod( m_effect, i );
			SDL_SetTextureBlendMode( m_effect, SDL_BLENDMODE_BLEND );
			SDL_RenderCopy( Instance()->GetGlobalRenderer(), m_texture, NULL, NULL );
			SDL_RenderCopy( Instance()->GetGlobalRenderer(), m_effect, NULL, NULL );
			SDL_RenderPresent( Instance()->GetGlobalRenderer() );
			SDL_Delay( 5 );
		}*/
		break;
	}
}

void GameManager::ShowEffect( int _iEffect, SDL_Texture *_pSrcTexture, SDL_Texture *_pDstTexture )
{
	switch( _iEffect )
	{
	case FADE_IN:
		for( int i=0; i<256; i++ )
		{
			SDL_RenderClear( Instance()->GetGlobalRenderer() );
			SDL_SetTextureAlphaMod( _pSrcTexture, i );
			SDL_SetTextureBlendMode( _pSrcTexture, SDL_BLENDMODE_BLEND );
			SDL_RenderCopy( Instance()->GetGlobalRenderer(), _pDstTexture, NULL, NULL );
			SDL_RenderCopy( Instance()->GetGlobalRenderer(), _pSrcTexture, NULL, NULL );
			SDL_RenderPresent( Instance()->GetGlobalRenderer() );
			SDL_Delay( 5 );
		}
		break;
	case FADE_OUT:

		break;
	}
}