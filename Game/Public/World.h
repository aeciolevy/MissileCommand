#pragma once
#include "Game\Public\GameObject.h"
#include "Game\Public\COGPhysics.h"
#include "Game\Public\COGBounce.h"
#include "Game\Public\COGMissileController.h"
#include "Game\Public\COGExplosionController.h"
#include "Engine/Public/EngineInterface.h"
#include "Game/Public/AIMissile.h"

class Factory;
// the world, it contains all of our game objects and defines the order of updates
class World
{
public:

	World(exEngineInterface* pEngine);

	void Initialize();

	void Destroy();

	void Update(float fDeltaT);

	virtual void DrawGameOver();

	virtual void MouseClick();

	virtual void LauchMissile();

private:

	Factory*							mFactory;
	AIMissile*							mAIMissile;
	std::vector<GameObjectHandle>		mGameObjects;
	std::vector<exVector2>				mCitiesPosition;
	exEngineInterface*					mEngine;
	exVector2							mMousePosition;
	int									mCities;
	int									mMouseLeft;
	bool								mMouseLeftOld;
};
