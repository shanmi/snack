#define BORDER_SIZE 30 //���ɾ���ı�Ե����
#define SNACK_SIZE 28  //�ߵĴ�С
#define MOVE_PACE 2.4  //�ƶ�����
#define MOVE_SPEED 1  //�ƶ��ٶ�
#define NEED_FOOD 6  //һ���������6��ʳ��

#define NOTIFY_VIEWS(_FUNC_ ,...)						\
for (size_t index = 0; index < m_views.size(); ++index) \
{														\
	m_views[index]->_FUNC_(__VA_ARGS__);				\
}
