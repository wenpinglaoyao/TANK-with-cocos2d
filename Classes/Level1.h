/*
��Ӣ����̹�˵Ŀ���֮һ
�������ܣ���Ӣ�۴�С����Զ�̣���Ӣ���ǽ�ս

Q���ܣ�ѡ��һ���з���λ����Ǹõ�λ4��ʱ�䣬�ڴ��ڼ䣬��Ӣ�۶������λ��ÿ��Զ�̹������ӵ������д�͸Ч��������;�ĵз���λ���80%����ʵ�˺�

W���ܣ�������

E���ܣ�������

�ռ����ܣ�ѡ��һ���з�Ӣ�ۣ�����5��ʱ�䡣�ڴ��ڼ䣬��Ӣ�۵�ÿ���չ�����ս���͵ģ��������Ŀ�����0�˺�����Ϊ�չ����˺���ת�Ƶ��˱�����������
�з�Ӣ������
*/

/*
һ��ADC

�ռ����У��������к��ڳ���5��ʱ���ڣ���Ӣ��ÿ��һ��˲ʱ�˺�������Ķ������͵Ĳ��㣩���������󱻻���һ�ξ��롣
*/

/*
�ռ�����֮�����ϣ��������к󣬸�Ӣ�۵������޷����κζ���������ǰһ�ξ����ͷ�һ����¡����¡��ĸ�������������һ������¡�����8��ʱ���Ա���
�ڴ��ڼ�Ҳ�ɱ����˴�������ô����ָ�����
*/
#pragma once
#include "HelloWorldScene.h"
#include "cocos2d.h"
#include <iostream>
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
using namespace ui;
using namespace CocosDenshion;
#define MAX 6

class Level1 :public cocos2d::Scene {
public:
	bool _pause;//����Ƿ������ͣ״̬
	Hero* _hero;//Ӣ��̹��
	Bullet* _bullet1,*_bullet2;//Ӣ�۵������ڵ�
	Tank*  _enemy[MAX];//����̹��������
	Bullet* _bullet[MAX];//���˵��ڵ�������
	Vector<Sprite*> _obstacleVector;//�ϰ����������
	int _taskCount;
	int _GameState;

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Level1);
	void update(float delta);
};
