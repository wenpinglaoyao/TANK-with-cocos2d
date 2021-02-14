#include "Level4.h"
USING_NS_CC;

cocos2d::Scene* Level4::createScene()
{
	return Level4::create();
}


bool Level4::init()
{
	{
		if (!Scene::init()) return false;

		_taskCount = 0;
		_GameState = 0;
		_countInterrogate = 0;
		_sirCount = 1;
		auto background = Sprite::create("BG.png");//�������һ����ɫ����ͼƬ
		background->setContentSize(Size(600, 800));
		background->setPosition(WID4 + background->getContentSize().width / 2, background->getContentSize().height / 2);
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
				Director::getInstance()->replaceScene(Level4::createScene());
			}
		});
		refurbish->setPosition(Vec2(1050, 800 - refurbish->getContentSize().width / 2));
		addChild(refurbish);



		SimpleAudioEngine::getInstance()->playBackgroundMusic("4.mp3");//���ű�������

		_hero = Hero::createWithSpriteName(HEROSPEED, 0);//��ʼ������
		_hero->setPosition(26, 400);
		addChild(_hero);
		_bullet = Bullet::createWithSpriteName(16, _hero->getRotation(), "bullet.png");
		_bullet->setPosition(-100, -100);
		addChild(_bullet);

		_bullet = Bullet::createWithSpriteName(BUSP, _hero->getRotation(), "bullet.png");
		_bullet->setPosition(_hero->getPositionX(), _hero->getPositionY());
		addChild(_bullet);
		this->scheduleUpdate();
	}//ģ��������

	//��ʼ���ĸ�ʯͷ
	{
	_stone[0] = Sprite::create("obstacle.png");
	_stone[0]->setPosition(STONESIZE4 / 2, STONESIZE4 / 2);
	addChild(_stone[0]);
	_stone[1] = Sprite::create("obstacle.png");
	_stone[1]->setPosition(STONESIZE4 / 2, HEI4 - STONESIZE4 / 2);
	addChild(_stone[1]);
	_stone[2] = Sprite::create("obstacle.png");
	_stone[2]->setPosition(WID4 - STONESIZE4 / 2, HEI4 - STONESIZE4 / 2);
	addChild(_stone[2]);
	_stone[3] = Sprite::create("obstacle.png");
	_stone[3]->setPosition(WID4 - STONESIZE4 / 2, STONESIZE4 / 2);
	addChild(_stone[3]);
	}//ʯͷ��ʼ������

	std::string s = "sir";
	s.append(StringUtils::format("%d.png", _sirCount));
	_sir = Sprite::create(s.c_str());
	_sir->setPosition(WID4 / 2, HEI4 / 2);
	addChild(_sir);

	for (int i = 0;i < MAXE4;i++)
	{
		_enemy[i] = Tank::createWithSpriteName(ESP4, int(CCRANDOM_0_1() * 4 + 1), 30, "enemy4.png");
		_enemy[i]->setRotation(90.0f * (_enemy[i]->getDirection() - 1));
		_enemy[i]->setPosition(80 + i * 51, 80 + i * 51);
		_enemy[i]->setContentSize(Size(50, 50));
		_enemy[i]->setFire(false);
		addChild(_enemy[i], 98);
	}
	for (int i = 0;i < MAXE4;i++)
	{
		int x, y;
		resetPos:
		x = CCRANDOM_0_1()*(WID4-152);
		y = CCRANDOM_0_1()*(HEI4-152);
		x += 76;y += 76;
		_enemy[i]->setPosition(x, y);
		
		for (int j = 0;j < MAXE4;j++)
		{
			if (i!=j&&tankColl(_enemy[i], _enemy[j]))
				goto resetPos;
		}
	}

	return true;
}

void Level4::update(float delta)
{
	switch (_GameState)
	{
	case 0:

		if (!_pause)//�����û�н�����ͣ״̬
		{
			if (_taskCount >= 3 && _countInterrogate<=0)//���ץ�񳤹ٵ������㹻��
			{
				_GameState = 1;
			}
			if (_countInterrogate-- == 0)
			{
				_sir->setVisible(true);
			}
			if (_hero->getDirection()) //���Ӣ�۴���ǰ��״̬
			{
				_hero->tankRun();
				if (_hero->isInfringeBorder(WID4, HEI4, -_hero->getContentSize().width / 2))
					_hero->tankBack();
				for (int i = 0;i < 4;i++)
				{
					if (tankColl(_hero, _stone[i]))
						_hero->tankBack();
				}

				for (int i = 0;i < MAXE4;i++) //���Ӣ��ײ���˱��̹��
				{
					if (tankColl(_hero,_enemy[i]))
					{
						if (backDetection(_enemy[i], _hero->getDirection(), _hero->getSpeed()))
						{
							_hero->tankBack();
						}
					}
				}

				if (tankColl(_hero, _sir) && _countInterrogate<=0)//���ץ���˿���¶���ĳ���
				{
					//��������ͷ����������³���λ��
					_countInterrogate = INTERROGATETIME;
					_sirCount++;
					_taskCount++;
					std::string s = "sir";
					s.append(StringUtils::format("%d.png", _sirCount));
					_sir->setTexture(s.c_str());
					_sir->setVisible(false);
					int x = CCRANDOM_0_1() * 300 - 150;
					int y = CCRANDOM_0_1() * 300 - 150;
					_sir->setPosition(WID4 / 2 + x, HEI4 / 2 + y);
				}
			}//Ӣ�۵�����״̬���

			 //���ӵ���
			{
				_bullet->bulletRun();

				if (_bullet->isInfringeBorder(WID4, HEI4, _bullet->getContentSize().height / 2))//����ӵ�Խ����
				{
					_bullet->setPosition(_hero->getPositionX(), _hero->getPositionY());
					_bullet->setDirection(_hero->getRotation());
					_GameState = -1;
				}

				for (int i = 0;i < MAXE4;i++)
				{
					if (tankColl(_bullet, _enemy[i]))
					{
						SimpleAudioEngine::getInstance()->playEffect("BOOM2.mp3");
						_bullet->setPosition(_hero->getPositionX(),_hero->getPositionY());
						_bullet->setDirection(_hero->getRotation());

						_enemy[i]->setPosition(-50, -50);
						_enemy[i]->setDirection(0);
					}
				}
				for (int i = 0;i < 4;i++)
				{
					if (tankColl(_bullet, _stone[i]))
					{
						_bullet->setPosition(_hero->getPositionX(), _hero->getPositionY());
						_bullet->setDirection(_hero->getRotation());
					}
				}
			}//Ӣ�۵��ӵ��������

			 //�ֵ������ж���
			for (int i = MAXE4 - 1;i >= 0;i--)
			{
				if (0 == _enemy[i]->getCool()) //����õ��˵Ľ���ʱ���Ѿ�������
				{
					{
						_enemy[i]->tankRun();//�������������һ��
						if (_enemy[i]->isInfringeBorder(WID4, HEI4, -25)) //����õ���Խ����
						{
							_enemy[i]->tankBack(); //��ô������
							if (3 > _enemy[i]->getDirection()) _enemy[i]->setDirection(_enemy[i]->getDirection() + 2);
							else _enemy[i]->setDirection((_enemy[i]->getDirection() + 2) % 4);

							_enemy[i]->setRotation((_enemy[i]->getDirection() - 1) * 90);
							goto endDetectionColl;
						}

						//�ȼ������Ƿ�ײ��Ӣ��
						if (tankColl(_enemy[i],_hero)) //����õ��������ǳ�ͻ��
						{
							_enemy[i]->tankBack();
							_enemy[i]->setDirection((_hero->getRotation()/90)+1);
							_enemy[i]->setRotation((_enemy[i]->getDirection() - 1) * 90);
							goto endDetectionColl;
							break;
						}

						//�������Ƿ�ײ��ʯͷ
						for (int j = 0;j < 4;j++)
						{
							if (tankColl(_enemy[i],_stone[j]))
							{
								_enemy[i]->tankBack();
								if (3 > _enemy[i]->getDirection()) _enemy[i]->setDirection(_enemy[i]->getDirection() + 2);
								else _enemy[i]->setDirection((_enemy[i]->getDirection() + 2) % 4);
								_enemy[i]->setRotation(90.0f*(_enemy[i]->getDirection() - 1));
								goto endDetectionColl;
							}
						}

						//���������Ƿ�ײ���Լ���
						for (int j = 0;j < MAXE4;j++)
						{
							if (j != i && tankColl(_enemy[i], _enemy[j]))
							{
								_enemy[i]->tankBack();
								///****���¼������������������Լ��˵ĵ���������***/
								//{
								//	if (3 > _enemy[i]->getDirection()) _enemy[i]->setDirection(_enemy[i]->getDirection() + 2);
								//	else _enemy[i]->setDirection((_enemy[i]->getDirection() + 2) % 4);
								//	_enemy[i]->setRotation(90.0f*(_enemy[i]->getDirection() - 1));
								//}
								///***�����ߵĴ������***/
								break;
							}
						}
					endDetectionColl:;
					}
				}
				else  //������˵Ľ���ʱ�仹û�н���
					_enemy[i]->setCool(_enemy[i]->getCool() - 1);//���ٵ��˵Ľ���ʱ��

			}

		}//�Ƿ����״̬�߼����
		break;
	case 1:
	{ //�������Ҫ���ϻ����ţ���Ȼ��ĳЩ�������У�����Ϊ�ֲ������������������뱨��
		//�ѹؿ�������Ϊ4����ʾ�ô��������4����
		{
			if (4 > UserDefault::getInstance()->getIntegerForKey("level"))
			{
				UserDefault::getInstance()->setIntegerForKey("level", 4);
				UserDefault::getInstance()->flush();
			}
		}
		_hero->setScale(10.0f);
		Text* winText = Text::create("You Win!!Next level?", "Arial", 64);
		winText->setRotation(270);
		addChild(winText, 199);

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
		addChild(next, 199);
		_GameState = 2;
	}
	break;
	case -1://���������Բ��ӻ����ţ���Ϊ�������һ��case��֧�ˣ�������ڳ�ʼ����case�����ı��뱨��
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();//ֹͣ���ű�������
		auto chnStrings = CCDictionary::createWithContentsOfFile("xixi.xml");
		auto failText = Text::create(((CCString*)chnStrings->objectForKey("failLevel41"))->getCString(), "", 64);
		failText->setRotation(270);
		failText->setPosition(Vec2(400, 400));
		addChild(failText, 199);
		_GameState = 2;//����Ƿ�ֹһֱֹͣ���ű������֣����һֱֹͣ�Ļ����ٴ����¼��ز���BGM�Ļ����ᾲ����
	}
	break;
	case -2:
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		Text* failText2 = Text::create("hero be killed by bullet", "Arial", 64);
		failText2->setRotation(270);
		failText2->setPosition(Vec2(400, 400));
		addChild(failText2, 199);
		_GameState = 2;//����Ƿ�ֹһֱֹͣ���ű������֣����һֱֹͣ�Ļ����ٴ����¼��ز���BGM�Ļ����ᾲ����
	}
	break;
	case -3:
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		Text* failText3 = Text::create("GameOver!partner be killed by BOOM", "Arial", 64);
		failText3->setRotation(270);
		failText3->setPosition(Vec2(400, 400));
		addChild(failText3);
		_GameState = 2;//����Ƿ�ֹһֱֹͣ���ű������֣����һֱֹͣ�Ļ����ٴ����¼��ز���BGM�Ļ����ᾲ����
		break;
		break;
	}
}