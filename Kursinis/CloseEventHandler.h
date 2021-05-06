#pragma once

class CloseEventHandler
{
public:
	virtual bool on_close() { return false; }
};

