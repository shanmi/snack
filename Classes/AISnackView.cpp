#include "AISnackView.h"
#include "HandleModel.h"
#include "GameSceneModel.h"
#include "FoodModel.h"
#include "FoodNode.h"
#include "SnackModel.h"

USING_NS_CC;

AISnackView *AISnackView::create(int snackId, CCSize areaSize)
{
	AISnackView *snack = new AISnackView(snackId, areaSize);
	snack->autorelease();
	snack->init();
	return snack;
}

AISnackView::AISnackView(int snackId, CCSize areaSize)
: m_distance(0)
, m_moveSpeed(MOVE_SPEED)
, m_randomTime(5.0f)
, m_countTime(0)
, m_foodCount(0)
{
	m_moveAngle = 90/*CCRANDOM_0_1() * 360.0f*/;
	m_snackId = snackId;
	m_areaSize = areaSize;
}

AISnackView::~AISnackView()
{

}

void AISnackView::onEnter()
{
	CCNode::onEnter();
	TouchModel::theModel()->addView(this);
	AISnackModel::theModel()->addView(this);
}

void AISnackView::onExit()
{
	CCNode::onExit();
	TouchModel::theModel()->removeView(this);
	AISnackModel::theModel()->removeView(this);
}

bool AISnackView::init()
{
	m_nodeId = -1;
	m_skin = rand() % 10 + 1;
	addHead(m_skin);
	addBody(m_skin, 5);

	//setAnchorPoint(ccp(0, 0));

	scheduleUpdate();

	return true;
}

void AISnackView::addHead(int type)
{
	m_head = AISnackModel::theModel()->createHead(m_snackId, 0, type);
	CCSize size = m_head->getContentSize();
	setContentSize(size);
	m_head->setPosition(ccp(size.width * 0.5f, size.height * 0.5f));
	addChild(m_head);
}

void AISnackView::addBody(int type, int count)
{
	for (int i = 0; i < count; ++i)
	{
		SnackNode *node = AISnackModel::theModel()->createBody(m_snackId, i+1, type);
		addNode(node);
		if (i == count - 1)
		{
			node->setTail(true);
		}
	}
}

void AISnackView::onTonchBegan(cocos2d::CCTouch *pTouch)
{
	handleMove(pTouch);
}

void AISnackView::onTouchMoved(cocos2d::CCTouch *pTouch)
{
	handleMove(pTouch);
}

void AISnackView::onTouchEnded(cocos2d::CCTouch *pTouch)
{

}

void AISnackView::setPosition(float x, float y)
{
	m_position = ccp(x, y);
	auto bodys = AISnackModel::theModel()->getBodys(m_snackId);
	for (int i = 0; i < bodys.size(); i++)
	{
		bodys[i]->setPosInView(m_position);
	}
	CCNode::setPosition(x, y);
}

CCPoint AISnackView::getPositon()
{
	return m_position;
}

void AISnackView::upperSpeed()
{
	m_moveSpeed = MOVE_SPEED * 2;
}

void AISnackView::lowerSpeed()
{
	m_moveSpeed = MOVE_SPEED;
}

void AISnackView::handleMove(cocos2d::CCTouch *pTouch)
{
	

}

void AISnackView::update(float dt)
{
	m_countTime += dt;
	if (m_countTime > m_randomTime)
	{
		m_countTime = 0;
		m_randomTime = CCRANDOM_0_1() * 3.0f + 1.0f;
		m_moveAngle = CCRANDOM_0_1() * 360.0f;
	}
	
	CCPoint curPos = m_head->getPosition();
	CCPoint targetPos = m_head->getPosition();

	m_head->setRotation(m_moveAngle);

	for (int i = 0; i < m_moveSpeed; i++)
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
			AISnackModel::theModel()->initMove(m_snackId, moveX, moveY);
		}
		else
		{
			AISnackModel::theModel()->startMove(m_snackId);
		}
		checkFoodsCollision();
		checkSnacksCollision();
		checkWallCollision();
	}
}

void AISnackView::checkFoodsCollision()
{
	CCPoint posInView = m_head->getPosition() + getPosition();
	auto foods = FoodModel::theModel()->getFoods(posInView);
	for (int i = 0; i < foods.size(); i++)
	{
		auto food = foods[i];
		float distance = abs(ccpDistance(posInView, food->getPosition()));
		if (distance < m_head->getContentSize().height/2)
		{
			FoodModel::theModel()->removeFood(food);
			addSnackNode(m_snackId, food->getScore());
			SnackModel::theModel()->addFoodNode();
		}
	}
}

void AISnackView::checkSnacksCollision()
{
	CCPoint posInView = m_head->getPosition() + getPosition();
	auto snacks = SnackModel::theModel()->getSnacks(posInView);
	for (int i = 0; i < snacks.size(); i++)
	{
		auto snack = snacks[i];
		float distance = abs(ccpDistance(posInView, snack->getPosInView() + snack->getPosition()));
		if (distance < m_head->getContentSize().height / 2)
		{
			GameSceneModel::theModel()->removeAISnackById(m_snackId);
			break;
		}
	}

	auto aisnacks = AISnackModel::theModel()->getSnacks(posInView, m_snackId);
	for (int i = 0; i < aisnacks.size(); i++)
	{
		auto aisnack = aisnacks[i];
		float distance = abs(ccpDistance(posInView, aisnack->getPosInView() + aisnack->getPosition()));
		if (distance < m_head->getContentSize().height / 2)
		{
			GameSceneModel::theModel()->removeAISnackById(m_snackId);
			break;
		}
	}
}

void AISnackView::bodyToFood()
{
	auto bodys = AISnackModel::theModel()->getBodys(m_snackId);
	for (int i = 0; i < bodys.size(); i++)
	{

	}
}

void AISnackView::checkWallCollision()
{
	CCPoint posInView = m_head->getPosition() + getPosition();
	if (abs(posInView.x) > m_areaSize.width * 0.5f - (BORDER_SIZE*0.5f))
	{
		m_moveAngle = m_moveAngle + 135;
		m_countTime = 0;
		m_randomTime = 3;
	}
	else if (abs(posInView.y) > m_areaSize.height * 0.5f - (BORDER_SIZE*0.5f))
	{
		m_moveAngle = m_moveAngle + 135;
		m_countTime = 0;
		m_randomTime = 3;
	}
}

void AISnackView::addNode(SnackNode *node)
{
	CCSize size = getContentSize();
	node->setPosition(ccp(-size.width + m_head->getPositionX() + node->getContentSize().width, size.height / 2));
	node->setPosInView(m_position);
	addChild(node);
	setContentSize(ccp(size.width + node->getContentSize().width*0.8, size.height));
}

void AISnackView::removeNode(SnackNode *node)
{
	AISnackModel::theModel()->removeNode(m_snackId, node);
}

void AISnackView::addSnackNode(int snackId, int score)
{
	if (snackId == m_snackId)
	{
		m_foodCount = m_foodCount + score;
		if (m_foodCount >= NEED_FOOD)
		{
			m_foodCount = 0;
			std::vector<SnackNode *> m_bodys = AISnackModel::theModel()->getBodys(m_snackId);
			auto previousBody = m_bodys[m_bodys.size() - 1];
			previousBody->setTail(false);
			CCPoint pos = previousBody->getPosition();
			SnackNode *node = AISnackModel::theModel()->createBody(m_snackId, m_bodys.size(), m_skin);
			node->setTail(true);
			node->setPosition(pos);
			node->setPosInView(m_position);
			addChild(node);
		}
	}
}