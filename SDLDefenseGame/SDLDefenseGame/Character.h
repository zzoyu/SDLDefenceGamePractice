#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "Texture.h"
#include "Bullet.h"
#include "Timer.h"
#include <vector>
#include <time.h>

class Character
{
private:
	Texture *m_pTexture[2];
	BulletShooter *m_bulletShooter;
	std::vector<Bullet*> m_vBullet;

	Timer *m_tMove;
	int m_iLevel;
	int m_iRange;
	int m_iPower;
	int m_iX;
	int m_iY;

public:
	Character( int _iNumber, BulletShooter* _BBangYa, int _iX, int _iY, int _iRange, int _iDelay, int _iPower );

	~Character() {}

	void Render();

	bool Check()
	{
		if( !m_tMove->Check() )
			return false;
		m_tMove->Renew();
		return true;
	}

	bool Check( int _iX, int _iY, int _iRadius )
	{
		float m_fDistance = sqrtf(
		pow( _iX - (m_iX+((float)m_pTexture[0]->m_iWidth/2)), 2 ) + pow( _iY - (m_iY+((float)m_pTexture[0]->m_iHeight/2)), 2 )
		);
		if( m_fDistance < m_iRange+_iRadius )
			return true;
		else
			return false;
	}

	Bullet* Shoot( int _iDestX, int _iDestY )
	{
		return m_bulletShooter->ShootTheBullet( m_iX + (m_pTexture[0]->m_iWidth/2), m_iY + (m_pTexture[0]->m_iHeight/2), _iDestX, _iDestY );
	}
};

#endif