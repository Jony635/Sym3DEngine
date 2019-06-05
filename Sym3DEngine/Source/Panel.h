#pragma once

class Panel
{
	friend class ModuleImGUI;

public:
	virtual void Draw() = 0;

protected:
	bool active = true;
};