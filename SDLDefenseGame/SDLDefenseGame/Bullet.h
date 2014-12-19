#ifndef __BULLET_H__
#define __BULLET_H__

#include "Texture.h"
#include "Timer.h"
#include <math.h>

class GameManager;

class Bullet
{
private:
	Texture *m_pTexture;
	bool m_bIsHomming;
	int m_iX;
	int m_iY;
	int m_iRadius;
	float m_fRadian;
	int m_iDestX;
	int m_iDestY;

	Timer *m_tMove;

public:
	int m_iDamage;

	Bullet( Texture* _pTexture, int _iX, int _iY, int _iDestX, int _iDestY, int _iDamage, int _iRadius, bool _bIsHomming )
	{
		m_pTexture = _pTexture;
		m_bIsHomming = _bIsHomming;
		m_iX = _iX;
		m_iY = _iY;
		m_iDestX = _iDestX;
		m_iDestY = _iDestY;
		m_iRadius = _iRadius;
		m_iDamage = _iDamage;
		
		m_fRadian = atan2f((float)(m_iDestY - (m_iY+(m_pTexture->m_iHeight/2))),(float)(m_iDestX - (m_iX+(m_pTexture->m_iWidth/2))));

		m_tMove = new Timer( 100 );
	}

	~Bullet()
	{
	}

	void Render();

	void Move();

	bool Check();
	bool Check( int _iRadius );
	bool Check( int _iX, int _iY, int _iRadius );
};

class BulletShooter
{
private:
	Texture *m_pTexture;
	bool m_bIsHomming;
	int m_iRadius;
	int m_iDistance;
	int m_iDamage;
public:

	BulletShooter( Texture* _pTexture, int _iDamage, int _iRadius, int _iDistance, bool _bIsHomming )
	{
		m_pTexture = _pTexture;
		m_bIsHomming = _bIsHomming;
		m_iRadius = _iRadius;
		m_iDistance = _iDistance;
		m_iDamage = _iDamage;
	}

	~BulletShooter()
	{
	}

	Bullet * ShootTheBullet( int _iOriginX, int _iOriginY, int _iDestX, int _iDestY )
	{
		return new Bullet( m_pTexture, _iOriginX, _iOriginY, _iDestX, _iDestY, m_iDamage, m_pTexture->m_iWidth, false );
	}
};

#endif