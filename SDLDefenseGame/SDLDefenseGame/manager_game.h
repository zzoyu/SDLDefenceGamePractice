#ifndef __MANAGER_GAME_H__
#define __MANAGER_GAME_H__

//===========================================
// ¡á °ÔÀÓ ¸Å´ÏÀú Å¬·¡½º ( Goddamn Singleton )
//===========================================

#include "Texture.h"	// ºô¾î¸ÔÀ» ÅØ½ºÃÄ Å¬·¡½º
#include "Sound.h"		// ºô¾î¸ÔÀ» »ç¿îµå Å¬·¡½º
#include "Scene.h"		// ºô¾î¸ÔÀ» ½ºÅ×ÀÌÁöÁ¤º¸
#include "Character.h"
#include "Enemy.h"
#include <SDL.h>		// ºô¾î¸ÔÀ» SDL
#include <SDL_ttf.h>	// ºô¾î¸ÔÀ» Æ®·çÅ¸ÀÔÆùÆ®
#include <list>			// ºô¾î¸ÔÀ» ¸®½ºÆ®
#include <vector>		// ºô¾î¸ÔÀ» º¤ÅÍ
#include <string>		// ºô¾î¸ÔÀ» ¹®ÀÚ¿­
#include <Windows.h>	// ¾¾¹ß!!!!
#include <time.h>	// ¾¾¹ß!!!!
#include <locale>	// ¸ÁÇÒ À¯´ÏÄÚµå!!! ºô¾î¸ÔÀ» ÇÑ±Û!!!
#include <iostream>
#include <sstream>
#include <map>

class GameManager
{
private:
	enum {
		FADE_IN,
		FADE_OUT
	} EFFECT;

	enum {
		TITLE,
		IN_GAME
	} SCENE_TYPE;

	enum
	{
		LAND,
		ROAD,
		WATER,
		SNOW,
		ROCK
	} TILE_TYPE;

	static GameManager * m_pInstance;

	bool m_bGameFlag;
	bool m_bDialogFlag;
	bool m_bIsStageEnded;
	bool m_bIsEffectShown;
	bool m_bIsAddCharMode;
	bool m_bIsFuncExecuted;
	
	EVENT_MESSAGE m_stTempMessage;

	unsigned int m_uiWidth;
	unsigned int m_uiHeight;

	int m_iCurrentSceneIndex;

	SDL_Window * m_pWindow;
	SDL_Surface * m_pScreenSurface;
	SDL_Renderer * m_pRenderer;

	Scene * m_pCurrentScene;

	std::vector<Scene *> m_vScene;
	std::vector<Texture *> m_vTexture;
	std::vector<Texture *> m_vTile;
	std::map<int, std::vector<Texture *>> m_mStanding;
	std::map<int, std::vector<Texture *>> m_mSprite;
	EnemyCreator *m_pEnemyCreator;

	std::list<SFX *> m_lSFX;
	std::list<BGM *> m_lBGM;
	TTF_Font * m_pFont;
	SDL_Event m_stSDLEvent;

	unsigned int m_uiScore;

public:
	static GameManager* Instance();

	enum
	{
		MARISA,
		NITORI,
		KEDAMA,
		BULLET,
		HP_GAUGE,
		BUBBLE
	} SPRITE;

	enum
	{
		TITLE_BG,
		TITLE_TEXT,
		START_IDLE,
		START_HOVER,
		QUIT_IDLE,
		QUIT_HOVER,
		SLOT,
		QUOTE_BASE,
		TOWN,
		GAME_OVER,
		LOADING,
		GAME_END,
		POINT
	} GRAPHIC;

	enum
	{
		NORMAL,
		SMILE,
		ANGRY
	} EMOTION;

	enum
	{
		SCENE_TITLE,
		SCENE_GAMEOVER,
		SCENE_GAMEEND,
		SCENE_LOADING,
		SCENE_SCENE
	} SCENE;

	bool Initialize();
	void Destroy();
	bool IsGameRunning();
	void Work();
	void Event();
	void DrawText( std::wstring &_strDisplay, SDL_Color _stColor );
	void DrawText( std::wstring &_strDisplay, int _iX, int _iY, SDL_Color _stColor );
	void ShowEffect( int _iEffect );
	void ShowEffect( int _iEffect, SDL_Texture *_pSrcTexture );
	void ShowEffect( int _iEffect, SDL_Texture *_pSrcTexture, SDL_Rect *_stpRect );
	void ShowEffect( int _iEffect, SDL_Texture *_pSrcTexture, SDL_Texture *_pDstTexture );

	SDL_Renderer *GetGlobalRenderer()
	{
		return m_pRenderer;
	}

	EnemyCreator *GetEnemyCreator()
	{
		return m_pEnemyCreator;
	}

	std::vector<Scene *> *GetVectorScene()
	{
		return &m_vScene;
	}

	int GetCurrentSceneIndex()
	{
		return m_iCurrentSceneIndex;
	}

	std::vector<Texture *> *GetVectorUITexture()
	{
		return &m_vTexture;
	}

	std::vector<Texture *> *GetVectorTileTexture()
	{
		return &m_vTile;
	}

	std::map<int, std::vector<Texture *>> *GetMapStandingTexture()
	{
		return &m_mStanding;
	}

	std::map<int, std::vector<Texture *>> *GetMapSpriteTexture()
	{
		return &m_mSprite;
	}

	void SetGameFlag( bool _bFlag )
	{
		m_bGameFlag = _bFlag;
	}

	void SetDialogFlag( bool _bFlag )
	{
		m_bDialogFlag = _bFlag;
	}

	bool GetDialogFlag()
	{
		return m_bDialogFlag;
	}

	void SetStageEndFlag( bool _bFlag )
	{
		m_bIsStageEnded = _bFlag;
	}

	void SetEffectFlag( bool _bFlag )
	{
		m_bIsEffectShown = _bFlag;
	}

	bool GetEffectFlag()
	{
		return m_bIsEffectShown;
	}

	bool GetStageEndFlag()
	{
		return m_bIsStageEnded;
	}

	bool GetAddCharFlag()
	{
		return m_bIsAddCharMode;
	}

	void SetAddCharFlag( bool _bIsAddCharMode )
	{
		m_bIsAddCharMode = _bIsAddCharMode;
	}

	bool GetFuncExecutedFlag()
	{
		return m_bIsFuncExecuted;
	}

	void SetFuncExecutedFlag( bool _bIsFuncExecuted )
	{
		m_bIsFuncExecuted = _bIsFuncExecuted;
	}

	int (*GetMap())[9][10]
	{
		return m_pCurrentScene->GetMap();
	}

	void ScreenCapture()
	{
		int i = 0;
		time_t m_stTime;
		struct tm m_stTm;
		char m_cBuffer[30];
		char m_cTime[20];
		HANDLE m_hFile;

		SDL_Surface *m_screenSurface = SDL_CreateRGBSurface( 0, Instance()->m_uiWidth, Instance()->m_uiHeight, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF );
		SDL_RenderReadPixels( Instance()->GetGlobalRenderer(), NULL, SDL_PIXELFORMAT_RGBA8888, m_screenSurface->pixels, m_screenSurface->pitch );
		
		time( &m_stTime );
		localtime_s( &m_stTm, &m_stTime );
		strftime( m_cTime, sizeof(m_cBuffer), "%Y%m%d-%H%M%S", &m_stTm );

		while( true )
		{
			sprintf_s( m_cBuffer, "%s_%d.png", m_cTime, i );

			if( (m_hFile = CreateFile( m_cBuffer, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL )) == INVALID_HANDLE_VALUE )	// ÆÄÀÏ ¾øÀ»½Ã »ý¼º
			{
				SDL_SaveBMP( m_screenSurface, m_cBuffer );
				break;
			}
			CloseHandle( m_hFile );
			i++;
		}

		SDL_FreeSurface( m_screenSurface );
	}

	void StartGame( EVENT_MESSAGE )
	{
		ShowEffect( FADE_OUT );
		printf( "GUI TEST\n" );
		Instance()->SetCurrentScene( GameManager::SCENE_LOADING );
		Instance()->SetFuncExecutedFlag( false );
		Instance()->SetEffectFlag( false );
	}

	void QuitGame( EVENT_MESSAGE )
	{
		ShowEffect( FADE_OUT );
		printf( "QUIT\n" );
		Instance()->SetGameFlag( false );
	}

	void SetMessageData( EVENT_MESSAGE _stMessage )
	{
		m_stTempMessage = _stMessage;
	}

	EVENT_MESSAGE *GetMessageData()
	{
		return &m_stTempMessage;
	}

	void AddCharacter( EVENT_MESSAGE _stMessage )
	{
		Instance()->SetAddCharFlag( true );
		Instance()->SetMessageData( _stMessage );
	}

	void LoadScene()
	{
		int m_iTempMap[2][9][10];
		FILE * m_hFile;
		int m_iTemp;
		wchar_t m_cBuffer[256];
		std::wstring m_strTemp, m_strName, m_strEmotion, m_strQuote;
		Texture * m_pTexture;
		std::wostringstream m_strStream;
		GUIDialogue * m_tempDialogue;
		Scene::START_INFO m_stTempInfo;
		setlocale( LC_ALL, "korean" );
		int i = 1;

		if( m_vScene.size() > GameManager::SCENE_SCENE )
			m_vScene.erase( m_vScene.begin()+GameManager::SCENE_SCENE, m_vScene.end() );
		while( true )
		{
			m_strStream << TEXT("scene") << i << TEXT(".dat");
			m_strTemp = m_strStream.str();

			_wfopen_s( &m_hFile, m_strTemp.c_str(), L"r, ccs=UNICODE" );

			if( m_hFile != NULL )
			{
				fseek( m_hFile, 0-(sizeof(m_iTempMap)+sizeof(Scene::START_INFO)), SEEK_END );
				fread( &m_stTempInfo, sizeof(m_stTempInfo), 1, m_hFile );
				fread( m_iTempMap, sizeof(m_iTempMap), 1, m_hFile );
				fseek( m_hFile, 0, SEEK_SET );

				m_vScene.push_back( new Scene( IN_GAME, NULL, (int*)&m_iTempMap, m_stTempInfo, &GameManager::Scene_Map ) );

				while( true )
				{
					fgetws( m_cBuffer, 256, m_hFile );
					m_strTemp = m_cBuffer;

					if( m_strTemp.find( L"END" ) == 0 )
						break;

					m_iTemp = m_strTemp.find( ' ' )+1;
					m_strName = m_strTemp.substr( m_iTemp, m_strTemp.find( '(' )-m_iTemp );

					m_iTemp = m_strTemp.find( '(' )+1;
					m_strEmotion = m_strTemp.substr( m_iTemp, m_strTemp.find( ')' )-m_iTemp );

					m_iTemp = m_strTemp.find( ':', 2 )+1;
					m_strQuote = m_strTemp.substr( m_iTemp, m_strTemp.length()-m_iTemp-1 );

					m_pTexture = NULL;

					if( m_strName == L"marisa" )
					{
						if( m_strEmotion == L"normal" )
							m_pTexture = m_mStanding[GameManager::MARISA].at(GameManager::NORMAL);
						else if( m_strEmotion == L"smile" )
							m_pTexture = m_mStanding[GameManager::MARISA].at(GameManager::SMILE);
						else if( m_strEmotion == L"angry" )
							m_pTexture = m_mStanding[GameManager::MARISA].at(GameManager::ANGRY);
						m_tempDialogue = new GUIDialogue(
							std::wstring(L"¸¶¸®»ç"), m_strQuote,
							m_vTexture.at(7), m_pTexture,
							0, 380, 300, 85
							);
					}
					else if( m_strName == L"nitori" )
					{
						if( m_strEmotion == L"normal" )
							m_pTexture = m_mStanding[GameManager::NITORI].at(GameManager::NORMAL);
						else if( m_strEmotion == L"smile" )
							m_pTexture = m_mStanding[GameManager::NITORI].at(GameManager::SMILE);
						else if( m_strEmotion == L"angry" )
							m_pTexture = m_mStanding[GameManager::NITORI].at(GameManager::ANGRY);
						m_tempDialogue = new GUIDialogue(
							std::wstring(L"´ÏÅä¸®"), m_strQuote,
							m_vTexture.at(7), m_pTexture,
							0, 380, 300, 85
							);
					}
					else if( m_strName == L"kedama" )
						m_tempDialogue = new GUIDialogue(
						std::wstring(L"¸ð¿Ás"), m_strQuote,
						m_vTexture.at(7), m_mStanding[GameManager::KEDAMA].at(GameManager::NORMAL),
						0, 380, 150, 85
						);

					if( m_strTemp.at(0) == 'S' )
						((Scene *)(m_vScene.at(i+GameManager::SCENE_SCENE-1)))->AddGUI( 0, m_tempDialogue );
					else
						((Scene *)(m_vScene.at(i+GameManager::SCENE_SCENE-1)))->AddGUI( 1, m_tempDialogue );
				}
				fclose( m_hFile );

				EVENT_MESSAGE m_stTempMessage;
				BUTTON_TEXTURE stTexture;
				GUIButton * m_tempButton;
				m_stTempMessage.iType = 0;
				m_stTempMessage.iData = 0;

				stTexture.idle = m_mSprite[GameManager::MARISA].at(0);
				stTexture.hover = m_mSprite[GameManager::MARISA].at(1);
				m_tempButton = new GUIButton( 10, 440, stTexture, (&GameManager::AddCharacter), &m_stTempMessage );
				m_vScene.at(i+GameManager::SCENE_SCENE-1)->AddGUI( m_tempButton );

				m_stTempMessage.iData = 1;

				stTexture.idle = m_mSprite[GameManager::NITORI].at(0);
				stTexture.hover = m_mSprite[GameManager::NITORI].at(1);
				m_tempButton = new GUIButton( 60, 440, stTexture, (&GameManager::AddCharacter), &m_stTempMessage );
				m_vScene.at(i+GameManager::SCENE_SCENE-1)->AddGUI( m_tempButton );

				ENEMY_INFO m_stEnemyInfo;
				m_stEnemyInfo.iNumber = GameManager::KEDAMA;
				m_stEnemyInfo.iHP = 50;
				m_stEnemyInfo.iSpeed = 10;

				m_pEnemyCreator = new EnemyCreator( m_stTempInfo.iDirection, m_stTempInfo.iX, m_stTempInfo.iY );
				m_pEnemyCreator->AddEnemyInfo( m_stEnemyInfo );

				i++;
			}
			else
				break;
		}
	}

	SDL_Event *GetSDLEvent()
	{
		return &m_stSDLEvent;
	}

	Scene *GetCurrentScene()
	{
		return m_pCurrentScene;
	}

	void SetCurrentScene( int _iIndex )
	{
		m_pCurrentScene = m_vScene.at( _iIndex );
		m_iCurrentSceneIndex = _iIndex;
	}

	void Scene_Title()
	{
		Texture * m_temp0 = Instance()->GetVectorUITexture()->at(0);
		Texture * m_temp1 = Instance()->GetVectorUITexture()->at(1);

		if( Instance()->GetEffectFlag() == false )
		{
			m_temp0->Render( Instance()->GetGlobalRenderer() );
			ShowEffect( FADE_IN );
			ShowEffect( FADE_IN, m_temp1->GetTexture(), m_temp0->GetTexture() );
		}

		Instance()->SetEffectFlag( true );

		m_temp0->Render( Instance()->GetGlobalRenderer() );
		m_temp1->Render( Instance()->GetGlobalRenderer() );
	}

	void Scene_Loading()
	{
		Texture * m_temp0 = Instance()->GetVectorUITexture()->at(GameManager::LOADING);
		
		SDL_RenderClear( Instance()->GetGlobalRenderer() );
		m_temp0->Render( Instance()->GetGlobalRenderer() );

		if( Instance()->GetEffectFlag() == false )
		{
			ShowEffect( FADE_IN );
			Instance()->LoadScene();
		}

		Instance()->SetCurrentScene( GameManager::SCENE_SCENE );
	}

	void Scene_GameOver()
	{
		Texture * m_temp0 = Instance()->GetVectorUITexture()->at(GameManager::GAME_OVER);
		
		SDL_RenderClear( Instance()->GetGlobalRenderer() );
		m_temp0->Render( Instance()->GetGlobalRenderer() );

		if( Instance()->GetEffectFlag() == false )
		{
			ShowEffect( FADE_IN );
		}

		GameManager::Instance()->SetFuncExecutedFlag( true );
	}

	void Scene_GameEnd()
	{
		Texture * m_temp0 = Instance()->GetVectorUITexture()->at(GameManager::GAME_END);
		
		SDL_RenderClear( Instance()->GetGlobalRenderer() );
		m_temp0->Render( Instance()->GetGlobalRenderer() );

		if( Instance()->GetEffectFlag() == false )
		{
			ShowEffect( FADE_IN );
		}

		GameManager::Instance()->SetFuncExecutedFlag( true );
	}

	void GameOver( EVENT_MESSAGE _stMessage )
	{
		ShowEffect( FADE_OUT );
		Instance()->SetCurrentScene( GameManager::SCENE_TITLE );
		Instance()->SetFuncExecutedFlag( false );
	}

	void Scene_Map()
	{
		Instance()->SetDialogFlag( true );

		GameManager::Instance()->SetFuncExecutedFlag( true );
	}
};

#endif