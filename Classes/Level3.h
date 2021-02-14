#pragma once
#include "HelloWorldScene.h"
#include "cocos2d.h"
#include <iostream>
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
using namespace ui;
using namespace CocosDenshion;

#define MAXENEMY3 4//���˵��������
#define SNOW_SPEED 1.3//ѩ��ǰ�����ٶ�
#define SOUND_SPEED 1.3//����ǰ�����ٶ�
#define WID 800
#define HEI 800
#define ENEMYBUSP 6//�����ӵ����ٶ�
#define TASKNUM 4
#define ENEMYSPEED 0.9f
#define SNOWDISTANCE 42//ѩ��֮��ľ���
#define STONESIZE 78 //ʯͷ�ĳߴ�
#define COOLTIME 180

class Level3 :public cocos2d::Scene {
	bool _pause;//����Ƿ������ͣ״̬
	Hero* _hero;//Ӣ��̹��
	Bullet* _bullet;//Ӣ�۵��ڵ�
	Tank*  _enemy[4];//����̹��������
	Vector<Bullet*> _soundVector; //������������
	Vector<Bullet*> _snowVector; //ѩ����������
	Sprite* _stone;
	int _taskCount;
	int _GameState;

public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Level3);
	void update(float delta);
	bool backDetection(Tank* tank,int direction,float speed);//��̹�˵ļ�⺯��
	bool isInfringeBorder(Tank* tank, int direction,int limit); //����ļ��Խ�纯��
	void backTank(Tank* tank, int directin, float);
	bool tankColl(Sprite*, Sprite*);
	bool isShoot(Tank*);
	void createSnowLine(int);
};