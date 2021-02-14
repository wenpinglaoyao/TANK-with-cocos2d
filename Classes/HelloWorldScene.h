#ifndef  __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <iostream>
#define WIDTH 1400
#define HEIGHT 800
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;//����������ʹ��Text�ı�

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void update(float delta);

	static cocos2d::Scene* createLevelGame();
	static int level;
	Sprite* _authorSprite;
	Text * _bgStory;
	Text* _levelTxt;
	bool _authorFlag;
};


class Tank :public Sprite
{
protected:
	float _speed;//����ǵ�ǰ̹�˵������ٶ�
	
	int _direction;//�������ǰ̹�˵����߷���
	bool _fire;//����ǵ�ǰ̹���Ƿ��ڿ���״̬�ı��
	unsigned int _cool;//��������³���̹�˵Ľ���ʱ�䣬Ҳ���������޵�ʱ��
public:
	Tank() {
		_direction = int(CCRANDOM_0_1()) * 4; //�����ʼ����̹�˸յ���ʱ�ķ���
	}
	static Tank* createWithSpriteName(float speed,int direction,int cool,const std::string& name)//����̹�˾���ĳ�ʼ������
	{
		Tank* tank = new Tank();
		if (tank && tank->initWithFile(name.c_str()))
		{
			tank->autorelease();
			tank->_speed = speed;
			tank->_direction = direction;
			tank->_cool = cool;
			return tank;
		}
		CC_SAFE_DELETE(tank);
		return nullptr;
	}

	void setSpeed(float speed) { _speed = speed; } //����̹�˵������ٶ�
	float getSpeed() { return _speed; }//��ȡ̹�˵������ٶ�

	void setFire(bool fire) { _fire = fire; }
	bool getFire() { return _fire; }

	void setDirection(int direction) { _direction = direction; }
	int getDirection() { return _direction; }

	void setCool(int cool) { _cool = cool; }
	int getCool() { return _cool; }

	/*̹��ǰ��*/
	void tankRun()
	{
		switch (this->_direction)
		{
		case 1://������
			this->setPositionY(this->getPositionY() + this->_speed);
			break;

		case 3://������
			this->setPositionY(this->getPositionY() - this->_speed);
			break;

		case 4://������
			this->setPositionX(this->getPositionX() - this->_speed);
			break;

		case 2://������
			this->setPositionX(this->getPositionX() + this->_speed);
			break;
		}
	}
	/*̹�˺���*/
	void tankBack()
	{
		switch (this->_direction)
		{
		case 1://��Ϊ�����ϣ��������³���
			this->setPositionY(this->getPositionY() - this->_speed);
			break;

		case 3://��Ϊ�������£��������ϳ���
			this->setPositionY(this->getPositionY() + this->_speed);
			break;

		case 4://��Ϊ���������������ҳ���
			this->setPositionX(this->getPositionX() + this->_speed);
			break;

		case 2://��Ϊ�������ң�����������
			this->setPositionX(this->getPositionX() - this->_speed);
			break;
		}
	}

	/*̹���Ƿ�Խ��*/
	bool isInfringeBorder(int WID, int HEI, int limit) {
		switch (_direction) {
		case 1:
			if (this->getPositionY() >= HEI + limit) 
				return true;
		case 3:
			if (this->getPositionY() <= -limit)
				return true;
			break;
		case 2:
			if (this->getPositionX() >= WID + limit) 
				return true;
			break;
		case 4:
			if (this->getPositionX() <= -limit) 
				return true;
			break;
		}
		return false;
	}
};

class Hero :public Tank {
public:
	static Hero* createWithSpriteName(float speed, int direction) {
		Hero* hero = new Hero();
		if (hero && hero->initWithFile("hero.png")) {
			hero->autorelease();
			hero->_speed = speed;
			hero->_direction = direction;
			return hero;
		}
		CC_SAFE_DELETE(hero);
		return nullptr;
	}
};

class Bullet :public Sprite
{
protected:
	int _direction;//�ڵ��ķ���
	float _speed;//�ڵ����ٶ�
	int _power;//�ڵ�������

public:
	static Bullet* createWithSpriteName(float speed,int direction,const std::string& name) {
		Bullet* bullet = new Bullet();
		if (bullet && bullet->initWithFile(name)) {
			bullet->autorelease();
			bullet->_speed = speed;
			bullet->_direction = direction;
			return bullet;
		}
		CC_SAFE_DELETE(bullet);
		return nullptr;
	}

	void setDirection(int direction) { _direction = direction; }//�����ڵ�����
	int getDirection() { return _direction; }
	void setSpeed(float speed) { _speed = speed; }//�����ڵ��ٶ�
	float getSpeed() { return _speed; }
	void setPower(int power) { _power = power; }//�����ڵ�����
	int getPower() { return _power; }//��ȡ�ڵ�����

	void bulletRun()
	{
		switch (this->_direction)
		{
		case 0://������
			this->setPositionY(this->getPositionY() + this->_speed);
			break;

		case 180://������
			this->setPositionY(this->getPositionY() - this->_speed);
			break;

		case 270://������
			this->setPositionX(this->getPositionX() - this->_speed);
			break;

		case 90://������
			this->setPositionX(this->getPositionX() + this->_speed);
			break;
		}
	}

	bool isInfringeBorder(int WID, int HEI,int limit) {
		switch (_direction)
		{
		case 0:
			if (this->getPositionY() >= HEI + limit) return true;
		case 180:
			if (this->getPositionY() <= -limit) return true;
			break;
		case 270:
			if (this->getPositionX() <= -limit) return true;
			break;
		case 90:
			if (this->getPositionX() >= WID+limit) return true;
			break;
		}
		return false;
	}
};

class BOSS :public Sprite
{
	int _life;//�����boss������ֵ
	int _power;//�����boss������
};
#endif // __HELLOWORLD_SCENE_H__

