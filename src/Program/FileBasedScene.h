#ifndef OBJREADER_FILEBASEDSCENE_H
#define OBJREADER_FILEBASEDSCENE_H

#include "Scene.h"

class FileBasedScene : public Scene {
private:
    void initialize_object (SceneObject *obj, glm::vec3 position);
public:
    void init_draw_program(Context *c) override;
};


#endif //OBJREADER_FILEBASEDSCENE_H
