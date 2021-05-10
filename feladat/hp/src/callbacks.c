#include "callbacks.h"

#include "obj/draw.h"
#include <obj/load.h>
#include <GL/glut.h>

#define VIEWPORT_RATIO (4.0 / 3.0)
#define VIEWPORT_ASPECT 50.0

float ambient_light[] = { 0.8f, 0.8f, 0.8f, 1.0f };

struct {
    int x;
    int y;
} mouse_position;

int help_on = 0;

void display()
{
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    

    glPushMatrix();
    set_view(&camera);
    draw_scene(&scene);
    glPopMatrix();

    if (is_preview_visible) {
        show_texture_preview();
    }

    if(help_on)
    {
        glLoadIdentity();    
                
        gluOrtho2D(0, 640, 480, 0);
                
        draw_help(scene.help_texture_id);

        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    }

    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO) {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(VIEWPORT_ASPECT, VIEWPORT_RATIO, 0.01, 10000.0);
}

void mouse(int button, int state, int x, int y)
{
    mouse_position.x = x;
    mouse_position.y = y;
}

void motion(int x, int y)
{
    rotate_camera(&camera, mouse_position.x - x, mouse_position.y - y);
    mouse_position.x = x;
    mouse_position.y = y;
    glutPostRedisplay();
}

void specialKeyHandler(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_F1:
            if(help_on == 1)
			{
				help_on = 0;
			}
			else help_on = 1;
            
    }
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 'w':
        set_camera_speed(&camera, 3);
        break;
    case 's':
        set_camera_speed(&camera, -3);
        break;
    case 'a':
        set_camera_side_speed(&camera, 3);
        break;
    case 'd':
        set_camera_side_speed(&camera, -3);
        break;
    case 't':
        if (is_preview_visible) {
            is_preview_visible = FALSE;
        }
        else {
            is_preview_visible = TRUE;
        }
        break;

    case '+':
        if (ambient_light[0] < 1.0)
            ambient_light[0] = ambient_light[1] = ambient_light[2] += 0.05;
            glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
		break;
	case '-':	
        if (ambient_light[0] > 0.0)
			ambient_light[0] = ambient_light[1] = ambient_light[2] -= 0.05 ;
            glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
		break;
    }

    glutPostRedisplay();
}

void keyboard_up(unsigned char key, int x, int y)
{
    switch (key) {
    case 'w':
    case 's':
        set_camera_speed(&camera, 0.0);
        break;
    case 'a':
    case 'd':
        set_camera_side_speed(&camera, 0.0);
        break;
    }

    glutPostRedisplay();
}


void idle()
{
    static int last_frame_time = 0;
    int current_time;
    double elapsed_time;
   
    current_time = glutGet(GLUT_ELAPSED_TIME);
    elapsed_time = (double)(current_time - last_frame_time) / 1000;
    last_frame_time = current_time;

    update_camera(&camera, elapsed_time);

    update_scene(&scene, elapsed_time);

    glutPostRedisplay();
}
