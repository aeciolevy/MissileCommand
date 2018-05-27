#include "Game\Public\COGExplosionController.h"
#include "Game\Public\Factory.h"

std::vector<COGExplosionController*> COGExplosionController::mMissileControllerComponents;

COGExplosionController::COGExplosionController(GameObject* pGO, COGTransform* pTransform)
	: Component(pGO)
{
	mGO = pGO;
	mTransform = pTransform;
	mPosition = pTransform->GetPosition();
	mVelocity = 80.0f;
}

bool COGExplosionController::ReachFinalPosition()
{
	if (mDirection.x > 0)
	{
		if (mPosition.x >= mFinalPosition.x)
		{
			return true;
		}
	}
	else
	{
		if (mPosition.x <= mFinalPosition.x)
		{
			return true;
		}
	}
	return false;
}


void COGExplosionController::Update(float DeltaTime)
{
	if (ReachFinalPosition() == false)
	{
		mPosition.x += mUnitVector.x * mVelocity * DeltaTime;
		mPosition.y += mUnitVector.y * mVelocity * DeltaTime;
		mTransform->SetFinalPos(mPosition);
	}
	else
	{
		Factory::Instance()->addToStaleList(mGO);
	}
}