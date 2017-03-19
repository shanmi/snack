#include "SnackView.h"
#include "HandleModel.h"
#include "GameSceneModel.h"
#include "FoodModel.h"
#include "FoodNode.h"
#include "AISnackModel.h"

USING_NS_CC;

SnackView *SnackView::create(CCSize areaSize)
{
	SnackView *snack = new SnackView(areaSize);
	snack->autorelease();
	snack->init();
	return snack;
}

SnackView::SnackView(CCSize areaSize)
: m_moveAngle(90)
, m_distance(0)
, m_moveSpeed(MOVE_SPEED)
, m_foodCount(0)
{
	m_areaSize = areaSize;
}

SnackView::~SnackView()
{

}

void SnackView::onEnter()
{
	CCNode::onEnter();
	TouchModel::theModel()->addView(this);
	SnackModel::theModel()->addView(this);
}

void SnackView::onExit()
{
	CCNode::onExit();
	TouchModel::theModel()->removeView(this);
	SnackModel::theModel()->removeView(this);
}

bool SnackView::init()
{
	m_snackId = -1;
	m_nodeId = -1;
	addHead(4);
	addBody(9, 1000);

	//setAnchorPoint(ccp(0, 0));

	scheduleUpdate();

	return true;
}

void SnackView::addHead(int type)
{
	m_head = SnackModel::theModel()->createHead(m_snackId, 0, 4);
	CCSize size = m_head->getContentSize();
	setContentSize(size);
	m_head->setPosition(ccp(size.width * 0.5f, size.height * 0.5f));
	addChild(m_head);
}

void SnackView::addBody(int type, int count)
{
	for (int i = 0; i < count; ++i)
	{
		SnackNode *node = SnackModel::theModel()->createBody(m_snackId, i+1, type);
		addNode(node);
		if (i == count - 1)
		{
			node->setTail(true);
		}
	}
}

void SnackView::onTonchBegan(cocos2d::CCTouch *pTouch)
{
	handleMove(pTouch);
}

void SnackView::onTouchMoved(cocos2d::CCTouch *pTouch)
{
	handleMove(pTouch);
}

void SnackView::onTouchEnded(cocos2d::CCTouch *pTouch)
{

}

void SnackView::setPosition(float x, float y)
{
	m_position = ccp(x, y);
	auto bodys = SnackModel::theModel()->getBodys();
	for (int i = 0; i < bodys.size(); i++)
	{
		bodys[i]->setPosInView(m_position);
	}
	CCNode::setPosition(x, y);
}

CCPoint SnackView::getPositon()
{
	return m_position;
}

void SnackView::upperSpeed()
{
	m_moveSpeed = MOVE_SPEED * 2;
}

void SnackView::lowerSpeed()
{
	m_moveSpeed = MOVE_SPEED;
}

void SnackView::handleMove(cocos2d::CCTouch *pTouch)
{
	CCPoint location = pTouch->getLocation() - getPosition();
	CCPoint beginPos = getPosition();

	m_moveAngle = HandleModel::theModel()->getAngle();

	m_head->setRotation(m_moveAngle);

}

void SnackView::update(float dt)
{
	CCPoint curPos = m_head->getPosition();
	CCPoint targetPos = m_head->getPosition();

	for (float i = 0; i < m_moveSpeed; i++)
	{
		float const_pi = 180.0f / (float)M_PI;
		float distance = (90 - m_moveAngle) / const_pi;
		float moveX = cos(distance)*MOVE_PACE;
		float moveY = sin(distance)*MOVE_PACE;

		targetPos.x += moveX;
		targetPos.y += moveY;
		m_head->setPosition(targetPos);
		m_head->addNextPosition(targetPos);

		m_distance += abs(moveX);
		if (m_distance < m_head->getContentSize().width * 0.8f)
		{
			SnackModel::theModel()->initMove(moveX, moveY);
		}
		else
		{
			SnackModel::theModel()->startMove();
		}
	}
	GameSceneModel::theModel()->updateViewPosition(targetPos);

	checkFoodsCollision();
	checkSnacksCollision();
	checkWallCollision();
	
}

void SnackView::checkFoodsCollision()
{
	CCPoint posInView = m_head->getPosition() + getPosition();
	auto foods = FoodModel::theModel()->getFoods(posInView);
	for (int i = 0; i < foods.size(); i++)
	{
		auto food = foods[i];
		float distance = abs(ccpDistance(posInView, food->getPosition()));
		if (distance < m_head->getContentSize().height / 2)
		{
			addSnackNode(food->getScore());
			FoodModel::theModel()->removeFood(food);
			SnackModel::theModel()->addFoodNode();
		}
	}
}

void SnackView::checkSnacksCollision()
{
	CCPoint posInView = m_head->getPosition() + getPosition();
	auto snacks = AISnackModel::theModel()->getSnacks(posInView);
	for (int i = 0; i < snacks.size(); i++)
	{
		auto snack = snacks[i];
		float distance = abs(ccpDistance(posInView, snack->getPosInView()+ snack->getPosition()));
		if (distance < m_head->getContentSize().height / 2)
		{
			
		}
	}
}

void SnackView::checkWallCollision()
{
	CCPoint posInView = m_head->getPosInView() + getPosition();
	if (abs(posInView.x) > m_areaSize.width * 0.5f)
	{
		//CCLOG("headpos====================%f", posInView.x);
	}
	if (abs(posInView.y) > m_areaSize.height * 0.5f)
	{
		//CCLOG("headpos====================%f", posInView.y);
	}
}

void SnackView::addNode(SnackNode *node)
{
	CCSize size = getContentSize();
	node->setPosition(ccp(-size.width + m_head->getPositionX() + node->getContentSize().width, size.height / 2));
	node->setPosInView(m_position);
	addChild(node);
	setContentSize(ccp(size.width + node->getContentSize().width*0.8, size.height));
}

void SnackView::removeNode(SnackNode *node)
{
	SnackModel::theModel()->removeNode(node);
}

void SnackView::addSnackNode(int score)
{
	CCLOG("score===================%d", score);
	m_foodCount = m_foodCount + score;
	if (m_foodCount >= NEED_FOOD)
	{
		m_foodCount = m_foodCount - NEED_FOOD;
		std::vector<SnackNode *> m_bodys = SnackModel::theModel()->getBodys();
		auto previousBody = m_bodys[m_bodys.size() - 1];
		previousBody->setTail(false);
		CCPoint pos = previousBody->getPosition();
		SnackNode *node = SnackModel::theModel()->createBody(m_snackId, m_bodys.size(), 9);
		node->setTail(true);
		node->setPosition(pos);
		node->setPosInView(m_position);
		addChild(node);
	}
}