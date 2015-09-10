#include "Player.h"

Player::Player() {
/*��ʼ��������Ծ���Ϊfalse*/
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

	/*��������֡������ӵ��б���*/
	for (int i = 1;i <= 4;i++) {
		frame = frameCache->getSpriteFrameByName(StringUtils::format("Hforward%d.png", i));
		frameList.pushBack(frame);
	}

	/*���ݾ���֡���󴴽���������*/
	Animation* animation = Animation::createWithSpriteFrames(frameList);
	animation->setLoops(-1);              //ѭ������
	animation->setDelayPerUnit(0.08f);    //ÿ֡���ż��

	/*������������*/
	Animate* animate = Animate::create(animation);

	/*����ִ�ж���*/
	m_sprite->runAction(animate);
}

void Player::setViewPointByPlayer() {
	
	if (m_sprite == NULL){
	return; }

	Layer* parent = (Layer*)getParent();

	/*��ͼ��������*/
	Size mapTiledNum = m_map->getMapSize();

	/*��ͼ�������Ӵ�С*/
	Size tiledSize = m_map->getTileSize();

	/*��ͼ��С*/
	Size mapSize = Size(mapTiledNum.width*tiledSize.width, mapTiledNum.height*tiledSize.height);

	/*��Ļ��С*/
	Size visibleSize = Director::getInstance()->getVisibleSize();

	/*��������*/
	Point spritePos = getPosition();

	/*�����������С����Ļ��һ�룬��ȡ��Ļ�е�����꣬����ȡ���ǵ�����*/
	float x = std::max(spritePos.x, visibleSize.width / 2);
	float y = std::max(spritePos.y, visibleSize.height / 2);

	/*���x y������������Ͻǵļ���ֵ����ȡ����ֵ�����꣬���ߵ��յ���ͼ������*/
	x = std::min(x, mapSize.width - visibleSize.width / 2);
	y = std::min(y, mapSize.height - visibleSize.height / 2);

	/*Ŀ���*/
	Point destPos = Point(x, y);

	/*��Ļ�е�*/
	Point centerPos = Point(visibleSize.width / 2, visibleSize.height / 2);

	/*������Ļ�е����Ҫ�ƶ���Ŀ�ĵ�֮��ľ���*/
	Point viewPos = centerPos - destPos;

	parent->setPosition(viewPos);

}

void Player::setTagPosition(int x, int y) {
	Entity::setTagPosition(x, y);

	/*������С��Ϊ�����ƶ���ͼ*/
	setViewPointByPlayer();

}

void Player::setTiledMap(TMXTiledMap* map) {
	this->m_map = map;
}

void Player::jump() {
	if (getSprite() == NULL) {
		return;
	}

	/*������ǻ�����Ծ�У����ظ�ִ��*/
	if (m_isJumping) {
		return;
	}

	/*�������Ϊ��Ծ״̬*/
	m_isJumping = true;

	/*������Ծ������ԭ����Ծ*/
	auto jump = JumpBy::create(2.0f, Point(0, 0), 250, 1);

	/*�����ص���������Ծ�������޸�m_isJumping���Ϊfalse*/
	auto callFunc = CallFunc::create([&]() {
		m_isJumping = false;
	});

	/*������������*/
	auto jumpActions = Sequence::create(jump, callFunc, NULL);

	/*ִ�ж���*/
	this->runAction(jumpActions);
}