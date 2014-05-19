#pragma once

#include "cocos2d.h"

using namespace cocos2d;

const int Tag_Air_Plane = 747;

class PlaneLayer:public Layer{
public:
	PlaneLayer();

	~PlaneLayer();
	
	static PlaneLayer* create();

	virtual bool init();

	void moveTo(Point pos);

	void blowup(int passScore);

	void removePlane();

public:
	static PlaneLayer* sharedPlane;

	bool isAlive;
	int score;

};