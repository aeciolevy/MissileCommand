//
// * ENGINE-X
// * SAMPLE GAME
//
// + Game.cpp
// implementation of MyGame, an implementation of exGameInterface
//

#include "Game/Private/Game.h"

#include "Engine/Public/EngineInterface.h"
#include "Engine/Public/SDL.h"

//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* gWindowName = "Pong with Components";

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::MyGame()
	: mEngine( nullptr )
	, mWorld( nullptr )
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::~MyGame()
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::Initialize( exEngineInterface* pEngine )
{
	mEngine = pEngine;

	mScoreManager = ScoreManager::Instance();
	mScoreManager->Initialize(mEngine);

	mWorld = new World(mEngine);
	mWorld->Initialize();
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* MyGame::GetWindowName() const
{
	return gWindowName;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::GetClearColor( exColor& color ) const
{
	color.mColor[0] = 0;
	color.mColor[1] = 0;
	color.mColor[2] = 0;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::OnEvent( SDL_Event* pEvent )
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::OnEventsConsumed()
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::Run( float fDeltaT )
{
	mWorld->Update(fDeltaT);
	mScoreManager->Render();
}
