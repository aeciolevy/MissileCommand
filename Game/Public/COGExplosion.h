#pragma once
#include "Game\Public\COGTransform.h"
#include "Game\Public\COGShape.h"

class COGExplosion : public COGShape
{
public:
	COGExplosion(exEngineInterface* pEngine, GameObject* pGO, COGTransform* pTransform, exVector2 startPosition, float fRadius, exColor color)
		: COGShape(pGO)
		, mRadius(fRadius)
		, mCenter(startPosition)
		, mColor(color)
	{
		mEngine = pEngine;
		mTransform = pGO->FindComponent<COGTransform>(ComponentType::Transform);
		mColor.mColor[0] = 255;
		mColor.mColor[1] = 255;
		mColor.mColor[2] = 255;
		mColor.mColor[3] = 255;
	}

	virtual ComponentType GetType() const { return ComponentType::Explosion; }

	virtual float GetRadius()
	{
		return mRadius;
	}

	virtual exVector2 GetCenter()
	{
		return mTransform->GetPosition();
	}

	virtual void Render() override
	{
		mEngine->DrawCircle(mCenter, mRadius, mColor, 2);
	}

private:
	
	exEngineInterface *		mEngine;
	exColor					mColor;
	float					mRadius;
	exVector2				mCenter;
	COGTransform*			mTransform;
};
