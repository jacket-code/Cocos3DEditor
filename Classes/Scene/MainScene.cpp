
#include "../Global/GlobalDefine.h"
#include "../Global/FileLoadManager.h"
#include "../Model/LoadModel.h"
#include "../MyLibrary/MyLibrary.h"
#include "./MainScene.h"

USING_NS_CC;
USING_NS_C3E;

Scene* MainScene::createScene( void )
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

bool MainScene::init( void )
{
	if( !Layer::init() ) { return false; }

	auto director = Director::getInstance();
	auto glView = dynamic_cast<GLViewImpl*>(director->getOpenGLView());

	if( glView != nullptr )
	{
		glView->setFileDropCallback( CC_CALLBACK_2( MainScene::fileDropCallback, this ));
	}

	scheduleUpdate();

	return true;
}

void MainScene::update( float delta )
{
}

void MainScene::fileDropCallback( int count, const char** paths )
{
	auto loadManager = FileLoadManager::getInstance();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	for( int i = 0; i < count; i++ )
	{
		loadManager->LoadFile( paths[i] );
		Sprite3D* model = LoadModel::getInstance()->getModelData( MyLibrary::StringUtility::getFileName( paths[i] ));
		if( model == nullptr )
		{
			continue;
		}
		model->setPosition( visibleSize.width * 0.5f, visibleSize.height * 0.5f );
		addChild( model );
	}
}