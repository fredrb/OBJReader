#ifndef DRAW_PROGRAM_H
#define DRAW_PROGRAM_H

#include "../GL/Context.h"

class DrawProgram {

public:
	virtual void init_draw_program (Context* c) = 0;

	virtual void on_frame (const float timestamp) = 0;
};

#endif
