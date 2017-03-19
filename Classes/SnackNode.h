#ifndef __SNACK_NODE_H__
#define __SNACK_NODE_H__

#include "cocos2d.h"

enum SnackSkin
{
	SKIN_HAT,

	SKIN_GREEN,
};

enum NodeType
{
	TYPE_HEAD,
	TYPE_BODY,
};

class SnackNode
	: public cocos2d::CCNode
{
public:
	static SnackNode *create(int snackId, int nodeId, int nodeType, int skinType, int skinType2 = -1);
	~SnackNode();

	virtual bool init();
	virtual void update(float dt);

	virtual void initLayout(){}
	
public:
	int getSnackId(){ return m_snackId; }
	int getNodeId(){ return m_nodeId; }
	void setPosInView(cocos2d::CCPoint pos);
	cocos2d::CCPoint getPosInView(){ return m_posInView; }

	void setScale(float scale){ m_scale = scale; }
	void addNextPosition(cocos2d::CCPoint pos);
	void removeFirstPosition();
	cocos2d::CCPoint getNextPos(int size);
	void setStartMoving(bool startMoving){ b_startMoving = startMoving; }
	bool isTail(){ return b_isTail; }
	void setTail(bool isTail){ b_isTail = isTail; }

protected:
	SnackNode(int snackId, int nodeId, int skinType, int skinType2 = -1);

public:
	int m_snackId;
	int m_nodeId;
	float m_scale;
	int m_skinType;
	int m_skinType2;
	cocos2d::CCPoint m_posInView;
	cocos2d::CCPointArray *m_posArray;
	int m_posIndex;
	int m_curIndex;
	bool b_startMoving;
	bool b_isTail;
};

/////////////////////////////////////////////////

class SnackHead : public SnackNode
{
public:
	SnackHead(int snackId, int nodeId, int nodeType) : SnackNode(snackId, nodeId, nodeType){}
	virtual void initLayout();
};

/////////////////////////////////////////////////
class SnackBody : public SnackNode
{
public:
	SnackBody(int snackId, int nodeId, int skinType, int skinType2) : SnackNode(snackId, nodeId, skinType, skinType2){}
	virtual void initLayout();
};
#endif