#pragma once
#include "Object.h"
#include <SFML/Graphics.hpp>

class Item : public Object
{
public:
	// Use the Object's c-tor
	using Object::Object;
	// d-tor
	virtual ~Item();
};

