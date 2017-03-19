#include "SnackNode.h"
#include "TouchModel.h"
#include "HandleModel.h"
#include "SnackModel.h"
#include "AISnackModel.h"
#include "GameSceneModel.h"

USING_NS_CC;

SnackNode *SnackNode::create(int snackId, int nodeId, int nodeType, int skinType, int skinType2)
{
	if (skinType2 = -1)
	{
		skinType2 = skinType;
	}
	SnackNode *node;
	switch (nodeType)
	{
	case TYPE_HEAD:
		node = new SnackHead(snackId, nodeId, skinType);
		break;
	case TYPE_BODY:
		node = new SnackBody(snackId, nodeId, skinType, skinType2);
		break;
	default:
		node = new SnackBody(snackId, nodeId, skinType, skinType2);
		break;
	}
	node->autorelease();
	node->init();
	return node;
}

SnackNode::SnackNode(int snackId, int nodeId, int skinType, int skinType2)
{
	m_snackId = snackId;
	m_nodeId = nodeId;
	m_skinType = skinType;
	if (skinType2 == -1)
	{
		m_skinType2 = skinType;
	}
	else
	{
		m_skinType2 = skinType2;
	}
	b_startMoving = false;
	m_posArray = CCPointArray::create(200);
	m_posIndex = 0;
	m_curIndex = 3;
	b_isTail = false;
	m_posArray->retain();

}

bool SnackNode::init()
{
	initLayout();

	scheduleUpdate();

	return true;
}

SnackNode::~SnackNode()
{
	m_posArray->release();
}

void SnackNode::addNextPosition(CCPoint pos)
{
	m_posIndex = m_posIndex % 200;
	if (m_posArray->count() >= 200)
	{
		m_posArray->replaceControlPoint(pos, m_posIndex++);
	}
	else
	{
		m_posIndex++;
;		m_posArray->addControlPoint(pos);
	}
}

void SnackNode::removeFirstPosition()
{
	//m_posArray->removeControlPointAtIndex(0);
}

CCPoint SnackNode::getNextPos(int size)
{
	m_curIndex = m_curIndex % 200;
	return m_posArray->getControlPointAtIndex(m_curIndex++);
}

void SnackNode::setPosInView(CCPoint pos)
{
	m_posInView = pos;
}

void SnackNode::update(float dt)
{
	if (m_nodeId == 0) //头
	{
		if (m_snackId == -1) //自己
		{
			//判断跟其他蛇的碰撞

		}
		else
		{
			
		}
		return; 
	}
	if (m_snackId == -1) //自己
	{
		if (b_startMoving)
		{
			auto previousBody = SnackModel::theModel()->getBodyById(m_nodeId - 1);
			CCPoint pos = previousBody->getNextPos(m_nodeId);
			setPosition(pos);
			addNextPosition(pos);
			previousBody->removeFirstPosition();
		}
		if (b_isTail)
		{
			m_curIndex = (m_posIndex - 5) % 200;
		}

		CCPoint posInView = getPosition() + getPosInView();
		/*auto heads = AISnackModel::theModel()->getHeads();
		for (int i = 0; i < heads.size(); i++)
		{
			auto snack = heads[i];
			float distance = abs(ccpDistance(posInView, snack->getPosInView() + snack->getPosition()));
			if (distance < getContentSize().height / 2)
			{
				GameSceneModel::theModel()->removeAISnackById(m_snackId);
				break;
			}
		}*/
		/*for (int i = 0; i < 10; i++)
		{
			auto snack = AISnackModel::theModel()->haha(i);
			float distance = abs(ccpDistance(posInView, snack->getPosInView() + snack->getPosition()));
			if (distance < getContentSize().height / 2)
			{
				GameSceneModel::theModel()->removeAISnackById(m_snackId);
				break;
			}
		}*/
	}
	else
	{
		if (b_startMoving)
		{
			//auto bodys = AISnackModel::theModel()->getBodys(m_snackId);
			auto previousBody = AISnackModel::theModel()->getBodyById(m_snackId, m_nodeId - 1);
			CCPoint pos = previousBody->getNextPos(m_nodeId);
			setPosition(pos);
			addNextPosition(pos);
			previousBody->removeFirstPosition();
		}
		if (b_isTail)
		{
			m_curIndex = (m_posIndex - 5) % 200;
		}
		//CCPoint posInView = getPosition() + getPosInView();
		//auto head = SnackModel::theModel()->getHead();
		//float distance = abs(ccpDistance(posInView, head->getPosInView() + head->getPosition()));
		//if (distance < getContentSize().height / 2)
		//{
		//	//GameSceneModel::theModel()->removeAISnackById(m_snackId);
		//}

	}
	

}
///////////////////////////////////////////////////////////////

void SnackHead::initLayout()
{
	char temp[50] = {0};
	sprintf(temp, "snack/skin_%d_head.png", m_skinType);
	CCSprite *head = CCSprite::create(temp);
	m_scale = SNACK_SIZE / head->getContentSize().width;
	head->setScale(m_scale);
	CCSize size = head->getContentSize() * m_scale;    
	head->setPosition(ccp(size.width * 0.5f, size.height * 0.5f));
	setContentSize(size);
	addChild(head);

	setRotation(90);
	setAnchorPoint(ccp(0.5f, 0.5f));
}

///////////////////////////////////////////////////////////////

void SnackBody::initLayout()
{
	char temp[100] = {0};
	sprintf(temp, "snack/skin_%d_body.png", m_skinType);
	CCSprite* body = CCSprite::create(temp);
	m_scale = SNACK_SIZE / body->getContentSize().width * 0.75f;
	body->setScale(m_scale);
	CCSize size = body->getContentSize()*m_scale;
	body->setPosition(ccp(size.width * 0.5f, size.height * 0.5f));
	addChild(body);

	setRotation(90);
	setAnchorPoint(ccp(0.5f, 0.5f));

	setContentSize(size);
}