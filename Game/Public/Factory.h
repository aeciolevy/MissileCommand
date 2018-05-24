#pragma once
#include "Game\Public\Singleton.h"
#include "Engine\Public\EngineInterface.h"
#include "Game\Public\COGTransform.h"
#include "Game\Public\COGBoxShape.h"
#include "Game\Public\COGPhysics.h"
#include <iostream>

//std::hash<std::string> s_hash;

enum class GameObjectType : int
{
	City = 0,
	Base,
	MissileFriend,
	Missile,
	Explosion,
};


class GameObject;


class Factory : public Singleton<Factory>
{
	
public:
	friend class Singleton<Factory>;

	GameObject* CreateGameObject(exEngineInterface* pEngine, exVector2 startPosition, GameObjectType gameType) {
		GameObject* newGameObject;
		switch (gameType)
		{
		case GameObjectType::City :
			return newGameObject = CreateCity(pEngine, startPosition);
		default:
			std::cout << "Wrong type" << std::endl;
			break;
		}
	}

	GameObject* CreateCity(exEngineInterface* pEngine, exVector2 startPosition)
	{
		const float CITY_WIDTH = 50.0f;
		const float CITY_HEIGHT = 10.0f;

		exColor cityColor;
		cityColor.mColor[0] = 255;
		cityColor.mColor[1] = 10;
		cityColor.mColor[2] = 10;
		cityColor.mColor[3] = 255;

		GameObject* city = new GameObject();
		
		COGTransform* pTransform = new COGTransform(city, startPosition);
		city->AddComponent(pTransform);
		
		COGBoxShape* pBoxShape = new COGBoxShape(pEngine, city, CITY_WIDTH, CITY_HEIGHT, cityColor);
		city->AddComponent(pBoxShape);
		
		COGPhysics* pPhysics = new COGPhysics(city, true);
		city->AddComponent(pPhysics);

		city->Initialize();

		return city;
	}

};