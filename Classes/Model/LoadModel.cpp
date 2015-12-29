
#include "../Global/GlobalDefine.h"
#include "../MyLibrary/MyLibrary.h"
#include "./LoadModel.h"

USING_NS_CC;
USING_NS_C3E;
USING_NS_STD;

class LoadModel::Private
{
public:
	map<string,Sprite3D*> _modelData;
};

LoadModel::LoadModel()
{
	p = new Private();
}

LoadModel::~LoadModel()
{
	delete p;
}

bool	LoadModel::loadModelData( const string& filePath )
{
	string str = MyLibrary::StringUtility::getFileName( filePath );
	Sprite3D* model = Sprite3D::create( filePath );
	p->_modelData[str] = model;
	return true;
}

Sprite3D* LoadModel::getModelData( int number )
{
	return nullptr;
}

Sprite3D* LoadModel::getModelData( const string& fileName )
{
	return p->_modelData[fileName];
}
