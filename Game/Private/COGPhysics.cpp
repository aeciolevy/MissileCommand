#include "Game\Public\COGPhysics.h"
#include "Game\Public\COGBounce.h"

std::vector<COGPhysics*> COGPhysics::mPhysicsComponents;

COGPhysics::COGPhysics(GameObject* pGO, bool bGenerateCollisionEvents)
	: Component(pGO)
	, mGenerateCollisionEvents(bGenerateCollisionEvents)
{
	mVelocity = { 0.0f, 0.0f };
}

void COGPhysics::Initialize() 
{
	mTransform = mGO->FindComponent<COGTransform>(ComponentType::Transform);
	mBoxShape = mGO->FindComponent<COGBoxShape>(ComponentType::BoxShape);
	mCircleShape = mGO->FindComponent<COGCircleShape>(ComponentType::CircleShape);
	AddToComponentVector(mPhysicsComponents);
	// If it is a ball add bounce to Event collision vector
	if (mGenerateCollisionEvents)
	{
		COGBounce* mBounce = mGO->FindComponent<COGBounce>(ComponentType::Bounce);
		// Upcast bounce to IPhysicsCollision event
		IPhysicsCollisionEvent* temp = dynamic_cast<COGBounce*>(mBounce);
		mCollisionEventListeners.push_back(temp);
	}
}

COGPhysics::~COGPhysics()
{
	for (int i = 0; i < int(mCollisionEventListeners.size()); i++)
	{
		if (dynamic_cast<Component *>(mCollisionEventListeners[i]) == nullptr)
		{
			delete mCollisionEventListeners[i];
		}

		mCollisionEventListeners.erase(mCollisionEventListeners.begin() + i);
	}
}


void COGPhysics::Destroy()
{
	RemoveFromComponentVector(mPhysicsComponents);
}

void COGPhysics::Update(float fDeltaT)
{
	// check collisions
	if (mGenerateCollisionEvents)
	{
		for (COGPhysics* pPhysicsOther : COGPhysics::mPhysicsComponents)
		{
			// do not collide with self
			if (pPhysicsOther == this)
			{
				continue;
			}

			const bool bResult = IsColliding(pPhysicsOther);

			if (bResult)
			{
				exVector2 normal = GetNormal(pPhysicsOther);
				for (IPhysicsCollisionEvent* pCollisionEventListener : mCollisionEventListeners)
				{
					pCollisionEventListener->OnCollision(this, pPhysicsOther, normal);
				}
			}
		}
	}
}

exVector2& COGPhysics::GetVelocity()
{
	return mVelocity;
}

void COGPhysics::SetVelocity(exVector2 newVelocity)
{
	mVelocity = newVelocity;
}

CircleParams COGPhysics::GetCircleParams()
{
	CircleParams temp;
	temp.Radius = mCircleShape->GetRadius();
	temp.Center = mCircleShape->GetCenter();
	return temp;
}

BoxParams COGPhysics::GetBoxParams(COGBoxShape* boxShape)
{
	BoxParams temp;
	temp.vertex1 = boxShape->GetVertex1();
	temp.vertex2 = boxShape->GetVertex2();
	return temp;
}

float findNearestPoint(float Center, float TopLeft, float BottomRight)
{
	return std::max(TopLeft, std::min(Center, BottomRight));
}

exVector2 GetNearestVector(CircleParams Circle, BoxParams Box)
{
	float x = Circle.Center.x - findNearestPoint(Circle.Center.x, Box.vertex1.x, Box.vertex2.x);
	float y = Circle.Center.y - findNearestPoint(Circle.Center.y, Box.vertex1.y, Box.vertex2.y);
	return { x, y };
}
// Based on https://yal.cc/rectangle-circle-intersection-test/
bool IsCircleBoxColliding(CircleParams Circle, BoxParams Box)
{
	float DeltaX = GetNearestVector(Circle, Box).x;
	float DeltaY = GetNearestVector(Circle, Box).y;
	return (DeltaX * DeltaX + DeltaY * DeltaY) < (Circle.Radius * Circle.Radius);
}



exVector2 COGPhysics::GetNormal(COGPhysics* pOther)
{
	CircleParams circle = GetCircleParams();
	BoxParams box = GetBoxParams(pOther->mBoxShape);
	float xPoint = GetNearestVector(circle, box).x;
	float yPoint = GetNearestVector(circle, box).y;
	exVector2 temp = { xPoint, yPoint };
	return temp.Normalize();
}


bool COGPhysics::IsColliding(COGPhysics* pOther)
{
	if (mCircleShape != nullptr && pOther->mBoxShape != nullptr)
	{
		CircleParams circle = GetCircleParams();
		BoxParams box = GetBoxParams(pOther->mBoxShape);
		bool checkCollision = IsCircleBoxColliding(circle, box);
		return checkCollision;
	}

	// we don't cover the other cases
	// maybe assert here?

	return false;
}




