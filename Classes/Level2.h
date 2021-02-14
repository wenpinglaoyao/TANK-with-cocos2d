#pragma once
#include "HelloWorldScene.h"
#include "cocos2d.h"
#include <iostream>
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
using namespace ui;
using namespace CocosDenshion;
#define MAX_ENEMY 9 //���˵��������
#define MAX_PARTNER 3 //����ѵ��������

class Level2 :public cocos2d::Scene {
public:
	bool _pause;//����Ƿ������ͣ״̬
	Hero* _hero;//Ӣ��̹��
	Bullet* _bullet;//Ӣ�۵��ڵ�
	Tank* _partner[MAX_PARTNER];//�Ѿ�̹������
	Tank*  _enemy[MAX_ENEMY];//����̹��������
	Bullet* _enemyBullet[MAX_ENEMY];//���˵��ڵ�
	Vector<Bullet*> _BOOMVector; //��ը��������
	int _taskCount;
	int _GameState;
	float _addCircle;//���˱�ը�뾶��������

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Level2);
	void update(float delta);
	bool circleDetection(Point circlePos, float radius, Point tankPos);//��ըɱ�˵ļ�⺯��
};
