
#ifndef __INPUT_LAYER_H__
#define __INPUT_LAYER_H__

#include "cocos2d.h"

namespace Cocos3DEditor
{

class InputLayer : public cocos2d::Layer
{
public:
#define KEY_CODE EventKeyboard::KeyCode

	enum MouseFlags
	{
		PUSH_FLAG		 = ( 1 << 0),
		LEFT_PUSH_FlAG	 = ( 1 << 1),
		RIGHT_PUSH_FlAG	 = ( 1 << 2),
		CENTER_PUSH_FlAG = ( 1 << 3),
	};

	CREATE_FUNC( InputLayer );

	bool isMousePush( MouseFlags flagNumber );
	cocos2d::Point getMousePosition( void ) const;
	cocos2d::Point getMouseStartPosition( void ) const;
	cocos2d::Point getMouseEndPosition( void ) const;
	cocos2d::Vec2 getMouseVector( void ) const;
	float getMouseScroll( void ) const;

	bool isKeyboradPush( cocos2d::EventKeyboard::KeyCode keyCode );
	bool isKeyboradPushDown( cocos2d::EventKeyboard::KeyCode keyCode );
	bool isKeyboradPushUp( cocos2d::EventKeyboard::KeyCode keyCode );

private:
	bool init( void ) override;
	void update( float delta ) override;


	InputLayer();
	~InputLayer();

private:
	class Private;
	Private* p;
};

}

#endif // __INPUT_LAYER_H__