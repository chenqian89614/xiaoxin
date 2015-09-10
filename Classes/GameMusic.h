#ifndef _GameMusic_H_
#define _GameMusic_H_

class GameMusic {

public:
	~GameMusic();
	static GameMusic* getInstance();

	void prepare();

	void playmusic();

private:
	static GameMusic* _instance;
};



#endif
