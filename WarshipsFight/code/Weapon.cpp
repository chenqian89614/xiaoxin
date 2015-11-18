#include "cocos2d.h"
#include "Weapon.h"
using namespace cocos2d;

Weapon* Weapon::create(int index,Point p,int launchForm)
{
	Weapon* tempWp = new Weapon(launchForm);
	std::string objPath = StringUtils::format("daodan%d.obj",index);
	std::string pngPath = StringUtils::format("daodan%d.png",index);
	tempWp->initWithFile(objPath.c_str());
	tempWp->setTexture(pngPath.c_str());
    tempWp->retain();
	tempWp->setRotation3D(Vertex3F(-90,90,0 ));
	tempWp->setPosition(p);
	return tempWp;
}
Weapon::Weapon(int launchForm)
{
	this->launchForm = launchForm;
}
