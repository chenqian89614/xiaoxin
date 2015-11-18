#ifndef _Constant_H_
#define _Constant_H_

#include <vector>

class Constant
{
public:
	static double PI;
	static int THING_TAG[12];
	static int redOrGreen;
	static int level;
	static int state;
	static int redX;
	static int redY;
	static int greenX;
	static int greenY;
	static float redTankAngle;
	static float greenTankAngle;
	static float redGunAngle;
	static float greenGunAngle;
	static int redGunState;
	static int greenGunState;
	static int redHealth;
	static int greenHealth;
	static int otherGunState;

	static int offset;
	static int score;

	static int bossNum;
	static int bossX;
	static int bossY;
	static bool bossFlag;

	static std::vector<float> mainBullet;
	static std::vector<float> mainMissile;
	static std::vector<float> otherBullet;
	static std::vector<float> bossBullet;

	static std::vector<int> mapData;
	static std::vector<int> mapTree;
	static std::vector<int> mapTank;
	static std::vector<int> explosion;
	static std::vector<int> award;

	static bool effectFlag;
	static bool musicFlag;

	static void playEffect(const char *path);
	static void playMusic();
};
#endif
