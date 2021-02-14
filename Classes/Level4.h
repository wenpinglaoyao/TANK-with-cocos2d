#pragma once
#include "HelloWorldScene.h"
#include "cocos2d.h"
#include <iostream>
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
using namespace ui;
using namespace CocosDenshion;

#define MAXE4 6//���˵��������
#define BUSP 2.5f//�����ӵ�����
#define WID4 800
#define HEI4 800
#define ESP4 0.5//���˵��ٶ�
#define TASKNUM4 4
#define STONESIZE4 50
#define HEROSPEED 2.0f
#define INTERROGATETIME 300//���������ʱ��

class Level4 :public cocos2d::Scene {
	bool _pause;//����Ƿ������ͣ״̬
	Hero* _hero;//Ӣ��̹��
	Bullet* _bullet;//Ӣ�۵��ڵ�
	Tank*  _enemy[MAXE4];//����̹��������
	Sprite* _stone[4];
	Sprite* _sir;//����ǳ���
	int _countInterrogate;//�����һ�����ٱ�ץ�����ʿ�ʼ�ļ�ʱ
	int _taskCount;
	int _GameState;
	int _sirCount;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Level4);
	void update(float delta);
	/****���������һ���ݹ麯��������ʵ�������������Ĺ��ܣ�������
	�������ŵ��ˡ��ϰ���һ��ǰ����������cocos������û���������ӣ�
	�����������ǵ��Լ���һ��****/
	bool backDetection(Tank* tank, int direction, float speed)
	{
		switch (direction)//���Ȱ�̹�˰��շ�����λһ���ٶ���
		{
		case 1:
			tank->setPositionY(tank->getPositionY() + speed);
			break;
		case 3:
			tank->setPositionY(tank->getPositionY() - speed);
			break;
		case 4:
			tank->setPositionX(tank->getPositionX() - speed);
			break;
		case 2:
			tank->setPositionX(tank->getPositionX() + speed);
			break;
		}
		tank->setCool(1);

		if (this->isInfringeBorder(tank, direction, -tank->getContentSize().width / 2))//������̹����λ��Խ����
		{
			backTank(tank, direction, speed);
			return true;
		}
		for (int i = 0;i < 4;i++)
		{
			if (tankColl(tank, _stone[i]))//������̹��ײ����ʯ��
			{
				backTank(tank, direction, speed);
				return true;
			}
		}


		for (int i = 0;i < MAXE4;i++)
		{
			if (!_enemy[i]->getCool() && tankColl(_enemy[i], tank))//�����̹���ص��˱��̹��
			{
				if (backDetection(_enemy[i], direction, speed) == true)
				{
					backTank(tank, direction, speed);
					return true;
				}
			}
		}

		return false;
	}
	bool isInfringeBorder(Tank* tank, int direction, int limit)
	{
		switch (direction)
		{
		case 1:
			if (tank->getPositionY() >= HEI4 + limit)
				return true;
		case 3:
			if (tank->getPositionY() <= -limit)
				return true;
			break;
		case 2:
			if (tank->getPositionX() >= WID4 + limit)
				return true;
			break;
		case 4:
			if (tank->getPositionX() <= -limit)
				return true;
			break;
		}
		return false;
	}
	void backTank(Tank* tank, int direction, float speed)
	{
		switch (direction)
		{
		case 1:
			tank->setPositionY(tank->getPositionY() - speed);
			break;
		case 3:
			tank->setPositionY(tank->getPositionY() + speed);
			break;
		case 4:
			tank->setPositionX(tank->getPositionX() + speed);
			break;
		case 2:
			tank->setPositionX(tank->getPositionX() - speed);
			break;
		}
		//tank->setPosition(tank->getPositionX(), tank->getPositionY());
	}
	bool tankColl(Sprite* t1, Sprite* t2)//��һ��Ҫ�Լ�д����ײ��⺯������Ȼ��bug
	{
		float wid = t1->getContentSize().width / 2 + t2->getContentSize().width / 2;
		float hei = t1->getContentSize().height / 2 + t2->getContentSize().height / 2;
		wid = wid*wid;
		hei = hei*hei;
		if ((t1->getPositionX() - t2->getPositionX())*(t1->getPositionX() - t2->getPositionX()) <= wid &&
			(t1->getPositionY() - t2->getPositionY())*(t1->getPositionY() - t2->getPositionY()) <= hei)
			return true;
		return false;
	}
};