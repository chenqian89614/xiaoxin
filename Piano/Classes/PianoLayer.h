#ifndef __PianoLayer_H__
#define __PianoLayer_H__

#include "cocos2d.h"
#include "GameSceneManager.h"
#include "ui/CocosGUI.h"
#include "extensions/cocos-ext.h"

#include <map>

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace std;
using namespace ui;

class PianoLayer : public cocos2d::Layer
{
public:
	bool musicFlag;						//�������ֱ�־λ
	bool pauseFlag;						//��ͣ��־λ
	bool changeFlag;					//��������־λ
	int temp[10];						//�����жϺڼ��Ƿ��ڵ��״̬����
	int index;							//�ڼ������ڼ��Ű׼�
	int degree;							//3Dģ��ת���ĽǶ�
	int touchIndex[10];					//��ǰ������׼��ı��
	int blackIndex[10];					//��ǰ������ڼ��ı��
	int instrumentNumber;				//��¼�����ı��
	int musicNum;						//�������ֱ��
	float percent;						//��ǰѡ���������λ�ðٷֱ�
	float timeL;						//�����ƶ���ʱ��
	float timeR;						//�����ƶ���ʱ��
	string instrumentName;				//��������
	Scheduler* schedRound;				//�߳�
	Slider* slider;						//������
	Size sSize;							//ѡ��������ߴ�
	Size menuSize;						//������ߴ��С
	Size leftSize;						//���ͷ����ߴ��С
	Size rightSize;						//�Ҽ�ͷ����ߴ��С
	Size smallSize;						//С�׼�
	Size volumeSize;					//�����ߴ��С
	Size whiteSize;						//�׼�����ߴ��С
	Size blackSize;						//�ڼ�����ߴ��С
	Size backSize;						//ѡ����ߴ��С
	Size sliderSize;					//�������ߴ��С
	Sprite* menuBack;					//�˵���������
	Sprite* underside;					//���澫��
	Sprite* selection;					//������������
	Sprite* instrument;					//��������
	Sprite* selectBack;					//ѡ�����
	Sprite* exit;						//�˳�����
	GameSceneManager* sceneManager;		//����ָ��
	map<string, Sprite*> piano;			//�׼�����
	map<string, Sprite*> piano_black;	//�ڼ�����
	map<string, Sprite*> select;		//ѡ��˵���������
public:
    virtual ~PianoLayer();
	//��ʼ���ķ���
	virtual bool init();
	void changePic(int number);
	void deleteSelf();
	void sliderEvent(Ref *pSender, Slider::EventType type);
	void percentUpdate();

	//�˳�������ʼ�ص�����
	bool onTouchExitBegan(Touch* touch, Event* event);
	//ѡ������ص�����
	bool onTouchSelectBegan(Touch* touch, Event* event);
	void onTouchSelectMoved(Touch* touch, Event* event);
	//����ť�����ص�����
	bool onTouchLeftBegan(Touch* touch, Event* event);
	void onTouchLeftEnded(Touch* touch, Event* event);
	//���Ұ�ť�����ص�����
	bool onTouchRightBegan(Touch* touch, Event* event);
	void onTouchRightEnded(Touch* touch, Event* event);
	//ѡ�����������ص�����
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	//�������������λ��
	bool onMyTouchBegan(Touch* touch, Event* event);
	//���ѡ���
	bool onTouchBeganInstrument(Touch* touch, Event* event);
	void onTouchEndedInstrument(Touch* touch, Event* event);
	//��ʼ��㴥���¼��Ĵ�����
	void onMyTouchesBegan(const std::vector<Touch*>& pTouches, Event *pEvent);
	//��㴥���ƶ��¼��Ĵ�����
	void onMyTouchesMoved(const std::vector<Touch*>& pTouches, Event *pEvent);
	//��㴥�ؽ����¼��Ĵ�����
	void onMyTouchesEnded(const std::vector<Touch*>& pTouches, Event *pEvent);
	//��ʱ�ص����°ٷֱ�
	void update(float delta);
    //Cocos2d-x�ж����һ���꣬����ָ�����͵Ķ���
    //��������Ӧ�ĳ�ʼ�����ͷŹ���s
    CREATE_FUNC(PianoLayer);
};

#endif
