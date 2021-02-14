#include "Level3.h"
USING_NS_CC;

cocos2d::Scene* Level3::createScene()
{
	return Level3::create();
}

bool Level3::init()
{
	{
		if (!Scene::init()) return false;

		auto background = Sprite::create("BG.png");//�������һ����ɫ����ͼƬ
		background->setContentSize(Size(600, 800));
		background->setPosition(WID + background->getContentSize().width / 2, background->getContentSize().height / 2);
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
				Director::getInstance()->replaceScene(Level3::createScene());
			}
		});
		refurbish->setPosition(Vec2(1050, 800 - refurbish->getContentSize().width / 2));
		addChild(refurbish);



		SimpleAudioEngine::getInstance()->playBackgroundMusic("3.mp3");//���ű�������

		_hero = Hero::createWithSpriteName(4.99f, 0);//��ʼ������
		_hero->setPosition(500, 400);
		addChild(_hero);
		_bullet = Bullet::createWithSpriteName(16, _hero->getRotation(), "bullet.png");
		_bullet->setPosition(-100,-100);
		addChild(_bullet);

		Button* fire = Button::create("BOOM.png");//��ʼ�����䰴ť
		fire->ignoreContentAdaptWithSize(false);
		fire->setContentSize(Size(250, 250));
		fire->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
			if (Widget::TouchEventType::BEGAN == type)
			{
				if (!_hero->getFire()) {
					_bullet->setPosition(_hero->getPosition());
					_bullet->setSpeed(16);
					_bullet->setDirection(_hero->getRotation());
					_hero->setFire(true);

					//�����ĸ����������
					for (int direction = 0;direction <= 270;direction += 90)
					{
						auto sound = Bullet::createWithSpriteName(SOUND_SPEED, direction, "sound.png");
						sound->setRotation(direction);
						sound->setPosition(_hero->getPositionX(),_hero->getPositionY());
						_soundVector.pushBack(sound);
						addChild(sound, 100);
					}//��������
				}
			}
		});
		fire->setPosition(Vec2(WIDTH - fire->getContentSize().width / 2, HEIGHT - fire->getContentSize().height / 2));
		addChild(fire);
		_pause = false;
		this->scheduleUpdate();
	}
	//�����ʼ������
	{
	for (int i = 0;i < MAXENEMY3;i++)
	{
		_enemy[i] = Tank::createWithSpriteName(ENEMYSPEED, int(CCRANDOM_0_1() * 4 + 1), 0, "snowmonster.png");
		_enemy[i]->setRotation(90.0f * (_enemy[i]->getDirection() - 1));
		_enemy[i]->setPosition(100 + i * 51, 100 + i * 51);
		_enemy[i]->setFire(false);
		addChild(_enemy[i],98);
	}
	for (int i = 0;i < MAXENEMY3;i++)
	{
		_enemy[i]->setDirection(4);
		_enemy[i]->setRotation(90.0f * (_enemy[i]->getDirection() - 1));
		_enemy[i]->setPosition(300 + (i+1) * 59,100);
		_enemy[i]->setFire(false);
	}
	}//���˳�ʼ������

	//���м����һ����ʯ��
	_stone = Sprite::create("obstacle.png");
	_stone->setContentSize(Size(STONESIZE, STONESIZE));
	_stone->setPosition(WID / 2, HEI / 2);
	addChild(_stone, 99);
	return true;
}

void Level3::update(float delta)
{
	switch (_GameState)
	{
	case 0:
		if (_taskCount >= TASKNUM && _snowVector.size()<=0 && _soundVector.size()<=0)
		{
			_GameState = 1;
		}
		if (!_pause)//�����û�н�����ͣ״̬
		{
			if (_hero->getDirection()) //���Ӣ�۴���ǰ��״̬
			{
				_hero->tankRun();
				if (_hero->isInfringeBorder(WID, HEI, -_hero->getContentSize().width / 2))
					_hero->tankBack();
				if (tankColl(_hero, _stone))
					_hero->tankBack();

				for (int i = 0;i < MAXENEMY3;i++) //���Ӣ��ײ���˱��̹��
				{
					if (_hero->getBoundingBox().intersectsRect(_enemy[i]->getBoundingBox())) 
					{
						if (_enemy[i]->getCool())
						{
							_GameState = -2;
						}
						if (backDetection(_enemy[i], _hero->getDirection(), _hero->getSpeed()))
						{
							_hero->tankBack();
						}
					}
				}
			}//Ӣ�۵�����״̬���

			 //���ӵ���
			if (_hero->getFire())
			{
				_bullet->bulletRun();

				if (_bullet->isInfringeBorder(WID, HEI, _bullet->getContentSize().height / 2))
				{
					_bullet->setPosition(1000,1000);
					_hero->setFire(false);
				}

				for (int i = 0;i < MAXENEMY3;i++)
				{
					if (tankColl(_bullet, _enemy[i]))//����ӵ�������ѩ��
					{
						SimpleAudioEngine::getInstance()->playEffect("BOOM1.mp3");
						_bullet->setPosition(1000, 1000);
						_bullet->setSpeed(0.0f);
						_hero->setFire(false);
						++_taskCount;
						//�����ĸ����������
						for (int direction = 0;direction <= 270;direction += 90)
						{
							auto sound = Bullet::createWithSpriteName(SOUND_SPEED, direction, "sound.png");
							sound->setRotation(direction);
							sound->setPosition(_enemy[i]->getPositionX(), _enemy[i]->getPositionY());
							_soundVector.pushBack(sound);
							addChild(sound, 100);
						}//��������

						_enemy[i]->setPosition(-100-i*60, -100-i*60);
						_enemy[i]->setDirection(0);
					}
				}
			}//Ӣ�۵��ӵ��������

			 //�ֵ������ж���
			for (int i = MAXENEMY3-1;i >= 0;i--)
			{
				if (_enemy[i]->getCool())
				{
					if (_enemy[i]->getCool() == 1)
					{
						_enemy[i]->setTexture("snowmonster.png");
						_enemy[i]->setSpeed(ENEMYSPEED);
					}
					_enemy[i]->setCool(_enemy[i]->getCool() - 1);
				}
				{
					if (CCRANDOM_0_1() < 1.0f / 970.0f) //�ı�����Ǹ��������ı�ת�����
					{
						_enemy[i]->setDirection(_enemy[i]->getDirection()%4+1);
						_enemy[i]->setRotation(90.0f*(_enemy[i]->getDirection() - 1));
					}//���������˸ı䷽���ˣ��Ǿ����ˣ�����Ͳ�������
					else
					{
						_enemy[i]->tankRun();//�������������һ��
						if (_enemy[i]->isInfringeBorder(WID, HEI, -25)) //����õ���Խ����
						{
							_enemy[i]->tankBack(); //��ô������
							_enemy[i]->setDirection(_enemy[i]->getDirection() % 4 + 1);
							_enemy[i]->setRotation(90.0f*(_enemy[i]->getDirection() - 1));
							goto endDetectionColl;
						}

						//�ȼ������Ƿ�ײ��Ӣ��
						if (_enemy[i]->getBoundingBox().intersectsRect(_hero->getBoundingBox())) //����õ��������ǳ�ͻ��
						{
							_enemy[i]->tankBack();
							_enemy[i]->setDirection(_enemy[i]->getDirection() % 4 + 1);
							_enemy[i]->setRotation(90.0f*(_enemy[i]->getDirection() - 1));
							if (_enemy[i]->getCool())//���Ǳ�����ѩ��ײ��
							{
								_GameState = -2;
							}
							goto endDetectionColl;
							break;
						}

						//�������Ƿ�ײ��ʯͷ
						if (_enemy[i]->getBoundingBox().intersectsRect(_stone->getBoundingBox()))
						{
							_enemy[i]->tankBack();
							_enemy[i]->setDirection(_enemy[i]->getDirection() % 4 + 1);
							_enemy[i]->setRotation(90.0f*(_enemy[i]->getDirection() - 1));
							goto endDetectionColl;
						}

						//���������Ƿ�ײ���Լ���
						for (int j = 0;j < MAXENEMY3;j++)
						{
							if (j != i &&/* _enemy[i]->getBoundingBox().intersectsRect(_enemy[j]->getBoundingBox())*/
								tankColl(_enemy[i],_enemy[j]))
							{
								_enemy[i]->tankBack();
								_enemy[i]->setDirection(_enemy[i]->getDirection() % 4 + 1);
								_enemy[i]->setRotation(90.0f*(_enemy[i]->getDirection() - 1));
								if (_enemy[i]->getCool() + _enemy[i]->getCool() > 0)
								{
									if (!_enemy[i]->getCool())
									{
										_enemy[i]->setTexture("dreadmonster.png");
										_enemy[i]->setCool(COOLTIME);
										_enemy[i]->setRotation((_enemy[i]->getDirection() - 1) * 90);
										_enemy[i]->setSpeed(ENEMYSPEED * 8);
									}
									else
									{
										_enemy[j]->setTexture("dreadmonster.png");
										_enemy[j]->setCool(COOLTIME);
										_enemy[j]->setRotation((_enemy[i]->getDirection() - 1) * 90);
										_enemy[j]->setSpeed(ENEMYSPEED * 8);
									}
								}
								break;
							}
						}
						//��������ѩ���Ƿ񿴵�����
						if (!_enemy[i]->getCool() && isShoot(_enemy[i]))
						{
							{
								_enemy[i]->setTexture("dreadmonster.png");
								_enemy[i]->setCool(COOLTIME);
								//�������д����Ǹı�ѩ�ֵķ�������������������
								if (3 > _enemy[i]->getDirection()) _enemy[i]->setDirection(_enemy[i]->getDirection() + 2);
								else _enemy[i]->setDirection((_enemy[i]->getDirection() + 2) % 4);

								_enemy[i]->setRotation((_enemy[i]->getDirection() - 1) * 90);
								_enemy[i]->setSpeed(ENEMYSPEED * 8);
								//�����ĸ����������
								for (int direction = 0;direction <= 270;direction += 90)
								{
									auto sound = Bullet::createWithSpriteName(SOUND_SPEED, direction, "sound.png");
									sound->setRotation(direction);
									sound->setPosition(_enemy[i]->getPositionX(), _enemy[i]->getPositionY());
									_soundVector.pushBack(sound);
									addChild(sound, 100);
								}//��������
							}
						}
					endDetectionColl:;
					}
				}
			}

			//����������һ����
			for (int si = 0;si < _soundVector.size();si++)
			{
				auto sound = _soundVector.at(si);
				sound->bulletRun();
				if (sound->getPositionX() > HEI || sound->getPositionX() < 0
					|| sound->getPositionY() > WID || sound->getPositionY() < 0)
				{
					createSnowLine(sound->getDirection());
					removeChild(sound, true);
					_soundVector.eraseObject(sound);
				}
			}//�����������

			//ѩ���ļ��
			for (int i = 0;i < _snowVector.size();i++)
			{
				auto snow = _snowVector.at(i);
				snow->bulletRun();

				_stone->setContentSize(Size(20, 20));//���þ�ʯ��С
				if (tankColl(snow, _stone))
					goto removeSnow;
				_stone->setContentSize(Size(STONESIZE, STONESIZE));//���þ�ʯ���

				_hero->setContentSize(Size(16, 16));//�����Ǳ�С
				if (tankColl(_hero, snow)) //������Ǳ�ѩ������
				{
					_GameState = -1;
					goto removeSnow;
				}
				_hero->setContentSize(Size(50, 50));//�����Ǳ��

				if (snow->getPositionX() > HEI +50|| snow->getPositionX() < -50
					|| snow->getPositionY() > WID+50 || snow->getPositionY() < -50)
					goto removeSnow;
				continue;
			removeSnow:
				removeChild(snow);
				_snowVector.eraseObject(snow);
			}
		}//�Ƿ����״̬�߼����
		break;
	case 1:
	{ //�������Ҫ���ϻ����ţ���Ȼ��ĳЩ�������У�����Ϊ�ֲ������������������뱨��
		//�ѹؿ�������Ϊ4����ʾ�ô��������4����
		{
			if (3 > UserDefault::getInstance()->getIntegerForKey("level"))
			{
				UserDefault::getInstance()->setIntegerForKey("level", 3);
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
				Director::getInstance()->replaceScene(HelloWorld::createLevelGame());
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
		auto failText = Text::create(((CCString*)chnStrings->objectForKey("failLevel32"))->getCString(), "", 64);
		failText->setRotation(270);
		failText->setPosition(Vec2(400, 400));
		addChild(failText,199);
		_snowVector.clear();
		_soundVector.clear();
		_GameState = 2;//����Ƿ�ֹһֱֹͣ���ű������֣����һֱֹͣ�Ļ����ٴ����¼��ز���BGM�Ļ����ᾲ����
	}
	break;
	case -2:
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		auto chnStrings = CCDictionary::createWithContentsOfFile("xixi.xml");
		auto failText2 = Text::create(((CCString*)chnStrings->objectForKey("failLevel31"))->getCString(), "", 64);
		failText2->setRotation(270);
		failText2->setPosition(Vec2(400, 400));
		addChild(failText2,199);
		_snowVector.clear();
		_soundVector.clear();
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

/****���������һ���ݹ麯��������ʵ�������������Ĺ��ܣ�������
�������ŵ��ˡ��ϰ���һ��ǰ����������cocos������û���������ӣ�
�����������ǵ��Լ���һ��****/
bool Level3::backDetection(Tank* tank, int direction, float speed)
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
	tank->setSpeed(0);

	if (this->isInfringeBorder(tank,direction,-tank->getContentSize().width / 2))//������̹����λ��Խ����
	{ 
		backTank(tank, direction, speed);
		tank->setSpeed(ENEMYSPEED);
		return true;
	}
	if (tankColl(tank,_stone))//������̹��ײ����ʯ��
	{
		backTank(tank, direction, speed);
		tank->setSpeed(ENEMYSPEED);
		return true;
	}
		

	for (int i = 0;i < MAXENEMY3;i++)
	{
		if (_enemy[i]->getSpeed() && tankColl(_enemy[i],tank))//�����̹���ص��˱��̹��
		{
			if (backDetection(_enemy[i], direction, speed)==true)
			{
				backTank(tank, direction, speed);
				tank->setSpeed(ENEMYSPEED);
				return true;
			}
		}
	}
	tank->setSpeed(ENEMYSPEED);
	return false;
}

bool Level3::isInfringeBorder(Tank* tank, int direction,int limit)
{
	switch (direction)
	{
	case 1:
		if (tank->getPositionY() >= HEI + limit)
			return true;
	case 3:
		if (tank->getPositionY() <= -limit)
			return true;
		break;
	case 2:
		if (tank->getPositionX() >= WID + limit)
			return true;
		break;
	case 4:
		if (tank->getPositionX() <= -limit)
			return true;
		break;
	}
	return false;
}
void Level3::backTank(Tank* tank, int direction, float speed)
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

bool Level3::tankColl(Sprite* t1, Sprite* t2)//��һ��Ҫ�Լ�д����ײ��⺯������Ȼ��bug
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

bool Level3::isShoot(Tank* tank)//�Ƿ�÷���
{
	float offsetX = _hero->getPositionX() - tank->getPositionX();
	float offsetY = _hero->getPositionY() - tank->getPositionY();
	switch (tank->getDirection())
	{
	case 1:
		if (offsetX<=50 && offsetX>=-50 && _hero->getPositionY() > tank->getPositionY())
			return true;
		break;
	case 3:
		if (offsetX <= 50 && offsetX >= -50 &&_hero->getPositionY() < tank->getPositionY())
			return true;
		break;
	case 4:
		if (offsetY <= 50 && offsetY >= -50 &&_hero->getPositionX() < tank->getPositionX())
			return true;
		break;
	case 2:
		if (offsetY <= 50 && offsetY >= -50 &&_hero->getPositionX() > tank->getPositionX())
			return true;
		break;
	}
	return false;
}

void Level3::createSnowLine(int direction)
{
	switch (direction)
	{
	case 0:
		for (int i = 0;i < WID;i += SNOWDISTANCE)
		{
			auto snow = Bullet::createWithSpriteName(SNOW_SPEED, 180, "snow.png");
			snow->setRotation(180);
			snow->setPosition(i, HEI + 25);
			_snowVector.pushBack(snow);
			addChild(snow);
		}
		break;
	case 90:
		for (int i = 0;i < HEI;i += SNOWDISTANCE)
		{
			auto snow = Bullet::createWithSpriteName(SNOW_SPEED, 270, "snow.png");
			snow->setRotation(270);
			snow->setPosition(WID+25,i);
			_snowVector.pushBack(snow);
			addChild(snow);
		}
		break;
	case 180:
		for (int i = 0;i < WID;i += SNOWDISTANCE)
		{
			auto snow = Bullet::createWithSpriteName(SNOW_SPEED, 0, "snow.png");
			snow->setRotation(0);
			snow->setPosition(i, -25);
			_snowVector.pushBack(snow);
			addChild(snow);
		}
		break;
	case 270:
		for (int i = 0;i < WID;i += SNOWDISTANCE)
		{
			auto snow = Bullet::createWithSpriteName(SNOW_SPEED, 90, "snow.png");
			snow->setRotation(90);
			snow->setPosition(-25,i);
			_snowVector.pushBack(snow);
			addChild(snow);
		}
		break;
	}
}