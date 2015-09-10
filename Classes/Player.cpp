#include "Player.h"

Player::Player() {
/*初始化主角跳跃标记为false*/
	m_isJumping = false;
}

Player::~Player() {

}

bool Player::init() {
	return true;
}

void Player::run() {
	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("Hforward.plist", "Hforward.png");

	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*>frameList;

	/*创建精灵帧对象，添加到列表里*/
	for (int i = 1;i <= 4;i++) {
		frame = frameCache->getSpriteFrameByName(StringUtils::format("Hforward%d.png", i));
		frameList.pushBack(frame);
	}

	/*根据精灵帧对象创建动画对象*/
	Animation* animation = Animation::createWithSpriteFrames(frameList);
	animation->setLoops(-1);              //循环播放
	animation->setDelayPerUnit(0.08f);    //每帧播放间隔

	/*创建动画动作*/
	Animate* animate = Animate::create(animation);

	/*精灵执行动作*/
	m_sprite->runAction(animate);
}

void Player::setViewPointByPlayer() {
	
	if (m_sprite == NULL){
	return; }

	Layer* parent = (Layer*)getParent();

	/*地图方块数量*/
	Size mapTiledNum = m_map->getMapSize();

	/*地图单个格子大小*/
	Size tiledSize = m_map->getTileSize();

	/*地图大小*/
	Size mapSize = Size(mapTiledNum.width*tiledSize.width, mapTiledNum.height*tiledSize.height);

	/*屏幕大小*/
	Size visibleSize = Director::getInstance()->getVisibleSize();

	/*主角坐标*/
	Point spritePos = getPosition();

	/*如果主角坐标小于屏幕的一半，则取屏幕中点的坐标，否则取主角的坐标*/
	float x = std::max(spritePos.x, visibleSize.width / 2);
	float y = std::max(spritePos.y, visibleSize.height / 2);

	/*如果x y的坐标大于右上角的极限值，则取极限值的坐标，即走到终点后地图不动了*/
	x = std::min(x, mapSize.width - visibleSize.width / 2);
	y = std::min(y, mapSize.height - visibleSize.height / 2);

	/*目标点*/
	Point destPos = Point(x, y);

	/*屏幕中点*/
	Point centerPos = Point(visibleSize.width / 2, visibleSize.height / 2);

	/*计算屏幕中点和所要移动的目的点之间的距离*/
	Point viewPos = centerPos - destPos;

	parent->setPosition(viewPos);

}

void Player::setTagPosition(int x, int y) {
	Entity::setTagPosition(x, y);

	/*以主角小新为中心移动地图*/
	setViewPointByPlayer();

}

void Player::setTiledMap(TMXTiledMap* map) {
	this->m_map = map;
}

void Player::jump() {
	if (getSprite() == NULL) {
		return;
	}

	/*如果主角还在跳跃中，则不重复执行*/
	if (m_isJumping) {
		return;
	}

	/*标记主角为跳跃状态*/
	m_isJumping = true;

	/*创建跳跃动作，原地跳跃*/
	auto jump = JumpBy::create(2.0f, Point(0, 0), 250, 1);

	/*创建回调动作，跳跃结束后修改m_isJumping标记为false*/
	auto callFunc = CallFunc::create([&]() {
		m_isJumping = false;
	});

	/*创建连续动作*/
	auto jumpActions = Sequence::create(jump, callFunc, NULL);

	/*执行动作*/
	this->runAction(jumpActions);
}