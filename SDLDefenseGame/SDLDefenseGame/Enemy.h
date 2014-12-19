#ifndef	__ENEMY_H__
#define __ENEMY_H__

#include <vector>
#include "Texture.h"
#include "Timer.h"

typedef struct _enemyInfo
{
	int iNumber;
	int iHP;
	int iSpeed;
} ENEMY_INFO;

class Enemy
{
private:
	Texture *m_pTexture[2];
	int m_iMaxHP, m_iCurrentHP;
	int m_iSpeed;
	int m_iDirection;
	int m_iXOffset, m_iYOffset;
	int m_iX;
	int m_iY;

	Timer *m_tMove;

public:
	Enemy( int _iNumer, int _iX, int _iY, int _iHP, int _iSpeed, int _iDirection );

	~Enemy() {}

	void Render();

	int GetCurrentHP()
	{
		return m_iCurrentHP;
	}

	int GetCenterX()
	{
		return m_iX + m_pTexture[0]->m_iWidth/2;
	}

	int GetCenterY()
	{
		return m_iY + m_pTexture[0]->m_iHeight/2;
	}

	void Attack( int _iDamage )
	{
		m_iCurrentHP = m_iCurrentHP - _iDamage;
	}

	bool Move( int (*_iMap) [9][10] );

	bool Check()
	{
		if( m_iCurrentHP <= 0 )
			return true;
		return false;
	}
};

class EnemyCreator
{
private:
	std::vector<ENEMY_INFO> m_vEnemyInfo;
	int m_iX;
	int m_iY;
	int m_iDirection;

public:
	EnemyCreator( int _iDirection, int _iX, int _iY )
	{
		m_iDirection = _iDirection;
		m_iX = _iX*50;
		m_iY = _iY*50;
	}

	~EnemyCreator()
	{
	}

	void AddEnemyInfo( ENEMY_INFO _stEnemyInfo )
	{
		m_vEnemyInfo.push_back( _stEnemyInfo );
	}

	Enemy *CreateEnemy( int _iNumber );
};

#endif