
#include "../Global/FileLoadManager.h"
#include "../Global/GlobalDefine.h"
#include "../Model/LoadModel.h"
#include "../MyLibrary/MyLibrary.h"
#include "./MainScene.h"

USING_NS_CC;
USING_NS_C3E;

Scene*	MainScene::createScene( void )
{
	auto scene = Scene::create();
	auto layer = MainScene::create();
	scene->addChild( layer );
	return scene;
}

MainScene::MainScene()
{
}

MainScene::~MainScene()
{
}

bool	MainScene::init( void )
{
	if( !Layer::init() ) { return false; }

	_inputLayer = InputLayer::create();
	addChild( _inputLayer );

	_modelArray.clear();
	_selectModel = nullptr;

	scheduleUpdate();

	return true;
}

void	MainScene::update( float delta )
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	/*
	if( _inputLayer->isKeyboradPushDown( KEY_CODE::KEY_ENTER ) == true ) 
	{
		log( "enter push" );
	}

	if( _inputLayer->isKeyboradPushDown( KEY_CODE::KEY_ESCAPE ) == true ) 
	{
		log( "escape push" );
	}
*/

	Sprite3D* sprite = FileLoadManager::getInstance()->getSprite3D( _modelArray.size() );
	if( sprite != nullptr )
	{
		sprite->setPosition( visibleSize.width * 0.5f, visibleSize.height * 0.5f );
		sprite->setScale( 300.0f );
		addChild( sprite );
		_modelArray.pushBack( sprite );
	}

	
	if( _selectModel != nullptr )
	{
		_selectModel->setScale( _selectModel->getScale() + _inputLayer->getMouseScroll() * 2.0f );
		_selectModel->setPosition( CCPoint( _inputLayer->getMousePosition().x, _inputLayer->getMousePosition().y - (_selectModel->getContentSize().height * _selectModel->getScale()) * 0.5f ));
	}

	if( _inputLayer->isMousePush( InputLayer::MouseFlags::LEFT_PUSH_FlAG ) == true && _selectModel == nullptr)
	{
		for( int i = 0; i < (int)_modelArray.size(); i++ )
		{
			auto rect = _modelArray.at( i )->getBoundingBox();
			if( rect.containsPoint( _inputLayer->getMousePosition() ) == true )
			{
				log( "Model Push" );
				_selectModel = _modelArray.at( i );
			}
		}
	}
	else
	{
		_selectModel = nullptr;
	}
}
