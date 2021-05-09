#include "scene.h"

#include <GL/glut.h>

#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene* scene)
{
    load_model(&(scene->base), "data/obj/base.obj");
    scene->base_texture_id = load_texture("data/textures/base.bmp"); 

    scene->material.ambient.red = 0.8;
    scene->material.ambient.green = 0.8;
    scene->material.ambient.blue = 0.8;

    scene->material.diffuse.red = 0.8;
    scene->material.diffuse.green = 0.8;
    scene->material.diffuse.blue = 0.8;

    scene->material.specular.red = 0.8;
    scene->material.specular.green = 0.8;
    scene->material.specular.blue = 0.8;

    scene->material.shininess = 0.8;
}

void set_lighting() /*FÉNY*/
{
    
    float diffuse_light[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    float specular_light[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void draw_scene(const Scene* scene)
{
    set_material(&(scene->material));
    set_lighting(); 
    

    glPushMatrix();
    glTranslatef(0.75, 5.87, 0);
    glRotatef(90, 50, 1, 1);
    glBindTexture(GL_TEXTURE_2D, scene->base_texture_id);
    draw_model(&(scene->base));
    glPopMatrix();
    
}


