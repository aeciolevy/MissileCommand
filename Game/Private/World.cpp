#include "Game\Public\World.h"
#include "Game\Public\Factory.h"

World::World(exEngineInterface* pEngine)
{
	mEngine = pEngine;
	mFactory = Factory::Instance();
}

void World::Initialize()
{
	GameObject* city = mFactory->CreateGameObject(mEngine, { 50.0f, 590.0f }, GameObjectType::City);
	// mGameObjects.push_back(city->GetHandle()); << the future
	mGameObjects.push_back(city);
}

void World::Destroy()
{
	for (GameObject* pGameObject : mGameObjects)
	{
		delete pGameObject;
	}

	mGameObjects.clear();
}

void World::Update(float fDeltaT)
{

	for (COGInput* pInput : COGInput::mInputComponents)
	{
		pInput->Update(fDeltaT);
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