#ifndef MULTIPLE_OBJECT_SCENE
#define MULTIPLE_OBJECT_SCENE

#include "Scene.h"

class MultipleObjectScene : public Scene { 
private:
	void initialize_object (SceneObject *obj, glm::mat4 model);
public:
	void init_draw_program (Context* c) override;
};

#endif
