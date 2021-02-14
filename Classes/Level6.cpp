#include "Level6.h"
USING_NS_CC;

cocos2d::Scene* Level6::createScene()
{
	return Level6::create();
}

bool Level6::init()
{
	{
		if (!Scene::init()) return false;

		_taskCount = 0;
		_GameState = 0;
		_barValue = BARMAX6;
		_speedX = _speedY = 0.0f;
		_moveFlag = false;
		_coolTime = 0;
		auto background = Sprite::create("BG.png");//�������һ����ɫ����ͼƬ
		background->setContentSize(Size(400, 800));
		background->setPosition(WID6 + background->getContentSize().width / 2, background->getContentSize().height / 2);
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
				Director::getInstance()->replaceScene(Level6::createScene());
			}
		});
		refurbish->setPosition(Vec2(1050, 800 - refurbish->getContentSize().width / 2));
		addChild(refurbish);



		SimpleAudioEngine::getInstance()->playBackgroundMusic("6.mp3", true);//���ű�������

		_hero = Hero::createWithSpriteName(HEROSPEED5, 0);//��ʼ������
		_hero->setPosition(26, 400);
		addChild(_hero);
		_bullet = Bullet::createWithSpriteName(16, _hero->getRotation(), "bullet.png");
		_bullet->setPosition(-100, -100);
		addChild(_bullet);

		_aim = Sprite::create("bullet.png");
		addChild(_aim,999);

		_aim2 = Sprite::create("bullet.png");
		addChild(_aim2, 999);

	
		this->scheduleUpdate();
	}//ģ��������

	Button* fire = Button::create("BOOM.png");//��ʼ�����䰴ť
	fire->ignoreContentAdaptWithSize(false);
	fire->setContentSize(Size(250, 250));
	fire->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
		if (Widget::TouchEventType::BEGAN == type)
		{
			if (!_hero->getFire()) {
				_bullet = Bullet::createWithSpriteName(BUSP6, _hero->getRotation(), "icebullet.png");
				_bullet->setPosition(_hero->getPosition());
				addChild(_bullet);

				_hero->setFire(true);
			}
		}
	});
	fire->setPosition(Vec2(WIDTH - fire->getContentSize().width / 2, HEIGHT - fire->getContentSize().height / 2));
	addChild(fire);

	for (int i = 0;i < MAXE6;i++) //���˵ĳ�ʼ��
	{
		_enemy[i] = Tank::createWithSpriteName(ENEMYSP6, int(CCRANDOM_0_1() * 4 + 1), 0, "snowmonster.png");
		_enemy[i]->setRotation(90.0f * (_enemy[i]->getDirection() - 1));
		_enemy[i]->setPosition(100 + i * 51, 150 + i * 51);
		_enemy[i]->setFire(false);
		addChild(_enemy[i], 98);
	}
	for (int i = 0;i < MAXE6;i++)
	{
		_enemyBullet[i] = Bullet::createWithSpriteName(EBUSP6, (_enemy[i]->getDirection() - 1) * 90, "bullet.png");
		_enemyBullet[i]->setPosition(_enemy[i]->getPosition());
		addChild(_enemyBullet[i]);
	}

	_bar = Sprite::create("HP.png");
	_bar->setContentSize(Size(20, _barValue));
	_bar->setPosition(WID6 + _bar->getContentSize().width / 2, 300 + _bar->getContentSize().height / 2);
	addChild(_bar, 2);

	_football = Sprite::create("football.png");
	_football->setContentSize(Size(BALLSIZE, BALLSIZE));
	_football->setPosition(WID6 / 2, HEI6 / 2);
	addChild(_football, 100);

	_star = Sprite::create("star.png");
	_star->setVisible(false);
	addChild(_star, 101);

	return true;
}

void Level6::update(float delta)
{
	switch (_GameState)
	{
	case 0:
		if (!_pause)//�����û�н�����ͣ״̬
		{
			_aim->setPosition(_hero->getPosition());//�ȵ����������ϵ�׼��
			_aim2->setPosition(_football->getPosition());//�ٵ����������ĵ�׼��
			//�����߶�������
			{
				_bar->setContentSize(Size(20, _barValue));
				_bar->setPosition(WID6 + _bar->getContentSize().width / 2, 300 + _bar->getContentSize().height / 2);
				_barValue -= 0.3;
			}
			
			if (_barValue<=0)//����߶���������
			{
				_moveFlag = true; //��ʯ��ʼ����
				_star->setVisible(true); //��ʯ¶��
				_starSize = STARMAXSIZE; //��ʯ�����ó����ߴ�
				_coolTime = 0; //��ʼ������ʱ
				_barValue = BARMAX6; //�߶�����������Ϊ��Ѫ
			}

			_football->setPosition(_football->getPositionX() + _speedX, _football->getPositionY() + _speedY);//�����ƶ�
			for (int i = 0;i < MAXE6;i++)//��������Ƿ�ײ������
			{
				//���������ƶ�״̬����ײ���˵���
				if (_enemy[i]->getBoundingBox().intersectsCircle(_football->getPosition(), BALLSIZE / 2) && (_speedX || _speedY))
				{
					_speedX = _speedY = 0.0f;//����ֹס

					if (++_taskCount >= TASKNUM6) //������е����������ڵ���������
						_GameState = 1; //��Ϸʤ��
					if (_taskCount <= TASKNUM6 - MAXE6)//����ĳ�������е����������ٵĻ�����ô�����˻���λ�ü��ؽ���ʱ�伴��
					{
					resetpos1:
						_enemy[i]->setPosition(CCRANDOM_0_1() * (WID6 - 50) + 25, CCRANDOM_0_1() * (HEI6 - 50) + 25);
						if (_enemy[i]->getBoundingBox().intersectsRect(_hero->getBoundingBox())) //����õ��˵���λ�������ǳ�ͻ
							goto resetpos1;
						for (int j = 0;j < MAXE6;j++)
						{
							if (i != j && _enemy[i]->getBoundingBox().intersectsRect(_enemy[j]->getBoundingBox()))//�����λ������һ�����˳�ͻ
								goto resetpos1;
						}
						_enemy[i]->setPositionX(_enemy[i]->getPositionX());
						_enemy[i]->setPositionY(_enemy[i]->getPositionY());
						_enemy[i]->setCool(80);//�����˼���һ����������ʱ��
					}
					else //��Ȼ���õ�������"��ʧ"
					{
						_enemy[i]->setPosition(-50 - i * 60, -50 - i * 60);
						_enemy[i]->setDirection(0);
					}
					break;
				}
			}

			if (true == _moveFlag)//�����ʯ�Ѿ������������������ƶ�
			{
				if (STARMAXSIZE <= _starSize) //����Ƕ����տ�ʼ
				{
					_star->setPosition(_hero->getPosition()); //����ʯ��׼����
				}
			
				if (STARMINSIZE < _starSize) //�����ʯ��û���㹻�ӽ����棨�����ҵ����ǻ�����
				{
					_starSize--; //��ʯ��������
					_star->setContentSize(Size(_starSize, _starSize)); //����ʯ��С�������С�����)
				}
				else if(_star->getBoundingBox().intersectsCircle(_football->getPosition(),BALLSIZE/2-15))//����ʯ�����˲����ҵ�������
				{
					SimpleAudioEngine::getInstance()->playEffect("BOOM2.mp3");
					 //�����������ٶ������ƶ���������ʯ����
					{
						_speedX = _football->getPositionX() - _star->getPositionX();
						_speedY = _football->getPositionY() - _star->getPositionY();
						_speedX /= 5;
						_speedY /= 5;

						MoveBy*  moveBy = MoveBy::create(1.0, Vec2(-_speedX*100, -_speedY*100));
						_star->runAction(moveBy);//�������ʯ������
						_moveFlag = false; //��������
					}
				}
				else //��Ȼ������ʯû��������û�ҵ����򣩣������ҵ�������
				{
					_moveFlag = false; //��������
					_GameState = -2;
				}

				_coolTime++; //������ʱ���߶�
			}
			else //��Ȼ��Һ͵��˿������ɻ
			{
				if (_hero->getDirection()) //���Ӣ�۴���ǰ��״̬
				{
					_hero->tankRun();
					if (_hero->isInfringeBorder(WID6, HEI6, -_hero->getContentSize().width / 2))
						_hero->tankBack();

					for (int i = 0;i < MAXE6;i++) //���Ӣ��ײ���˱��̹��
					{
						if (_hero->getBoundingBox().intersectsRect(_enemy[i]->getBoundingBox())) {
							_hero->tankBack();
							break;
						}
					}

					if (_hero->getBoundingBox().intersectsCircle(_football->getPosition(),BALLSIZE/2-12))
					{
						_hero->tankBack();
						moveByDir();
					}
				}//Ӣ�۵�����״̬���

				 //���ӵ���
				if (_hero->getFire())
				{
					if (_bullet)//����ӵ�������
					{
						_bullet->bulletRun();//���ӵ���
						bool removeFlag1 = false; //����һ���Ƿ�ɾ���ӵ��ı�ʶ
						if (_bullet->isInfringeBorder(WID6, HEI6, _bullet->getContentSize().height / 2)) //����ӵ���Խ�˱߽�
						{
							removeFlag1 = true;
							goto removeBullet1;
						}//����ӵ�Խ���ˣ��ӵ���ʧ

						/****������ǵ��ӵ�����������***/
						if (_bullet->getBoundingBox().intersectsRect(_football->getBoundingBox())) {
							_barValue -= 10;
							removeFlag1 = true;
							goto removeBullet1;
						}

						for (int i = 0;i < MAXE6;i++) //����ӵ�����˵���ײ
						{
							if (_bullet->getBoundingBox().intersectsRect(_enemy[i]->getBoundingBox()))//����ڵ������˵���
							{
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
				for (int i = 0;i < MAXE6;i++)
				{
					if (0 == _enemy[i]->getCool()) //����õ��˵Ľ���ʱ���Ѿ�������
					{
						{
							_enemy[i]->setSpeed(ENEMYSP6 + _taskCount*SPADD);
							_enemy[i]->tankRun();//�������������һ��
							if (_enemy[i]->isInfringeBorder(WID6, HEI6, -_enemy[i]->getContentSize().width / 2)) //����õ���Խ����
							{
								_enemy[i]->tankBack(); //��ô������
								if (3 > _enemy[i]->getDirection()) _enemy[i]->setDirection(_enemy[i]->getDirection() + 2);
								else _enemy[i]->setDirection((_enemy[i]->getDirection() + 2) % 4);

								_enemy[i]->setRotation((_enemy[i]->getDirection() - 1) * 90);
							}

							if (_enemy[i]->getBoundingBox().intersectsCircle(_football->getPosition(), BALLSIZE / 2))//�������ײ��������
							{
								_enemy[i]->tankBack(); //��������

								if (3 > _enemy[i]->getDirection()) _enemy[i]->setDirection(_enemy[i]->getDirection() + 2);//ԭ·����
								else _enemy[i]->setDirection((_enemy[i]->getDirection() + 2) % 4);

								_enemy[i]->setRotation((_enemy[i]->getDirection() - 1) * 90);
							}
								
													   //�ȼ������Ƿ�ײ��Ӣ��
							if (_enemy[i]->getBoundingBox().intersectsRect(_hero->getBoundingBox())) //����õ��������ǳ�ͻ��
							{
								_enemy[i]->tankBack();
								_enemy[i]->setDirection(_hero->getRotation()/90 + 1);//�õ��˵ķ����ø�����һ��
								_enemy[i]->setRotation(90.0f*(_enemy[i]->getDirection() - 1));
								break;
							}

							//���������Ƿ�ײ���Լ���
							for (int j = 0;j < MAXE6;j++)
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
				for (int i = 0;i < MAXE6;i++)
				{
					_enemyBullet[i]->bulletRun();

					if (_enemyBullet[i]->isInfringeBorder(WID6, HEI6, 0))//����ӵ�Խ����
					{
						_enemyBullet[i]->setPosition(_enemy[i]->getPosition());
						_enemyBullet[i]->setDirection((_enemy[i]->getDirection() - 1) * 90);
						continue;
					}

					if (_hero->getBoundingBox().intersectsRect(_enemyBullet[i]->getBoundingBox()))//������Ǳ��ӵ�����
					{
						_enemyBullet[i]->setPosition(_enemy[i]->getPosition());
						_enemyBullet[i]->setSpeed(0);
						_enemyBullet[i]->setVisible(false);
						_GameState = -1;
						continue;
					}

					if (_enemyBullet[i]->getBoundingBox().intersectsRect(_football->getBoundingBox()))//����õ����ӵ�����������
					{
						_enemyBullet[i]->setPosition(_enemy[i]->getPosition());
						_enemyBullet[i]->setDirection((_enemy[i]->getDirection() - 1) * 90);
						continue;
					}
				}
			}

		}
		break;
	case 1:
	{ //�������Ҫ���ϻ����ţ���Ȼ��ĳЩ�������У�����Ϊ�ֲ������������������뱨��
		//�ѹؿ�������Ϊ1����ʾ�ô�������ڶ�����
		{
			if (6 > UserDefault::getInstance()->getIntegerForKey("level"))
			{
				UserDefault::getInstance()->setIntegerForKey("level", 6);
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
		auto failText2 = Text::create(((CCString*)chnStrings->objectForKey("failLevel61"))->getCString(), "", 64);
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