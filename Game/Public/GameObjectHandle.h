#pragma once
#include "Game/Public/GameObject.h"

typedef unsigned int Hash;

class GameObject;
class GameObjectInventory;

class GameObjectHandle
{
public:
	Hash mHash;

	bool IsValid() const;
	GameObject* Get() const;

private:
	GameObjectInventory * mInventory;
};