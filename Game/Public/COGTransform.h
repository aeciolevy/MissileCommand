#pragma once
#include "Game\Public\GameObject.h"
#include "Engine/Public/EngineTypes.h"

class COGTransform : public Component
{
public:

	COGTransform(GameObject* pGO, exVector2 startPosition)
		: Component(pGO)
	{
		mPosition = startPosition;
	}

	virtual ComponentType GetType() const { return ComponentType::Transform; }

	exVector2& GetPosition() { return mPosition; }

	void SetPosition(float increment) 
	{
		mPosition.y += increment;
	}

	void ResetPosition(exVector2 newPosition)
	{
		mPosition = newPosition;
	}

private:

	exVector2 mPosition;

};