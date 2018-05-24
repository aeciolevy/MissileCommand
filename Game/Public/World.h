#pragma once
#include "Game\Public\GameObject.h"
#include "Game\Public\COGPhysics.h"
#include "Game\Public\COGBounce.h"
#include "Game\Public\COGInput.h"
#include "Engine/Public/EngineInterface.h"

class Factory;
// the world, it contains all of our game objects and defines the order of updates
class World
{
public:

	World(exEngineInterface* pEngine);

	void Initialize();

	void Destroy();

	void Update(float fDeltaT);

private:

	Factory*						mFactory;
	std::vector<GameObject*>		mGameObjects;
	exEngineInterface*				mEngine;
};
