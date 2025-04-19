#include "MathAddon.h"


const float MathAddon::PI = 3.14159265359f;




float MathAddon::angleRadToDeg(float angle) {
	return angle * 180.0f / PI;
}


float MathAddon::angleDegToRad(float angle) {
	return angle * PI / 180.0f;
}


float MathAddon::randFloat() {
	return ((float)rand() / RAND_MAX);
}


float MathAddon::randAngleRad() {
	return randFloat() * 2 * PI;
}