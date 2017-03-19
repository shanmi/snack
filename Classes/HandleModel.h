#ifndef __HANDLE_MODEL_H__
#define __HANDLE_MODEL_H__

#include "cocos2d.h"

class HandleModel 
{
public:
	static HandleModel *theModel();
	~HandleModel(){}

public:
	float getDegreeTwoPoints(cocos2d::CCPoint p1, cocos2d::CCPoint p2);
	void setAngle(float angle) { m_angle = angle; }
	float getAngle() { return m_angle; }
private:
	HandleModel();

private:
	float m_angle;

};
#endif