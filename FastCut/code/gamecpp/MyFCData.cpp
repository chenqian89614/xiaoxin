#include "MyFCData.h"
#include "../bnGeolibHelper/BNPolyObject.h"
#include "../bnBox2DHelp/PhyObject.h"
#include "../bnBox2DHelp/JointHelp.h"
#include "GameLayer.h"
#include "AppConstant.h"
using namespace std;
int MyFCData::levelNum=0;
int MyFCData::radius;//��뾶
MyFCData::MyFCData(GameLayer* layerIn, int levelNumIn)
{
	this->layer = layerIn;
	this->levelNum = levelNumIn;
	if(levelNum == 1){createMyFCData1();}
	else if(levelNum == 2){createMyFCData2();}
	else if(levelNum == 3){createMyFCData3();}
	else if(levelNum == 4){createMyFCData4();}
	else if(levelNum == 5){createMyFCData5();}
	else if(levelNum == 6){createMyFCData6();}
}

void MyFCData::createMyFCData1()
{
	levelNum=1;
	//����һ������"Ŀ�������40%/"���ݵ��ı���ǩ
	layer->label = Label::createWithTTF("\u76ee\u6807\u9762\u79ef\uff1a40%", fonts_PATH+"FZKATJW.ttf", 40);
	//���ñ�ǩ�������ɫ
	layer->label->setTextColor(Color4B::WHITE);
	//�����ı���ǩ��λ��
	layer->label->setPosition
	(
		Point
		(
			layer->origin.x + 180,
			layer->origin.y + layer->visibleSize.height - layer->label->getContentSize().height
		)
	);
	//���ı���ǩ��ӵ�������
	layer->addChild(layer->label, 1);

	float fa[]={127,547, 37,354, 260,145, 511,687, 343,773, 232,389};
	std::string  pics= pic_PATH+StringUtils::format("s_0%d.png", levelNum);
	layer->bpoCurrMain=new BNPolyObject(pics,fa,6,layer);

	layer->createEdge(fa,sizeof(fa)/sizeof(fa[0]));

	layer->data=new float[3]{314-layer->visibleSize.width/2,332-layer->visibleSize.height/2,26};				//����Բ�θ��������
	layer->ids=new std::string("C4");															//����Բ�θ����id
	layer->po=new CirclePhyObject(layer->ids,false,layer,layer->world,pic_PATH+"dartsmall.png",layer->data,2.0f,0.1f,0.9f);//����Բ�θ������
	layer->pom[*(layer->ids)]=layer->po;
	layer->pomCircle[*(layer->ids)]=layer->po;
	layer->po->body->SetLinearVelocity(b2Vec2(-20,10));

	layer->data=new float[3]{421-layer->visibleSize.width/2,733-layer->visibleSize.height/2,26};				//����Բ�θ��������
	layer->ids=new std::string("C5");															//����Բ�θ����id
	layer->po=new CirclePhyObject(layer->ids,false,layer,layer->world,pic_PATH+"dartsmall.png",layer->data,2.0f,0.1f,0.9f);//����Բ�θ������
	layer->pom[*(layer->ids)]=layer->po;
	layer->pomCircle[*(layer->ids)]=layer->po;
	layer->po->body->SetLinearVelocity(b2Vec2(-20,-10));
	radius =layer->pomCircle["C5"]->body->GetFixtureList()->GetShape()->m_radius*pixToMeter;//��뾶
	JointHelp(layer->pomCircle["C4"]->body,layer->pomCircle["C5"]->body, layer->world);

}
void MyFCData::createMyFCData2()
{
	levelNum=2;
	//����һ������"Ŀ�������30%/"���ݵ��ı���ǩ
	layer->label = Label::createWithTTF("\u76ee\u6807\u9762\u79ef\uff1a30%", fonts_PATH+"FZKATJW.ttf", 40);
	//���ñ�ǩ�������ɫ
	layer->label->setTextColor(Color4B::WHITE);
	//�����ı���ǩ��λ��
	layer->label->setPosition
	(
		Point
		(
				layer->origin.x + 180,
				layer->origin.y + layer->visibleSize.height - layer->label->getContentSize().height
		)
	);
	//���ı���ǩ��ӵ�������
	layer->addChild(layer->label, 1);

	float fa[]={347,819, 57,423, 208,382, 159,100, 487,494, 291,534};
	std::string  pics= pic_PATH+StringUtils::format("s_0%d.png", levelNum);
	layer->bpoCurrMain=new BNPolyObject(pics,fa,6,layer);
	layer->createEdge(fa,sizeof(fa)/sizeof(fa[0]));

	layer->data=new float[3]{179-layer->visibleSize.width/2,471-layer->visibleSize.height/2,26};				//����Բ�θ��������
	layer->ids=new std::string("C4");															//����Բ�θ����id
	layer->po=new CirclePhyObject(layer->ids,false,layer,layer->world,pic_PATH+"dartsmall.png",layer->data,2.0f,0.1f,0.9f);//����Բ�θ������
	layer->pom[*(layer->ids)]=layer->po;
	layer->pomCircle[*(layer->ids)]=layer->po;
	layer->po->body->SetLinearVelocity(b2Vec2(-20,10));

	layer->data=new float[3]{322-layer->visibleSize.width/2,452-layer->visibleSize.height/2,26};				//����Բ�θ��������
	layer->ids=new std::string("C5");															//����Բ�θ����id
	layer->po=new CirclePhyObject(layer->ids,false,layer,layer->world,pic_PATH+"dartsmall.png",layer->data,2.0f,0.1f,0.9f);//����Բ�θ������
	layer->pom[*(layer->ids)]=layer->po;
	layer->pomCircle[*(layer->ids)]=layer->po;
	layer->po->body->SetLinearVelocity(b2Vec2(-20,-10));
	radius =layer->pomCircle["C5"]->body->GetFixtureList()->GetShape()->m_radius*pixToMeter;//��뾶
	JointHelp(layer->pomCircle["C4"]->body,layer->pomCircle["C5"]->body, layer->world);
}

void MyFCData::createMyFCData3()
{
	levelNum=3;
	//����һ������"Ŀ�������20%/"���ݵ��ı���ǩ
	layer->label = Label::createWithTTF("\u76ee\u6807\u9762\u79ef\uff1a20%", fonts_PATH+"FZKATJW.ttf", 40);
	//���ñ�ǩ�������ɫ
	layer->label->setTextColor(Color4B::WHITE);
	//�����ı���ǩ��λ��
	layer->label->setPosition
	(
		Point
		(
				layer->origin.x + 180,
				layer->origin.y + layer->visibleSize.height - layer->label->getContentSize().height
		)
	);
	//���ı���ǩ��ӵ�������
	layer->addChild(layer->label, 1);

	float fa[]={269,769, 191,604, 22,575, 141,450, 116,262, 269,350, 426,262, 396,448, 519,577, 348,605};
	layer->bpoCurrMain=new BNPolyObject(pic_PATH+"s_03.png",fa,10,layer);
	layer->createEdge(fa,sizeof(fa)/sizeof(fa[0]));

	layer->data=new float[3]{165-layer->visibleSize.width/2,533-layer->visibleSize.height/2,26};				//����Բ�θ��������
	layer->ids=new std::string("C4");															//����Բ�θ����id
	layer->po=new CirclePhyObject(layer->ids,false,layer,layer->world,pic_PATH+"dartsmall.png",layer->data,2.0f,0.1f,0.9f);//����Բ�θ������
	layer->pom[*(layer->ids)]=layer->po;
	layer->pomCircle[*(layer->ids)]=layer->po;
	layer->po->body->SetLinearVelocity(b2Vec2(-20,10));

	layer->data=new float[3]{200-layer->visibleSize.width/2,400-layer->visibleSize.height/2,26};				//����Բ�θ��������
	layer->ids=new std::string("C5");															//����Բ�θ����id
	layer->po=new CirclePhyObject(layer->ids,false,layer,layer->world,pic_PATH+"dartsmall.png",layer->data,2.0f,0.1f,0.9f);//����Բ�θ������
	layer->pom[*(layer->ids)]=layer->po;
	layer->pomCircle[*(layer->ids)]=layer->po;
	layer->po->body->SetLinearVelocity(b2Vec2(-20,-10));
	radius =layer->pomCircle["C5"]->body->GetFixtureList()->GetShape()->m_radius*pixToMeter;//��뾶
	JointHelp(layer->pomCircle["C4"]->body,layer->pomCircle["C5"]->body, layer->world);
}

void MyFCData::createMyFCData4()
{
	levelNum=4;
	//����һ������"Ŀ�������20%/"���ݵ��ı���ǩ
	layer->label = Label::createWithTTF("\u76ee\u6807\u9762\u79ef\uff1a20%", fonts_PATH+"FZKATJW.ttf", 40);
	//���ñ�ǩ�������ɫ
	layer->label->setTextColor(Color4B::WHITE);
	//�����ı���ǩ��λ��
	layer->label->setPosition
	(
		Point
		(
				layer->origin.x + 180,
				layer->origin.y + layer->visibleSize.height - layer->label->getContentSize().height
		)
	);
	//���ı���ǩ��ӵ�������
	layer->addChild(layer->label, 1);

	float fa[]={272,798, 59,707, 59,526, 164,476, 57,426, 57,243, 272,150, 485,243, 483,427, 375,476, 483,526, 483,707};
	layer->bpoCurrMain=new BNPolyObject(pic_PATH+"s_04.png",fa,12,layer);
	layer->createEdge(fa,sizeof(fa)/sizeof(fa[0]));

	layer->data=new float[3]{165-layer->visibleSize.width/2,533-layer->visibleSize.height/2,26};				//����Բ�θ��������
	layer->ids=new std::string("C4");															//����Բ�θ����id
	layer->po=new CirclePhyObject(layer->ids,false,layer,layer->world,pic_PATH+"dartsmall.png",layer->data,2.0f,0.1f,0.9f);//����Բ�θ������
	layer->pom[*(layer->ids)]=layer->po;
	layer->pomCircle[*(layer->ids)]=layer->po;
	layer->po->body->SetLinearVelocity(b2Vec2(-20,10));

	layer->data=new float[3]{200-layer->visibleSize.width/2,400-layer->visibleSize.height/2,26};				//����Բ�θ��������
	layer->ids=new std::string("C5");															//����Բ�θ����id
	layer->po=new CirclePhyObject(layer->ids,false,layer,layer->world,pic_PATH+"dartsmall.png",layer->data,2.0f,0.1f,0.9f);//����Բ�θ������
	layer->pom[*(layer->ids)]=layer->po;
	layer->pomCircle[*(layer->ids)]=layer->po;
	layer->po->body->SetLinearVelocity(b2Vec2(-20,-10));
	radius =layer->pomCircle["C5"]->body->GetFixtureList()->GetShape()->m_radius*pixToMeter;//��뾶
	JointHelp(layer->pomCircle["C4"]->body,layer->pomCircle["C5"]->body, layer->world);
}

void MyFCData::createMyFCData5()
{
	levelNum=5;
	//����һ������"Ŀ�������20%/"���ݵ��ı���ǩ
	layer->label = Label::createWithTTF("\u76ee\u6807\u9762\u79ef\uff1a20%", fonts_PATH+"FZKATJW.ttf", 40);
	//���ñ�ǩ�������ɫ
	layer->label->setTextColor(Color4B::WHITE);
	//�����ı���ǩ��λ��
	layer->label->setPosition
	(
		Point
		(
				layer->origin.x + 180,
				layer->origin.y + layer->visibleSize.height - layer->label->getContentSize().height
		)
	);
	//���ı���ǩ��ӵ�������
	layer->addChild(layer->label, 1);

	float fa[]={271,772, 190,545, 25,596, 144,382, 52,258, 494,258, 397,382, 514,596, 353,546};
	layer->bpoCurrMain=new BNPolyObject(pic_PATH+"s_05.png",fa,9,layer);
	layer->createEdge(fa,sizeof(fa)/sizeof(fa[0]));

	layer->data=new float[3]{165-layer->visibleSize.width/2,533-layer->visibleSize.height/2,26};				//����Բ�θ��������
	layer->ids=new std::string("C4");															//����Բ�θ����id
	layer->po=new CirclePhyObject(layer->ids,false,layer,layer->world,pic_PATH+"dartsmall.png",layer->data,2.0f,0.1f,0.9f);//����Բ�θ������
	layer->pom[*(layer->ids)]=layer->po;
	layer->pomCircle[*(layer->ids)]=layer->po;
	layer->po->body->SetLinearVelocity(b2Vec2(-20,10));

	layer->data=new float[3]{200-layer->visibleSize.width/2,400-layer->visibleSize.height/2,26};				//����Բ�θ��������
	layer->ids=new std::string("C5");															//����Բ�θ����id
	layer->po=new CirclePhyObject(layer->ids,false,layer,layer->world,pic_PATH+"dartsmall.png",layer->data,2.0f,0.1f,0.9f);//����Բ�θ������
	layer->pom[*(layer->ids)]=layer->po;
	layer->pomCircle[*(layer->ids)]=layer->po;
	layer->po->body->SetLinearVelocity(b2Vec2(-20,-10));
	radius =layer->pomCircle["C5"]->body->GetFixtureList()->GetShape()->m_radius*pixToMeter;//��뾶
	JointHelp(layer->pomCircle["C4"]->body,layer->pomCircle["C5"]->body, layer->world);

}
void MyFCData::createMyFCData6()
{
	levelNum=6;
	//����һ������"Ŀ�������20%/"���ݵ��ı���ǩ
	layer->label =Label::createWithTTF("\u76ee\u6807\u9762\u79ef\uff1a20%", fonts_PATH+"FZKATJW.ttf", 40);
	//���ñ�ǩ�������ɫ
	layer->label->setTextColor(Color4B::WHITE);
	//�����ı���ǩ��λ��
	layer->label->setPosition
	(
		Point
		(
				layer->origin.x + 180,
				layer->origin.y + layer->visibleSize.height - layer->label->getContentSize().height
		)
	);
	//���ı���ǩ��ӵ�������
	layer->addChild(layer->label, 1);

	float fa[]={146,778, 146,412, 47,293, 151,170, 400,170, 400,536, 500,658, 400,778};
	layer->bpoCurrMain=new BNPolyObject(pic_PATH+"s_06.png",fa,8,layer);
	layer->createEdge(fa,sizeof(fa)/sizeof(fa[0]));

	layer->data=new float[3]{165-layer->visibleSize.width/2,533-layer->visibleSize.height/2,26};				//����Բ�θ��������
	layer->ids=new std::string("C4");															//����Բ�θ����id
	layer->po=new CirclePhyObject(layer->ids,false,layer,layer->world,pic_PATH+"dartsmall.png",layer->data,2.0f,0.1f,0.9f);//����Բ�θ������
	layer->pom[*(layer->ids)]=layer->po;
	layer->pomCircle[*(layer->ids)]=layer->po;
	layer->po->body->SetLinearVelocity(b2Vec2(-20,10));

	layer->data=new float[3]{200-layer->visibleSize.width/2,400-layer->visibleSize.height/2,26};				//����Բ�θ��������
	layer->ids=new std::string("C5");															//����Բ�θ����id
	layer->po=new CirclePhyObject(layer->ids,false,layer,layer->world,pic_PATH+"dartsmall.png",layer->data,2.0f,0.1f,0.9f);//����Բ�θ������
	layer->pom[*(layer->ids)]=layer->po;
	layer->pomCircle[*(layer->ids)]=layer->po;
	layer->po->body->SetLinearVelocity(b2Vec2(-20,-10));
	radius =layer->pomCircle["C5"]->body->GetFixtureList()->GetShape()->m_radius*pixToMeter;//��뾶
	JointHelp(layer->pomCircle["C4"]->body,layer->pomCircle["C5"]->body, layer->world);
}

