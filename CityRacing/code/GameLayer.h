#ifndef  _GameLayer_H_
#define  _GameLayer_H_
#include "CityRacingSceneManager.h"
#include "cocos2d.h"
#include "PlayerCar.h"
#include "EnemyCar.h"
#include "vector"
#include "Coin.h"
#include "Rocket.h"

//#include "cocostudio/CocoStudio.h"
//using namespace cocostudio;
using namespace cocos2d;
class GameLayer : public cocos2d::Layer
{
	public:
		CityRacingSceneManager* crsm;
		int pointR=0;
		//速度
		int v = 0;
		int baseSpeed = 10;
		int count = 0;
		int t = 0;
		int lifeValue = 135 ;
		int distance = 0;
		int gold = 0;
		int restTime = 30;
		int rocketCount = 0;
		int deltaDistance = 1 ;
		int no2Count = 0;
		int currItemIndex = -1;
		int itemSpeed = 20;
		int djsTime = 0;
		Sprite* bgSpriteO;
		Sprite* bgSpriteT;
		Sprite* pointSprite;
		Sprite* (redSprite) [3];
		Sprite* (puaseSprite) [3];
		Sprite* puaseMenuBg;
		PlayerCar* playerCar;
		Sprite* lifeSprite;
		Sprite* no2Sprite;
		Sprite* spriteTouch;
		LabelAtlas* distanceLabel;
		LabelAtlas* goldLabel;
		LabelAtlas* rocketLabel;
		LabelAtlas* no2Label;
		LabelAtlas* restTimeLabel;
		MenuItemImage* pauseItem;
		MenuItemImage* no2Item;
		MenuItemImage* rocketItem;
		static bool isGameOver ;
		bool onKeyFlag = false ;
		bool isOnAcceleration = false;

		Animate* anmiAc[10];
		Sprite* boomSprite ;
		//Sprite* sparksFrame;
		float moveSpan=0;
		float angle = 0;
		std::vector<EnemyCar*>* allEnemyCarVCT;
		std::vector<EnemyCar*>* delEnemyCarVCT;
		std::vector<Coin*>* 	coinSpriteVCT;
		std::vector<Coin*>* 	delCoinSpriteVCT;
		std::vector<Rocket*>* 	rocketSpriteVCT;
		std::vector<Rocket*>* 	delRocketSpriteVCT;
		std::vector<Sprite*>* 	allItemSpriteVCT;
		std::vector<Sprite*>* 	delItemSpriteVCT;

		virtual bool init();
		void initUserData();
		void initYBP();
		void initMusic();
		void initPlyerCar();
		void initFrameCache();
		void initHJFire();
		void initBoomHZJL();
		void initSpeedLine();
		void initBigFire();
		void initNo2();
		void initSilver();
		void initPower();
		void removeBoomHZJL();
		void initNo2Che();
		void JSMenuCallback();
		void removeNo2SpriteR();
		void removeNo2SpriteL();
		void removeNo2Sprite();
		void removeSpeedLineSprite();
		void removePowerSprite();
		void rocketMenuCallback();
		void DJHCarFire();
		void removeTaskSP();
		void trafficUpdate();
		void playerCarUpdate();
		void enemyCarUpdate();
		void addStageUpdate();
		void enemyCarPositionUpdate();
		void collisionTestUpdate();
		void timeUpdate();
		void collisionTestRocketAndEnemyCar();
		void addFireLZXT(EnemyCar* enemyCar);
		void collisionTestPlayerCarAndItem();
		void collisionTestPlayerCarAndCoin();
		void collisionTestPlayerCarAndEnemyCar();
		void bgUpdate();
		void distanceUpdate();
		bool onTouchBegan(Touch* touch, Event* event);
		void onTouchEnded(Touch* touch, Event* event);
		void onAcceleration(Acceleration* acc, Event* unused_event);	//重力感应回调方法
		void pauseMenuCallback();
		void resumeMenuCallback();
		void restartMenuCallback();
		void shopMenuCallback();
		void mainMenuCallback();
		void removeMenuBg();
		void gameOver();
		void gameDataReset();
		void gameRestart();
		int myGetIntegerForKey(std::string key);
		void mySetIntegerForKey(std::string key,int value);
	    //Cocos2d-x中定义的一个宏，创建指定类型的对象
	    //并做好相应的初始化与释放工作
	    CREATE_FUNC(GameLayer);
};
#endif
