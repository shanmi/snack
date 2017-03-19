#ifndef __GAME_SCENE_MODEL_H__
#define __GAME_SCENE_MODEL_H__

#include "cocos2d.h"

struct IGameSceneView
{
	virtual void updateViewPosition(cocos2d::CCPoint &pos){}
	virtual void removeAISnackById(int snackId){}
};

class GameSceneModel
{
public:
	static GameSceneModel *theModel();
	~GameSceneModel(){}

	void addView(IGameSceneView *view);
	void removeView(IGameSceneView *view);

	void updateViewPosition(cocos2d::CCPoint &pos);
	void removeAISnackById(int snackId);

private:
	GameSceneModel();

private:
	std::vector<IGameSceneView *> m_views;
};
#endif