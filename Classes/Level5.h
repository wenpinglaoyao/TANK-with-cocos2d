#pragma once
#include "HelloWorldScene.h"
#include "cocos2d.h"
#include <iostream>
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
using namespace ui;
using namespace CocosDenshion;

#define MAXE5 4//���˵��������
#define ENEMYSP5 1//���˵��ٶ�
#define BUSP5 25.5f//�����ӵ�����
#define WID5 1000
#define HEI5 800
#define EBUSP5 17 //���˵�����
#define TASKNUM5 24
#define HEROSPEED5 5.0f
#define BARMAX 220

class Level5 :public cocos2d::Scene {
	bool _pause;//����Ƿ������ͣ״̬
	Hero* _hero;//Ӣ��̹��
	Bullet* _bullet;//Ӣ�۵��ڵ�
	Sprite* _bar;
	Tank*  _enemy[MAXE5];//����̹��
	Vector<Bullet*> _enemyBulletVector;
	Vector<Sprite*> _iceVector;
	int _taskCount;
	int _GameState;
	int _barValue;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Level5);
	void update(float delta);
};
