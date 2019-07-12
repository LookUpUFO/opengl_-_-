#pragma once
#include "Object.h"
#include <list>
#include "Component.h"
#include <iostream>

#include <string>
#include "Translate.h"
#include "ComponentCollection.h"
 



class GameObject:public Object
{

public:
	std::string m_Name;
	std::shared_ptr< Translate> m_translate;

private:
	std::list<std::shared_ptr< Component>> m_componentList;

	
public:
	GameObject();
	~GameObject() {};

public:
	template <typename T>
	std::shared_ptr< T>   AddComponent()
	{	 
		return ComponentCollection::Instance()->AddComponent<T>();
	}


	/*
	获取组件
	模板T :必须是继承Component 类
	*/
	template <typename T  > 
	std::shared_ptr<T> GetCompoent()
	{
		for (auto itear = m_componentList.begin(); itear != m_componentList.end(); itear++)
		{
			std::shared_ptr<T> pointer = std::dynamic_pointer_cast<T> (itear);
			if (pointer != NULL)
				return pointer;
		} 
		return NULL;
	}

};

