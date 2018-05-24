#pragma once
#include "Engine\Public\EngineTypes.h"
#include "Game\Public\GameObject.h"
#include "Game\Public\COGTransform.h"
#include "Game\Public\COGBoxShape.h"
#include "Game\Public\COGCircleShape.h"
#include "Game\Public\Output.h"


struct CircleParams
{
	exVector2 Center;
	float Radius;
};

struct BoxParams
{
	exVector2 vertex1;
	exVector2 vertex2;
};

// our interface that allows COGPhysics to talk to anyone
class IPhysicsCollisionEvent;

// COGPhysics - lets move around
class COGPhysics : public Component
{
public:

	static std::vector<COGPhysics*> mPhysicsComponents;

public:

	COGPhysics(GameObject* pGO, bool bGenerateCollisionEvents);

	~COGPhysics();

	virtual ComponentType GetType() const { return ComponentType::Physics; }

	virtual void Initialize() override;

	virtual void Destroy() override;

	virtual void Update(float fDeltaT);

	bool IsColliding(COGPhysics* pOther);

	CircleParams GetCircleParams();

	BoxParams	GetBoxParams(COGBoxShape* boxShape);

	exVector2 GetNormal(COGPhysics* pOther);

	exVector2& GetVelocity();

	void SetVelocity(exVector2 newVelocity);

private:

	COGTransform * mTransform;
	COGBoxShape* mBoxShape;
	COGCircleShape* mCircleShape;

	exVector2 mVelocity;	
	bool mGenerateCollisionEvents;
	std::vector<IPhysicsCollisionEvent*> mCollisionEventListeners;

};

class IPhysicsCollisionEvent
{
public:

	virtual void OnCollision(COGPhysics* pMe, COGPhysics* pOther, exVector2 normal) = 0;
};

