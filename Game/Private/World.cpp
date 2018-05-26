#include "Game\Public\World.h"
#include "Game\Public\Factory.h"
#include "Engine/Public/SDL.h"

World::World(exEngineInterface* pEngine)
{
	mEngine = pEngine;
	mFactory = Factory::Instance();
}

void World::Initialize()
{
	GameObject* city = mFactory->CreateGameObject(mEngine, { 50.0f, 590.0f }, GameObjectType::City);
	mGameObjects.push_back(city->GetHandle());
	GameObject* base = mFactory->CreateGameObject(mEngine, { 10.0f, 590.0f }, GameObjectType::Base);
	mGameObjects.push_back(base->GetHandle());
}

bool World::MouseClick()
{
	int x, y;
	unsigned int r = SDL_GetMouseState(&x, &y);

	mMousePosition.x = (float)x;
	mMousePosition.y = (float)y;

	int MouseLeft = r & SDL_BUTTON(SDL_BUTTON_LEFT);
	return (bool) MouseLeft;
}

void World::LauchMissile()
{
	GameObject* missile = mFactory->CreateMissiles(mEngine, { 30.0f, 590.0f }, mMousePosition, GameObjectType::MissileFriend);
}

void World::Destroy()
{
}

void World::Update(float fDeltaT)
{

	if (MouseClick())
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
}