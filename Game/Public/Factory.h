#pragma once
#include <iostream>
#include <string>
#include <functional>
#include "Game\Public\Singleton.h"
#include "Engine\Public\EngineInterface.h"
#include "Game\Public\COGTransform.h"
#include "Game\Public\COGBoxShape.h"
#include "Game\Public\COGPhysics.h"
#include "Game\Public\COGController.h"
#include "Game\Public\COGLineShape.h"
#include "Game\Public\GameObjectInventory.h"

extern std::hash<std::string> s_hash;

enum class GameObjectType : int
{
	City = 0,
	Base,
	MissileFriend,
	Missile,
	Explosion,
};

class GameObjectInventory;
class GameObjectHandle;
class GameObject;

class Factory : public Singleton<Factory>
{
	
public:
	friend class Singleton<Factory>;
	
	Factory()
		: mIdentify(0)
	{

	}

	GameObject* CreateGameObject(exEngineInterface* pEngine, exVector2 startPosition, GameObjectType gameType) {
		GameObject* newGameObject;
		++mIdentify;
		switch (gameType)
		{
		case GameObjectType::City :
			return newGameObject = CreateCity(s_hash("City" + std::to_string(mIdentify)), pEngine, startPosition);
		case GameObjectType::Base :
			return newGameObject = CreateBase(s_hash("Base" + std::to_string(mIdentify)), pEngine, startPosition);
		default:
			std::cout << "Wrong type" << std::endl;
			return nullptr;
		}
	}

	GameObject* CreateMissiles(exEngineInterface* pEngine, exVector2 startPosition, exVector2 finalPosition, GameObjectType gameType) {
		GameObject* newGameObject;
		++mIdentify;
		switch (gameType)
		{
		case GameObjectType::MissileFriend: {
			/*std::string temp = std::to_string(mIdentify) + "Missile";*/
			newGameObject = CreateFriendMissile(s_hash("Missile" + std::to_string(mIdentify)), pEngine, startPosition, finalPosition);
			return newGameObject;
		}
		default:
			std::cout << "Wrong type" << std::endl;
			return nullptr;
		}
	}

	GameObject* CreateCity(Hash hash, exEngineInterface* pEngine, exVector2 startPosition);
	GameObject* CreateBase(Hash hash, exEngineInterface* pEngine, exVector2 startPosition);
	GameObject* CreateFriendMissile(Hash hash, exEngineInterface* pEngine, exVector2 startPosition, exVector2 finalPosition);
	void addToStaleList(GameObject* gameObject);
	void cleanStaleList();
	

private:
	std::vector<GameObject* >	mStaleGameObjects;
	int							mIdentify;
};