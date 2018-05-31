#include "Game\Public\World.h"
#include "Game\Public\Factory.h"
#include "Engine/Public/SDL.h"
#include "Game\Public\Help.h"

extern std::hash<std::string> s_hash;

World::World(exEngineInterface* pEngine)
{
	mEngine = pEngine;
	mFactory = Factory::Instance();
	mCities = 6;
	mMouseLeft = 0;
}

void World::Initialize()
{
	for (int i = 0; i < mCities; i++)
	{
		mCitiesPosition.push_back(Help::CreateCities(mCities, i));
		GameObject* city = mFactory->CreateGameObject(mEngine, Help::CreateCities(mCities, i), GameObjectType::City);
	}
	mAIMissile = new AIMissile(mEngine, mCitiesPosition);
}

void World::MouseClick()
{
	int x, y;
	unsigned int r = SDL_GetMouseState(&x, &y);

	mMousePosition.x = (float)x;
	mMousePosition.y = (float)y;

	mMouseLeft = r & SDL_BUTTON(SDL_BUTTON_LEFT);
}

void World::LauchMissile()
{
	if (Factory::mMissiliesAvailable > 0)
	{
		exVector2 base1 = { 133.0f, 590.0f };
		exVector2 base2 = { 399.0f, 590.0f };
		exVector2 base3 = { 665.0f, 590.0f };
		if (mMousePosition.x < 266)
		{
			GameObject* missile = mFactory->CreateMissiles(mEngine, base1, mMousePosition, GameObjectType::MissileFriend);
		}
		else if (mMousePosition.x >= 266.0f && mMousePosition.x < 532.0f)
		{
			GameObject* missile = mFactory->CreateMissiles(mEngine, base2, mMousePosition, GameObjectType::MissileFriend);
		}
		else if (mMousePosition.x >= 532.0f && mMousePosition.x <= kViewPortWidth)
		{
			GameObject* missile = mFactory->CreateMissiles(mEngine, base3, mMousePosition, GameObjectType::MissileFriend);
		}
	}
}

void World::Destroy()
{
}

void World::DrawGameOver()
{
	int FontID = mEngine->LoadFont("PressStart2P.ttf", 20);
	exVector2 gameOverTextPos = { (kViewPortWidth / 2.0f), (kViewPortHeight / 2.0f)  };
	exColor TextColor;
	TextColor.SetColor(255, 255, 255, 255);
	mEngine->DrawText(FontID, gameOverTextPos, "Game Over", TextColor, 1);
}

void World::Update(float fDeltaT)
{
	if (Factory::Instance()->mCities > 0)
	{
		MouseClick();
		if ((bool)mMouseLeft && !mMouseLeftOld)
		{
			LauchMissile();
		}

		mAIMissile->Update(fDeltaT);

		for (COGMissileController* pMissileController : COGMissileController::mMissileControllerComponents)
		{
			pMissileController->Update(fDeltaT);
		}

		for (COGExplosionController* pExplosionController : COGExplosionController::mExplosionControllerComponents)
		{
			pExplosionController->Update(fDeltaT);
		}

		// run simulation first
		for (COGPhysics* pPhysics : COGPhysics::mPhysicsComponents)
		{
			pPhysics->Update(fDeltaT);
		}

		// then render everything
		for (COGShape* pShape : COGShape::mShapeComponents)
		{
			pShape->Render();
		}

		Factory::Instance()->cleanStaleList();
		mMouseLeftOld = (bool)mMouseLeft;
	}
	else
	{
		DrawGameOver();
	}
}