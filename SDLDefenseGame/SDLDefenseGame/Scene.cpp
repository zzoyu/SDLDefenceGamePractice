#include "Scene.h"
#include "manager_game.h"

void Scene::CheckButton( int _iX, int _iY, bool _bIsClicked )
{
	for( std::vector<GUIButton*>::iterator i = m_vButton.begin();
		i != m_vButton.end(); i++ )
	{
		if( (*i)->Check( _iX, _iY ) )
		{
			if( _bIsClicked )
				(*i)->Work();
			else
				(*i)->SetHover( true );
		}
		else
			(*i)->SetHover( false );
	}
}

bool Scene::CheckDialogue()
{
	std::list<GUIDialogue*>::iterator i;
	std::list<GUIDialogue*> * m_pList;

	GameManager::Instance()->SetEffectFlag( false );

	if( GameManager::Instance()->GetStageEndFlag() == false )
	{
		i = m_lDialogOnStart.begin();
		m_pList = &m_lDialogOnStart;
	}
	else
	{
		i = m_lDialogOnEnd.begin();
		m_pList = &m_lDialogOnEnd;
	}

	if( (*i)->GetVisible() )
		m_pList->pop_front();

	if( m_pList->size() == 0 )
		return false;
	else
		return true;
}

void Scene::Work()
{
	static DWORD m_dFlag = 0, m_dLastShot= 0;

	if( GameManager::Instance()->GetFuncExecutedFlag() == false )
		if( m_fp )
		{
			((GameManager* const)this->*m_fp)();
		}

	if( m_iSceneType )
	{
		if( m_iHP <= 0 )
		{
			GameManager::Instance()->SetCurrentScene( GameManager::SCENE_GAMEOVER );
			GameManager::Instance()->SetFuncExecutedFlag( false );
			GameManager::Instance()->SetEffectFlag( false );
			return;
		}
		if( m_tClear->Check() )
		{
			GameManager::Instance()->SetStageEndFlag( true );
			GameManager::Instance()->SetDialogFlag( true );
		}
		else if( GameManager::Instance()->GetStageEndFlag() && !GameManager::Instance()->GetDialogFlag() )
		{
			if( GameManager::Instance()->GetVectorScene()->size()-1 == GameManager::Instance()->GetCurrentSceneIndex() )
			{
				GameManager::Instance()->SetEffectFlag( false );
				GameManager::Instance()->SetCurrentScene( GameManager::SCENE_GAMEEND );
			}
			else
				GameManager::Instance()->SetCurrentScene( GameManager::Instance()->GetCurrentSceneIndex()+1 );
		}

		for( unsigned int i=0; i<m_vBullet.size(); i++ )
		{
			if( m_vBullet.at(i)->Check() )
			{
				m_vBullet.erase( m_vBullet.begin()+i );
				i--;
				continue;
			}

			for( unsigned int j=0; j<m_vEnemy.size(); j++ )
			{
				if( m_vBullet.at(i)->Check( m_vEnemy.at(j)->GetCenterX(), m_vEnemy.at(j)->GetCenterY(), 25 ) )
				{
					m_vEnemy.at(j)->Attack( m_vBullet.at(i)->m_iDamage );
					if( m_vEnemy.at(j)->Check() )
					{
						m_vEnemy.erase( m_vEnemy.begin()+j );
						j--;
					}
					m_vBullet.erase( m_vBullet.begin()+i );
					i--;
					break;
				}
			}
		}

		if( GameManager::Instance()->GetDialogFlag() == true )
		{
			m_tStart->Disable();
			m_tClear->Disable();
			m_tCreate->Disable();
			printf( "123\n" );
			return;
		}
		else
		{
			if( m_tStart->IsDisabled() )
				m_tStart->Renew();
			if( m_tClear->IsDisabled() )
				m_tClear->Renew();
		}

		if( m_tStart->Check() == true )
		{
			m_tCreate->Renew();
		}

		if( m_tCreate->Check() )
		{
			m_vEnemy.push_back( GameManager::Instance()->GetEnemyCreator()->CreateEnemy( 0 ) );
			m_tCreate->Renew();
		}

		for( std::vector<Bullet*>::iterator i = m_vBullet.begin();
		i != m_vBullet.end(); i++ )
			(*i)->Move();

		for( unsigned int i=0; i<m_vEnemy.size(); i++ )
		{
			if( m_vEnemy.at(i)->Move( m_iMap ) )
			{
				m_iHP -= 25;

				m_vEnemy.erase( m_vEnemy.begin()+i );
				i--;
			}
		}

		for( std::vector<Character*>::iterator i = m_vCharacter.begin();
		i != m_vCharacter.end(); i++ )
		{
			for( unsigned int j=0; j<m_vEnemy.size(); j++ )
			{
				if( (*i)->Check( m_vEnemy.at(j)->GetCenterX(), m_vEnemy.at(j)->GetCenterY(), 50 ) )
				{
					if( (*i)->Check() )
						m_vBullet.push_back((*i)->Shoot( m_vEnemy.at(j)->GetCenterX(), m_vEnemy.at(j)->GetCenterY() ));
					//m_vBullet.push_back((*i)->Shoot( 0, 0 ));
				}
			}
		}
	}
}

void Scene::Render( SDL_Renderer * _pRenderer )
{
	if( m_iSceneType )
	{
		for( int i=0; i<9; i++ )
			for( int j=0; j<10; j++ )
				GameManager::Instance()->GetVectorTileTexture()->at( m_iMap[0][i][j]-1 )->Render( _pRenderer, j*50, i*50 );

		for( std::vector<Character*>::iterator i = m_vCharacter.begin();
		i != m_vCharacter.end(); i++ )
		{
			(*i)->Render();
		}
		for( std::vector<Enemy*>::iterator i = m_vEnemy.begin();
		i != m_vEnemy.end(); i++ )
		{
			(*i)->Render();
		}
		for( std::vector<Bullet*>::iterator i = m_vBullet.begin();
		i != m_vBullet.end(); i++ )
		{
			(*i)->Render();
		}
		GameManager::Instance()->GetVectorUITexture()->at( GameManager::SLOT )->Render( _pRenderer );
		GameManager::Instance()->GetVectorUITexture()->at( GameManager::TOWN )->Render( _pRenderer, 500-130, 450 );
		if( m_iHP > 75 )
			GameManager::Instance()->GetMapSpriteTexture()->at( GameManager::BUBBLE ).at(0)->Render( _pRenderer, 500-130-40, 450 );
		else if( m_iHP > 50 )
			GameManager::Instance()->GetMapSpriteTexture()->at( GameManager::BUBBLE ).at(1)->Render( _pRenderer, 500-130-40, 450 );
		else if( m_iHP > 25 )
			GameManager::Instance()->GetMapSpriteTexture()->at( GameManager::BUBBLE ).at(2)->Render( _pRenderer, 500-130-40, 450 );
		else if( m_iHP > 0 )
			GameManager::Instance()->GetMapSpriteTexture()->at( GameManager::BUBBLE ).at(3)->Render( _pRenderer, 500-130-40, 450 );
	}

	for( std::vector<GUIButton*>::iterator i = m_vButton.begin();
		i != m_vButton.end(); i++ )
	{
		(*i)->Render( _pRenderer );
	}

	if( GameManager::Instance()->GetAddCharFlag() )
	{
		GameManager::Instance()->GetMapSpriteTexture()->at(GameManager::Instance()->GetMessageData()->iData).at(0)->Render( _pRenderer, (GameManager::Instance()->GetSDLEvent()->motion.x/50)*50, (GameManager::Instance()->GetSDLEvent()->motion.y/50)*50, 127 );
	}

	if( GameManager::Instance()->GetDialogFlag() )
		GameManager::Instance()->GetCurrentScene()->RenderDialogue( _pRenderer, (int)GameManager::Instance()->GetStageEndFlag() );
	else if( GameManager::Instance()->GetCurrentScene()->GetSceneType() != 0 )
	{
		SDL_Color m_stColor = { 255, 255, 255 };
		std::wostringstream m_streamTemp;

		if( !m_tStart )
			return;
		m_streamTemp << std::setfill(L'0') << std::setw(2) << m_tClear->GetRemainTime()/1000/60 << L":" << std::setfill(L'0') << std::setw(2) << m_tClear->GetRemainTime()/1000%60;

		GameManager::Instance()->DrawText( m_streamTemp.str(), 230, 10, m_stColor );
	}

	SDL_RenderPresent( _pRenderer );
}
void Scene::RenderDialogue( SDL_Renderer * _pRenderer, int _iType )
{
	std::list<GUIDialogue*>::iterator i;

	if( _iType == 0 )
		i = m_lDialogOnStart.begin();
	else
		i = m_lDialogOnEnd.begin();

	if( (*i)->GetVisible() )
		(*i)->Render( _pRenderer );
}