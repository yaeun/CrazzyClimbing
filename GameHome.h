#pragma once

#include "SDL.h"

class Home : public PhaseInterface
{
public:
	Home();
	~Home();
	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();

private:

};
