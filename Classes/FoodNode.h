#ifndef __FOOD_NODE_H__
#define __FOOD_NODE_H__

enum FoodColor
{
	cColor1 = 1,
	cColor2,
	cColor3,
	cColor4,
	cColor5,
	cColor6,
	cColor7,
	cColor8,
};

class SnackNode;
#include "cocos2d.h"
#include "GameSceneModel.h"

#define FOOD_SIZE 8

class FoodNode 
	: public cocos2d::CCSprite
	, public IGameSceneView
{
public:
	static FoodNode *create(int color);
	~FoodNode(){}

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	virtual void update(float dt);

public:
	void setScore(int score){ m_score = score; }
	int getScore(){ return m_score; }

private:
	FoodNode(int color);

private:
	int m_color;
	float m_scale;
	int m_score;
};

#endif