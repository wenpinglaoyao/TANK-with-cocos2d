#include "Level5.h"
USING_NS_CC;

cocos2d::Scene* Level5::createScene()
{
	return Level5::create();
}

bool Level5::init()
{
	{
		if (!Scene::init()) return false;

		_taskCount = 0;
		_GameState = 0;
		_barValue = BARMAX;
		auto background = Sprite::create("BG.png");//�������һ����ɫ����ͼƬ
		background->setContentSize(Size(400, 800));
		background->setPosition(WID5 + background->getContentSize().width / 2, background->getContentSize().height / 2);
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
				Director::getInstance()->replaceScene(Level5::createScene());
			}
		});
		refurbish->setPosition(Vec2(1050, 800 - refurbish->getContentSize().width / 2));
		addChild(refurbish);



		SimpleAudioEngine::getInstance()->playBackgroundMusic("5.mp3",true);//���ű�������

		_hero = Hero::createWithSpriteName(HEROSPEED5, 0);//��ʼ������
		_hero->setPosition(26, 400);
		addChild(_hero);
		/*_bullet = Bullet::createWithSpriteName(16, _hero->getRotation(), "bullet.png");
		_bullet->setPosition(-100, -100);
		addChild(_bullet);

		_bullet = Bullet::createWithSpriteName(BUSP5, _hero->getRotation(), "bullet.png");
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
				_bullet = Bullet::createWithSpriteName(BUSP5, _hero->getRotation(), "icebullet.png");
				_bullet->setPosition(_hero->getPosition());
				addChild(_bullet);

				for (int i = 0;i < MAXE5;i++)
				{
					if (_enemy[i]->getDirection())
					{
						Bullet* bullet = Bullet::createWithSpriteName(EBUSP5, (_enemy[i]->getDirection() - 1) * 90, "bullet.png");
						bullet->setPosition(_enemy[i]->getPosition());
						bullet->bulletRun();bullet->bulletRun();//���õ����ڵ��ɳ�����Χ
						addChild(bullet);
						_enemyBulletVector.pushBack(bullet);
					}
				}
				_hero->setFire(true);
			}
		}
	});
	fire->setPosition(Vec2(WIDTH - fire->getContentSize().width / 2, HEIGHT - fire->getContentSize().height / 2));
	addChild(fire);

	for (int i = 0;i < MAXE5;i++)
	{
		_enemy[i] = Tank::createWithSpriteName(ENEMYSP5, int(CCRANDOM_0_1() * 4 + 1), 0, "enemy2.PNG");
		_enemy[i]->setRotation(90.0f * (_enemy[i]->getDirection() - 1));
		_enemy[i]->setPosition(100 + i * 51, 100 + i * 51);
		_enemy[i]->setFire(false);
		addChild(_enemy[i], 98);
	}

	_bar = Sprite::create("HP.png");
	_bar->setContentSize(Size(20, _barValue));
	_bar->setPosition(WID5 + _bar->getContentSize().width / 2,300+_bar->getContentSize().height/2);
	addChild(_bar, 2);
	return true;
}

void Level5::update(float delta)
{
	switch (_GameState)
	{
	case 0:
		if (!_pause)//�����û�н�����ͣ״̬
		{
			{
				_bar->setContentSize(Size(20, _barValue));
				_bar->setPosition(WID5 + _bar->getContentSize().width / 2, 300 + _bar->getContentSize().height / 2);
			}
			_barValue--;
			if (!_barValue) _barValue = BARMAX;
			
			if (_hero->getDirection()) //���Ӣ�۴���ǰ��״̬
			{
				_hero->tankRun();
				if (_hero->isInfringeBorder(WID5, HEI5, -_hero->getContentSize().width / 2))
					_hero->tankBack();

				for (int i = 0;i < MAXE5;i++) //���Ӣ��ײ���˱��̹��
				{
					if (_hero->getBoundingBox().intersectsRect(_enemy[i]->getBoundingBox())) {
						_hero->tankBack();
						break;
					}
				}
				for (int i = 0;i < _iceVector.size();i++)
				{
					auto ice = _iceVector.at(i);
					if (_hero->getBoundingBox().intersectsRect(ice->getBoundingBox()))
					{
						_hero->tankBack();
						break;
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
					if (_bullet->isInfringeBorder(WID5, HEI5, _bullet->getContentSize().height / 2)) //����ӵ���Խ�˱߽�
					{
						removeFlag1 = true;
						goto removeBullet1;
					}//����ӵ�Խ���ˣ��ӵ���ʧ

					for (int i = 0;i < MAXE5;i++) //����ӵ�����˵���ײ
					{
						if (_bullet->getBoundingBox().intersectsRect(_enemy[i]->getBoundingBox()))//����ڵ������˵���
						{
							SimpleAudioEngine::getInstance()->playEffect("beng.mp3");
							auto ice = Sprite::create("ice.png");
							ice->setPosition(_enemy[i]->getPosition());
							addChild(ice);
							_iceVector.pushBack(ice);
							if (++_taskCount >= TASKNUM5) //������е����������ڵ���������
								_GameState = 1; //��Ϸʤ��
							if (_taskCount <= TASKNUM5 - MAXE5)//����ĳ�������е����������ٵĻ�����ô�����˻���λ�ü��ؽ���ʱ�伴��
							{
							resetpos1:
								_enemy[i]->setPosition(CCRANDOM_0_1() * (WID5 - 50) + 25, CCRANDOM_0_1() * (HEI5 - 50) + 25);
								if (_enemy[i]->getBoundingBox().intersectsRect(_hero->getBoundingBox())) //����õ��˵���λ�������ǳ�ͻ
									goto resetpos1;
								for (int j = 0;j < MAXE5;j++)
								{
									if (i != j && _enemy[i]->getBoundingBox().intersectsRect(_enemy[j]->getBoundingBox()))//�����λ������һ�����˳�ͻ
										goto resetpos1;
								}
								for (auto ice : _iceVector)
								{
									if (_enemy[i]->getBoundingBox().intersectsRect(ice->getBoundingBox()))
										goto resetpos1;
								}
								_enemy[i]->setPositionX(_enemy[i]->getPositionX());
								_enemy[i]->setPositionY(_enemy[i]->getPositionY());
								_enemy[i]->setCool(180);//�����˼���һ����������ʱ��
							}
							else //��Ȼ���õ�������"��ʧ"
							{
								_enemy[i]->setPosition(-50-i*60, -50-i*60);
								_enemy[i]->setDirection(0);
							}
							removeFlag1 = true;
							goto removeBullet1;//�������Ҫ�ӣ���Ȼ�ӵ��Ѿ�ɾ���ˣ������ᱻ���Ե�
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

			 //�ֵ������ж���
			for (int i = 0;i < MAXE5;i++)
			{
				if (0 == _enemy[i]->getCool()) //����õ��˵Ľ���ʱ���Ѿ�������
				{
					if (_barValue<=1) //�ı�����Ǹ��������ı�ת�����
					{
						_enemy[i]->setDirection(CCRANDOM_0_1() * 4 + 1);
						_enemy[i]->setRotation(90.0f*(_enemy[i]->getDirection() - 1));
					}//���������˸ı䷽���ˣ��Ǿ����ˣ�����Ͳ�������
					else
					{
						_enemy[i]->tankRun();//�������������һ��
						if (_enemy[i]->isInfringeBorder(WID5, HEI5, -_enemy[i]->getContentSize().width / 2)) //����õ���Խ����
							_enemy[i]->tankBack(); //��ô������
												   //�ȼ������Ƿ�ײ��Ӣ��
						if (_enemy[i]->getBoundingBox().intersectsRect(_hero->getBoundingBox())) //����õ��������ǳ�ͻ��
						{
							_enemy[i]->tankBack();
							_enemy[i]->setDirection(CCRANDOM_0_1() * 4 + 1);
							_enemy[i]->setRotation(90.0f*(_enemy[i]->getDirection() - 1));
							break;
						}

						//�������Ƿ�ײ������
						for (auto ice : _iceVector)
						{
							if (_enemy[i]->getBoundingBox().intersectsRect(ice->getBoundingBox()))
							{
								_enemy[i]->tankBack();
								_enemy[i]->setDirection(CCRANDOM_0_1() * 4 + 1);
								_enemy[i]->setRotation(90.0f*(_enemy[i]->getDirection() - 1));
							}
						}

						//���������Ƿ�ײ���Լ���
						for (int j = 0;j < MAXE5;j++)
						{
							if (j != i && _enemy[i]->getBoundingBox().intersectsRect(_enemy[j]->getBoundingBox()))
							{
								_enemy[i]->tankBack();
								_enemy[i]->setDirection(CCRANDOM_0_1() * 4 + 1);
								_enemy[i]->setRotation(90.0f*(_enemy[i]->getDirection() - 1));
								break;
							}
						}
					}
				}
				else  //������˵Ľ���ʱ�仹û�н���
					_enemy[i]->setCool(_enemy[i]->getCool() - 1);//���ٵ��˵Ľ���ʱ��

			}

			//�õ��˵��ӵ��ж���
			for (int i = 0;i < _enemyBulletVector.size();i++)
			{
				auto bullet = _enemyBulletVector.at(i);
				bullet->bulletRun();

				if (bullet->isInfringeBorder(WID5, HEI5, 0))//����ӵ�Խ����
				{
					removeChild(bullet, true);
					_enemyBulletVector.eraseObject(bullet);
					for (int i = 0;i < MAXE5;i++) _enemy[i]->setVisible(true);
					continue;
				}

				if (_hero->getBoundingBox().intersectsRect(bullet->getBoundingBox()))//������Ǳ��ӵ�����
				{
					removeChild(bullet, true);
					_enemyBulletVector.eraseObject(bullet);
					_GameState = -1;
					continue;
				}

				for (int j = 0;j < MAXE5;j++)//�������ӵ�����˵���ײ
				{
					_enemy[j]->setVisible(true);//���õ�������
					if (_enemy[j]->getCool() > 1)//������˻����ڸճ����׶�
					{
						_enemy[j]->setVisible(false);//���õ������Σ��´���һ������������λ����������һ���ڵ�����켣��
					}
					else if(_enemy[j]->getBoundingBox().intersectsRect(bullet->getBoundingBox()))//�������ڵ���ĳһ��������ײ��
					{
						removeChild(bullet, true);
						_enemyBulletVector.eraseObject(bullet);
						_GameState = -2;
						goto END;
					}
				}

				for (int j = 0;j < _iceVector.size();j++)//�����˵��ӵ��Ƿ��뱻�����ĵ�����ײ
				{
					auto ice = _iceVector.at(j);
					if (ice->getBoundingBox().intersectsRect(bullet->getBoundingBox()))
					{
						removeChild(bullet);
						_enemyBulletVector.eraseObject(bullet);
						_GameState = -3;
						goto END;
					}
				}
			END:;
			}
	
		}
		break;
	case 1:
	{ //�������Ҫ���ϻ����ţ���Ȼ��ĳЩ�������У�����Ϊ�ֲ������������������뱨��
		//�ѹؿ�������Ϊ1����ʾ�ô�������ڶ�����
		{
			if (5 > UserDefault::getInstance()->getIntegerForKey("level"))
			{
				UserDefault::getInstance()->setIntegerForKey("level", 5);
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
		auto chnStrings = CCDictionary::createWithContentsOfFile("xixi.xml");
		auto failText = Text::create(((CCString*)chnStrings->objectForKey("failLevel11"))->getCString(), "", 64);
		failText->setRotation(270);
		failText->setPosition(Vec2(400, 400));
		addChild(failText);
		_GameState = 2;//����Ƿ�ֹһֱֹͣ���ű������֣����һֱֹͣ�Ļ����ٴ����¼��ز���BGM�Ļ����ᾲ����
	}
	break;
	case -2:
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		auto chnStrings = CCDictionary::createWithContentsOfFile("xixi.xml");
		auto failText2 = Text::create(((CCString*)chnStrings->objectForKey("failLevel51"))->getCString(), "", 64);
		failText2->setRotation(270);
		failText2->setPosition(Vec2(400, 400));
		addChild(failText2);
		_GameState = 2;//����Ƿ�ֹһֱֹͣ���ű������֣����һֱֹͣ�Ļ����ٴ����¼��ز���BGM�Ļ����ᾲ����
	}
	break;
	case -3:
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		auto chnStrings = CCDictionary::createWithContentsOfFile("xixi.xml");
		auto failText3 = Text::create(((CCString*)chnStrings->objectForKey("failLevel52"))->getCString(), "", 64);
		failText3->setRotation(270);
		failText3->setPosition(Vec2(400, 400));
		addChild(failText3);
		_GameState = 2;//����Ƿ�ֹһֱֹͣ���ű������֣����һֱֹͣ�Ļ����ٴ����¼��ز���BGM�Ļ����ᾲ����
		break;
		break;
	}
}