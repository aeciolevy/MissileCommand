#include "Game\Public\COGInput.h"

std::vector<COGInput*> COGInput::mInputComponents;

bool isButtonDown(int nScancode)
{
	int nKeys = 0;
	const Uint8 *pState = SDL_GetKeyboardState(&nKeys);
	return pState[nScancode];
}


void COGInput::Update(float DeltaTime)
{
	mPosition = mTransform->GetPosition();
	// Move Paddle  with WS
	if (mPaddle == PaddleIdentifier::PaddleRight)
	{
		if (isButtonDown(SDL_SCANCODE_UP) && mPosition.y > kViewPortHeightMin + 10.0f)
		{
			float temp = - (mVelocity * DeltaTime);
			mTransform->SetPosition(temp);
		}
		else if (isButtonDown(SDL_SCANCODE_DOWN) && mPosition.y + PaddleHeight < kViewPortHeight - 10.0f)
		{
			float temp = (mVelocity * DeltaTime);
			mTransform->SetPosition(temp);
		}
	}

	if (mPaddle == PaddleIdentifier::PaddleLeft)
	{
		if (isButtonDown(SDL_SCANCODE_W) && mPosition.y > kViewPortHeightMin + 10.0f)
		{
			float temp = -(mVelocity * DeltaTime);
			mTransform->SetPosition(temp);
		}
		else if (isButtonDown(SDL_SCANCODE_S) && mPosition.y + PaddleHeight  < kViewPortHeight - 10.0f)
		{
			float temp = (mVelocity * DeltaTime);
			mTransform->SetPosition(temp);
		}
	}

}
