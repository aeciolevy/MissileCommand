#pragma once
#include <iostream>
#include <string>
#include <functional>
#include "Game\Public\Singleton.h"
#include "Engine\Public\EngineInterface.h"
#include "Game\Public\COGTransform.h"
#include "Game\Public\COGBoxShape.h"
#include "Game\Public\COGPhysics.h"


extern std::hash<std::string> s_hash;

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
			return newGameObject = CreateCity(s_hash("City"), pEngine, startPosition);
		case GameObjectType::Base :
			return newGameObject = CreateBase(s_hash("Base"), pEngine, startPosition);
		default:
			std::cout << "Wrong type" << std::endl;
			return nullptr;
		}
	}

	GameObject* CreateCity(Hash hash, exEngineInterface* pEngine, exVector2 startPosition);
	GameObject* CreateBase(Hash hash, exEngineInterface* pEngine, exVector2 startPosition);
};