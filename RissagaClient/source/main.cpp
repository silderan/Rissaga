
#include "Utils/Math.h"
#include "Utils\Point.h"

using namespace Ris;

int main(int argc, char *argv[])
{
	Pointf punto(1.0f, 1.5f);
	float rad = punto.getRadian();
	float deg = punto.getAngle();
	float deg1 = punto.getAngle180();
	float deg3 = punto.getAngle360();
	Pointf l = punto.limitX(1.2f, 1.3f);
	Pointf c = punto.limit(2,5);
	return 0;
}
