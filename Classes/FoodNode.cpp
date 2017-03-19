#include "FoodNode.h"
#include "SnackModel.h"
#include "AISnackModel.h"
#include "FoodModel.h"
#include "SnackNode.h"

USING_NS_CC;

FoodNode::FoodNode(int color)
:m_color(color)
{
	m_score = 1;
}

void FoodNode::onEnter()
{
	CCNode::onEnter();
	GameSceneModel::theModel()->addView(this);
}

void FoodNode::onExit()
{
	CCNode::onExit();
	GameSceneModel::theModel()->removeView(this);
}

FoodNode *FoodNode::create(int color)
{
	char temp[20] = { 0 };
	sprintf(temp, "node%d.png", color);
	FoodNode *node = new FoodNode(color);
	if (node && node->initWithSpriteFrameName(temp))
	{
		node->autorelease();
		node->init();
		return node;
	}
	CC_SAFE_DELETE(node);
	return NULL;
}

bool FoodNode::init()
{
	m_scale = FOOD_SIZE / getContentSize().width;
	setScale(m_scale);
	CCSize size = getContentSize() * m_scale;
	setContentSize(size);

	scheduleUpdate();

	return true;
}

void FoodNode::update(float dt)
{
	//CCPoint posInView = getPosition();
	/*auto heads = AISnackModel::theModel()->getHeads();
	for (int i = 0; i < heads.size(); i++)
	{
		auto head = heads[i];
		float distance = abs(ccpDistance(posInView, head->getPosInView() + head->getPosition()));
		if (distance < getContentSize().height / 2)
		{
			FoodModel::theModel()->removeFood(this);
		}
	}*/

	/*auto head = SnackModel::theModel()->getHead();
	float distance = abs(ccpDistance(posInView, head->getPosInView() + head->getPosition()));
	if (distance < head->getContentSize().height / 2)
	{
		FoodModel::theModel()->removeFood(this);
	}*/
}
