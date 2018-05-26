#include "Game\Public\COGController.h"
#include "Game\Public\Output.h"

std::vector<COGController*> COGController::mControllerComponents;


void COGController::Update(float DeltaTime)
{
	mPosition = mTransform->GetPosition();
}
