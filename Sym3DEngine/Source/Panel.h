#pragma once

class Panel
{
	friend class ModuleImGUI;

public:
	inline void ToggleActive() { active = !active; }

private:
	virtual void Draw() = 0;

protected:
	bool active = true;
};