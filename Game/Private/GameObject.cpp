#include "Game\Public\GameObject.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
	for (Component* pComponent : mComponents)
	{
		pComponent->Destroy();

		delete pComponent;
	}
}

void GameObject::Initialize() 
{
	for (Component* pComponent : mComponents)
	{
		pComponent->Initialize();
	}
}

void GameObject::AddComponent(Component* pComponent)
{
	mComponents.push_back(pComponent);
}
