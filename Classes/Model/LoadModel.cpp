
#include "../Global/GlobalDefine.h"
#include "../MyLibrary/MyLibrary.h"
#include "./LoadModel.h"

USING_NS_CC;
USING_NS_C3E;
USING_NS_STD;

LoadModel::LoadModel()
{
}

LoadModel::~LoadModel()
{
}

Sprite3D* LoadModel::loadModelData( const string& filePath )
{
	string str = MyLibrary::StringUtility::getFileName( filePath );
	Sprite3D* model = Sprite3D::create( filePath );
	return model;
}

Sprite3D* LoadModel::loadModelData( const string& filePath, const string& extension )
{
	Sprite3D* sprite3D = nullptr;

	if( extension == ".fbx" )
	{
	}
	else if( extension == ".c3b" || extension == ".c3t" || extension == ".obj" )
	{
		sprite3D = Sprite3D::create( filePath );
	}

	return sprite3D;
}
