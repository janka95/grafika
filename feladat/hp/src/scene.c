#include "scene.h"

#include <GL/glut.h>

#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene* scene)
{
    load_model(&(scene->base), "data/obj/base.obj");
    scene->base_texture_id = load_texture("data/textures/base.bmp"); 

    load_model(&(scene->harry), "data/obj/harry.obj");
    scene->harry_texture_id = load_texture("data/textures/harry.png"); 

    load_model(&(scene->snitch), "data/obj/snitch.obj");
    scene->snitch_texture_id = load_texture("data/textures/snitch.png");

    scene->help_texture_id = load_texture("data/textures/help.png");

    scene->snitch_rotation = 0.0;
    scene->harry_rotation = 0.0;
    scene->snitch_rotation_ownaxis = 0.0;
    
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

void update_scene(Scene* scene, double time)
{
     scene->snitch_rotation += 100.0 * time; 
     scene->harry_rotation += 50.0 * time;
     scene->snitch_rotation_ownaxis += 1000.0 * time;
     
}

void set_lighting()  
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

    /*BASE*/
    glPushMatrix();
    glTranslatef(0.75, 5.87, 0);
    glRotatef(90, 50, 1, 1);
    glBindTexture(GL_TEXTURE_2D, scene->base_texture_id);
    draw_model(&(scene->base));
    glPopMatrix();
    
    /*HARRY*/
    glPushMatrix();
    glRotatef(scene->harry_rotation, 0, 0, 1);
    glRotatef(scene->harry_rotation, 0.3, 0, 1);
    glTranslatef(0, 2, 1);
    glRotatef(90, 50, 1, 1);
    glBindTexture(GL_TEXTURE_2D, scene->harry_texture_id);
    draw_model(&(scene->harry));
    glPopMatrix();

    /*SNITCH*/
    glPushMatrix();  
    glRotatef(scene->snitch_rotation, 0, 0, 1);
    glTranslatef(0.0, -1.2, 1.8);
    glRotatef(scene->snitch_rotation_ownaxis, 0, 0, 1);
    glRotatef(scene->snitch_rotation_ownaxis, 1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, scene->snitch_texture_id);
    draw_model(&(scene->snitch));
    glPopMatrix();
}

void draw_help(int texture) {


    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    
    glBindTexture(GL_TEXTURE_2D, texture);
    glLoadIdentity();
    glColor3f(1, 1, 1);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1.99, 1.5, -3);
    glTexCoord2f(1, 0);
    glVertex3f(1.99, 1.5, -3);
    glTexCoord2f(1, 1);
    glVertex3f(1.99, -1.5, -3);
    glTexCoord2f(0, 1);
    glVertex3f(-1.99, -1.5, -3);
    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    
}


