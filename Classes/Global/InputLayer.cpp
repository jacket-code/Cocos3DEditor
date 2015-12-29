
#include "../MyLibrary/MyLibrary.h"
#include "./GlobalDefine.h"
#include "./InputLayer.h"

USING_NS_CC;
USING_NS_C3E;

class InputLayer::Private : public Layer
{
public:
	enum
	{
		LEFT_BUTTON = 0,
		RIGHT_BUTTON,
		CENTER_BUTTON,

		KEYCODE_NUM = EventKeyboard::KeyCode::KEY_NUM,
	};

	CREATE_FUNC( Private );

	bool init( void ) override;
	void update( float delta ) override;

	void onMouseDown( EventMouse* event );
	void onMouseUp( EventMouse* event );
	void onMouseMove( EventMouse* event );
	void onMouseScroll( EventMouse* event );
	void onKeyPressed( KEY_CODE keyCode , Event* keyEvent );
	void onKeyReleased( KEY_CODE keyCode , Event* keyEvent );
	
private:
	Private();
	~Private();

public:
	bool							_onKeyCode[KEYCODE_NUM];
	bool							_onKeyCodeOld[KEYCODE_NUM];
	bool							_onKeyCodeArray[KEYCODE_NUM];

	Vec2							_mouseVector;
	Point							_mousePos;
	Point							_mouseStartPos;
	Point							_mouseEndPos;
	MyLibrary::Bit<unsigned char>	_mouseFlag;

	float							_mouseScroll;
	int32_t							_keyCodeCount;
	bool							_inputFlag;
	bool							_keyboradFlag;
};

InputLayer::InputLayer()
{
}

InputLayer::~InputLayer()
{
}

bool	InputLayer::init( void )
{
	if( Layer::init() == false ) { return false; }

	p = Private::create();
	addChild( p );

	return true;
}

void	InputLayer::update( float delta )
{
}

bool	InputLayer::isMousePush( MouseFlags flagNumber )
{
	return p->_mouseFlag.check( static_cast<const unsigned char>(flagNumber) );
}

Point	InputLayer::getMousePosition( void ) const
{
	return p->_mousePos;
}

Point	InputLayer::getMouseStartPosition( void ) const
{
	return p->_mouseStartPos;
}

Point	InputLayer::getMouseEndPosition( void ) const
{
	return p->_mouseEndPos;
}

Vec2	InputLayer::getMouseVector( void ) const
{
	return p->_mouseVector;
}

float	InputLayer::getMouseScroll( void ) const
{
	return p->_mouseScroll;
}

bool	InputLayer::isKeyboradPush( EventKeyboard::KeyCode keyCode )
{
	return p->_onKeyCode[keyCode];
}

bool	InputLayer::isKeyboradPushDown( EventKeyboard::KeyCode keyCode )
{
	return (( p->_onKeyCode[keyCode] == true ) && ( p->_onKeyCodeOld[keyCode] == false ));
}

bool	InputLayer::isKeyboradPushUp( EventKeyboard::KeyCode keyCode )
{
	return (( p->_onKeyCode[keyCode] == false ) && ( p->_onKeyCodeOld[keyCode] == true ));
}

InputLayer::Private::Private() : _mouseVector()
, _mousePos( 0.0f, 0.0f )
, _mouseStartPos( 0.0f, 0.0f )
, _mouseEndPos( 0.0f, 0.0f )
, _mouseFlag( 0 )
, _mouseScroll( 0.0f )
, _keyCodeCount( 0 )
, _inputFlag( false )
, _keyboradFlag( false )
{
	for( auto &p : _onKeyCode ) { p = false; }
	for( auto &p : _onKeyCodeOld ) { p = false; }
	for( auto &p : _onKeyCodeArray ) { p = false; }
}

InputLayer::Private::~Private()
{
}

bool	InputLayer::Private::init( void )
{
	if( Layer::init() == false ) { return false; }

	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseUp	 = CC_CALLBACK_1( InputLayer::Private::onMouseUp, this );
	mouseListener->onMouseDown	 = CC_CALLBACK_1( InputLayer::Private::onMouseDown, this );
	mouseListener->onMouseScroll = CC_CALLBACK_1( InputLayer::Private::onMouseScroll, this );
	mouseListener->onMouseMove	 = CC_CALLBACK_1( InputLayer::Private::onMouseMove, this );
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority( mouseListener, this );

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2( InputLayer::Private::onKeyPressed, this );
	keyboardListener->onKeyReleased = CC_CALLBACK_2( InputLayer::Private::onKeyReleased, this );
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority( keyboardListener , this );

	scheduleUpdate();

	return true;
}

void	InputLayer::Private::update( float delta )
{
	for( int i = 0; i < KEY_CODE::KEY_NUM; i++ )
	{
		if( _onKeyCodeArray[i] == true )
		{
			_onKeyCodeArray[i] = false;
		}
		else
		{
			_onKeyCodeOld[i] = _onKeyCode[i];
		}
	}
}

void	InputLayer::Private::onMouseDown( EventMouse* event )
{
	EventMouse* e = dynamic_cast<EventMouse*>(event);
	if( e == nullptr ) { return; }

	if( _mouseFlag.check( PUSH_FLAG ) == false )
	{
		_mouseFlag.set( PUSH_FLAG );
		_mouseFlag.set( 1 << (e->getMouseButton() + PUSH_FLAG ));	
	}
}

void	InputLayer::Private::onMouseUp( EventMouse* event )
{
	EventMouse* e = dynamic_cast<EventMouse*>(event);
	if( e == nullptr ) { return; }

	if( _mouseFlag.check( PUSH_FLAG ))
	{
		_mouseFlag.allReset();
	}
}

void	InputLayer::Private::onMouseMove( EventMouse* event )
{
	EventMouse* e = dynamic_cast<EventMouse*>(event);
	if( e == nullptr ) { return; }

	_mousePos = Point( e->getCursorX(), e->getCursorY() );
	
	if( _inputFlag == true && _mouseFlag.check( PUSH_FLAG ) == false )
	{
		_inputFlag = false;
		_mouseVector = _mousePos - _mouseStartPos;
		_mouseEndPos = _mousePos;
	}
	else if( _inputFlag == false && _mouseFlag.check( PUSH_FLAG ) == true )
	{
		_inputFlag = true;
		_mouseStartPos = _mousePos;
	}
}

void	InputLayer::Private::onMouseScroll( EventMouse* event )
{
	EventMouse* e = dynamic_cast<EventMouse*>(event);
	if( e == nullptr ) { return; }

	_mouseScroll = e->getScrollY();
}

void	InputLayer::Private::onKeyPressed( KEY_CODE keyCode , Event* keyEvent )
{
	_onKeyCode[keyCode] = true;
	_onKeyCodeArray[keyCode] = true;
}

void	InputLayer::Private::onKeyReleased( KEY_CODE keyCode , Event* keyEvent )
{
	_onKeyCode[keyCode] = false;
	_onKeyCodeArray[keyCode] = true;
}
