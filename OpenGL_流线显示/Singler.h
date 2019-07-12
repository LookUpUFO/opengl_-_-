#pragma once
#include "iostream"

template <typename T>
class Singler
{
public:
	static	std::shared_ptr<T> Instance()
	{
		static std ::shared_ptr<T> m_instance =NULL;
		if (m_instance == NULL)
			m_instance = std::make_shared<T>();
		return  m_instance;
	}

protected:
	  ~Singler() {};
	  Singler() {};

private:
	Singler(const Singler&);
	Singler& operator =(const Singler&) =default;
};

 