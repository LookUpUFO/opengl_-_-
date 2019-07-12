#include "GameObject.h"


GameObject::GameObject()
{
	m_translate = AddComponent<Translate>();
}

 
//template<typename T>
//std::shared_ptr<T> GameObject::AddComponent()
//{
//
//	return NULL;
//	 //return ComponentCollection::Instance()->AddComponent<T>();
//}

