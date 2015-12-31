
#include <algorithm>

#include "../Model/LoadModel.h"
#include "../MyLibrary/MyLibrary.h"
#include "./FileLoadManager.h"
#include "./GlobalDefine.h"
#include "./InputLayer.h"

USING_NS_CC;
USING_NS_C3E;
USING_NS_STD;

class FileLoadManager::Private
{
public:
	Private();
	~Private();

	bool LoadFile( const std::string& filePath );
	void fileDropCallback( int count, const char** paths );

public:
	Point				_mousePos;
	vector<Sprite3D*>	_sprite3DArray;
};

FileLoadManager::FileLoadManager()
{
	p = new Private();
}

FileLoadManager::~FileLoadManager()
{
	delete p;
}

Sprite3D* FileLoadManager::getSprite3D( int number )
{
	if( number > p->_sprite3DArray.size() - 1 )
	{
		return nullptr;
	}

	if( p->_sprite3DArray.size() > 0 )
	{
		return p->_sprite3DArray[number];
	}
	return nullptr;
}

Sprite3D* FileLoadManager::getSprite3D( const string& fileName )
{
	for( int i = 0; i < (int)p->_sprite3DArray.size(); i++ )
	{
		if( p->_sprite3DArray[i]->getName() == fileName )
		{
			return p->_sprite3DArray[i];
		}
	}

	return nullptr;
}

FileLoadManager::Private::Private()
{
	auto director = Director::getInstance();
	auto glView = dynamic_cast<GLViewImpl*>(director->getOpenGLView());

	if( glView != nullptr )
	{
		glView->setFileDropCallback( CC_CALLBACK_2( FileLoadManager::Private::fileDropCallback, this ));
	}
}

FileLoadManager::Private::~Private()
{

}

bool	FileLoadManager::Private::LoadFile( const string& filePath )
{
	string extension = MyLibrary::StringUtility::getExtension( filePath );

	// ‚·‚×‚Ä¬•¶Žš‚É
	transform( extension.cbegin(), extension.cend(), extension.begin(), tolower );

	// 3DModel
	if( extension == ".fbx" || extension == ".obj" || extension == ".c3b" || extension == ".c3t" )
	{
		Sprite3D* sprite = LoadModel::getInstance()->loadModelData( filePath, extension );
		if( sprite != nullptr )
		{
			sprite->setName(  MyLibrary::StringUtility::getFileName( filePath ));
			_sprite3DArray.push_back( sprite );
		}
		else
		{
			return false;
		}
	}

	// Texture
	if( extension == ".png" || extension == ".jpg" || extension == ".bmp" || extension == ".tga" )
	{
	}

	// Script
	if( extension == ".lua" )
	{
	}

	return true;
}

void	FileLoadManager::Private::fileDropCallback( int count, const char** paths )
{
	for( int i = 0; i < count; i++ )
	{
		LoadFile( paths[i] );
	}
}