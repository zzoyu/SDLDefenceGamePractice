#include "Bullet.h"
#include "manager_game.h"
#include <math.h>

void Bullet::Render()
{
	m_pTexture->RenderWithRotation( GameManager::Instance()->GetGlobalRenderer(),
		m_fRadian, m_iX-(m_pTexture->m_iWidth/2), m_iY-(m_pTexture->m_iHeight/2) );
}

void Bullet::Move()
{
	if( m_tMove->Check() == false )
	{
		return;
	}
	m_tMove->Renew();

	m_iX = m_iX + (int)( cos( m_fRadian ) * 25 );
	m_iY = m_iY + (int)( sin( m_fRadian ) * 25 );
}

bool Bullet::Check()
{
	if(
		( (m_iX-m_pTexture->m_iWidth) < 0 ) ||
		( (m_iX-m_pTexture->m_iWidth) > 500 ) ||
		( (m_iY-m_pTexture->m_iHeight) < 0 ) ||
		( (m_iY-m_pTexture->m_iHeight) > 500 )
	)
		return true;
	else
		return false;
}

bool Bullet::Check( int _iRadius )
{
	float m_fDistance = sqrtf(
		pow( m_iDestX - (m_iX+((float)m_pTexture->m_iWidth/2)), 2 ) + pow( m_iDestY - (m_iY+((float)m_pTexture->m_iHeight/2)), 2 )
		);
	if( m_fDistance < m_iRadius+_iRadius )
		return true;
	else
		return false;
}

bool Bullet::Check( int _iX, int _iY, int _iRadius )
{
	float m_fDistance = sqrtf(
		pow( _iX - (m_iX+((float)m_pTexture->m_iWidth/2)), 2 ) + pow( _iY - (m_iY+((float)m_pTexture->m_iHeight/2)), 2 )
		);
	if( m_fDistance < m_iRadius+_iRadius )
		return true;
	else
		return false;
}