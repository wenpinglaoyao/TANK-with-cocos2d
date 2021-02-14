#include "BOSS.h"
USING_NS_CC;

cocos2d::Scene* Level8::createScene()
{
	return Level8::create();
}

bool Level8::init()
{
	if (!Scene::init()) return false;

	_GameState = 0;//��Ϸ״̬�ǽ�����
	_BOSSHP = BOSSHP; //Ϊboss��������ֵ
	_BOSSPowerVal = 9700; //Ϊboss���ó�ʼ����ֵ
	_speedX = CCRANDOM_0_1() * 2 - 1;
	_speedY = CCRANDOM_0_1() * 2 - 1;

	/****��Ӻ��౦���Ľ��ܣ�ʤ��ʱ��***/
	{
		auto chnStrings = CCDictionary::createWithContentsOfFile("xixi.xml");
		_text = Text::create(((CCString*)chnStrings->objectForKey("bossStory"))->getCString(), "", 26);
		_text->setRotation(270);
		_text->setPosition(Vec2(900, 400));
		_text->setVisible(false);
		addChild(_text);
	}
	/****���ܺ��౦���Ĵ���ν���***/

	/****���һ��������****/
	{
		auto background = Sprite::create("BG.png");
		background->setContentSize(Size(400, 800));
		background->setPosition(WID8 + background->getContentSize().width / 2, background->getContentSize().height / 2);
		addChild(background, 100);
	}
	/****�������߼�����****/

	/****������������ĸ���ť*****/
	{
		Button* up = Button::create("up.png");//����һ������̹�����ϵİ�ť
		up->setRotation(45);
		up->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
			switch (type)
			{
			case Widget::TouchEventType::BEGAN: _hero->setDirection(1);if (!_isAttack)_hero->setRotation(0);break;
			case Widget::TouchEventType::MOVED:_hero->setDirection(1);if (!_isAttack)_hero->setRotation(0);break;
			case Widget::TouchEventType::ENDED:_hero->setDirection(0);break;
			case Widget::TouchEventType::CANCELED:_hero->setDirection(0);break;
			}
		});
		up->setPosition(Vec2(1200, 300));
		addChild(up, 101);

		Button* down = Button::create("up.png");//���µİ�ť
		down->setRotation(180 + 45);
		down->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
			switch (type)
			{
			case Widget::TouchEventType::BEGAN:_hero->setDirection(3);if (!_isAttack)_hero->setRotation(180);break;
			case Widget::TouchEventType::MOVED:_hero->setDirection(3);if (!_isAttack)_hero->setRotation(180);break;
			case Widget::TouchEventType::ENDED:_hero->setDirection(0);break;
			case Widget::TouchEventType::CANCELED:_hero->setDirection(0);break;
			}
		});
		down->setPosition(Vec2(1200, 100));
		addChild(down, 101);

		Button* left = Button::create("up.png");//����İ�ť
		left->setRotation(270 + 45);
		left->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
			switch (type) {
			case Widget::TouchEventType::BEGAN:_hero->setDirection(4);if (!_isAttack)_hero->setRotation(270);break;
			case Widget::TouchEventType::MOVED:_hero->setDirection(4);if (!_isAttack)_hero->setRotation(270);break;
			case Widget::TouchEventType::ENDED:_hero->setDirection(0);break;
			case Widget::TouchEventType::CANCELED:_hero->setDirection(0);break;
			}
		});
		left->setPosition(Vec2(1100, 200));
		addChild(left, 101);

		Button* right = Button::create("up.png");//���ҵİ�ť
		right->setRotation(90 + 45);
		right->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
			switch (type) {
			case Widget::TouchEventType::BEGAN:_hero->setDirection(2);if (!_isAttack)_hero->setRotation(90);break;
			case Widget::TouchEventType::MOVED:_hero->setDirection(2);if (!_isAttack)_hero->setRotation(90);break;
			case Widget::TouchEventType::ENDED:_hero->setDirection(0);break;
			case Widget::TouchEventType::CANCELED:_hero->setDirection(0);break;
			}
		});
		right->setPosition(Vec2(1300, 200));
		addChild(right, 101);
	}
	/****�������Ұ�ť����߼�����*****/

	/****�����ͣ��ˢ����������ť****/
	{
		Button* pause = Button::create("button.png"); //����һ����ͣ��ť
		pause->setTitleText("pause");
		pause->setTitleFontSize(32);
		pause->setRotation(90);
		pause->setScaleY(4.0);
		pause->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
			if (Widget::TouchEventType::BEGAN == type) _pause = !_pause;
		});
		pause->setPosition(Vec2(1150, 800 - pause->getContentSize().width / 2));
		addChild(pause, 102);

		//Button* refurbish = Button::create("button.png"); //����һ��ˢ�°�ť
		//refurbish->setTitleText("New");
		//refurbish->setTitleFontSize(32);
		//refurbish->setRotation(270);
		//refurbish->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type)
		//{
		//	if (Widget::TouchEventType::ENDED == type)
		//		Director::getInstance()->replaceScene(Level8::createScene());
		//});
		//refurbish->setPosition(Vec2(1050, 800 - refurbish->getContentSize().width / 2));
		//addChild(refurbish, 103);
	}
	/****��ͣ��ˢ������ť������߼�����****/

	SimpleAudioEngine::getInstance()->playBackgroundMusic("8.mp3");//���Źؿ���������

	/*****�������ӣ�Ҫ����fireǰ�棬��Ϊfire����Ҫ�õ���****/
	{
		_layer = Sprite::create("BG.png");
		_layer->setAnchorPoint(Vec2(0.5, 0));
		_layer->setVisible(false);
		addChild(_layer, 2);
	}
	/****������ӽ���****/
	
	/****�������****/
	{
		_hero = Hero::createWithSpriteName(HEROSPEED8, 10);
		_hero->setPosition(900, 400);
		_hero->setCool(HEROHP);//�������������һ���������ֵ
		addChild(_hero);
	}
	/****��������߼�����****/
	
	/****���һ������ť****/
	{
		Button* fire = Button::create("BOOM.png");
		fire->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
			switch (type)
			{
			case Widget::TouchEventType::BEGAN:
				_isAttack = true;
				break;
			case Widget::TouchEventType::MOVED:
				_isAttack = true;
				break;
			case Widget::TouchEventType::CANCELED:
				_isAttack = false;
				_layer->setVisible(false);
				break;
			case Widget::TouchEventType::ENDED:
				_isAttack = false;
				_layer->setVisible(false);
			}
		});
		fire->setPosition(Vec2(WIDTH - fire->getContentSize().width / 2, HEIGHT - fire->getContentSize().height / 2));
		addChild(fire, 103);
	}
	/****����ť�߼���ӽ���****/

	/****���boss�Լ���boss*****/
	{
		BOSS = Sprite::create("boss.jpg");
		BOSS->setPosition(0, 400);
		addChild(BOSS, 99);

		_falseBOSS = Sprite::create("boss.jpg");
		_falseBOSS->setPosition(-200, -200);//���������bossһ������ȥ(���Σ�
		addChild(_falseBOSS, 99);
	}
	/****boss�����ķ�������߼�����*****/

	///****������ܵĺ���***/
	{
		_sea[0] = Sprite::create("button.png");
		_sea[0]->setContentSize(Size(1400, BOSS->getContentSize().width / 2+5));
		_sea[0]->setPosition(WID8 / 2, HEI8 - _sea[0]->getContentSize().height / 2+27);
		this->addChild(_sea[0]);//���һ���ϱߵĺ���

		_sea[1] = Sprite::create("button.png");
		_sea[1]->setContentSize(_sea[0]->getContentSize());
		_sea[1]->setPosition(WID8 / 2, _sea[1]->getContentSize().height / 2 - 27);
		addChild(_sea[1]);//���һ���±ߵĺ���

		_sea[2] = Sprite::create("button.png");
		_sea[2]->setContentSize(Size(BOSS->getContentSize().width / 2+5,1400));
		_sea[2]->setPosition(_sea[2]->getContentSize().width / 2 - 27,HEI8/2);
		addChild(_sea[2]);

		_sea[3] = Sprite::create("button.png");
		_sea[3]->setContentSize(_sea[2]->getContentSize());
		_sea[3]->setPosition(WID8 - _sea[3]->getContentSize().width / 2 + 27, HEI8 / 2);
		addChild(_sea[3]);
	}
	///****��Ӻ����߼�����***/

	/****boss��Ѫ����������������*****/
	{
		_BOSSXueTiao = Sprite::create("HP.png");
		_BOSSXueTiao->setAnchorPoint(Vec2(0.5, 0));
		_BOSSXueTiao->setPosition(Vec2(1020, 400 - _BOSSXueTiao->getContentSize().height / 2));
		addChild(_BOSSXueTiao, 104);

		_BOSSPOWER = Sprite::create("button.png");
		_BOSSPOWER->setAnchorPoint(Vec2(0.5, 0));
		_BOSSPOWER->setContentSize(_BOSSXueTiao->getContentSize());//��������������Ѫ������С�ߴ�һ��
		_BOSSPOWER->setPosition(_BOSSXueTiao->getPosition());
		addChild(_BOSSPOWER, 105);
	}
	/****bossѪ���Լ�������ӵ��߼�����*****/

	/****���һ������Ž��Ļ�Ч��***/
	{
		_spark = Sprite::create("BOOM.png");
		_spark->setVisible(false);
		addChild(_spark, 106);
	}
	/****��Ч����ӵ��߼�����***/

	/*********/

	/*********/
	this->scheduleUpdate();

	return true;
}

void Level8::update(float delta)
{
	switch (_GameState)
	{
	case 0://��Ϸ������
	{
		if (!_pause)//�����Ϸû����ͣ
		{
			/****���û𻨵ĳߴ�����С****/
			_spark->setContentSize(Size(_spark->getContentSize().width - REDUCE, _spark->getContentSize().height - REDUCE));
			if (1 >= _spark->getContentSize().width)//����𻨵ĳߴ��㹻Ц��
				_spark->setVisible(false);//��ô�û�����
			/****���ڻ𻨵��߼�����****/

			if(!_isSkill)//�Ǵ�������£���boss�ļ������Σ�����boss�ڿ�ʼ�Ŵ���ʱ�����boss����������״̬�����Ǻ����ж�boss��ŵ��ˣ�
				_falseBOSS->setVisible(false);
		
			if(0 <=_BOSSHP) _BOSSXueTiao->setScaleY((_BOSSHP+14) / BOSSHP);//����boss����ֵѪ����
			_BOSSPOWER->setScaleY((_BOSSPowerVal+14) / BOSSHP);//����boss����������

			/****������ǵ�����ֵ�Ѿ�����û��*****/
			if (_hero->getCool() <= 0)
			{
				auto* rotateTo = RotateBy::create(0.2, 360*10);
				_hero->runAction(rotateTo);
				_hero->setCool(10);
				_GameState = -1;
			}
			/****�����������߼��������******/

			/*****�����ƶ����߼���ʼ****/
			if (_hero->getDirection())
			{
				_hero->tankRun();//�������ƶ�
				//�������������ǽ��
				if (_hero->isInfringeBorder(WID8, HEI8, -_hero->getContentSize().width / 2))
					_hero->tankBack();

				/****������ǽ��뺣���������˻�***/
				for (int i = 0;i < 4;i++)
				{
					if (_sea[i]->getBoundingBox().intersectsRect(_hero->getBoundingBox()))//����������������ܵĺ���
					{
						_hero->tankBack();//��ô�������˻�
						break;
					}
				}
				/*****������Ǻ����˻ص��߼�����****/
			}
			/*****�ƶ����߼�����*****/

			////������4�д��뿪��ȫ��������ʵ���ã�һ��Ҫɾ��
			//if (!_isSkill)
			//{
			//	_BOSSHP -= AGGRESSIVITY;
			//}

			/****���ǿ�����߼���ʼ****/
			if (_isAttack) //��������ǿ���״̬
			{
				switch ((int)_hero->getRotation())
				{
				case 0://������ļ���
					_layer->setContentSize(Size(LAYERWID, HEI8 - _hero->getPositionY()));
					_layer->setAnchorPoint(Vec2(0.5, 0));
					_layer->setPosition(_hero->getPosition());
					if (_layer->getBoundingBox().intersectsRect(BOSS->getBoundingBox()))//��������䵽��boss
					{
						_layer->setContentSize(Size(LAYERWID, BOSS->getPositionY() - _hero->getPositionY() - BOSS->getContentSize().width / 2));//�������ü��ⳤ��

						//������Ӧ�Ļ�
						_spark->setPosition(_hero->getPositionX(), BOSS->getPositionY() - BOSS->getContentSize().width / 2);
						_spark->setContentSize(Size(SPARKSIZE, SPARKSIZE));
						_spark->setVisible(true);

						if (!_isSkill)//���bossû���ڷŴ���״̬��
						{
							_BOSSHP -= AGGRESSIVITY;
							_falseBOSS->setVisible(true);//�ü���������״̬������boss�Ŵ���ʱ���Ϳ�����һ�������������ж���ŵ���
						}
					}
					_layer->setVisible(true);//�ü�������
					break;
				case 90://������ļ���
					_layer->setContentSize(Size(WID8 - _hero->getPositionX(), LAYERWID));
					_layer->setAnchorPoint(Vec2(0, 0.5));
					_layer->setPosition(_hero->getPosition());
					if (_layer->getBoundingBox().intersectsRect(BOSS->getBoundingBox()))//��������䵽��boss
					{
						_layer->setContentSize(Size(BOSS->getPositionX() - _hero->getPositionX()-BOSS->getContentSize().width/2, LAYERWID));//�������ü��ⳤ��

						//������Ӧ�Ļ�
						_spark->setPosition(BOSS->getPositionX() - BOSS->getContentSize().width / 2, _hero->getPositionY());
						_spark->setContentSize(Size(SPARKSIZE, SPARKSIZE));
						_spark->setVisible(true);

						if (!_isSkill)//���bossû���ڷŴ���״̬��
						{
							_BOSSHP -= AGGRESSIVITY;
							_falseBOSS->setVisible(true);//�ü���������״̬������boss�Ŵ���ʱ���Ϳ�����һ�������������ж���ŵ���
						}
					}
					_layer->setVisible(true);//�ü�������
					break;
				case 180://������ļ���
					_layer->setContentSize(Size(LAYERWID, _hero->getPositionY()));
					_layer->setAnchorPoint(Vec2(0.5, 1));
					_layer->setPosition(_hero->getPosition());
					if (_layer->getBoundingBox().intersectsRect(BOSS->getBoundingBox()))//��������䵽��boss
					{
						_layer->setContentSize(Size(LAYERWID, _hero->getPositionY() - BOSS->getPositionY() - BOSS->getContentSize().width/2));//�������ü��ⳤ��

						//������Ӧ�Ļ�
						_spark->setPosition(_hero->getPositionX(), BOSS->getPositionY() + BOSS->getContentSize().width / 2);
						_spark->setContentSize(Size(SPARKSIZE, SPARKSIZE));
						_spark->setVisible(true);

						if (!_isSkill)//���bossû���ڷŴ���״̬��
						{
							_BOSSHP -= AGGRESSIVITY;
							_falseBOSS->setVisible(true);//�ü���������״̬������boss�Ŵ���ʱ���Ϳ�����һ�������������ж���ŵ���
						}
					}

					_layer->setVisible(true);//�ü�������
					break;
				case 270://������ļ���
					_layer->setContentSize(Size(_hero->getPositionX(), LAYERWID));
					_layer->setAnchorPoint(Vec2(1, 0.5));
					_layer->setPosition(_hero->getPosition());
					if (_layer->getBoundingBox().intersectsRect(BOSS->getBoundingBox()))
					{
						_layer->setContentSize(Size(_hero->getPositionX() - BOSS->getPositionX()-BOSS->getContentSize().width/2, LAYERWID));//�������ü��ⳤ��

						//������Ӧ�Ļ�
						_spark->setPosition(BOSS->getPositionX() + BOSS->getContentSize().width / 2, _hero->getPositionY());
						_spark->setContentSize(Size(SPARKSIZE, SPARKSIZE));
						_spark->setVisible(true);

						if (!_isSkill)//���bossû���ڷŴ���״̬��
						{
							_BOSSHP -= AGGRESSIVITY;
							_falseBOSS->setVisible(true);//�ü���������״̬������boss�Ŵ���ʱ���Ϳ�����һ�������������ж���ŵ���
						}	
					}
					_layer->setVisible(true);//�ü�������
				}
			}
			/****������߼�����****/

			/***��������BOSS�߼���***/
			if (0 < _BOSSHP)//���BOSS����Ѫ�������
			{
				if (_hero->getBoundingBox().intersectsRect(BOSS->getBoundingBox()))//���boss����������
				{
					_hero->setCool(_hero->getCool() - NORMALHURT);//��ô����������
				}

				if (!_isSkill)//���boss�������ͷŴ��е�״̬
				{
					_BOSSPowerVal += POWERRESUME;//����boss����������

					/****�����boss�ƶ�λ���Լ��Ƿ����չ�***/
					{
						/***��Ϸ�깤ʱ���ǵð�������Щע�͵Ĵ���ָ�����Ϊ���Ǿ���boss����״̬�µ�λ�ƺ��չ�***/
						int randFlag = CCRANDOM_0_1() * 1200;
						
						/*****���bossû�����ͷż��ܣ���ô��bossλ��****/
						if ( 0 >= _stoneVector.size() && 0 >= _BOOMSmallVector.size() && _BOSSHP > 1000)
						{
							///****bossȫ���ƶ�*****/
							//{
							//	BOSS->stopAllActions();
							//	float posX, posY;
							//	posX = CCRANDOM_0_1() * WID8;
							//	posY = CCRANDOM_0_1() * HEI8;
							//	float timeSpeed = sqrt((BOSS->getPositionX() - posX) * (BOSS->getPositionX() - posX) +
							//		(BOSS->getPositionY() - posY) * (BOSS->getPositionY() - posY)) / 30;
							//	auto moveTo = MoveTo::create(timeSpeed, Vec2(posX, posY));
							//	BOSS->runAction(moveTo);
							//}
							///****bossȫ���ƶ��߼�����*****/
						
							/*****�ĺ�boss�����ƶ�****/
							{
								float posX = BOSS->getPositionX() + _speedX;
								float posY = BOSS->getPositionY() + _speedY;
								if (50 < posX && WID8 - 50 > posX && 50 < posY && HEI8 - 50 > posY
									|| 0>posX || WID8<posX || 0>posY || HEI8<posY)
								{
									_speedX = CCRANDOM_0_1() * 1 - 0.5;
									_speedY = CCRANDOM_0_1() * 1 - 0.5;
								}
								else  BOSS->setPosition(posX, posY);
							}
							/****�����ƶ��߼�����****/
						}
						/*****bossλ���߼�����*****/

						/****�����boss�����չ��ӵ�****/
						if ((_BOSSHP > 2000) >= randFlag &&
							_stoneVector.size()<=0 && _BOOMSmallVector.size()<= 0)//���boss����ֵ����2000�����ᷢ���չ��ӵ�
						{
							float subX = _hero->getPositionX() - BOSS->getPositionX();//��ȡboss�����ǵ�ˮƽ��
							float subY = _hero->getPositionY() - BOSS->getPositionY();//��ȡboss�����ǵĴ�ֱ��
							float distance = sqrt(subX*subX + subY*subY);//��ȡ������boss֮��ľ���
							Sprite* solder = Sprite::create("bullet.png");
							solder->setContentSize(Size(40, 40));
							solder->setPosition(BOSS->getPosition());
							float speedX = subX*SOLDERSPEED / distance;
							float speedY = subY*SOLDERSPEED / distance;
							solder->setPositionZ(speedX);
							solder->setRotation(speedY);
							this->addChild(solder,100);
							_solderVector.pushBack(solder);

						}
						/****boss�����ӵ����߼�����***/
					}
					/****boss������ƶ����չ��߼�����****/

					/*****��ˢ���չ�С�����߼�״̬****/
					for (unsigned int i = 0;i < _solderVector.size();i++)
					{
						Sprite* solder = _solderVector.at(i);

						if (solder->getBoundingBox().intersectsRect(_hero->getBoundingBox()))//����ӵ�С������������
						{
							_hero->setCool(_hero->getCool() - NORMALHURT);//��ô����������
						}

						/****��������ڹ���״̬���һ�����boss���չ�С������ôС��������Ůɢ��****/
						if (_isAttack && solder->getBoundingBox().intersectsRect(_layer->getBoundingBox()))
						{
							float startX, startY;
							startX = solder->getPositionX();
							startY = solder->getPositionY();
							for (unsigned int angle = 0;angle < 360;angle += ANGLEADD)
							{
								float endX, endY;
								endX = startX + 2000 * cosf(angle*M_PI / 180);
								endY = startY + 2000 * sinf(angle*M_PI / 180);

								Sprite* flower = Sprite::create("bullet.png");
								/***�����Ҫ������һ�а���Ůɢ�����ӵ��ߴ����***/
								flower->setPosition(solder->getPosition());//����Щ���ӵ��ĳ�ʼλ�ú��չ�С������ʱ��λ���غ�
								this->addChild(flower);
								MoveTo* moveTo = MoveTo::create(3.0f, Vec2(endX, endY));
								flower->runAction(moveTo);

								_flowerVector.pushBack(flower);
							}

							this->removeChild(solder, true);
							_solderVector.eraseObject(solder);
							continue;
						}
						/****С����Ůɢ�����߼�����****/

						/****����Ĵ������չ�С��λ��****/
						{
							//�����´������չ�С��λ��
							float speedX, speedY;
							speedX = solder->getPositionZ();
							speedY = solder->getRotation();
							solder->setPositionX(solder->getPositionX() + speedX);
							solder->setPositionY(solder->getPositionY() + speedY);

							if (solder->getPositionX() < 0 || WID8 < solder->getPositionX())//������ӵ����ں������ϳ�����Ļ�����
								solder->setPositionZ(-speedX); //��ô����һ������
							if (solder->getPositionY() < 0 || HEI8 < solder->getPositionY()) //������ӵ������������ϳ�����Ļ�ϻ���
								solder->setRotation(-speedY); //��ô����һ������
						}
						/****�չ�С��λ�Ƶ��߼�����****/
					}
					/******�չ�С�����߼�����*******/

					/******ˢ����Ůɢ���ӵ����߼�*******/
					for (unsigned int i = 0;i < _flowerVector.size();i++)
					{
						Sprite* flower = _flowerVector.at(i);

						if (flower->getBoundingBox().intersectsRect(_hero->getBoundingBox()))//�������Ůɢ���ӵ��������ص�
						{
							_hero->setCool(_hero->getCool() - NORMALHURT);//��ô����������
						}

						/****������ӵ��ɳ�����Ļ****/
						if (0 > flower->getPositionX() || WID8<flower->getPositionX() || 0>flower->getPositionY() || HEI8 < flower->getPositionY())
						{
							this->removeChild(flower, true);
							_flowerVector.eraseObject(flower);
							continue;
						}
						/****�ɳ���Ļ�Ļ��ӵ��߼�����****/

						/***������Ůɢ�����ӵ��Ƿ�ײ���˱��С���ӵ�***/
						for (unsigned int j = 0;j < _solderVector.size();j++)
						{
							auto solder = _solderVector.at(j);
							/****�����Ůɢ��������ӵ�ײ����ĳ���չ�С������ô�ڸ�λ�ñ�����Ů��****/
							if (flower->getBoundingBox().intersectsRect(solder->getBoundingBox()))
							{
								{
									float startX, startY;
									startX = solder->getPositionX();
									startY = solder->getPositionY();
									for (unsigned int angle = 0;angle < 360;angle += ANGLEADD)
									{
										float endX, endY;
										endX = startX + 2000 * cosf(angle*M_PI / 180);
										endY = startY + 2000 * sinf(angle*M_PI / 180);
										auto flo = Sprite::create("icebullet.png");
										
										/***�����Ҫ������һ�а���Ůɢ�����ӵ��ߴ����***/
										
										flo->setPosition(solder->getPosition());
										this->addChild(flo);
										MoveTo* moveTo = MoveTo::create(3.0, Vec2(endX, endY));
										flo->runAction(moveTo);

										_flowerVector.pushBack(flo);
									}
								}

								_flowerVector.eraseObject(flower);
								this->removeChild(flower, true);//���������ײ�Ļ��ӵ�
								_solderVector.eraseObject(solder);
								this->removeChild(solder, true);//�������ײ���չ��ӵ�
								break;
							}
							/****������Ů�����߼�����****/
						}
						/****��Ůɢ���ӵ�ײ������չ��ӵ����߼�����****/
					}
					/******��Ůɢ�����߼�״̬����****/

					/***������ɵ�״̬�߼���ʼ***/
					for (unsigned int i = 0;i < _stoneVector.size();i++)
					{
						auto stone = _stoneVector.at(i);
						if (stone->getBoundingBox().intersectsRect(_hero->getBoundingBox()))//���ĳ����ʯ��������ײ
						{
							_hero->setCool(_hero->getCool() - NORMALHURT);//��ô����������
						}

						/****����������ǵļ���ɨ����ĳ����ʯ****/
						if (_isAttack && _layer->getBoundingBox().intersectsRect(stone->getBoundingBox()))
						{
							stone->setColor(Color3B::RED);//�ñ������䵽����ʯ�����Ѫ��ɺ�ɫ
							stone->stopAllActions();//�ñ������䵽����ʯ��ͣ�ƶ�
							/****������䱬��ĸʯ����ô�ڸ�λ�ñ�����Ů��*****/
							if(0<stone->getPositionZ())
							{
								switch (int(_hero->getRotation()))//�ü����ס���˵���ĸʯ
								{
								case 0:case 180:
									stone->setPositionX(_hero->getPositionX());
									break;
								case 90:case 270:
									stone->setPositionY(_hero->getPositionY());
									break;
								}
								stone->setPositionZ(stone->getPositionZ() - REDSTONELETHSLITY);//��ĸʯ����
								if (0 >= stone->getPositionZ()) //���ʽΪĸ��ʯ�ñ���
								{
									float startX, startY;
									startX = stone->getPositionX();
									startY = stone->getPositionY();
									for (unsigned int angle = 0;angle < 360;angle += ANGLEADD)
									{
										float endX, endY;
										endX = startX + 2000 * cosf(angle*M_PI / 180);
										endY = startY + 2000 * sinf(angle*M_PI / 180);
										Sprite* flower = Sprite::create("bullet.png");
										flower->setPosition(stone->getPosition());
										addChild(flower);
										MoveTo* moveTo = MoveTo::create(3.0, Vec2(endX, endY));
										flower->runAction(moveTo);
										_flowerVector.pushBack(flower);
									}
									this->removeChild(stone, true);
									_stoneVector.eraseObject(stone);
								}
								continue;
							}
							/****ĸʯ������Ů���߼�����*****/

							this->removeChild(stone, true);
							_stoneVector.eraseObject(stone);
							continue;
						}
						
						if (WID8 < stone->getPositionX())//���������ɳ�����Ļ���ɳ�����Ļ���ұߣ�
						{
							_stoneVector.eraseObject(stone);
							this->removeChild(stone, true);
							continue;
						}

						/****��������ʯ����Ůɢ���Ļ��ӵ����У���ô����ʯ������Ůɢ��****/
						{
							for (unsigned int j = 0;j < _flowerVector.size();j++)
							{
								auto flower = _flowerVector.at(j);
								if (stone->getBoundingBox().intersectsRect(flower->getBoundingBox()))
								{
									float startX, startY;
									startX = stone->getPositionX();
									startY = stone->getPositionY();
									for (int angle = 0;angle < 360;angle += ANGLEADD/6)
									{
										float endX, endY;
										endX = startX + 2000 * cosf(angle*M_PI / 180);
										endY = startY + 2000 * sinf(angle*M_PI / 180);
										Sprite* flow = Sprite::create("icebullet.png");
										flow->setPosition(startX, startY);
										addChild(flow);
										MoveTo* moveTo = MoveTo::create(3.0, Vec2(endX, endY));
										flow->runAction(moveTo);
										_flowerVector.pushBack(flow);
									}

									this->removeChild(flower, true);
									_flowerVector.eraseObject(flower);//�������ײ����ʯ�ϵĻ��ӵ�
									this->removeChild(stone, true);
									_stoneVector.eraseObject(stone);//���������������������ӵ�ײ������ʯ
									break;
								}
							}
						}
						/****��ʯ������Ůɢ�����߼�����*****/
					}
					/***�������״̬���߼����½���***/
					
					/*****�����ըը���߼���ʼ****/
					for (unsigned int i = 0;i < _BOOMSmallVector.size();i++)//���¿����ըǰ����߼�״̬
					{
						auto boom = _BOOMSmallVector.at(i);
						//�����������ÿ����ըը���𽥱�С
						boom->setContentSize(Size(boom->getContentSize().width - BOOMSMALLSUB, boom->getContentSize().height - BOOMSMALLSUB));

						/****��������ըը������������****/
						if (BOOMSMALLMINSIZE > boom->getContentSize().width)//��������ըը����С���㹻��
						{
							boom->setVisible(true);//��ô��������
							if (_isAttack && _layer->getBoundingBox().intersectsRect(boom->getBoundingBox()))//����ڿ���״̬���Ҽ����䵽�����δ����ը��
							{
								this->removeChild(boom, true);//��ô���������δ����ը��
								_BOOMSmallVector.eraseObject(boom);
								break;
							}
						}
						/****�ÿ����ըը��¶�������߼�����*****/
						
						/*****��������ըը����С�Ŀ�û���ˣ������ϣ����ڸ�λ�ô���һ���������ըȦ****/
						if (1 > boom->getContentSize().width)
						{
							if ( !BOSS->getBoundingBox().intersectsRect(boom->getBoundingBox()))//���δ����ը��û������boss���ϣ������ϣ�
							{
								Sprite* BOOM = Sprite::create("BOOM.png");
								BOOM->setPosition(boom->getPosition());
								BOOM->setContentSize(Size(1, 1));
								this->addChild(BOOM);
								_BOOMVector.pushBack(BOOM); //���ϼ��д����Ǵ�����ըȦ
							}

							_BOOMSmallVector.eraseObject(boom);//�������д�����ɾ������������ըǰ��
							this->removeChild(boom, true);
						}
						/*****�������ըȦ�����߼����*****/
					}
					/***�����ըǰ����ǰ�����߼�״̬�������***/

					/*****�����ը��������߼�״̬���¿�ʼ****/
					for (unsigned int i = 0;i < _BOOMVector.size();i++)
					{
						auto BOOM = _BOOMVector.at(i);
						BOOM->setContentSize(Size(BOOM->getContentSize().width + BOOMRADIUSADD, BOOM->getContentSize().height + BOOMRADIUSADD));
					
						if (_hero->getBoundingBox().intersectsCircle(BOOM->getPosition(),BOOM->getContentSize().width/2))//��������ըը��������
						{
							_hero->setCool(_hero->getCool() - NORMALHURT);//��ô����������
						}

						/****�����������д����չ�С�������Ƿ���С�����ÿ����ըը����****/
						for (unsigned int j = 0;j < _solderVector.size();j++)
						{
							auto solder = _solderVector.at(j);
						}
						/*****�����չ�С���Ƿ�ը�����߼�����***/
						
						/*****������һ�δ������ó����˫˫��������Ϊ��ż�������������һ���������ŵ����****/
						for (unsigned int j = 0;j < _BOOMVector.size();j++)
						{
							auto BOOM2 = _BOOMVector.at(j);
							if (BOOM2 == BOOM) break;
							float changdu;
							float wid = BOOM->getPositionX() - BOOM2->getPositionX();
							float hei = BOOM->getPositionY() - BOOM2->getPositionY();
							changdu = sqrt(wid*wid+hei*hei);
							if(changdu<BOOM->getContentSize().width/2+BOOM2->getContentSize().width/2)//�������С������������İ뾶֮��
							{
								_BOOMVector.eraseObject(BOOM2);
								this->removeChild(BOOM2, true);
								_BOOMVector.eraseObject(BOOM);
								this->removeChild(BOOM, true);
								break;
							}
						}
						/****�����ԧ��ʽ�������߼�����****/

						///****�����������������������ײ����������߼���ʼ***/
						//for (unsigned int a = 0;a < _BOOMVector.size();a++)
						//{
						//	auto BOOM2 = _BOOMVector.at(a);
						//	if (BOOM2 == BOOM) break;
						//	float changdu;
						//	float wid = BOOM->getPositionX() - BOOM2->getPositionX();
						//	float hei = BOOM->getPositionY() - BOOM2->getPositionY();
						//	changdu = sqrt(wid*wid + hei*hei);
						//	if (changdu < BOOM->getContentSize().width / 2 + BOOM2->getContentSize().width / 2)
						//	{
						//		if (2 == _BOOMVector.size() && 0 == _BOOMSmallVector.size())//����������ʣ�����������
						//		{
						//			_BOOMVector.eraseObject(BOOM);
						//			this->removeChild(BOOM, true);
						//			_BOOMVector.eraseObject(BOOM2);
						//			this->removeChild(BOOM2, true);
						//			break;
						//		}
						//		else //��Ȼ���ǳ������ʣ�˺ü���������2������ô�����������
						//		{
						//			if (BOOM->getContentSize().width < BOOM2->getContentSize().width)//���boom2�������boom��
						//			{
						//				_BOOMVector.eraseObject(BOOM2); //boom2��
						//				this->removeChild(BOOM2, true);
						//				break;
						//			}
						//			else//��Ȼ����boom������Ƚϴ���ôboom��
						//			{
						//				_BOOMVector.eraseObject(BOOM);
						//				this->removeChild(BOOM, true);
						//				break;
						//			}
						//		}
						//	}
						//}
						///****����������������߼�����****/
					}
					/******�����ը������߼����½���*****/

					/*****���boss�Ƿ������ˣ��Ǿ��ͷż���****/
					if (_BOSSPowerVal >= _BOSSHP)//���������
					{
						_BOSSPowerVal = 0;//�Ȱ�boss����������
						/*****��������forѭ����Ϊ�˰��չ��ӵ�����Ůɢ�����****/
						for (int i = 0;i < _solderVector.size();i++) {
							auto solder = _solderVector.at(i);
							_solderVector.eraseObject(solder);
							this->removeChild(solder, true);
						}
						for (int i = 0;i > _flowerVector.size();i++)
						{
							auto flower = _flowerVector.at(i);
							_flowerVector.eraseObject(flower);
							this->removeChild(flower, true);
						}
						int flag;
						//if (_BOSSHP <= BOSSHP / 4)//���boss����ֵ̫����
						//	flag = 3; //��ôflagΪ3����ζ��bossһֱ�ͷ��ռ�����
						//else  //��Ȼboss����ͷż��ܰ�
							flag = CCRANDOM_0_1() * 4;
							if (1000 >= _BOSSHP) flag = 2;

						switch (flag)
						{
						case 0://�ͷ������꼼��
						{
							for (unsigned int i = 0;i < METEORSHOWERNUM;i++)
							{
								float startPosX, startPosY, endPosX, endPosY;
								startPosX = CCRANDOM_0_1()*WID8 - WID8;//�������д��������ʯ�ĳ�ʼλ��
								startPosY = CCRANDOM_0_1()*HEI8 * 3-HEI8;
								endPosX = CCRANDOM_0_1()*WID8 + WID8;//������ʯ��Ŀ��λ��
								endPosY = CCRANDOM_0_1()*HEI8 * 3-HEI8;
								Sprite* stone = Sprite::create("obstacle.png");
								stone->setPosition(startPosX, startPosY);
								int randFlag = CCRANDOM_0_1()*(METEORSHOWERNUM + STONERAND);
								if (1 >= randFlag)//�����д��뽫�����ʯ���ó�Σ����ʯ�����䱬���ɢ����Ůɢ����
								{
									stone->setPositionZ(1);
								}
								auto moveTo = MoveTo::create(5.0, Vec2(endPosX, endPosY));
								stone->runAction(moveTo);
								addChild(stone,99);
								_stoneVector.pushBack(stone);
							}
						}
							break;
						case 1://�ͷſ����ը����
						{
							for (unsigned int i = 0;i < BOOMNUM;i++)
							{
								float randSize = CCRANDOM_0_1() * (BOOMSMALLMAXSIZE-BOOMSMALLMINSIZE);//���������ըȦǰ�������ʱ��
								randSize += BOOMSMALLMINSIZE;//�����������룬������ըȦǰ����ܴ�С
								float posX = CCRANDOM_0_1()*WID8;//�������д�������ñ�ըȦǰ������λ��
								float posY = CCRANDOM_0_1()*HEI8;
								Sprite* boom = Sprite::create("zhadan.png");
								boom->setColor(Color3B::WHITE);
								boom->setContentSize(Size(randSize,randSize));
								boom->setPosition(posX, posY);
								boom->setVisible(false);
								addChild(boom,99);
								_BOOMSmallVector.pushBack(boom);
							}
						}
							break;
						case 3: //�ͷŻعⷵ�ռ���
						{
							_BOSSHP = int((HPRECOVER + _BOSSHP) / BOSSHP)*BOSSHP;
							if (_BOSSHP < BOSSHP - HPRECOVER)
								_BOSSHP += HPRECOVER;
							else _BOSSHP = BOSSHP;
							_BOSSPowerVal += POWERRECOVER;
						}
							break;
						case 2://�ͷ��ռ�����
						{
							BOSS->stopAllActions();
							/****boss�ͷŴ����ˣ�����������ܻ�����*****/
							{
								for (int i = 0;i < _solderVector.size();i++)
								{
									auto solder = _solderVector.at(i);
									this->removeChild(solder, true);
									_solderVector.eraseObject(solder);
								}
								for (int i = 0;i < _flowerVector.size();i++)
								{
									auto flower = _flowerVector.at(i);
									this->removeChild(flower, true);
									_flowerVector.eraseObject(flower);
								}
								for (int i = 0;i < _stoneVector.size();i++)
								{
									auto stone = _stoneVector.at(i);
									this->removeChild(stone, true);
									_stoneVector.eraseObject(stone);
								}
								for (int i = 0;i < _BOOMSmallVector.size();i++)
								{
									auto boom = _BOOMSmallVector.at(i);
									this->removeChild(boom, true);
									_BOOMSmallVector.eraseObject(boom);
								}
								for (int i = 0;i < _BOOMVector.size();i++)
								{
									auto BOOM = _BOOMVector.at(i);
									this->removeChild(BOOM, true);
									_BOOMVector.eraseObject(BOOM);
								}
							}
							/*****����������****/
							_speedX = CCRANDOM_0_1();
							_speedY = SKILLSTARTSPEED - _speedX;
							if (WID8 / 2 <= BOSS->getPositionX())//���boss����Ļ���Ұ��
								_speedX = -_speedX; //��ôboss�ռ����ܵĳ�ʼ���������ƶ�
							if (HEI8 / 2 <= BOSS->getPositionY())//���boss����Ļ������
								_speedY = -_speedY;//��ôboss�ռ����ܵĳ�ʼ���������ƶ�
							_skillFlagNum = 3; //����boss���ڵ��������������˴��н�����
							_isSkill = true; //����bossΪ������״̬
							
							_falseBOSS->setPosition(BOSS->getPosition());//��boss����ͣ����boss�����������Ի����
							BOSS->setOpacity(int(_BOSSHP / 1000)*11);
						}
							break;
						}
					}
					/****�������ͷż��ܵ��߼�����****/
				}
				else//boss���ͷ��ռ�����
				{
					BOSS->setPositionX(BOSS->getPositionX() + _speedX);
					BOSS->setPositionY(BOSS->getPositionY() + _speedY);

					/****���ھ��µķ����߼���ʼ****/
					{
						bool flagX = false;
						bool flagY = false;//������������boss��ͷ
						auto posX = BOSS->getPositionX();//�Ȼ�ȡ������Ļ��boss��X��λ��
						if (0 > posX)//���boss��������Ļ���
						{
							SimpleAudioEngine::getInstance()->playEffect("BOOM2.mp3");
							auto indexY = _speedY*posX / _speedX; //��ȡbossӦ���˻ص�Y����
							BOSS->setPosition(0, BOSS->getPositionY() - indexY); //��������boss��������Լ��˻���Ӧ��Y����
							flagX = true;
							--_skillFlagNum;
							if (0 >= _skillFlagNum)//������ڴ����ﵽ3��
							{
								_isSkill = false;//boss���ռ������ͷ����
								_falseBOSS->setPosition(-200, -200);
								BOSS->setOpacity(255);
							}
						/*	else
							{
								auto* rotateTo = RotateBy::create(0.1, 360 * 10);
								_hero->runAction(rotateTo);
							}*/
						}
						else if (WID8 < posX)//���boss��������Ļ�ұ�
						{
							SimpleAudioEngine::getInstance()->playEffect("BOOM2.mp3");
							auto indexY = _speedY*(posX - WID8) / _speedX;
							BOSS->setPosition(WID8, BOSS->getPositionY() - indexY);
							flagX = true;
							--_skillFlagNum;
							if (0 >= _skillFlagNum)//������ڴ����ﵽ3��
							{
								_isSkill = false;//boss���ռ������ͷ����
								_falseBOSS->setPosition(-200, -200);
								BOSS->setOpacity(255);
							}
							/*else
							{
								auto* rotateTo = RotateBy::create(0.1, 360 * 10);
								_hero->runAction(rotateTo);
							}*/
						}
						auto posY = BOSS->getPositionY();
						if (0 > posY)//���boss��������Ļ����
						{
							SimpleAudioEngine::getInstance()->playEffect("BOOM2.mp3");
							auto indexX = _speedX*posY / _speedY;
							BOSS->setPosition(BOSS->getPositionX() - indexX, 0);
							flagY = true;
							--_skillFlagNum;
							if (0 >= _skillFlagNum)//������ڴ����ﵽ3��
							{
								_isSkill = false;//boss���ռ������ͷ����
								_falseBOSS->setPosition(-200, -200);
								BOSS->setOpacity(255);
							}
							/*else
							{
								auto* rotateTo = RotateBy::create(0.1, 360 * 10);
								_hero->runAction(rotateTo);
							}*/
						}
						else if (HEI8 < posY)//���boss��������Ļ����
						{
							SimpleAudioEngine::getInstance()->playEffect("BOOM2.mp3");
							auto indexX = _speedX*(posY - HEI8) / _speedY;
							BOSS->setPosition(BOSS->getPositionX() - indexX, HEI8);
							flagY = true;
							--_skillFlagNum;
							if (0 >= _skillFlagNum)//������ڴ����ﵽ3��
							{
								_isSkill = false;//boss���ռ������ͷ����
								_falseBOSS->setPosition(-200, -200);
								BOSS->setOpacity(255);
							}
						/*	else
							{
								auto* rotateTo = RotateBy::create(0.1, 360 * 10);
								_hero->runAction(rotateTo);
							}*/
						}
						if (flagX) _speedX = -_speedX;
						if (flagY) _speedY = -_speedY;
					}
					/****���ھ��µķ����߼�����****/
					
					_speedX *= SPEEDADD;
					_speedY *= SPEEDADD;
				}
				/****boss�ͷ��ռ����ܵĴ���ν���****/
			}
			else /****boss����������ʼ�Ա�****/
			{
				if (0 >= _deadBOOM.size())//�����û���Ա�������
				{
					for (int i = 0;i < 50;i++)
					{
						Sprite* deadBOOM = Sprite::create("BOOM.png");
						deadBOOM->setPosition(BOSS->getPositionX() + BOSS->getContentSize().width*CCRANDOM_0_1() - BOSS->getContentSize().width / 2,
							BOSS->getPositionY() + BOSS->getContentSize().width*CCRANDOM_0_1() - BOSS->getContentSize().width / 2);
						deadBOOM->setContentSize(Size(1, 1));
						DelayTime* delayTime = DelayTime::create(CCRANDOM_0_1()*5.0F);
						auto scaleTo = ScaleTo::create(0.4, 50);
						Sequence* sequence = Sequence::create(delayTime, scaleTo, NULL);
						deadBOOM->runAction(sequence);
						this->addChild(deadBOOM, 108);
						_deadBOOM.pushBack(deadBOOM);
					}
				}
				else if (1 <= _deadBOOM.size() && 9 >= _deadBOOM.size()) //�Ա�������������ʣ���仨�����Բ����Ա��ˣ���boss��·����Ϸ�������ʤ����
				{
					for (int i = 0;i < _deadBOOM.size();i++)
						_deadBOOM.at(i)->setVisible(false);
					for (int i = 0;i < 4;i++)
						_sea[i]->setVisible(false);
					BOSS->setVisible(false);
					_hero->setVisible(false);

					_text->setVisible(true);
					_text->setPositionX(_hero->getPositionX());
				}
				else for (unsigned int i = 0;i < _deadBOOM.size();i++) //ѭ���Ա������������������ɱ����Ļ�
					{
						auto deadBOOM = _deadBOOM.at(i);
						if (50 <= deadBOOM->getScaleX())
						{
							this->removeChild(deadBOOM, true);
							_deadBOOM.eraseObject(deadBOOM);
						}
					}
			}
			/****boss�Ա��Ĵ���ν���*****/
			/****boss�����Ա��������߼��������****/
				;
		}
		else//��Ȼ��������ͣʱ����Ϊ������Ȼ��ܻ������Ҫ�����Ƿ�ײ��������
		{
			for (int i = 0;i < _flowerVector.size();i++) {
				auto flower = _flowerVector.at(i);
				if (_hero->getBoundingBox().intersectsRect(flower->getBoundingBox())) {
					_GameState = -1;
				}
			}

			for (int i = 0;i < _stoneVector.size();i++) {
				auto stone = _stoneVector.at(i);
				if (_hero->getBoundingBox().intersectsRect(stone->getBoundingBox())) {
					_GameState = -1;
				}
			}
		}
		

	}
		break;
	case 1://��Ϸ�������ʤ��
	{
	}
		break;
	case -1:
	{//����һ����ť�����Է��ص��ÿ�ʼ��Ϸ
		auto next = Button::create("button.png");
		next->setTitleText("NEW");
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
	case -2:
		break;
	case -3:
		break;

	}
}