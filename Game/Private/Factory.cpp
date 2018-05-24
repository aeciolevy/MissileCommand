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