#include "Game\Public\ScoreManager.h"
#include <string>
//Initializing static member outside of the constructor
ScoreManager* Singleton<ScoreManager>::mSingleton = nullptr;

int ScoreManager::scoreP1 = 0;
int ScoreManager::scoreP2 = 0;

void ScoreManager::Initialize(exEngineInterface* engine)
{
	mEngine = engine;
	mFontID = mEngine->LoadFont("PressStart2P.ttf", 20);
	mTextP1 = { ((kViewPortWidth / 2.0f) - 300.0f), 15.0f };
	mScorePositionP1 = { ((kViewPortWidth / 2.0f) - 250.0f), 40.0f };
	mTextP2 = { ((kViewPortWidth / 2.0f) + 200.0f), 15.0f };
	mScorePositionP2 = { ((kViewPortWidth / 2.0f) + 250.0f), 40.0f };
	mTextColor.mColor[0] = 255;
	mTextColor.mColor[1] = 255;
	mTextColor.mColor[2] = 255;
	mTextColor.mColor[3] = 255;
}


void ScoreManager::P1RenderText()
{
	mEngine->DrawText(mFontID, mTextP1, "Player1", mTextColor, 0);
	std::string p1Score(std::to_string(ScoreManager::scoreP1));
	const char* p1ScoreChar = p1Score.c_str();
	mEngine->DrawText(mFontID, mScorePositionP1, p1ScoreChar, mTextColor, 0);
}


void ScoreManager::P2RenderText()
{
	mEngine->DrawText(mFontID, mTextP2, "Player2", mTextColor, 0);
	std::string p2Score(std::to_string(ScoreManager::scoreP2));
	const char* p2ScoreChar = p2Score.c_str();
	mEngine->DrawText(mFontID, mScorePositionP2, p2ScoreChar, mTextColor, 0);
}

void ScoreManager::Render()
{
	P1RenderText();
	P2RenderText();
}