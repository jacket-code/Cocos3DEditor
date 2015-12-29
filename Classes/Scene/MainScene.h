
#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "../Global/InputLayer.h"
#include "cocos2d.h"

namespace Cocos3DEditor
{

class MainScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene( void );
	CREATE_FUNC( MainScene );

private:
	MainScene();
	~MainScene();

	bool init( void ) override;
	void update( float delta );

	void fileDropCallback( int count, const char** paths );

private:
	InputLayer* _inputLayer;
};

}

#endif // __MAIN_SCENE_H__
