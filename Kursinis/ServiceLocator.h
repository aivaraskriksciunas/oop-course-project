#pragma once

#include "ResourceManager.h"
#include "EventManager.h"

class ServiceLocator
{
public:
	static void provide( ResourceManager* rmanager );
	static const ResourceManager* get_resource_manager();

private: 
	static ResourceManager* resource_manager;
};

