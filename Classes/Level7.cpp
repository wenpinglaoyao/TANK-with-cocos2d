#include "Level7.h"
#include "cmath"
#include <iostream>
USING_NS_CC;

cocos2d::Scene* Level7::createScene()
{
	return Level7::create();
}

bool Level7::init()
{
	{
		if (!Scene::init()) return false;

		_taskCount = 0;
		_GameState = 0;
		_isStopRota = false;
		_rotaTime = ROTATIME;
		_rotaAdd = 1;
		
		auto background = Sprite::create("BG.png");//�������һ����ɫ����ͼƬ
		background->setContentSize(Size(400, 800));
		background->setPosition(WID7 + background->getContentSize().width / 2, background->getContentSize().height / 2);
		addChild(background);

		Button* up = Button::create("up.png");//����һ������̹�����ϵİ�ť
		up->setRotation(45);
		up->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
			switch (type) {
			case Widget::TouchEventType::BEGAN:_hero->setDirection(1);_hero->setRotation(0);break;
			case Widget::TouchEventType::MOVED:_hero->setDirection(1);break;
			case Widget::TouchEventType::ENDED:_hero->setDirection(0);break;
			case Widget::TouchEventType::CANCELED:_hero->setDirection(0);break;
			}
		});
		up->setPosition(Vec2(1200, 300));
		addChild(up);

		Button* down = Button::create("up.png");//���µİ�ť
		down->setRotation(180 + 45);
		down->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
			switch (type) {
			case Widget::TouchEventType::BEGAN:_hero->setDirection(3);_hero->setRotation(180);break;
			case Widget::TouchEventType::MOVED:_hero->setDirection(3);break;
			case Widget::TouchEventType::ENDED:_hero->setDirection(0);break;
			case Widget::TouchEventType::CANCELED:_hero->setDirection(0);break;
			}
		});
		down->setPosition(Vec2(1200, 100));
		addChild(down);

		Button* left = Button::create("up.png");//����İ�ť
		left->setRotation(270 + 45);
		left->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
			switch (type) {
			case Widget::TouchEventType::BEGAN:_hero->setDirection(4); _hero->setRotation(270);break;
			case Widget::TouchEventType::MOVED:_hero->setDirection(4);break;
			case Widget::TouchEventType::ENDED:_hero->setDirection(0);break;
			case Widget::TouchEventType::CANCELED:_hero->setDirection(0);break;
			}
		});
		left->setPosition(Vec2(1100, 200));
		addChild(left);

		Button* right = Button::create("up.png");//���ҵİ�ť
		right->setRotation(90 + 45);
		right->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
			switch (type) {
			case Widget::TouchEventType::BEGAN:_hero->setDirection(2);_hero->setRotation(90);break;
			case Widget::TouchEventType::MOVED:_hero->setDirection(2);break;
			case Widget::TouchEventType::ENDED:_hero->setDirection(0);break;
			case Widget::TouchEventType::CANCELED:_hero->setDirection(0);break;
			}
		});
		right->setPosition(Vec2(1300, 200));
		addChild(right);

		Button* pause = Button::create("button.png");//����һ����ͣ��ť
		pause->setTitleText("pause");
		pause->setTitleFontSize(32);
		pause->setRotation(90);
		pause->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
			if (Widget::TouchEventType::BEGAN == type) _pause = !_pause;
		});
		pause->setPosition(Vec2(1120, 800 - pause->getContentSize().width / 2));
		addChild(pause);

		Button* refurbish = Button::create("button.png");//����һ��ˢ�¹ؿ��İ�ť
		refurbish->setTitleText("New");
		refurbish->setTitleFontSize(32);
		refurbish->setRotation(270);
		refurbish->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
			if (Widget::TouchEventType::ENDED == type) {
				Director::getInstance()->replaceScene(Level7::createScene());
			}
		});
		refurbish->setPosition(Vec2(1050, 800 - refurbish->getContentSize().width / 2));
		addChild(refurbish);



		SimpleAudioEngine::getInstance()->playBackgroundMusic("7.mp3", true);//���ű�������

		_hero = Hero::createWithSpriteName(HEROSPEED7, 0);//��ʼ������
		_hero->setPosition(WID7/2-200, HEI7-25);
		addChild(_hero);
	/*	_bullet = Bullet::createWithSpriteName(16, _hero->getRotation(), "bullet.png");
		_bullet->setPosition(-100, -100);
		addChild(_bullet);

		_bullet = Bullet::createWithSpriteName(BUSP7, _hero->getRotation(), "bullet.png");
		_bullet->setPosition(_hero->getPositionX(), _hero->getPositionY());
		addChild(_bullet);*/
		this->scheduleUpdate();
	}//ģ��������

	Button* fire = Button::create("BOOM.png");//��ʼ�����䰴ť
	fire->ignoreContentAdaptWithSize(false);
	fire->setContentSize(Size(250, 250));
	fire->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
		if (Widget::TouchEventType::BEGAN == type)
		{
			if (!_hero->getFire()) {
				_bullet = Bullet::createWithSpriteName(BUSP7, _hero->getRotation(), "icebullet.png");
				_bullet->setPosition(_hero->getPosition());
				addChild(_bullet);

				_hero->setFire(true);
			}
		}
	});
	fire->setPosition(Vec2(WIDTH - fire->getContentSize().width / 2, HEIGHT - fire->getContentSize().height / 2));
	addChild(fire);

	_realEnemy = Sprite::create("ppp.png");//���һ�������
	_realEnemy->setPosition(400,400);
	addChild(_realEnemy);//�������ӽ���

	_falseEnemy = Sprite::create("snowmonster.png");//���һ���ٵ���
	_falseEnemy->setPosition(900,700);
	setFlasePos();
	addChild(_falseEnemy);//�ٵ�����ӽ���

	_layer = Sprite::create("BG.png");//���һ������
	_layer->setContentSize(Size(10, 1300));
	_layer->setAnchorPoint(Vec2(0.5, 0));
	_layer->setPosition(_realEnemy->getPosition());
	addChild(_layer);//������ӽ���

	//auto rota = RotateBy::create(_rotaTime, 360);
	//CallFunc* callFunc = CallFunc::create([&] {
	//	_isStopRota = true;
	//});
	//Sequence* sequence = Sequence::create(rota, callFunc, NULL);
	//_layer->runAction(sequence);

	////�����õĴ��룬������ʾ̹�˵ĽǶȣ��깤ɾ��
	//float XX = _hero->getPositionX() - _realEnemy->getPositionX();
	//float YY = _hero->getPositionY() - _realEnemy->getPositionY();
	//float pp = tan(XX / YY) * 180;
	//std::string s = "()";
	//s.append(StringUtils::format("%f", pp));

	//ext = Text::create(s, "Arial", 64);
	//ext->setPosition(Vec2(800, 400));
	//addChild(ext,99999);
	////�깤�����ϴ���ɾ��

	return true;
}

void Level7::update(float delta)
{
	switch (_GameState) //�����Ϸ�Ƿ������ͣ״̬
	{
	case 0:
		if (!_pause)//�����û�н�����ͣ״̬
		{
			removeChild(ext);
			float XX = _hero->getPositionX() - _realEnemy->getPositionX();
			float YY = _hero->getPositionY() - _realEnemy->getPositionY();
			float pp;

			/*����һ���ı���������ʾ�Ƕȣ������ã��깤��ɾ����Щ����*/
		/*	pp = transAngle(_hero->getPosition(),_realEnemy->getPosition());
			std::string s = "()";
			s.append(StringUtils::format("hero:%f", pp));
			s.append(StringUtils::format("layer:%f", _layer->getRotation()));

			 ext = Text::create(s, "Arial", 64);
			ext->setPosition(Vec2(800, 400));
			addChild(ext);*/
			//�깤�˰����ϴ���ɾ��

			_layer->setRotation(_layer->getRotation() + _rotaAdd); //�����ԽתԽ��
			if (360 < _layer->getRotation()) _layer->setRotation(_layer->getRotation() - 360);//��Ϊת��һȦ����360+����������Ҫ����С��360
			_rotaAdd *= ROTAADD; //��һ�μ�����תҪ���ӵķ�����΢�����һ��

			if (isHurt(XX,YY)) //�������ɨ��������
			{
				/*_GameState = -1;
				_layer->stopAllActions();*/

				////������δ�������ת����ٳ���
				//_rotaTime = ROTATIME;
				//Vec2 temp = _realEnemy->getPosition();
				//_realEnemy->setPosition(_falseEnemy->getPosition());
				//_layer->setPosition(_realEnemy->getPosition());
				//_falseEnemy->setPosition(temp);
				////ת����ٳ��Ͻ���
				_hero->setContentSize(Size(80, 80)); //�����Ǳ��һ�£���ʾ�������䵽��
				_GameState = -1;
			}

				if (_hero->getDirection()) //���Ӣ�۴���ǰ��״̬
				{
					_hero->tankRun(); //������ǰ��һ��
					if (_hero->isInfringeBorder(WID7, HEI7, -_hero->getContentSize().width / 2)) //�������ǰ����Խ����
						_hero->tankBack(); //����������������
					if (_hero->getBoundingBox().intersectsRect(_realEnemy->getBoundingBox()))//���Ӣ��ײ���������
					{
						_hero->tankBack(); //������������
						switch (_hero->getDirection()) //����Ӣ�۵����߷�����Ӣ��Ư�ƣ�Ư�Ƶ��ٶȸ�����ǰ���ٶ�һ��
						{
						case 1:
						case 3:
							if (_hero->getPositionX() >= _realEnemy->getPositionX())
								_hero->setPositionX(_hero->getPositionX() + HEROSPEED7);
							else _hero->setPositionX(_hero->getPositionX() - HEROSPEED7);
							break;
						case 2:
						case 4:
							if (_hero->getPositionY() >= _realEnemy->getPositionY())
								_hero->setPositionY(_hero->getPositionY() + HEROSPEED7);
							else _hero->setPositionY(_hero->getPositionY() - HEROSPEED7);
						}
					}
				}//Ӣ�۵�����״̬���

				 //���ӵ���
				if (_hero->getFire())
				{
					if (_bullet)//����ӵ�������
					{
						_bullet->bulletRun();//���ӵ���
						bool removeFlag1 = false; //����һ���Ƿ�ɾ���ӵ��ı�ʶ
						if (_bullet->isInfringeBorder(WID7, HEI7, _bullet->getContentSize().height / 2)) //����ӵ���Խ�˱߽�
						{
							removeFlag1 = true; //���Ƿ�Ӧ��ɾ���ӵ��ı����Ϊ��
							goto removeBullet1; //Ȼ��ȥɾ���ӵ�
						}//����ӵ�Խ���ˣ��ӵ���ʧ
						if (_bullet->getBoundingBox().intersectsRect(_realEnemy->getBoundingBox()))//����ӵ������������
						{
							if (++_taskCount >= TASKNUM7)//������е��˴ﵽ�ؿ�������
							{
								_GameState = 1;
							}
							else
							{
								_realEnemy->setPosition(_falseEnemy->getPosition());//�ü�����˱�������
								_layer->setPosition(_falseEnemy->getPosition());//�������д���������˺ͼ����λ��
								//_rotaTime = ROTATIME;//�ü�����ת��ʱ�����¹�λ����ý���һ�������ʱ����ת
								_rotaAdd = 1.0; //���»ָ���������Ҫ���ӵķ���
								setFlasePos();//����һ���¼�����˵�λ��
								removeFlag1 = true; //���Ƿ�Ӧ��ɾ���ӵ��ı����Ϊ��
								goto removeBullet1; //Ȼ��ȥɾ���ӵ�
							}
						}
					removeBullet1:
						if (true == removeFlag1)
						{
							this->removeChild(_bullet);
							_bullet = nullptr;
							_hero->setFire(false);
						}
					}
				}//Ӣ�۵��ӵ��������

		}
		break;
	case 1: //�����֧������Ҵﵽ�˹�������
	{ //�������Ҫ���ϻ����ţ���Ȼ��ĳЩ�������У�����Ϊ�ֲ������������������뱨��
		//�ѹؿ�������Ϊ1����ʾ�ô�������ڶ�����
		{
			if (7 > UserDefault::getInstance()->getIntegerForKey("level"))
			{
				UserDefault::getInstance()->setIntegerForKey("level", 7);
				UserDefault::getInstance()->flush();
			}
		}
		_hero->setScale(10.0f);
		Text* winText = Text::create("You Win!!Next level?", "Arial", 64);
		winText->setRotation(270);
		addChild(winText, 99);

		auto next = Button::create("button.png");
		next->setTitleText("Next");
		next->setRotation(270);
		next->setTitleFontSize(32);
		next->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
			if (Widget::TouchEventType::ENDED == type) //����������ӽ�����һ�ؿ������߼�
			{
				Director::getInstance()->replaceScene(HelloWorld::createScene());
			}
		});
		next->setPosition(Vec2(600, 400));
		addChild(next, 99);
		_GameState = 2;
	}
	break;
	case -1://���������Բ��ӻ����ţ���Ϊ�������һ��case��֧�ˣ�������ڳ�ʼ����case�����ı��뱨��
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();//ֹͣ���ű�������
		Text* failText = Text::create("hero be killed by layer", "Arial", 64);
		failText->setRotation(270);
		failText->setPosition(Vec2(400, 400));
		addChild(failText);
		_GameState = 2;//����Ƿ�ֹһֱֹͣ���ű������֣����һֱֹͣ�Ļ����ٴ����¼��ز���BGM�Ļ����ᾲ����

		float XX = _hero->getPositionX() - _realEnemy->getPositionX();
		float YY = _hero->getPositionY() - _realEnemy->getPositionY();
		float pp = tan(XX / YY) * 180;
		std::string s = "()";
		s.append(StringUtils::format("%f", pp));
		
		Text* ext = Text::create(s, "Arial", 64);
		ext->setPosition(Vec2(800, 400));
		addChild(ext);
	}
	break;
	case -2:
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		Text* failText2 = Text::create("enemy be killed by bullet", "Arial", 64);
		failText2->setRotation(270);
		failText2->setPosition(Vec2(400, 400));
		addChild(failText2);
		_GameState = 2;//����Ƿ�ֹһֱֹͣ���ű������֣����һֱֹͣ�Ļ����ٴ����¼��ز���BGM�Ļ����ᾲ����
	}
	break;
	case -3:
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		Text* failText3 = Text::create("ICE be killed by bullet", "Arial", 64);
		failText3->setRotation(270);
		failText3->setPosition(Vec2(400, 400));
		addChild(failText3);
		_GameState = 2;//����Ƿ�ֹһֱֹͣ���ű������֣����һֱֹͣ�Ļ����ٴ����¼��ز���BGM�Ļ����ᾲ����
		break;
		break;
	}
}

bool Level7::isHurt(float XX, float YY) //������⼤���Ƿ�ɨ�䵽��̹��
{
	float layerAngel = _layer->getRotation();//��ȡ����ĽǶ�
	float heroAngle = transAngle(_hero->getPosition(), _realEnemy->getPosition());//��ȡ̹������˵ĽǶ�
	return (layerAngel > heroAngle-3.1f && layerAngel < heroAngle+3.1f);
}

float Level7::transAngle(Vec2 origin, Vec2 target)//ת���Ƕ��ã���һ���Ǽ���Դ���ڶ�������������
{
	float x = origin.x - target.x;
	float y = origin.y - target.y;
	if (x >= 0.0) //̹����Լ�����˶��ԣ����������Ұ�����
	{
		if (y >= 0.0) //̹��������ڵ������Ͻǣ����target���ԣ�
		{
			return atan(x / y) * 180 / PI;
		}
		else // ��Ȼ̹�˾��������½ǣ����target���ԣ�
		{
			return 90 - atan(y / x) * 180 / PI;
		}
	}
	else //̹����Լ�����˶��ԣ����������������
	{
		if (y >= 0.0)//̹������ڵ������Ͻǣ����target���ԣ�
		{
			return 270.0 - atan(y / x) * 180 / PI;
		}
		else //��Ȼ̹�˾��������½ǣ����target���ԣ�
		{		
			return 180 + atan(x / y) * 180 / PI;
		}
	}
}

void Level7::setFlasePos() //���ü�����˵�λ��
{
start:
	float distance; //���������ٵ���������Զ���룬ˮƽ���봹ֱ�ߵĵ�����
	distance = MAXDIS - CCRANDOM_0_1()*OFFSET;  //Ȼ���ʵ�����ҽ���һ���Ѷȣ�����һ������
	float horizontal; //�������ٵ���ˮƽ�ߵľ���
	float vertical;  //�������ٵ��˴�ֱ�ߵľ���
	horizontal = CCRANDOM_0_1()*distance;  //�������һ����ٵ���ˮƽ�ߵľ���
	vertical = distance - horizontal; //Ȼ���ܾ����ȥˮƽ�߾��������ٵ��˵Ĵ�ֱ�߾���
	int random; //��һ�����ֵ������ʾˮƽ��ֱ�����������Ǹ���
	random = CCRANDOM_0_1() * 2;
	if (random ) horizontal = -horizontal;
	random = CCRANDOM_0_1() * 2;
	if (random) vertical = -vertical;
	horizontal = _falseEnemy->getPositionX() + horizontal; //�����¼��˷�λ��ˮƽֵ
	vertical += _falseEnemy->getPositionY(); //�����¼��˷�λ�Ĵ���ֵ
	if (horizontal<125 || horizontal>WID7 - 125 || vertical<125 || vertical>HEI7 - 125) //����¼��˵��·�λ����������Խ����߿����ĸ���
		goto start; //��ô����Ūһ���µķ�λֵ
	_falseEnemy->setPosition(Vec2(horizontal, vertical));
	return;
}