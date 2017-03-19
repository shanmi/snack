#include "AISnackModel.h"
#include "HandleModel.h"
#include "CommonMacros.h"
#include "SnackNode.h"
#include <algorithm>

using namespace std;

USING_NS_CC;

AISnackModel *AISnackModel::theModel()
{
	static AISnackModel model;
	return &model;
}

AISnackModel::AISnackModel()
{
	m_curZorder = -1;
	m_moveCount = 0;
}

void AISnackModel::addView(IAISnackNode *view)
{
	auto iter = find(m_views.begin(), m_views.end(), view);
	if (iter == m_views.end())
	{
		m_views.push_back(view);
	}
}

void AISnackModel::removeView(IAISnackNode *view)
{
	auto iter = find(m_views.begin(), m_views.end(), view);
	if (iter != m_views.end())
	{
		m_views.erase(iter);
	}
}

SnackNode *AISnackModel::createBody(int snackId, int nodeId, int type)
{
	auto bodys = getBodys(snackId);
	SnackNode *body = SnackBody::create(snackId, nodeId, TYPE_BODY, type);
	body->setZOrder(m_curZorder--);
	bodys.push_back(body);
	auto iter = m_bodys.find(snackId);
	if (iter == m_bodys.end())
	{
		m_bodys.insert(make_pair(snackId, bodys));
	}
	else
	{
		iter->second = bodys;
	}
	return body;
}

SnackNode *AISnackModel::createHead(int snackId, int nodeId, int type)
{
	SnackNode *head = SnackHead::create(snackId, nodeId, TYPE_HEAD, type);
	head->setZOrder(m_curZorder--);
	m_heads.push_back(head);

	//头也加进身体数组
	auto bodys = getBodys(snackId);
	bodys.push_back(head);
	auto iter = m_bodys.find(snackId);
	if (iter == m_bodys.end())
	{
		m_bodys.insert(make_pair(snackId, bodys));
	}
	else
	{
		iter->second = bodys;
	}
	return head;
}

vector<SnackNode *> AISnackModel::getBodys(int snackId)
{
	vector<SnackNode *> bodys = m_bodys[snackId];
	/*for (auto iter = m_bodys.begin(); iter != m_bodys.end(); ++iter)
	{
		if (iter->first == snackId)
		{
			bodys = iter->second;
			break;
		}
	}*/
	return bodys;
}

void AISnackModel::removeBodys(int snackId)
{
	for (auto iter = m_bodys.begin(); iter != m_bodys.end(); ++iter)
	{
		if (iter->first == snackId)
		{
			//m_bodys.erase(iter);
			vector<SnackNode *> bodys;
			iter->second = bodys;
			//bodys.clear();
			break;
		}
	}
	/*auto iter = m_bodys.find(snackId);
	if (iter != m_bodys.end())
	{
	m_bodys.erase(iter);
	}*/

	for (auto iter = m_heads.begin(); iter != m_heads.end(); ++iter)
	{
		auto head = (*iter);
		if (head->getSnackId() == snackId)
		{
			m_heads.erase(iter);
			break;
		}
	}

}

std::vector<SnackNode *> AISnackModel::getSnacks(cocos2d::CCPoint pos, int beside)
{
	std::vector<SnackNode *> neighbours;
	for (int i = 0; i < m_bodys.size(); i++)
	{
		if (i == beside)
		{
			continue;
		}
		vector<SnackNode *> bodys = m_bodys[i];
		for (int j = 0; j < bodys.size(); j++)
		{
			float distance = abs(ccpDistance(pos, bodys[j]->getPosInView() + bodys[j]->getPosition()));
			if (distance < SNACK_SIZE)
			{
				neighbours.push_back(bodys[j]);
			}
		}
	}
	//for (int i = 0; i < m_heads.size(); i++)
	//{
	//	float distance = abs(ccpDistance(pos, /*bodys[j]->getPositionInView() + */m_views[i]->getPosInView()));
	//	if (distance < SNACK_SIZE)
	//	{
	//		neighbours.push_back(m_heads[i]);
	//	}
	//}
	return neighbours;
}

SnackNode *AISnackModel::getBodyById(int snackId, int nodeId)
{
	auto bodys = getBodys(snackId);
	SnackNode *body;
	if (bodys.size() > 0)
	{
		body = bodys[nodeId];
	}
	return body;
}

void AISnackModel::removeNode(int snackId, SnackNode *node)
{
	auto bodys = getBodys(snackId);
	auto iter = find(bodys.begin(), bodys.end(), node);
	if (iter != bodys.end())
	{
		bodys.erase(iter);
	}
	node->removeFromParent();
}

void AISnackModel::initMove(int snackId, float moveX, float moveY)
{
	m_moveCount++;
	auto bodys = getBodys(snackId);
	for (int i = 1; i < bodys.size(); ++i)
	{
		SnackNode *body = bodys[i];
		body->setPosition(ccp(body->getPositionX() + moveX, body->getPositionY() + moveY));
		body->addNextPosition(body->getPosition());
	}
}

void AISnackModel::startMove(int snackId)
{
	auto bodys = getBodys(snackId);
	for (int i = 0; i < bodys.size(); ++i)
	{
		auto body = bodys[i];
		body->setStartMoving(true);
	}
}

void AISnackModel::addSnackNode(int snackId)
{

	NOTIFY_VIEWS(addSnackNode, snackId);
}

void AISnackModel::addFoodNode()
{
	NOTIFY_VIEWS(addFoodNode);
}

