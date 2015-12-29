
#include <algorithm>

#include "../Model/LoadModel.h"
#include "../MyLibrary/MyLibrary.h"
#include "./FileLoadManager.h"
#include "./GlobalDefine.h"

USING_NS_CC;
USING_NS_C3E;
USING_NS_STD;

class FileLoadManager::Private
{
public:
};

FileLoadManager::FileLoadManager()
{
}

FileLoadManager::~FileLoadManager()
{
}

bool	FileLoadManager::LoadFile( const string& filePath )
{
	string extension = MyLibrary::StringUtility::getExtension( filePath );

	// ‚·‚×‚Ä¬•¶Žš‚É
	transform( extension.cbegin(), extension.cend(), extension.begin(), tolower );

	// 3DModel
	if( extension == ".fbx" || extension == ".obj" || extension == ".c3b" || extension == ".c3t" )
	{
		if( LoadModel::getInstance()->loadModelData( filePath ) == true )
		{
			return true;
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