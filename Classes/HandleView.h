#ifndef __HANDLE_VIEW_H__
#define __HANDLE_VIEW_H__

#include "cocos2d.h"
#include "TouchModel.h"

class HandleView 
	: public cocos2d::CCNode
	, public ITouchView
{
public:
	static HandleView *create();
	virtual bool init();

	virtual void onEnter();
	virtual void onExit();

public:
	void onTonchBegan(cocos2d::CCTouch *pTouch);
	void onTouchMoved(cocos2d::CCTouch *pTouch);
	void onTouchEnded(cocos2d::CCTouch *pTouch);

public:
	void handleMove(cocos2d::CCTouch *pTouch);

private:
	HandleView();
	~HandleView();

private:
	cocos2d::CCSprite *m_circleArea;
	cocos2d::CCSprite *m_handle;
};

#endif