#ifndef __AI_SNACK_MODEL_H__
#define __AI_SNACK_MODEL_H__

#include "cocos2d.h"

struct IAISnackNode
{
	virtual void addSnackNode(int snackId){}
	virtual void addFoodNode(){}
};

class SnackNode;
class AISnackModel
{
public:
	static AISnackModel *theModel();
	~AISnackModel(){}

public:
	void addView(IAISnackNode *view);
	void removeView(IAISnackNode *view);

	SnackNode *createBody(int snackId, int nodeId, int type);
	SnackNode *createHead(int snackId, int nodeId, int type);

	std::vector<SnackNode *> getBodys(int snackId);
	SnackNode * haha(int id){ return m_heads[id]; }
	std::vector<SnackNode *> getHeads(){ return m_heads; }
	void removeBodys(int snackId);
	std::vector<SnackNode *> getSnacks(cocos2d::CCPoint pos, int beside = -1);
	SnackNode *getBodyById(int snackId, int nodeId);

	void removeNode(int snackId, SnackNode *node);

	void initMove(int snackId, float moveX, float moveY);
	void startMove(int snackId);

	void addSnackNode(int snackId);
	void addFoodNode();

	int getMoveCount(){ return m_moveCount; }
private:
	AISnackModel();

private:
	std::vector<SnackNode *> m_heads;
	std::map<int, std::vector<SnackNode *>> m_bodys;
	std::vector<IAISnackNode *> m_views;

	int m_curZorder;
	int m_moveCount; //初始移动次数
};

#endif