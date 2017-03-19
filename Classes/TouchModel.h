#ifndef __TOUCH_MODEL_H__
#define __TOUCH_MODEL_H__

#include "cocos2d.h"
#include "CommonMacros.h"

struct ITouchView
{
	virtual void onTonchBegan(cocos2d::CCTouch *pTouch){}
	virtual void onTouchMoved(cocos2d::CCTouch *pTouch){}
	virtual void onTouchEnded(cocos2d::CCTouch *pTouch){}
};

class TouchModel
{
public:
	static TouchModel *theModel();
	~TouchModel(){}

	void addView(ITouchView *view);
	void removeView(ITouchView *view);

public:
	void onTonchBegan(cocos2d::CCTouch *pTouch){ NOTIFY_VIEWS(onTonchBegan, pTouch); }
	void onTouchMoved(cocos2d::CCTouch *pTouch){ NOTIFY_VIEWS(onTouchMoved, pTouch); }
	void onTouchEnded(cocos2d::CCTouch *pTouch){ NOTIFY_VIEWS(onTouchEnded, pTouch); }

	float getMovePace(){ return m_movePace; }
private:
	TouchModel(){ m_movePace = 0; }

private:
	std::vector<ITouchView *> m_views;
	float m_movePace;
};

#endif