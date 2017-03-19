#ifndef __AI_SNACK_VIEW_H__
#define __AI_SNACK_VIEW_H__

#include "cocos2d.h"
#include "TouchModel.h"
#include "SnackNode.h"
#include "AISnackModel.h"

class AISnackView 
	: public cocos2d::CCNode
	, public ITouchView
	, public IAISnackNode
{
public:
	static AISnackView *create(int snackId, cocos2d::CCSize areaSize);
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
	void bodyToFood();

public:
	void handleMove(cocos2d::CCTouch *pTouch);
	void addNode(SnackNode *node);
	void removeNode(SnackNode *node);
	void addSnackNode(int snackId, int score);
	int getSnackId(){ return m_snackId; }

private:
	AISnackView(int snackId, cocos2d::CCSize areaSize);
	~AISnackView();

	void addHead(int type);
	void addBody(int type, int count);

private:
	int m_snackId;
	int m_nodeId;
	int m_skin;
	float m_moveAngle;
	cocos2d::CCPoint m_position;

	SnackNode *m_head;
	cocos2d::CCSize m_areaSize;

	float m_distance;

	float m_moveSpeed;

	float m_randomTime;
	float m_countTime;
	int m_foodCount;

};
#endif