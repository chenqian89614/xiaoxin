#include <vector>
#include "cocos2d.h"
#include "../geolib/GeoLib.h"

using namespace std;

class CalUtil
{
	public:
		static float xmin;
		static float xmax;
		static float ymin;
		static float ymax;
		static vector<C2DPolygon> calParts(float sx,float sy,float ex,float ey);
		static float* makeArray(float x,float y); 
};
