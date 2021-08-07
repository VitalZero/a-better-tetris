#include "location.h"

void Location::Add(const Location& location)
{
	x += location.x;
	y += location.y;
}