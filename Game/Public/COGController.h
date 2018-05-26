#pragma once
#include "Game\Public\GameObject.h"
#include "Game\Public\COGTransform.h"

class COGController : public Component
{
public:
	static std::vector<COGController*> mControllerComponents;
public:

	COGController(GameObject* pGO, COGTransform* pTransform)
		: Component(pGO)
	{
		mGO = pGO;
		mTransform = pTransform;
		mPosition = pTransform->GetPosition();
		mVelocity = 80.0f;
	}

	virtual ComponentType GetType() const { return ComponentType::Input; }

	virtual void Initialize() override
	{
		AddToComponentVector(mControllerComponents);
	}

	virtual void Destroy() override
	{
		RemoveFromComponentVector(mControllerComponents);
	}

	void SetVectorToMissile(exVector2 finalPosition);

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
};

