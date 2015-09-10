#include "Entity.h"
#include "DemoControllerListener.h"
#include "DemoController.h"

void Entity::bindSprite(Sprite* sprite){
	m_sprite = sprite;
	this->addChild(m_sprite);
}

void Entity::setController(DemoController* DemoController) {
	this->m_DemoController = DemoController;
	m_DemoController->setDemoControllerListener(this);
}

void Entity::setTagPosition(int x, int y) {
	setPosition(Point(x, y));
}

Point Entity::getTagPosition() {
	return getPosition();
}

Sprite* Entity::getSprite() {
	return this->m_sprite;
}