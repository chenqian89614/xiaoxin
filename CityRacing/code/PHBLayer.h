#ifndef _PHBLayer_H_
#define _PHBLayer_H_
#include "CityRacingSceneManager.h"
#include "cocos2d.h"
class PHBLayer :public cocos2d::Layer
{
public:
	CityRacingSceneManager* crsm;
	Sprite* bgSpriteO;
	Sprite* bgSpriteT;
	int record [5];
	LabelAtlas* (noLabel) [5];

	virtual bool init();
	void bgUpdate();
	void getRecord();
	void reSetRecord();
	void backMenuCallback();
	CREATE_FUNC(PHBLayer);
};
#endif
