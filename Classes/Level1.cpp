#include "Level1.h"
USING_NS_CC;

Scene* Level1::createScene()
{
	return Level1::create();
}

bool Level1::init()
{
	_taskCount = 0;
	_GameState = 0;//��Щ��÷�������ִ�е�λ�ã���Ȼ��Ϸ״̬�Ȼ�û�и����أ���������Ҳû�����Ű�
	{
		if (!Scene::init()) return false;

	auto background = Sprite::create("BG.png");//�������һ����ɫ����ͼƬ
	background->setContentSize(Size(400, 800));
	background->setPosition(1000 + background->getContentSize().width / 2, background->getContentSize().height / 2);
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
	down->setRotation(180+45);
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
	left->setRotation(270+45);
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
	right->setRotation(90+45);
	right->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
		switch (type) {
		case Widget::TouchEventType::BEGAN:_hero->setDirection(2);_hero->setRotation(90);break;
		case Widget::TouchEventType::MOVED:_hero->setDirection(2);break;
		case Widget::TouchEventType::ENDED:_hero->setDirection(0);break;
		case Widget::TouchEventType::CANCELED:_hero->setDirection(0);break;
		}
	});
	right->setPosition(Vec2(1300,200));
	addChild(right);

	Button* pause = Button::create("button.png");//����һ����ͣ��ť
	pause->setTitleText("pause");
	pause->setTitleFontSize(32);
	pause->setRotation(90);
	pause->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
		if (Widget::TouchEventType::BEGAN == type) _pause = !_pause;
	});
	pause->setPosition(Vec2(1120,800 - pause->getContentSize().width/2));
	addChild(pause);

	Button* refurbish = Button::create("button.png");//����һ��ˢ�¹ؿ��İ�ť
	refurbish->setTitleText("New");
	refurbish->setTitleFontSize(32);
	refurbish->setRotation(270);
	refurbish->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (Widget::TouchEventType::ENDED == type) {
			Director::getInstance()->replaceScene(Level1::createScene());
		}
	});
	refurbish->setPosition(Vec2(1050, 800 - refurbish->getContentSize().width/2));
	addChild(refurbish);



	SimpleAudioEngine::getInstance()->playBackgroundMusic("1.mp3");//���ű�������

	_hero = Hero::createWithSpriteName(4.99f, 0);//��ʼ������
	_hero->setPosition(500, 400);
	_hero->setPositionX(_hero->getPositionX());//���������ǵ�λ�ø������������ͬ��
	_hero->setPositionY(_hero->getPositionY());
	addChild(_hero);

	_pause = false;
	this->scheduleUpdate();
	}
     /**********������Щ��ģ�廯����*******************/


	Button* fire = Button::create("BOOM.png"); //��Ϊ��һ��һ�����������ӵ�������û��������ģ�廯����
	fire->ignoreContentAdaptWithSize(false);//ͨ���������Ϊfalse������button�ߴ��С
	fire->setContentSize(Size(250, 250));
	fire->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
		if (Widget::TouchEventType::BEGAN == type) {
			if (!_hero->getFire()) {
				_bullet1 = Bullet::createWithSpriteName(16, _hero->getRotation(), "bullet.png");
				_bullet1->setPosition(_hero->getPosition());
				_bullet1->bulletRun();_bullet1->bulletRun();_bullet1->bulletRun();_bullet1->bulletRun();//���õ�һ���ڵ���һ��
				addChild(_bullet1);

				_bullet2 = Bullet::createWithSpriteName(16, _hero->getRotation(), "bullet.png");
				_bullet2->setPosition(_hero->getPosition());
				addChild(_bullet2);

				_hero->setFire(true);
			}
		}
	});
	fire->setPosition(Vec2(WIDTH - fire->getContentSize().width/2,HEIGHT - fire->getContentSize().height/2));
	addChild(fire);

	//�����ʼ������ǽ��
	{for (int i = 25;i <= 800;i += 50) {
		auto temp = Sprite::create("obstacle.png");
		temp->setContentSize(Size(50, 50));
		temp->setPosition(25, i);
		_obstacleVector.pushBack(temp);
		addChild(_obstacleVector.at(_obstacleVector.size() - 1));
	}
	for (int i = 25;i <= 1000;i += 50) {
		auto temp = Sprite::create("obstacle.png");
		temp->setContentSize(Size(50, 50));
		temp->setPosition(i, 25);
		_obstacleVector.pushBack(temp);
		addChild(_obstacleVector.at(_obstacleVector.size() - 1));
	}
	for (int i = 25;i <= 800;i += 50) {
		auto temp = Sprite::create("obstacle.png");
		temp->setContentSize(Size(50, 50));
		temp->setPosition(975, i);
		_obstacleVector.pushBack(temp);
		addChild(_obstacleVector.at(_obstacleVector.size() - 1));
	}
	for (int i = 25;i <= 1000;i += 50) {
		auto temp = Sprite::create("obstacle.png");
		temp->setContentSize(Size(50, 50));
		temp->setPosition(i, 775);
		_obstacleVector.pushBack(temp);
		addChild(_obstacleVector.at(_obstacleVector.size() - 1));
	}}//ǽ�ڳ�ʼ������

	//�����ʼ��6������
	{
		for (int i = 0;i < 6;i++)
		{
			_enemy[i] = Tank::createWithSpriteName(1.01f, int(CCRANDOM_0_1() * 4 + 1),30,"enemy1.PNG");
			_enemy[i]->setRotation(90.0f * (_enemy[i]->getDirection()-1));
			_enemy[i]->setPosition(100 + i * 51, 100 + i * 51);
			_enemy[i]->setPositionX(_enemy[i]->getPositionX());
			_enemy[i]->setPositionY(_enemy[i]->getPositionY());
			_enemy[i]->setFire(false);
			addChild(_enemy[i]);
		}
	}//���˳�ʼ������
	for (int i = 0;i < 6;i++)//�����ӵ���ʼ��
	{
		_bullet[i] = Bullet::createWithSpriteName(0.0f, int(CCRANDOM_0_1() * 4 + 1),  "bullet.png");
		_bullet[i]->setPosition(_enemy[i]->getPosition());
		_bullet[i]->setVisible(true);
		addChild(_bullet[i]);
	}
	return true;
}

void Level1::update(float delta)
{
	switch (_GameState)
	{
	case 0:
		if (!_pause)//�����û�н�����ͣ״̬
		{
			if (_hero->getDirection()) //���Ӣ�۴���ǰ��״̬
			{
				_hero->tankRun();
				if (_hero->isInfringeBorder(1000, 800, -_hero->getContentSize().width / 2))
					_hero->tankBack();

				for (auto obstacle : _obstacleVector)//���Ӣ��ײ�����ϰ���
				{
					if (_hero->getBoundingBox().intersectsRect(obstacle->getBoundingBox())) {
						_hero->tankBack();
						break;
					}
				}
				for (int i = 0;i < 6;i++) //���Ӣ��ײ���˱��̹��
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
				if (_bullet1) {
					_bullet1->bulletRun();
					bool removeFlag1 = false;
					if (_bullet1->isInfringeBorder(1000, 800, _bullet2->getContentSize().height / 2)) {
						_GameState = -1;
						removeFlag1 = true;
						goto removeBullet1;
					}//����ӵ�Խ���ˣ��ӵ���ʧ

					for (int i = 0;i < 6;i++) {
						if (_bullet1->getBoundingBox().intersectsRect(_enemy[i]->getBoundingBox())) {
							if (++_taskCount >= 20) _GameState = 1;
							SimpleAudioEngine::getInstance()->playEffect("BOOM2.mp3");
							if (_taskCount <= 14)//����ĳ�������е����������ٵĻ�����ô�����˻���λ�ü��ؽ���ʱ�伴��
							{
							resetpos1:
								_enemy[i]->setPosition(CCRANDOM_0_1() * 1000, CCRANDOM_0_1() * 800);
								if (_enemy[i]->getBoundingBox().intersectsRect(_hero->getBoundingBox()))
									goto resetpos1;//����������˵�λ���������ص�����ô����������λ��
								/***����������˵�λ������һ�������ص�����ô����������λ��***/
								for (int j = 0;j < 6;j++) {
									if (i != j && _enemy[i]->getBoundingBox().intersectsRect(_enemy[j]->getBoundingBox()))
										goto resetpos1; 
								}
								/***����������˵�λ����ǽ���ص�����ô����������λ��****/
								for (int j = 0;j < _obstacleVector.size();j++) {
									auto obstacle = _obstacleVector.at(j);
									if (obstacle->getBoundingBox().intersectsRect(_enemy[i]->getBoundingBox()))
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
						removeChild(_bullet1);
						_bullet1 = nullptr;
					}
				}
				if (_bullet2)
				{
					_bullet2->bulletRun();
					bool removeFlag2 = false;
					if (_bullet2->isInfringeBorder(1000, 800, _bullet2->getContentSize().height / 2))
					{
						_GameState = -2;
						removeFlag2 = true;
						goto removeBullet2;
					}//����ӵ�Խ���ˣ��ӵ���ʧ

					 //����ӵ�����˵���ײ
					for (int i = 0;i < 6;i++) {
						if (_bullet2->getBoundingBox().intersectsRect(_enemy[i]->getBoundingBox())) {
							if (++_taskCount >= 20) _GameState = 1;
							SimpleAudioEngine::getInstance()->playEffect("BOOM2.mp3");
							if (_taskCount <= 14)//����ĳ�������е����������ٵĻ�����ô�����˻���λ�ü����޵�ʱ�伴��
							{
							resetpos2:
								_enemy[i]->setPosition(CCRANDOM_0_1() * 1000, CCRANDOM_0_1() * 800);
								if (_enemy[i]->getBoundingBox().intersectsRect(_hero->getBoundingBox()))
									goto resetpos2;
								for (int j = 0;j < 6;j++) {
									if (i != j && _enemy[i]->getBoundingBox().intersectsRect(_enemy[j]->getBoundingBox()))
										goto resetpos2;
								}
								for (int j = 0;j < _obstacleVector.size();j++) {
									auto obstacle = _obstacleVector.at(j);
									if (obstacle->getBoundingBox().intersectsRect(_enemy[i]->getBoundingBox()))
										goto resetpos2;
								}
								_enemy[i]->setPositionX(_enemy[i]->getPositionX());
								_enemy[i]->setPositionY(_enemy[i]->getPositionY());
								_enemy[i]->setCool(80);//�����˼���һ����������ʱ��
							}
							else {
								_enemy[i]->setPosition(-50, -50);
								_enemy[i]->setPositionX(-50);
								_enemy[i]->setPositionY(-50);
								_enemy[i]->setCool(-1);//�ǵø��õ��˼���һ�������Ľ���ʱ�䣬�ø����������ɡ�����
							}

							removeFlag2 = true;
							goto removeBullet2;//�������Ҫ�ӣ���Ȼ�ӵ��Ѿ�ɾ���ˣ������ᱻ���Ե�
						}
					}
				removeBullet2:
					if (removeFlag2 == true) {
						removeChild(_bullet2);
						_bullet2 = nullptr;
					}
				}
				if (nullptr == _bullet1 && nullptr == _bullet2)
					_hero->setFire(false);
			}//Ӣ�۵��ӵ��������

			 //�ֵ������ж���
			for (int i = 0;i < 6;i++)
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


						if (_enemy[i]->isInfringeBorder(1000, 800, -_enemy[i]->getContentSize().width / 2)) _enemy[i]->tankBack();

						//�ȼ������Ƿ�ײ��Ӣ��
						if (_enemy[i]->getBoundingBox().intersectsRect(_hero->getBoundingBox())) {
							_enemy[i]->tankBack();
							_enemy[i]->setDirection(CCRANDOM_0_1() * 4 + 1);
							_enemy[i]->setRotation(90.0f*(_enemy[i]->getDirection() - 1));
							break;
						}
						//�ڼ������Ƿ�ײǽ
						for (int j = 0;j < _obstacleVector.size();j++)
						{
							auto obstacle = _obstacleVector.at(j);
							if (_enemy[i]->getBoundingBox().intersectsRect(obstacle->getBoundingBox()))
							{
								_enemy[i]->tankBack();
								_enemy[i]->setDirection((_enemy[i]->getDirection() + 1) % 4 + 1);//��������ԭ·���أ������ת��
								_enemy[i]->setRotation(90.0f*(_enemy[i]->getDirection() - 1));
								break;
							}
						}
						//���������Ƿ�ײ���Լ���
						for (int j = 0;j < 6;j++)
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
							_bullet[i]->setVisible(true);
							_bullet[i]->setDirection(90.0f*(_enemy[i]->getDirection() - 1));
							_bullet[i]->setSpeed(3.0f);
							_enemy[i]->setFire(true);
						}
					}
				}
				else  //������˵Ľ���ʱ�仹û�н���
					_enemy[i]->setCool(_enemy[i]->getCool() - 1);//���ٵ��˵Ľ���ʱ��
		
			}

			//���õ��˵��ӵ���һ����
			for (int i = 0;i < 6;i++)
			{
				_bullet[i]->bulletRun();
				if (_bullet[i]->isInfringeBorder(1000, 800, _bullet[i]->getContentSize().height / 2) &&0 <= _enemy[i]->getCool()) {
					_bullet[i]->setPosition(_enemy[i]->getPosition());
					_bullet[i]->setVisible(false);
					_bullet[i]->setSpeed(0.0f);
					_enemy[i]->setFire(false);
					_GameState = -3;
				}
				if (_hero->getBoundingBox().intersectsRect(_bullet[i]->getBoundingBox())) {
					//����������ڵ����еĻ�������
					_GameState = -4;
				}
				for (int j = 0;j < _obstacleVector.size();j++)
				{
					auto obstacle = _obstacleVector.at(j);
					if (obstacle->getBoundingBox().intersectsRect(_bullet[i]->getBoundingBox())) {
						_bullet[i]->setPosition(_enemy[i]->getPosition());
						_bullet[i]->setVisible(false);
						_bullet[i]->setSpeed(0.0f);
						_enemy[i]->setFire(false);
					}
				}
			}

			//��������ڵ��Ƿ�������ǽ�ڷ�����ײ
			for (int i = 0;i < _obstacleVector.size();i++)
			{
				auto obstacle = _obstacleVector.at(i);
				if (_bullet1 && obstacle->getBoundingBox().intersectsRect(_bullet1->getBoundingBox()))
				{
					removeChild(obstacle);
					removeChild(_bullet1);
					_obstacleVector.eraseObject(obstacle);
					_bullet1 = nullptr;
					break;
				}
				if (_bullet2 && obstacle->getBoundingBox().intersectsRect(_bullet2->getBoundingBox()))
				{
					removeChild(_bullet2);
					removeChild(obstacle);
					_obstacleVector.eraseObject(obstacle);
					_bullet2 = nullptr;
				}
			}//�ϰ���Ĵ��루��Ҫ����Ӣ���ӵ���⣩���
		}
		break;
	case 1:
	{ //�������Ҫ���ϻ����ţ���Ȼ��ĳЩ�������У�����Ϊ�ֲ������������������뱨��
		{
			if (1 > UserDefault::getInstance()->getIntegerForKey("level"))
			{
				UserDefault::getInstance()->setIntegerForKey("level", 1);
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
	case -2:
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();//ֹͣ���ű�������
		CCDictionary* chnStrings = CCDictionary::createWithContentsOfFile("xixi.xml");
		Text* failText2 = Text::create(((CCString*)chnStrings->objectForKey("failLevel12"))->getCString(), "", 64);
		failText2->setRotation(270);
		failText2->setPosition(Vec2(400, 400));
		addChild(failText2);
		_GameState = 2;//����Ƿ�ֹһֱֹͣ���ű������֣����һֱֹͣ�Ļ����ٴ����¼��ز���BGM�Ļ����ᾲ����
	}
	break;
	case -3:
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();//ֹͣ���ű�������
		auto chnStrings = CCDictionary::createWithContentsOfFile("xixi.xml");
		Text* failText3 = Text::create(((CCString*)chnStrings->objectForKey("failLevel13"))->getCString(), "", 64);
		failText3->setRotation(270);
		failText3->setPosition(Vec2(400, 400));
		addChild(failText3);
		_GameState = 2;//����Ƿ�ֹһֱֹͣ���ű������֣����һֱֹͣ�Ļ����ٴ����¼��ز���BGM�Ļ����ᾲ����
	}
	break;
	case -4:
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();//ֹͣ���ű�������

	
		auto chnStrings = CCDictionary::createWithContentsOfFile("xixi.xml");
		const char * sss = ((CCString *)chnStrings->objectForKey("failLevel11"))->getCString();
		Text* failText4 = Text::create(sss, "", 64);
		failText4->setRotation(270);
		failText4->setPosition(Vec2(400, 400));
		addChild(failText4);
		_GameState = 2;//����Ƿ�ֹһֱֹͣ���ű������֣����һֱֹͣ�Ļ����ٴ����¼��ز���BGM�Ļ����ᾲ����
	}
	break;
	}
}