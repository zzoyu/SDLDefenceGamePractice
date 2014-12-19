#ifndef __SCENE_H__
#define __SCENE_H__

#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>
#include <list>
#include <iomanip>

#include "GUIButton.h"
#include "GUIDialogue.h"
#include "Character.h"
#include "Enemy.h"
#include "Timer.h"

class Scene
{
private:
	int m_iSceneType;	// GameManager�� SCENE enum ����
	bool m_bFunctionFlag;	// �Լ� ����?

	unsigned int m_uiScore;
	Timer *m_tStart, *m_tClear, *m_tCreate;

	int m_iHP;

	Mix_Music * m_pBGM;	// Background Music
	
	std::vector<GUIButton *> m_vButton;	// Custon GUI Buttons

	int m_iMap[2][9][10];

	void ( GameManager::*m_fp )();	// Scene �� �Լ�

	//std::list<Friendly> m_lFriendly;	// Friendly Character List
	//std::list<Enemy> m_lEnemy;	// Enemy Character List

public:
	typedef struct _startInfo
	{
		int iX;
		int iY;
		int iDirection;	// ��(1)/��(2)/��(3)/��(4)
	} START_INFO;
	START_INFO m_stStartInfo;

	std::vector<Character *> m_vCharacter;
	std::vector<Enemy *> m_vEnemy;
	std::vector<Bullet *> m_vBullet;

	std::list<GUIDialogue *> m_lDialogOnStart;	// ��� ���
	std::list<GUIDialogue *> m_lDialogOnEnd;	// ��� ���

	Scene( int _iSceneType, Mix_Music * _pBGM, int *_iMap, START_INFO _stInfo, void( GameManager::*_fp )() )
	{
		m_iSceneType = _iSceneType;
		m_pBGM = _pBGM;
		if( _iMap )
			memcpy( &m_iMap, _iMap, sizeof( m_iMap ) );
		m_stStartInfo = _stInfo;
		m_fp = _fp;
		m_bFunctionFlag = true;

		m_iHP = 100;
		m_uiScore = 500;

		m_tStart = new Timer( 10000 );
		m_tClear = new Timer( 120000 );
		m_tCreate = new Timer( 1500 );
	}

	Scene( int _iSceneType, Mix_Music * _pBGM, void( GameManager::*_fp )() )
	{
		m_iSceneType = _iSceneType;
		m_pBGM = _pBGM;
		m_fp = _fp;
		m_bFunctionFlag = true;

		m_iHP = 100;
	}

	~Scene()
	{
		m_vButton.clear();
	}

	void Work();

	int (*GetMap())[9][10]
	{
		return m_iMap;
	}

	int GetSceneType()
	{
		return m_iSceneType;
	}

	void AddGUI( GUIButton *_Button )
	{
		m_vButton.push_back( _Button );
	}

	void AddGUI( int _iType, GUIDialogue *_Dialogue )
	{
		if( _iType == 0 )
			m_lDialogOnStart.push_back( _Dialogue );
		else
			m_lDialogOnEnd.push_back( _Dialogue );
	}

	void CheckButton( int _iX, int _iY, bool _bIsClicked );
	bool CheckDialogue();
	void Render( SDL_Renderer * _pRenderer );
	void RenderDialogue( SDL_Renderer * _pRenderer, int _iType );

	
};

#endif