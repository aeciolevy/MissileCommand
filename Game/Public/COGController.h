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

	virtual void Update(float DeltaTime);


private:

	exVector2					mPosition;
	COGTransform *				mTransform;
	float						mVelocity;


};
