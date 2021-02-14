#pragma once
#include "HelloWorldScene.h"
#include "cocos2d.h"
#include <iostream>
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
using namespace ui;
using namespace CocosDenshion;

#define ROTATIME 5.0 //����Ǽ�����תһȦ��ʱ��
#define ROTASPADD 0.9 //����Ǽ���תȦ�ļ��ٶȣ���һ���������ϻ�ԽתԽ�죬�����˺����¿�ʼ���õ��ǳ˷���
#define WID7 1000
#define HEI7 800
#define TASKNUM7 7 //��Ҫ��ɵ�������
#define HEROSPEED7 1.9f//���ǵ����٣��깤�˿��Ըĳ�1.9f�������ǽ����Ѷȣ����������һ�أ�
#define BUSP7 2//�����ӵ�������
#define PI 3.1415126
#define MAXDIS 750//����������˵���Զ����
#define OFFSET 100//�ʵ����͵��������������
#define ROTAADD 1.00035 //������ת�ļ��ٶȣ��깤�˿��԰�4�ĳ�5��


class Level7 :public cocos2d::Scene {
	bool _pause;//����Ƿ������ͣ״̬
	Hero* _hero;//Ӣ��̹��
	Bullet* _bullet;//Ӣ�۵��ڵ�
	Sprite* _layer; //����
	double _rotaTime; //������תһȦ����Ҫ��ʱ��
	double _rotaAdd; //����ÿ����ת��Ҫ���ӵķ�����
	bool _isStopRota; //�����Ƿ���ת��һȦ�ı�־
	Sprite* _realEnemy;//��ĵ���
	Sprite* _falseEnemy;//�������
	Sprite* sss;
	Text* ext;
	int _taskCount;
	int _GameState;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Level7);
	void update(float delta);
	void setFlasePos();
	bool isHurt(float, float);
	float transAngle(Vec2, Vec2);
};
