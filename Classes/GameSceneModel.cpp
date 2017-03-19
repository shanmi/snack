#include "GameSceneModel.h"
#include "CommonMacros.h"
#include <algorithm>

USING_NS_CC;

GameSceneModel *GameSceneModel::theModel()
{
	static GameSceneModel model;
	return &model;
}

GameSceneModel::GameSceneModel()
{

}

void GameSceneModel::addView(IGameSceneView *view)
{
	auto iter = find(m_views.begin(), m_views.end(), view);
	if (iter == m_views.end())
	{
		m_views.push_back(view);
	}
}

void GameSceneModel::removeView(IGameSceneView *view)
{
	auto iter = find(m_views.begin(), m_views.end(), view);
	if (iter != m_views.end())
	{
		m_views.erase(iter);
	}
}

void GameSceneModel::updateViewPosition(CCPoint &pos)
{
	NOTIFY_VIEWS(updateViewPosition, pos);
}

void GameSceneModel::removeAISnackById(int snackId)
{
	NOTIFY_VIEWS(removeAISnackById, snackId);
}