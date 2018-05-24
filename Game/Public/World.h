#pragma once
#include "Game\Public\GameObject.h"
#include "Game\Public\COGPhysics.h"
#include "Game\Public\COGBounce.h"
#include "Game\Public\COGInput.h"
#include "Engine/Public/EngineInterface.h"


//
//inline GameObject* CreateBorder(exEngineInterface* pEngine, exVector2 position)
//{
//	const float fFloorWidth = kViewPortWidth;
//	const float fFloorHeight = 10.0f;
//
//	exColor borderColor;
//	borderColor.mColor[0] = 0;
//	borderColor.mColor[1] = 0;
//	borderColor.mColor[2] = 0;
//
//	GameObject* pFloor = new GameObject();
//
//	COGTransform* pTransform = new COGTransform(pFloor, position);
//	pFloor->AddComponent(pTransform);
//
//	COGBoxShape* pBoxShape = new COGBoxShape(pEngine, pFloor, fFloorWidth, fFloorHeight, borderColor);
//	pFloor->AddComponent(pBoxShape);
//
//	COGPhysics* pPhysics = new COGPhysics(pFloor, false);
//	pFloor->AddComponent(pPhysics);
//
//	pFloor->Initialize();
//
//	return pFloor;
//}
//
//
//// create our paddle
//inline GameObject* CreatePaddle(exEngineInterface* pEngine, exVector2 position, PaddleIdentifier paddle)
//{
//	const float fPaddleWidth = 15.0f;
//	const float fPaddleHeight = PaddleHeight;
//
//	exColor paddleColor;
//	paddleColor.mColor[0] = 255;
//	paddleColor.mColor[1] = 255;
//	paddleColor.mColor[2] = 255;
//	paddleColor.mColor[3] = 255;
//
//	GameObject* pPaddle = new GameObject();
//
//	COGTransform* pTransform = new COGTransform(pPaddle, position);
//	pPaddle->AddComponent(pTransform);
//
//	COGInput* pInput = new COGInput(pPaddle, pTransform,  paddle);
//	pPaddle->AddComponent(pInput);
//
//	COGBoxShape* pBoxShape = new COGBoxShape(pEngine, pPaddle, fPaddleWidth, fPaddleHeight, paddleColor);
//	pPaddle->AddComponent(pBoxShape);
//
//	COGPhysics* pPhysics = new COGPhysics(pPaddle, false);
//	pPaddle->AddComponent(pPhysics);
//
//	pPaddle->Initialize();
//
//	return pPaddle;
//}

// create ball (notice how it will generate events)
//inline GameObject* CreateBall(exEngineInterface* pEngine, exVector2 position)
//{
//	const float fBallRadius = 20.0f;
//
//	GameObject* pBall = new GameObject();
//
//	COGTransform* pTransform = new COGTransform(pBall, position);
//	pBall->AddComponent(pTransform);
//
//	COGCircleShape* pBoxShape = new COGCircleShape(pEngine, pBall, fBallRadius);
//	pBall->AddComponent(pBoxShape);
//
//	COGPhysics* pPhysics = new COGPhysics(pBall, true);
//	pBall->AddComponent(pPhysics);
//
//	COGBounce* pBounce = new COGBounce(pBall);
//	pBall->AddComponent(pBounce);
//
//	pBall->Initialize();
//
//	return pBall;
//}

class Factory;
// the world, it contains all of our game objects and defines the order of updates
class World
{
public:

	World(exEngineInterface* pEngine);

	void Initialize();

	void Destroy();

	void Update(float fDeltaT);

private:

	Factory*						mFactory;
	std::vector<GameObject*>		mGameObjects;
	exEngineInterface*				mEngine;
};
