#pragma once
#include "Game\Public\Singleton.h"
#include "Engine\Public\EngineTypes.h"
#include "Engine\Public\EngineInterface.h"
class ScoreManager : public Singleton<ScoreManager>
{
public:
	friend class Singleton<ScoreManager>;
	void Initialize(exEngineInterface* engine);
	void Render();
	void P1RenderText();
	void P2RenderText();
	static int scoreP1;
	static int scoreP2;
private:
	exEngineInterface * mEngine;
	int					mFontID;
	exColor				mTextColor;
	exVector2			mTextP1;
	exVector2			mTextP2;
	exVector2			mScorePositionP1;
	exVector2			mScorePositionP2;
};