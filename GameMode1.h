#pragma once

#include "SDL.h"

class Mode1 : public PhaseInterface
{
public:
	Mode1();
	~Mode1();

	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();
	void userMove();
	void holdMove();

private:

};