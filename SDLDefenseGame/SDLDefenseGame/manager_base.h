#ifndef	__MANAGER_BASE_H__
#define __MANAGER_BASE_H__

class Singleton
{
public:
	virtual bool Initialize() = 0;
	virtual void Destroy() = 0;

	Singleton()
	{
	}

	~Singleton()
	{
		// 인스턴스 자체는 new로 생성하기 때문에 자동 삭제된다
	};

	//static Singleton* m_pInstance;
};

#endif