#pragma once

#include "SDL.h"

class Mode2 : public PhaseInterface
{
public:
	Mode2();
	~Mode2();
	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();

private:

};

