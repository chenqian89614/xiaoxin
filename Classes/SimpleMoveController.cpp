#include "SimpleMoveController.h"

bool SimpleMoveController::init() {
	this->m_iSpeed = 0;

	/*cocos2dx中的自带帧函数update调用*/
	this->scheduleUpdate();

	return true;
}

void SimpleMoveController::update(float dt) {
	if (m_democontrollerlistener == NULL) {
		return;
	}

	/*增加移动对象的x坐标值*/
	Point pos = m_democontrollerlistener->getTagPosition();
	pos.x += m_iSpeed;
	m_democontrollerlistener->setTagPosition(pos.x, pos.y);
}

void SimpleMoveController::setiSpeed(int iSpeed) {

	this->m_iSpeed = iSpeed;
}