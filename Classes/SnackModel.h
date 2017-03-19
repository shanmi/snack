#ifndef __SNACK_MODEL_H__
#define __SNACK_MODEL_H__

#include "cocos2d.h"

struct ISnackNode
{
	virtual void addSnackNode(){}
	virtual void addFoodNode(){}
};

class SnackNode;
class SnackModel
{
public:
	static SnackModel *theModel();
	~SnackModel(){}

public:
	void addView(ISnackNode *view);
	void removeView(ISnackNode *view);

	SnackNode *createBody(int snackId, int nodeId, int type);
	SnackNode *createHead(int snackId, int nodeId, int type);

	std::vector<SnackNode *> getBodys(){ return m_bodys; }
	SnackNode *getHead(){ return m_head; }
	std::vector<SnackNode *> getSnacks(cocos2d::CCPoint pos);
	SnackNode *getBodyById(int id);

	void removeNode(SnackNode *node);

	void initMove(float moveX, float moveY);
	void startMove();

	void addSnackNode();
	void addFoodNode();

	int getMoveCount(){ return m_moveCount; }
private:
	SnackModel();

private:
	SnackNode *m_head;
	std::vector<SnackNode *> m_bodys;
	std::vector<ISnackNode *> m_views;

	int m_curZorder;
	int m_moveCount; //初始移动次数
};

#endif