#include "Game\Public\GameObject.h"
#include "Game\Public\COGTransform.h"
#include "Engine/Public/SDL.h"

class COGInput : public Component
{
public:
	static std::vector<COGInput*> mInputComponents;
public:

	COGInput(GameObject* pGO, COGTransform* pTransform, PaddleIdentifier paddle)
		: Component(pGO)
	{
		mPaddle = paddle;
		mTransform = pTransform;
		mPosition = pTransform->GetPosition();
		mVelocity = 80.0f;
	}

	virtual ComponentType GetType() const { return ComponentType::Input; }

	virtual void Initialize() override
	{
		AddToComponentVector(mInputComponents);
	}

	virtual void Destroy() override
	{
		RemoveFromComponentVector(mInputComponents);
	}

	virtual void Update(float DeltaTime);

private:

	exVector2					mPosition;
	COGTransform *				mTransform;
	PaddleIdentifier				mPaddle;
	float						mVelocity;


};
