#include "HandleModel.h"
#include "CommonMacros.h"

USING_NS_CC;

HandleModel *HandleModel::theModel()
{
	static HandleModel model;
	return &model;
}

HandleModel::HandleModel()
{

}

float HandleModel::getDegreeTwoPoints(CCPoint p1, CCPoint p2){

	float delta_x = (int)(p2.x - p1.x);
	float delta_y = (int)(p2.y - p1.y);
	float degree = 0.f;
	float fRadian = 0.f;
	float const_pi = 180.0f / (float)M_PI;
	if (delta_y >= 0)
	{
		if (delta_x > 0)
		{
			fRadian = atan((float)(delta_y / delta_x));
			degree = const_pi * fRadian;
		}
		else if (delta_x < 0){
			fRadian = atan((float)(delta_y / delta_x)) * (-1);
			degree = const_pi * (M_PI - fRadian);
		}
		else if (delta_x == 0){
			degree = 90;
		}
	}
	else if (delta_y < 0){
		if (delta_x > 0){
			fRadian = atan((float)(delta_y / delta_x)) * (-1);
			degree = const_pi * (2 * M_PI - fRadian);
		}
		else if (delta_x < 0){
			fRadian = atan((float)(delta_y / delta_x));
			degree = const_pi * (M_PI + fRadian);
		}
		else if (delta_x == 0){
			degree = 270;
		}
	}
	return 90 - degree;
}
