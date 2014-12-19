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
		// �ν��Ͻ� ��ü�� new�� �����ϱ� ������ �ڵ� �����ȴ�
	};

	//static Singleton* m_pInstance;
};

#endif