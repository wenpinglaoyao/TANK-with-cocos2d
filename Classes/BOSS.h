#pragma once
#include "HelloWorldScene.h"
#include "cocos2d.h"
#include <iostream>
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"

using namespace ui;
using namespace CocosDenshion;


#define WID8 1000
#define HEI8 800
#define HEROSPEED8 5.0F //���ǵ�����
#define BOSSSPEED 4//boss������
#define BOSSHP 10000  //BOSS������ֵ
#define BOSSWID 100//boss��������
#define HEROHP 100 //���ǵ�Ѫ��
#define AGGRESSIVITY 3.0f //Ӣ�۵Ĺ�������������boss�����ָ�ֵ�ĶԱȹ�ϵ�����������������ֻ�����
#define POWERRESUME 3.0f//BOSS�������ָ�ֵ
#define LAYERWID 5//����Ŀ��
#define SPARKSIZE 50//��������bossʱ�Ž����Ļ𻨵����ߴ�
#define REDUCE 1.7  //�𻨳ߴ�ļ�С���ȣ�ֵԽ�����ʧ��Խ��
#define SOLDERSPEED 5//boss�չ��ӵ���ǰ���ٶ�
#define NORMALHURT 10//bossһ�㼼�ܵ��˺�ֵ
#define ANGLEADD 30//���������Ůɢ����������ֵԽ��Խ����
#define BOOMNUM 26 //�����ը������
#define BOOMSMALLMAXSIZE 200 //�����ըը����������ߴ�
#define BOOMSMALLMINSIZE  100 //��С�ߴ磬�������Ǹ�������ը��������ʱ�䣬��С�ߴ���󣬿����ըը����������
#define BOOMSMALLSUB 0.7//���������ըȦը����С���ٶ�
#define BOOMRADIUSADD 6.5//�����ը������뾶�������ʣ���ը�ٶȣ�
#define BOOMMAXSIZE 380 //�����ը����������ߴ�
#define METEORSHOWERNUM 38//���������ʯ������
#define REDSTONELETHSLITY 0.022//����Ǽ���Ժ�ʯ���˰�����ı���ʯ����ɱ������ֵԽС��ҵ��Ѷ�ԽС��Ѹ�ٷ�Ӧ����ͣ��
#define STONERAND  0//��������������ʯ�к�ʯ���ֵĸ��ʣ�ֵԽ����ֺ�ʯ�ĸ���ԽС
#define SKILLSTARTSPEED 1 //��������ռ����ܵĳ�ʼ�ٶȣ��ڴ˻�����Խ��Խ�죡��
#define SPEEDADD 1.00999//�ռ����ܵļ��ٶ�
#define HPRECOVER 7000//boss�عⷵ�ջָ�����ֵ
#define POWERRECOVER 1000//boss�عⷵ�������ָ�ֵ

class Level8 :public cocos2d::Scene {
	int _GameState;
	Hero* _hero;
	Sprite* _sea[4];
	Sprite* _layer;//���ǵļ��⾫��
	Sprite* _spark;//���Ǽ��⹥��BOSSʱ�����Ļ�
	Sprite* BOSS;
	Sprite* _falseBOSS;//�����boss������ʱ�ļ���
	float _BOSSHP;//boss������ֵ
	float _BOSSPowerVal;//boss������ֵ
	double long _speedX, _speedY;//boss�ռ�����ʱ���ƶ��ٶ�
	int _skillFlagNum;
	Sprite* _BOSSXueTiao;
	Sprite* _BOSSPOWER;
	bool _pause; //������־��Ϸ�Ƿ������ͣ״̬
	bool _isAttack; //������־����Ƿ񿪻�״̬
	bool _isSkill;  //������־boss�Ƿ�������ѿ�״̬
	unsigned int _stateTime[5]; //���״̬���������һ�ͣ��ԭ�أ��ļ�ʱ���������������û���ܵ������ж�

	Vector<Sprite*> _solderVector; //�չ����ӵ�������
	Vector<Sprite*> _flowerVector;//�չ��ӵ���������������
	Vector<Sprite*> _stoneVector; //�����ʯ���ܵ���ʯ������
	Vector<Sprite*> _BOOMSmallVector;//�����ըǰ���������Խ��ԽС
	Vector<Sprite*> _BOOMVector; //�����ը����ʼ��ը��
	Vector<Sprite*> _deadBOOM; //boss����ʱ���Ա����������

	Text * _text;

	int _deadNum;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Level8);
	void update(float delta);

};

