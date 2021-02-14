#include "Level2.h"
USING_NS_CC;
#define WID 1000 //��Ļ�Ŀ��
#define HEI 800 //��Ļ�ĸ߶�
#define ENEMYBUSP 6 //�����ӵ����ٶ�
#define ENEMYALL 30; //��Ҫ������ܵ�������
#define BOOMLIVE 15 //��ը���ŵ����ʱ��
#define ADD 1.50f    //ÿ��һ�����˺󣬱�ը���ŵ��ٶ�������
#define TASKNUM 30 //��һ��Ҫ������˵�������
#define STOPTIME 2.0f //���������ѵľ�ֹʱ��


cocos2d::Scene* Level2::createScene()
{
	return Level2::create();
}
bool Level2::init()
{
	_taskCount = 0;
	_GameState = 0;
	_addCircle = 35.0f;
	{
		if (!Scene::init()) return false;

		auto background = Sprite::create("BG.png");//�������һ����ɫ����ͼƬ
		background->setContentSize(Size(400, 800));
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
				Director::getInstance()->replaceScene(Level2::createScene());
			}
		});
		refurbish->setPosition(Vec2(1050, 800 - refurbish->getContentSize().width / 2));
		addChild(refurbish);



		SimpleAudioEngine::getInstance()->playBackgroundMusic("2.mp3");//���ű�������

		_hero = Hero::createWithSpriteName(4.99f, 0);//��ʼ������
		_hero->setPosition(500, 400);
		_hero->setPositionX(_hero->getPositionX());//���������ǵ�λ�ø������������ͬ��
		_hero->setPositionY(_hero->getPositionY());
		addChild(_hero);

		_pause = false;
		this->scheduleUpdate();
	}
	/**********������Щ��ģ�廯����*******************/


	Button* fire = Button::create("BOOM.png");//��ʼ�����䰴ť
	fire->ignoreContentAdaptWithSize(false);
	fire->setContentSize(Size(250, 250));	
	fire->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
		if (Widget::TouchEventType::BEGAN == type) 
		{
			if (!_hero->getFire()) {
				_bullet = Bullet::createWithSpriteName(16, _hero->getRotation(), "bullet.png");
				_bullet->setPosition(_hero->getPosition());
				addChild(_bullet);

				_hero->setFire(true);
			}
		}
	});
	fire->setPosition(Vec2(WIDTH - fire->getContentSize().width / 2, HEIGHT - fire->getContentSize().height / 2));
	addChild(fire);

	  //�����ʼ������
	{
		for (int i = 0;i < MAX_ENEMY;i++)
		{
			_enemy[i] = Tank::createWithSpriteName(1.01f, int(CCRANDOM_0_1() * 4 + 1), 30, "enemy2.PNG");
			_enemy[i]->setRotation(90.0f * (_enemy[i]->getDirection() - 1));
			_enemy[i]->setPosition(100 + i * 51, 100 + i * 51);
			_enemy[i]->setPositionX(_enemy[i]->getPositionX());
			_enemy[i]->setPositionY(_enemy[i]->getPositionY());
			_enemy[i]->setFire(false);
			addChild(_enemy[i]);
		}
	}//���˳�ʼ������
	 //�����ӵ���ʼ��
	for (int i = 0;i <  MAX_ENEMY;i++)
	{
		_enemyBullet[i] = Bullet::createWithSpriteName(0.0f, int(CCRANDOM_0_1() * 4 + 1), "bullet.png");
		_enemyBullet[i]->setPosition(_enemy[i]->getPosition());
		_enemyBullet[i]->setVisible(true);
		addChild(_enemyBullet[i]);
	}
	//�Ѿ���ʼ��
	for (int i = 0;i < MAX_PARTNER;i++)
	{
		_partner[i] = Tank::createWithSpriteName(0.5f, int(CCRANDOM_0_1() * 4 + 1), 30, "partner.png");
	/*	_partner[i]->setRotation(90.0f * (_partner[i]->getDirection() - 1));*/
		_partner[i]->setPosition(100 + i * 51, 100 + i * 51);
		_partner[i]->setPositionX(_partner[i]->getPositionX());
		_partner[i]->setPositionY(_partner[i]->getPositionY());
		_partner[i]->setFire(true);
		addChild(_partner[i]);
	}

	return true;
}

void Level2::update(float delta)
{
	switch (_GameState)
	{
	case 0:
		if (!_pause)//�����û�н�����ͣ״̬
		{
			for ( int i = 0;i < MAX_PARTNER;i++)//��������ѵ�״̬
			{
				if (_partner[i]->getFire()) //����ö��ѵ�һ������ִ�����
				{
					_partner[i]->setFire(false);
					int x = (int)(CCRANDOM_0_1() * WID);
					int y = (int)(CCRANDOM_0_1() * HEI);
					float line = sqrt((x - _partner[i]->getPositionX())*(x - _partner[i]->getPositionX()) +
						(y - _partner[i]->getPositionY())*(y - _partner[i]->getPositionY()));
					MoveTo* moveTo = MoveTo::create(line/50.0f, Vec2(x, y));
					DelayTime* stopTime = DelayTime::create(STOPTIME);
					CallFunc* callFunc;
					switch (i) {
					case 0:
						callFunc = CallFunc::create([&] {
							_partner[0]->setFire(true);
						});
						break;
					case 1:
						callFunc = CallFunc::create([&] {
							_partner[1]->setFire(true);
						});
						break;
					case 2:
						callFunc = CallFunc::create([&] {
							_partner[2]->setFire(true);
						});
						break;
					}

					Sequence* sequence = Sequence::create( moveTo, stopTime, callFunc,NULL);
					_partner[i]->runAction(sequence);
				}
			}
			if (_hero->getDirection()) //���Ӣ�۴���ǰ��״̬
			{
				_hero->tankRun();
				if (_hero->isInfringeBorder(WID, HEI, -_hero->getContentSize().width / 2))
					_hero->tankBack();

				for (int i = 0;i < MAX_ENEMY;i++) //���Ӣ��ײ���˱��̹��
				{
					if (_hero->getBoundingBox().intersectsRect(_enemy[i]->getBoundingBox())) {
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
					if (_bullet->isInfringeBorder(WID, HEI, _bullet->getContentSize().height / 2)) //����ӵ���Խ�˱߽�
					{
						removeFlag1 = true;
						goto removeBullet1;
					}//����ӵ�Խ���ˣ��ӵ���ʧ

					for (int i = 0;i < MAX_ENEMY;i++) //����ӵ�����˵���ײ
					{
						if (_bullet->getBoundingBox().intersectsRect(_enemy[i]->getBoundingBox()))//����ڵ������˵���
						{
							SimpleAudioEngine::getInstance()->playEffect("BOOM1.mp3");
							//�򵹵��ˣ����˱�ը����
							{
								Bullet* boom = Bullet::createWithSpriteName(20.0f, 0, "BOOM.png");//20�ǵ��˱�ը�ĳ�ʼ��Χ
								boom->setPower(0);
								boom->setPosition(_enemy[i]->getPositionX(), _enemy[i]->getPositionY());
								addChild(boom, 99);
								_BOOMVector.pushBack(boom);
							}
							if (++_taskCount >= TASKNUM) //������е����������ڵ���������
								_GameState = 1; //��Ϸʤ��
							if (_taskCount <= TASKNUM - MAX_ENEMY)//����ĳ�������е����������ٵĻ�����ô�����˻���λ�ü��ؽ���ʱ�伴��
							{
							resetpos1:
								_enemy[i]->setPosition(CCRANDOM_0_1() * (WID-50)+25, CCRANDOM_0_1() * (HEI-50)+25);
								if (_enemy[i]->getBoundingBox().intersectsRect(_hero->getBoundingBox())) //����õ��˵���λ�������ǳ�ͻ
									goto resetpos1;
								for (int j = 0;j < MAX_ENEMY;j++) 
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
								_enemy[i]->setPosition(-50, -50);
								_enemy[i]->setPositionX(-50);
								_enemy[i]->setPositionY(-50);
								_enemy[i]->setCool(-1);//�ǵø��õ��˼���һ�������Ľ���ʱ�䣬�ø����������ɡ�����
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
			for (int i = 0;i < MAX_ENEMY;i++)
			{
				if (0 == _enemy[i]->getCool()) //����õ��˵Ľ���ʱ���Ѿ�������
				{
					if (CCRANDOM_0_1() < 1.0f / 170.0f) //�ı�����Ǹ��������ı�ת�����
					{
						_enemy[i]->setDirection(CCRANDOM_0_1() * 4 + 1);
						_enemy[i]->setRotation(90.0f*(_enemy[i]->getDirection() - 1));
					}//���������˸ı䷽���ˣ��Ǿ����ˣ�����Ͳ�������
					else
					{
						_enemy[i]->tankRun();//�������������һ��
						if (_enemy[i]->isInfringeBorder(WID, HEI, -_enemy[i]->getContentSize().width / 2)) //����õ���Խ����
							_enemy[i]->tankBack(); //��ô������
						//�ȼ������Ƿ�ײ��Ӣ��
						if (_enemy[i]->getBoundingBox().intersectsRect(_hero->getBoundingBox())) //����õ��������ǳ�ͻ��
						{
							_enemy[i]->tankBack();
							_enemy[i]->setDirection(CCRANDOM_0_1() * 4 + 1);
							_enemy[i]->setRotation(90.0f*(_enemy[i]->getDirection() - 1));
							break;
						}

						//���������Ƿ�ײ���Լ���
						for (int j = 0;j < MAX_ENEMY;j++)
						{
							if (j != i && _enemy[i]->getBoundingBox().intersectsRect(_enemy[j]->getBoundingBox()))
							{
								_enemy[i]->tankBack();
								_enemy[i]->setDirection(CCRANDOM_0_1() * 4 + 1);
								_enemy[i]->setRotation(90.0f*(_enemy[i]->getDirection() - 1));
								break;
							}
						}
						//�������������Ƿ�÷����ڵ�
						if (false == _enemy[i]->getFire()) {
							_enemyBullet[i]->setVisible(true);
							_enemyBullet[i]->setDirection(90.0f*(_enemy[i]->getDirection() - 1));
							_enemyBullet[i]->setSpeed(4.0f);
							_enemy[i]->setFire(true);
						}
					}
				}
				else  //������˵Ľ���ʱ�仹û�н���
					_enemy[i]->setCool(_enemy[i]->getCool() - 1);//���ٵ��˵Ľ���ʱ��

			}

			//���õ��˵��ӵ���һ����
			for (int i = 0;i < MAX_ENEMY;i++)
			{
				_enemyBullet[i]->bulletRun();
				if (_enemyBullet[i]->isInfringeBorder(WID, HEI, _enemyBullet[i]->getContentSize().height / 2)) {
					_enemyBullet[i]->setPosition(_enemy[i]->getPosition());
					_enemyBullet[i]->setVisible(false);
					_enemyBullet[i]->setSpeed(0.0f);
					_enemy[i]->setFire(false);
				}
				if (_hero->getBoundingBox().intersectsRect(_enemyBullet[i]->getBoundingBox())) {
					//����������ڵ����еĻ�������
					_GameState = -1;
				}
			}//�����ӵ��������

			//��ը������
			for (int i = 0;i < _BOOMVector.size();i++)
			{
				auto boom = _BOOMVector.at(i);
				
				//��ⱬը��û��ɱ����Χ�ĵ�λ
				{
					if (circleDetection(boom->getPosition(), boom->getContentSize().width / 2, _hero->getPosition()))
					{
						_GameState = -1;
					}

					for (int i = 0;i < MAX_ENEMY;i++)
					{
						if (!_enemy[i]->getCool() && //������˵Ľ���ʱ���������ը���˵���
							circleDetection(boom->getPosition(), boom->getContentSize().width / 2, _enemy[i]->getPosition()))
						{
							if (++_taskCount >= TASKNUM) _GameState = 1;
							if (_taskCount <= TASKNUM - MAX_ENEMY) //����������µ��˲���
							{
								//�򵹵��ˣ����˱�ը����
								{
									Bullet* boom = Bullet::createWithSpriteName(20.0f, 0, "BOOM.png");
									boom->setPower(0);
									boom->setPosition(_enemy[i]->getPositionX(), _enemy[i]->getPositionY());
									addChild(boom, 99);
									_BOOMVector.pushBack(boom);
								}
								//����һ���µ���
								{
								resetpos2:
									_enemy[i]->setPosition(CCRANDOM_0_1() * (WID-50)+25, CCRANDOM_0_1() * (HEI-50)+25);
									if (_enemy[i]->getBoundingBox().intersectsRect(_hero->getBoundingBox()))
										goto resetpos2;
									for (int j = 0;j < MAX_ENEMY;j++)
									{
										if (i != j && _enemy[i]->getBoundingBox().intersectsRect(_enemy[j]->getBoundingBox()))
											goto resetpos2;
									}
									_enemy[i]->setPositionX(_enemy[i]->getPositionX());
									_enemy[i]->setPositionY(_enemy[i]->getPositionY());
									_enemy[i]->setCool(80);//�����˼���һ����������ʱ��
								}
							}
							else //��ɱ���˹����ˣ�������������󣬲������油�ϳ�
							{
								_enemy[i]->setPosition(-50, -50);
								_enemy[i]->setPositionX(-50);
								_enemy[i]->setPositionY(-50);
								_enemy[i]->setCool(-1);//�ǵø��õ��˼���һ�������Ľ���ʱ�䣬�ø����������ɡ�����
							}

							_addCircle += ADD;//���������һ����ը���ŵ��ٶȣ�����˱�ը���������Ӷ����ӣ�
						}//�����˱�ը�������

						//���ը���������
						for (int i = 0;i < MAX_PARTNER;i++)
						{
							if (circleDetection(boom->getPosition(), boom->getContentSize().width / 2 - 10, _partner[i]->getPosition()))
							{
								_GameState = -3;
							}
						}//�������ѱ�ը�������
						if (circleDetection(boom->getPosition(), boom->getContentSize().width / 2, _hero->getPosition())) {
							_GameState = -2;
						}
					}
				}
				
				if (BOOMLIVE <= boom->getDirection()) //����ñ�ը���ŵ�����
				{
					boom->setVisible(boom->getDirection() % 3);//�ñ�ըһ��һ���ĸ�����
					/*boom->setRotation(CCRANDOM_0_1() * 360);*/ //���Կ����ñ�ը��ת
					if (BOOMLIVE*2 <= boom->getDirection()) //�����ը����̫��ʱ�䣬��������ʧ��
					{
						removeChild(boom);
						_BOOMVector.eraseObject(boom);
					}
				}
				else //��Ȼ�ñ�ը����
				{

					boom->setSpeed(boom->getSpeed() + _addCircle);//�ñ�ը��Χ����һ��
					boom->setContentSize(Size(boom->getSpeed(), boom->getSpeed()));
				}
				boom->setDirection(boom->getDirection() + 2);//���ӱ�ը������ʱ��
			}
		}
		break;
	case 1:
	{ //�������Ҫ���ϻ����ţ���Ȼ��ĳЩ�������У�����Ϊ�ֲ������������������뱨��
		//�ѹؿ�������Ϊ1����ʾ�ô�������ڶ�����
		{
			if (2 > UserDefault::getInstance()->getIntegerForKey("level"))
			{
				UserDefault::getInstance()->setIntegerForKey("level", 2);
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
		auto failText2 = Text::create(((CCString*)chnStrings->objectForKey("failLevel21"))->getCString(), "", 64);
		failText2->setRotation(270);
		failText2->setPosition(Vec2(400, 400));
		addChild(failText2);
		_GameState = 2;//����Ƿ�ֹһֱֹͣ���ű������֣����һֱֹͣ�Ļ����ٴ����¼��ز���BGM�Ļ����ᾲ����
	}
		break;
	case -3:
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		auto chnStrings = CCDictionary::createWithContentsOfFile("xixi.xml");
		auto failText3 = Text::create(((CCString*)chnStrings->objectForKey("failLevel22"))->getCString(), "", 64);
		failText3->setRotation(270);
		failText3->setPosition(Vec2(400, 400));
		addChild(failText3);
		_GameState = 2;//����Ƿ�ֹһֱֹͣ���ű������֣����һֱֹͣ�Ļ����ٴ����¼��ز���BGM�Ļ����ᾲ����
		break;
	break;
	}
}

bool Level2::circleDetection(Point circlePos, float radius, Point tankPos)
{
	float bb = sqrt((circlePos.x - tankPos.x)*(circlePos.x - tankPos.x) + (circlePos.y - tankPos.y)*(circlePos.y - tankPos.y));
	return radius + 25.0f > bb;
}