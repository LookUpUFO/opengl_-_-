#pragma once
#include "Singler.h"
#include <iostream>
#include "Component.h"
#include <list>


class ComponentCollection :public Singler<ComponentCollection> 
{
private:
	std::list< std::shared_ptr<Component>> m_componentList;

public:

	template<typename T>
	std::shared_ptr< T> AddComponent()
	{

		std::shared_ptr< T>  pCom = std::make_shared<T>();
		auto compon = std::dynamic_pointer_cast<Component>(pCom);
		if (compon != NULL)
		{
			m_componentList.push_back(compon);
			return  pCom;
		}
		return NULL;
	}

public: 

	void Update()
	{
		for (auto itear = m_componentList.begin(); itear != m_componentList.end(); itear++)
		{
			(*itear)->Update();
		}
	}

};

