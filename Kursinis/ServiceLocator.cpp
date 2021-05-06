#include "ServiceLocator.h"

ResourceManager* ServiceLocator::resource_manager;

void ServiceLocator::provide( ResourceManager* rmanager )
{
	resource_manager = rmanager;
}

const ResourceManager* ServiceLocator::get_resource_manager()
{
	return resource_manager;
}