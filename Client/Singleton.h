#pragma once

//===============================================
// ISingleton
// Info : ������ ������ �ϳ�, �� ������ ���� �ϳ��� Ŭ������ �� �ϳ��� �ν��Ͻ����� �����Ѵ�.
template <class T>
class ISingleton
{
private:
	static T* m_Instance;
public:
	ISingleton(VOID) { /* empty */ };
	~ISingleton(VOID) { delete m_Instance; };

	static T* GetInstance(VOID)
	{
		if (m_Instance == NULL)
		{
			m_Instance = new T();
		}
		return m_Instance;
	}
};

template <class T> T* ISingleton<T>::m_Instance = 0;