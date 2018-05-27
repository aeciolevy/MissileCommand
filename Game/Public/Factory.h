#pragma once
#include <iostream>
#include <string>
#include <functional>
#include "Game\Public\Singleton.h"
#include "Engine\Public\EngineInterface.h"
#include "Game\Public\COGTransform.h"
#include "Game\Public\COGBoxShape.h"
#include "Game\Public\COGPhysics.h"
#include "Game\Public\COGLineShape.h"
#include "Game\Public\COGExplosion.h"
#include "Game\Public\COGExplosionController.h"
#include "Game\Public\COGMissileController.h"
#include "Game\Public\GameObjectInventory.h"

class COGMissileController;

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
		case GameObjectType::Explosion :
			return newGameObject = CreateExplosion(s_hash("Explosion" + std::to_string(mIdentify)), pEngine, startPosition);
		default:
			std::cout << "Wrong type" << std::endl;
			return nullptr;
		}
	}

	GameObject* CreateExplosion(Hash hash, exEngineInterface* pEngine, exVector2 startPosition)
	{
		exColor explosionColor;
		explosionColor.mColor[0] = 255;
		explosionColor.mColor[1] = 255;
		explosionColor.mColor[2] = 196;
		explosionColor.mColor[3] = 255;

		float Radius = 40.0f;

		GameObject* explosion = new GameObject(hash);

		COGTransform* pTransform = new COGTransform(explosion, startPosition);
		explosion->AddComponent(pTransform);

		COGExplosionController* pExplosionController = new COGExplosionController(explosion, pTransform);
		explosion->AddComponent(pExplosionController);

		COGExplosion* pExplosion = new COGExplosion(pEngine, explosion, pTransform, startPosition, Radius, explosionColor);
		explosion->AddComponent(pExplosion);

		COGPhysics* pPhysics = new COGPhysics(explosion, true);
		explosion->AddComponent(pPhysics);

		explosion->Initialize();

		return explosion;
	}

	GameObject* CreateMissiles(exEngineInterface* pEngine, exVector2 startPosition, exVector2 finalPosition, GameObjectType gameType) {
		GameObject* newGameObject;
		++mIdentify;
		switch (gameType)
		{
		case GameObjectType::MissileFriend: 
			return newGameObject = CreateFriendMissile(s_hash("Missile" + std::to_string(mIdentify)), pEngine, startPosition, finalPosition);
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