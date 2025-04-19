#pragma once
#include <cstdlib>



class MathAddon
{
public:
	static const float PI;

	static float angleRadToDeg(float angle);
	static float angleDegToRad(float angle);

	static float randFloat();
	static float randAngleRad();
};