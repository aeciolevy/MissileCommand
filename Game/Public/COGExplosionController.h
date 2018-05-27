#pragma once
#include "Game\Public\GameObject.h"
#include "Game\Public\COGTransform.h"

class COGExplosionController : public Component
{
public:
	static std::vector<COGExplosionController*> mMissileControllerComponents;
public:

	COGExplosionController(GameObject* pGO, COGTransform* pTransform);

	virtual ComponentType GetType() const { return ComponentType::ExplosionController; }

	virtual void Initialize() override
	{
		AddToComponentVector(mMissileControllerComponents);
	}

	virtual void Destroy() override
	{
		RemoveFromComponentVector(mMissileControllerComponents);
	}

	bool ReachFinalPosition();

	virtual void Update(float DeltaTime);


private:

	exVector2					mFinalPosition;
	exVector2					mPosition;
	exVector2					mUnitVector;
	exVector2					mDirection;
	COGTransform *				mTransform;
	float						mVelocity;
	bool						mFinish;
	GameObject*					mGO;
	ComponentType				mType;
};