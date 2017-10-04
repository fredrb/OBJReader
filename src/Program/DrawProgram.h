#ifndef DRAW_PROGRAM_H
#define DRAW_PROGRAM_H

#include "../GL/Context.h"

enum KEY {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	QUIT,
	SCALE,
	ROTATE
};

class DrawProgram {

public:
	virtual void init_draw_program (Context* c) = 0;

	virtual void on_frame (const float timestamp) = 0;

	virtual void on_key_pressed (const KEY) = 0;

	virtual void on_mouse_moved (double xpos, double ypos) = 0;

	virtual void on_window_resize(int width, int height) = 0;
 
};

#endif
