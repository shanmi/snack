#include "TouchModel.h"

#include <algorithm>

TouchModel *TouchModel::theModel()
{
	static TouchModel model;
	return &model;
}

void TouchModel::addView(ITouchView *view)
{
	auto iter = find(m_views.begin(), m_views.end(), view);
	if (iter == m_views.end())
	{
		m_views.push_back(view);
	}
}

void TouchModel::removeView(ITouchView *view)
{
	auto iter = find(m_views.begin(), m_views.end(), view);
	if (iter != m_views.end())
	{
		m_views.erase(iter);
	}
}