#pragma once
#include "HelloWorldScene.h"
#include "cocos2d.h"
#include <iostream>
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
using namespace ui;
using namespace CocosDenshion;

#define MAXE6 12//���˵��������
#define ENEMYSP6 0.4//���˵��ٶ�
#define BUSP6 25.5f//�����ӵ�����
#define WID6 1000
#define HEI6 800
#define EBUSP6 5 //���˵�����
#define TASKNUM6 12
#define HEROSPEED5 4.0f
#define BARMAX6 200 //�߶����������
#define BALLSIZE 70 //����ĳߴ�
#define OFFSETMOVE 0.33f //ײ��������ССƫ�������������΢��λ��
#define STARMAXSIZE 140 //��ʯ�����ߴ�
#define STARMINSIZE 80 //��ʯ����С�ߴ�
#define OVERTIME 500 //����ʱ�����޶ȣ������˾���Ϸʧ��
#define SPADD 0.05 //�����ÿ��һ�����˺�ʣ����˵ļ��ٶ���


class Level6 :public cocos2d::Scene {
	bool _pause;//����Ƿ������ͣ״̬
	Hero* _hero;//Ӣ��̹��
	Sprite* _aim; //�����׼�ǣ�������Ҷ�׼�õ�
	Sprite* _aim2;
	Bullet* _bullet;//Ӣ�۵��ڵ�
	Tank*  _enemy[MAXE6];//����̹��
	Bullet* _enemyBullet[MAXE6];
	Sprite* _bar;
	Sprite* _star; //��ʯ����
	Sprite* _football; //������
	float _speedX, _speedY;//�����ƶ�ʱ���ٶ�
	float _starSize;//��ʯ��ʵ�ʳߴ�
	bool _moveFlag; //��ʯ�Ƿ����������Ƿ��ƶ��ı��
	int _coolTime; //�������ʱ��ͳ��
	int _taskCount;
	int _GameState;
	float _barValue;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Level6);
	void update(float delta);
	void moveByDir()
	{
		switch (_hero->getDirection())
		{
		case 1:
		case 3:
			if (_hero->getPositionX() < _football->getPositionX())
				_hero->setPositionX(_hero->getPositionX() - OFFSETMOVE);
			if (_hero->getPositionX() >= WID6 - 25 || _hero->getPositionX() <= 0 + 25)//���ƫ�ƺ�Խ����
				_hero->setPositionX(_hero->getPositionX() + OFFSETMOVE);//��ô������
			for (int i = 0;i < MAXE6;i++)
			{
				if (_hero->getBoundingBox().intersectsRect(_enemy[i]->getBoundingBox()))
				{
					_hero->setPositionX(_hero->getPositionX() + OFFSETMOVE);//��ô������
					break;
				}
			}


			if (_hero->getPositionX() > _football->getPositionX())
				_hero->setPositionX(_hero->getPositionX() + OFFSETMOVE);
			if (_hero->getPositionX() >= WID6 - 25 || _hero->getPositionX() <= 0 + 25)//���ƫ�ƺ�Խ����
				_hero->setPositionX(_hero->getPositionX() - OFFSETMOVE);//��ô������
			for (int i = 0;i < MAXE6;i++)
			{
				if (_hero->getBoundingBox().intersectsRect(_enemy[i]->getBoundingBox()))
				{
					_hero->setPositionX(_hero->getPositionX() - OFFSETMOVE);//��ô������
					break;
				}
			}
			break;

		case 2:
		case 4:
			if (_hero->getPositionY() < _football->getPositionY())//��ƫ��һ��СС��
				_hero->setPositionY(_hero->getPositionY() - OFFSETMOVE);
			if(_hero->getPositionY()>=HEI6-25 ||_hero->getPositionY()<=0+25)//���ƫ�ƺ�Խ����
				_hero->setPositionY(_hero->getPositionY() + OFFSETMOVE);//��ô������
			for (int i = 0;i < MAXE6;i++)
			{
				if (_hero->getBoundingBox().intersectsRect(_enemy[i]->getBoundingBox()))
				{
					_hero->setPositionY(_hero->getPositionY() + OFFSETMOVE);//��ô������
					break;
				}
			}


			if (_hero->getPositionY() > _football->getPositionY())
				_hero->setPositionY(_hero->getPositionY() + OFFSETMOVE);
			if (_hero->getPositionY() >= HEI6 - 25 || _hero->getPositionY() <= 0 + 25)
				_hero->setPositionY(_hero->getPositionY() - OFFSETMOVE);
			for (int i = 0;i < MAXE6;i++)
			{
				if (_hero->getBoundingBox().intersectsRect(_enemy[i]->getBoundingBox()))
				{
					_hero->setPositionY(_hero->getPositionY() - OFFSETMOVE);//��ô������
					break;
				}
			}
			break;
		}
	}
};
