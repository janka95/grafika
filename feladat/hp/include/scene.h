#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>

typedef struct Scene
{
    Model base;
    Model harry;
    Model snitch;
    Material material;
    GLuint base_texture_id;
    GLuint harry_texture_id;
    GLuint snitch_texture_id;
    GLuint help_texture_id;
    float snitch_rotation;
    float snitch_rotation_ownaxis;
    float harry_rotation;

} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Update loaded scenes.
 */
void update_scene(Scene* scene, double time);

/**
 * Set the lighting of the scene.
 */
void set_lighting();

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Draw the scene objects.
 */
void draw_scene(const Scene* scene);

/**
 * Draw the help window.
 */
void draw_help(int texture);



#endif /* SCENE_H */
