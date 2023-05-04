#pragma once

#include "SDL.h"

class Ending3 : public PhaseInterface
{
public:
	Ending3();
	~Ending3();
	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();

private:

};

