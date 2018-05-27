#include "Game\Public\Factory.h"

Factory* Singleton<Factory>::mSingleton = nullptr;

std::hash<std::string> s_hash;

GameObject* Factory::CreateCity(Hash hash, exEngineInterface* pEngine, exVector2 startPosition)
{
	const float CITY_WIDTH = 50.0f;
	const float CITY_HEIGHT = 10.0f;

	exColor cityColor;
	cityColor.mColor[0] = 255;
	cityColor.mColor[1] = 10;
	cityColor.mColor[2] = 10;
	cityColor.mColor[3] = 255;

	GameObject* city = new GameObject(hash);

	COGTransform* pTransform = new COGTransform(city, startPosition);
	city->AddComponent(pTransform);

	COGBoxShape* pBoxShape = new COGBoxShape(pEngine, city, CITY_WIDTH, CITY_HEIGHT, cityColor);
	city->AddComponent(pBoxShape);

	COGPhysics* pPhysics = new COGPhysics(city, true);
	city->AddComponent(pPhysics);

	city->Initialize();

	return city;
}

GameObject* Factory::CreateBase(Hash hash, exEngineInterface* pEngine, exVector2 startPosition)
{
	const float BASE_WIDTH = 25.0f;
	const float BASE_HEIGHT = 10.0f;

	exColor baseColor;
	baseColor.mColor[0] = 128;
	baseColor.mColor[1] = 1;
	baseColor.mColor[2] = 196;
	baseColor.mColor[3] = 255;

	GameObject* base = new GameObject(hash);

	COGTransform* pTransform = new COGTransform(base, startPosition);
	base->AddComponent(pTransform);

	COGBoxShape* pBoxShape = new COGBoxShape(pEngine, base, BASE_WIDTH, BASE_HEIGHT, baseColor);
	base->AddComponent(pBoxShape);

	COGPhysics* pPhysics = new COGPhysics(base, true);
	base->AddComponent(pPhysics);

	base->Initialize();

	return base;
}

GameObject* Factory::CreateFriendMissile(Hash hash, exEngineInterface* pEngine, exVector2 startPosition, exVector2 finalPosition)
{

	exColor missileColor;
	missileColor.mColor[0] = 255;
	missileColor.mColor[1] = 255;
	missileColor.mColor[2] = 196;
	missileColor.mColor[3] = 255;

	GameObject* missile = new GameObject(hash);

	COGTransform* pTransform = new COGTransform(missile, startPosition);
	missile->AddComponent(pTransform);

	COGMissileController* pMissileController = new COGMissileController(missile, pTransform, pEngine);
	pMissileController->SetVectorToMissile(finalPosition);
	missile->AddComponent(pMissileController);

	COGLineShape* pLineShape = new COGLineShape(pEngine, missile, startPosition, missileColor);
	missile->AddComponent(pLineShape);

	COGPhysics* pPhysics = new COGPhysics(missile, true);
	missile->AddComponent(pPhysics);

	missile->Initialize();

	return missile;
}

void Factory::addToStaleList(GameObject* gameObject)
{
	if (gameObject->GetHandle().IsValid())
	{
		mStaleGameObjects.push_back(gameObject);
	}
}

void Factory::cleanStaleList()
{
	if (mStaleGameObjects.size() > 0)
	{
		for (int i = 0; i < (int)mStaleGameObjects.size(); ++i)
		{
			GameObjectInventory::Instance()->Unregister(mStaleGameObjects[i]);
			mStaleGameObjects.erase(mStaleGameObjects.begin() + i);
		}
	}
}