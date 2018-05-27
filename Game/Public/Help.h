#pragma once
#include "Engine\Public\EngineTypes.h"

const float CITY_SIZE = 100;

class Help {

public:
	exVector2 static CreateCities(int numberOfCities, int index)
	{
		float spareSpace = kViewPortWidth - (numberOfCities * CITY_SIZE);
		float padding = spareSpace / numberOfCities;
		float xPos = padding * index + padding + index * CITY_SIZE;
		return { xPos, 590.0f };
	}
};