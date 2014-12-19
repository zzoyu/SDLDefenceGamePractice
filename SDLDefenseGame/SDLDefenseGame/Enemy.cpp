#include "Enemy.h"
#include "manager_game.h"

Enemy::Enemy( int _iNumber, int _iX, int _iY, int _iHP, int _iSpeed, int _iDirection )
{
	m_pTexture[0] = GameManager::Instance()->GetMapSpriteTexture()->at(_iNumber).at(0);
	m_pTexture[1] = GameManager::Instance()->GetMapSpriteTexture()->at(_iNumber).at(1);

	m_iX = _iX;
	m_iY = _iY;
	m_iMaxHP = _iHP;
	m_iCurrentHP = _iHP;
	m_iSpeed = _iSpeed;
	m_iDirection = _iDirection;

	m_iXOffset = 0;
	m_iYOffset = 0;

	m_tMove = new Timer( 200 );
}

void Enemy::Render()
{
	m_pTexture[time(NULL)%2]->Render( GameManager::Instance()->GetGlobalRenderer(), m_iX, m_iY );
	GameManager::Instance()->GetMapSpriteTexture()->at(GameManager::HP_GAUGE).at(0)->Render( GameManager::Instance()->GetGlobalRenderer(), m_iX, m_iY );
	GameManager::Instance()->GetMapSpriteTexture()->at(GameManager::HP_GAUGE).at(1)->Render( GameManager::Instance()->GetGlobalRenderer(), m_iX, m_iY, (int)(1+(float)48/m_iMaxHP*m_iCurrentHP), 7 );
}

bool Enemy::Move( int (*_iMap) [9][10] )
{
	if( m_tMove->Check() == false )
	{
		return false;
	}
	m_tMove->Renew();

	switch( m_iDirection )
	{
	case 1:	// µ¿
		m_iXOffset = 1;
		break;
	case 2:	// ¼­
		m_iXOffset = -1;
		break;
	case 3:	// ³²
		m_iYOffset = 1;
		break;
	case 4:	// ºÏ
		m_iYOffset = -1;
		break;
	}

	if(
		(( m_iY/50+m_iYOffset < 0 ) || ( m_iX/50+m_iXOffset < 0 ))
		||
		(( m_iY/50+m_iYOffset > 8 ) || ( m_iX/50+m_iXOffset > 9 ))
		)
		return true;

	if(( _iMap[0][m_iY/50+m_iYOffset][m_iX/50+m_iXOffset] != 2 )
		&&
		!(m_iY%50 + m_iX%50)
		)
	{
		switch( m_iDirection )
		{
		case 1:	// µ¿
		case 2:	// ¼­
			m_iXOffset = 0;
			if( _iMap[0][m_iY/50+1][m_iX/50] == 2 )
			{
				m_iDirection = 3;
				m_iYOffset = 1;
			}
			else
			{
				m_iDirection = 4;
				m_iYOffset = -1;
			}
			break;
		case 3:	// ³²
		case 4:	// ºÏ
			m_iYOffset = 0;
			if( _iMap[0][m_iY/50][m_iX/50+1] == 2 )
			{
				m_iDirection = 1;
				m_iXOffset = 1;
			}
			else
			{
				m_iDirection = 2;
				m_iXOffset = -1;
			}
			break;
		}
	}

	m_iX = m_iX + m_iSpeed * m_iXOffset;
	m_iY = m_iY + m_iSpeed * m_iYOffset;

	return false;
}

Enemy *EnemyCreator::CreateEnemy( int _iNumber )
{
	return new Enemy( m_vEnemyInfo.at(_iNumber).iNumber, m_iX, m_iY, m_vEnemyInfo.at(_iNumber).iHP, m_vEnemyInfo.at(_iNumber).iSpeed, m_iDirection );
}