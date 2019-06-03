#pragma once

class Module
{
public:
	virtual bool Init() { return true; }
	virtual bool Start() { return true; }
	virtual bool CleanUp() { return true; }
	virtual bool PreUpdate() { return true; }
	virtual bool Update() { return true; }
	virtual bool PostUpdate() { return true; }
};