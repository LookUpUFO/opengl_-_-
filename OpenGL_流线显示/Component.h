#pragma once
#include "Object.h"

class Component :Object
{

public:
	virtual void Update() {};


public:
 	 Component() =default;
	~Component()  = default ;
};

