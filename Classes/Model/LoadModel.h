
#ifndef __LOAD_MODEL_H__
#define __LOAD_MODEL_H__

#include "cocos2d.h"

namespace Cocos3DEditor
{

class LoadModel 
{
public:
	static LoadModel* getInstance( void )
	{
		static LoadModel* instance = nullptr;
		if( instance == nullptr )
		{
			instance = new LoadModel();
		}
		return instance;
	}

	~LoadModel();
	bool loadModelData( const std::string& filePath );
	cocos2d::Sprite3D* getModelData( int number );
	cocos2d::Sprite3D* getModelData( const std::string& fileName );

private:
	LoadModel();
	LoadModel( const LoadModel& obj ) {}
	LoadModel& operator=( const LoadModel& obj ) {}

private:
	class Private;
	Private* p;
};

}


#endif // __LOAD_MODEL_H__
