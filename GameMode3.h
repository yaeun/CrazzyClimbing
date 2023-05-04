#pragma once

#include "SDL.h"

class Mode3 : public PhaseInterface
{
public:
	Mode3();
	~Mode3();
	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();

private:

};

