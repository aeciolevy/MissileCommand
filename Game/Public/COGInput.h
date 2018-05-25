#include "Game\Public\GameObject.h"
#include "Game\Public\COGTransform.h"
#include "Engine/Public/SDL.h"

class COGInput : public Component
{
public:
	static std::vector<COGInput*> mInputComponents;
public:

	COGInput(GameObject* pGO, COGTransform* pTransform)
		: Component(pGO)
	{
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

	virtual bool MouseClick(int nScancode);

private:

	exVector2					mPosition;
	exVector2					mMousePosition;
	int							mMouseLeft;
	COGTransform *				mTransform;
	float						mVelocity;


};
