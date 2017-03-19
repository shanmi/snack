#include "SnackModel.h"
#include "HandleModel.h"
#include "CommonMacros.h"
#include "SnackNode.h"

#include <algorithm>

USING_NS_CC;

SnackModel *SnackModel::theModel()
{
	static SnackModel model;
	return &model;
}

SnackModel::SnackModel()
{
	m_curZorder = -1;
	m_moveCount = 0;
}

void SnackModel::addView(ISnackNode *view)
{
	auto iter = find(m_views.begin(), m_views.end(), view);
	if (iter == m_views.end())
	{
		m_views.push_back(view);
	}
}

void SnackModel::removeView(ISnackNode *view)
{
	auto iter = find(m_views.begin(), m_views.end(), view);
	if (iter != m_views.end())
	{
		m_views.erase(iter);
	}
}

SnackNode *SnackModel::createBody(int snackId, int nodeId, int type)
{
	SnackNode *body = SnackBody::create(snackId, nodeId, TYPE_BODY, type);
	body->setZOrder(m_curZorder--);
	m_bodys.push_back(body);
	return body;
}

SnackNode *SnackModel::createHead(int snackId, int nodeId, int type)
{
	m_head = SnackHead::create(snackId, nodeId, TYPE_HEAD, type);
	m_head->setZOrder(m_curZorder--);
	m_bodys.push_back(m_head);
	return m_head;
}

void SnackModel::removeNode(SnackNode *node)
{
	auto iter = find(m_bodys.begin(), m_bodys.end(), node);
	if (iter != m_bodys.end())
	{
		m_bodys.erase(iter);
	}
	node->removeFromParent();
}

SnackNode *SnackModel::getBodyById(int id)
{
	assert(id < m_bodys.size());
	return m_bodys[id];
}

std::vector<SnackNode *> SnackModel::getSnacks(cocos2d::CCPoint pos)
{
	std::vector<SnackNode *> neighbours;
	for (int i = 0; i < m_bodys.size(); i++)
	{
		float distance = abs(ccpDistance(pos, m_bodys[i]->getPosInView() + m_bodys[i]->getPosition()));
		if (distance < SNACK_SIZE)
		{
			neighbours.push_back(m_bodys[i]);
		}
	}
	return neighbours;
}

void SnackModel::initMove(float moveX, float moveY)
{
	m_moveCount++;
	for (int i = 1; i < m_bodys.size(); ++i)
	{
		SnackNode *body = m_bodys[i];
		body->setPosition(ccp(body->getPositionX() + moveX, body->getPositionY() + moveY));
		body->addNextPosition(body->getPosition());
	}
}

void SnackModel::startMove()
{
	for (int i = 0; i < m_bodys.size(); ++i)
	{
		auto body = m_bodys[i];
		body->setStartMoving(true);
	}
}

void SnackModel::addSnackNode()
{
	NOTIFY_VIEWS(addSnackNode);
}

void SnackModel::addFoodNode()
{
	NOTIFY_VIEWS(addFoodNode);
}

