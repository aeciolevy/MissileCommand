#include "Game\Public\COGController.h"
#include "Game\Public\Output.h"
#include "Game\Public\GameObjectInventory.h"

std::vector<COGController*> COGController::mControllerComponents;

void COGController::SetVectorToMissile(exVector2 finalPosition)
{
	mFinalPosition = finalPosition;
	mUnitVector = mPosition.GetVector(mFinalPosition);
	mUnitVector = mUnitVector.Normalize();
	mDirection = mUnitVector.VectorDirection();
}

bool COGController::ReachFinalPosition()
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

void COGController::Update(float DeltaTime)
{
	if (ReachFinalPosition() == false)
	{
		mPosition.x += mUnitVector.x * mVelocity * DeltaTime;
		mPosition.y += mUnitVector.y * mVelocity * DeltaTime;
		mTransform->SetFinalPos(mPosition);
	}
	
	
}
