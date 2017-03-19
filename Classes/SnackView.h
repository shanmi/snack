#ifndef __SNACK_VIEW_H__
#define __SNACK_VIEW_H__

#include "cocos2d.h"
#include "TouchModel.h"
#include "SnackNode.h"
#include "SnackModel.h"

class SnackView 
	: public cocos2d::CCNode
	, public ITouchView
	, public ISnackNode
{
public:
	static SnackView *create(cocos2d::CCSize areaSize);
	virtual bool init();

	virtual void onEnter();
	virtual void onExit();

	virtual void update(float dt);

public:
	void onTonchBegan(cocos2d::CCTouch *pTouch);
	void onTouchMoved(cocos2d::CCTouch *pTouch);
	void onTouchEnded(cocos2d::CCTouch *pTouch);
	virtual void setPosition(float x, float y);
	virtual cocos2d::CCPoint getPositon();
	void upperSpeed();
	void lowerSpeed();
	void checkFoodsCollision();
	void checkSnacksCollision();
	void checkWallCollision();

public:
	void handleMove(cocos2d::CCTouch *pTouch);
	void addNode(SnackNode *node);
	void removeNode(SnackNode *node);
	void addSnackNode(int score);

private:
	SnackView(cocos2d::CCSize areaSize);
	~SnackView();

	void addHead(int type);
	void addBody(int type, int count);

private:
	int m_snackId;
	int m_nodeId;
	cocos2d::CCPoint m_position;

	float m_moveAngle;

	SnackNode *m_head;

	float m_distance;

	cocos2d::CCSize m_areaSize;

	float m_moveSpeed;
	int m_foodCount;
};
#endif