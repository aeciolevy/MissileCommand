#include "Game\Public\World.h"
#include "Game\Public\Factory.h"
#include "Engine/Public/SDL.h"

extern std::hash<std::string> s_hash;

World::World(exEngineInterface* pEngine)
{
	mEngine = pEngine;
	mFactory = Factory::Instance();
	mCities = 6;
	mMouseLeft = 0;
}

void World::Initialize()
{
	for (int i = 0; i < mCities; i++)
	{
		GameObject* city = mFactory->CreateGameObject(mEngine, { 50.0f, 590.0f }, GameObjectType::City);
		mGameObjects.push_back(city->GetHandle());
	}
}

void World::MouseClick()
{
	int x, y;
	unsigned int r = SDL_GetMouseState(&x, &y);

	mMousePosition.x = (float)x;
	mMousePosition.y = (float)y;

	mMouseLeft = r & SDL_BUTTON(SDL_BUTTON_LEFT);
}

void World::LauchMissile()
{
	exVector2 base1 = { 133.0f, 590.0f };
	exVector2 base2 = { 399.0f, 590.0f };
	exVector2 base3 = { 665.0f, 590.0f };
	if (mMousePosition.x < 266)
	{
		GameObject* missile = mFactory->CreateMissiles(mEngine, base1, mMousePosition, GameObjectType::MissileFriend);
	}
	else if (mMousePosition.x >= 266.0f && mMousePosition.x < 532.0f)
	{
		GameObject* missile = mFactory->CreateMissiles(mEngine, base2, mMousePosition, GameObjectType::MissileFriend);
	}
	else if (mMousePosition.x >= 532.0f && mMousePosition.x <= kViewPortWidth)
	{
		GameObject* missile = mFactory->CreateMissiles(mEngine, base3, mMousePosition, GameObjectType::MissileFriend);
	}
	
}

void World::Destroy()
{
}

void World::Update(float fDeltaT)
{
	MouseClick();
	if ((bool) mMouseLeft && !mMouseLeftOld)
	{
		LauchMissile();
	}

	for (COGController* pController : COGController::mControllerComponents)
	{
		pController->Update(fDeltaT);
	}

	// run simulation first
	for (COGPhysics* pPhysics : COGPhysics::mPhysicsComponents)
	{
		pPhysics->Update(fDeltaT);
	}

	// then render everything
	for (COGShape* pShape : COGShape::mShapeComponents)
	{
		pShape->Render();
	}

	Factory::Instance()->cleanStaleList();
	mMouseLeftOld = (bool)mMouseLeft;
}