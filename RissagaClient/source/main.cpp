
#include "Utils/Math.h"
#include "Utils\Point.h"
#include "Utils/String.h"
#include "Utils/Rect.h"
#include "Utils/Size.h"

using namespace Ris;

int main(int argc, char *argv[])
{
/*	Pointf2D punto(-1.0f, 0.0f);
	float rad = punto.getRadians();
	float deg = punto.getDegrees();
	float deg1 = punto.getDegrees180();
	float deg3 = punto.getDegrees360();
	Pointf2D l = punto.limitX(1.2f, 1.3f);
	Pointf2D c = punto.limit(2, 5);
	Pointf2D r; r.fromDegrees(45);
	deg = r.getDegrees();
	r.rotateDegrees(-10);
	deg = r.getDegrees();
	return (int)deg;
*/
/*	std::string ss = "a";
	String s = ss;
	String a = 123;
	s.fromNumber(10);
	s.fromNumber(11.0f);
	return s.length();
*/
	Rect r(1, 2, 3, 4);
	Sizei i(10, 10);
	Rect rr(Pointi2D(10,10), i);
	return r.x;
}
