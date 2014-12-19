#include "Character.h"
#include "manager_game.h"

Character::Character( int _iNumber, BulletShooter* _BBangYa, int _iX, int _iY, int _iRange, int _iDelay, int _iPower )
{
	m_pTexture[0] = GameManager::Instance()->GetMapSpriteTexture()->at(_iNumber).at(0);
	m_pTexture[1] = GameManager::Instance()->GetMapSpriteTexture()->at(_iNumber).at(1);

	m_bulletShooter = _BBangYa;

	m_iX = _iX;
	m_iY = _iY;
	m_iRange = _iRange;
	m_iPower = _iPower;

	m_iLevel = 1;

	m_tMove = new Timer( _iDelay );
}

void Character::Render()
{
	m_pTexture[time(NULL)%2]->Render( GameManager::Instance()->GetGlobalRenderer(), m_iX, m_iY );
}