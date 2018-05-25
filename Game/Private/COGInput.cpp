#include "Game\Public\COGInput.h"

std::vector<COGInput*> COGInput::mInputComponents;

bool COGInput::MouseClick(int nScancode)
{
	int x, y;
	unsigned int r = SDL_GetMouseState(&x, &y);

	mMousePosition.x = (float)x;
	mMousePosition.y = (float)y;

	mMouseLeft = r & SDL_BUTTON(SDL_BUTTON_LEFT);
	return (bool) mMouseLeft;
}


void COGInput::Update(float DeltaTime)
{
	mPosition = mTransform->GetPosition();
	// Move Paddle  with WS
	/*if (mPaddle == PaddleIdentifier::PaddleRight)
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
	}*/

}
