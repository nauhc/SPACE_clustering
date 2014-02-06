//This tutorial demostrates how to use GLExtension::GLVertexBuffer
// 
#include <QApplication>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <memory>
#include "CLaMS.h"
using namespace std;

int window_width = 800;
int window_height = 600;
int mouseX=0, mouseY=0;
int	mousetype = -1;
float scale = 1.0f;
float xRotate=0.0f, yRotate=0.0f;
float xTranslate=0, yTranslate=0, zTranslate=-5.0f;

string clamsPuyehueFilePath	= "./data/clams/CLaMS_Puyehue.vtk.bin";
std::shared_ptr<CLaMS> clamsPuyehue;

void keyboard(unsigned char key, int x, int y){
    switch(key) 
    {
        case 'w':
            printf("W key pressed!\n");
            break;
        case(27) :
            printf("ESC key pressed!\n");
            exit(0);

        case 'I':{
            clamsPuyehue->setCurActivePathLineId(clamsPuyehue->getCurActivePathLineId()
                +clamsPuyehue->getMaxPathlineToShow());
            break;
                 }
        case 'i':{
            clamsPuyehue->setCurActivePathLineId(clamsPuyehue->getCurActivePathLineId()
                -clamsPuyehue->getMaxPathlineToShow());
            break;
                 }
    }
}

void mouseMotion(int x , int y){
    if (mousetype == GLUT_LEFT_BUTTON)
    {
        yRotate += (x-mouseX)*0.5f;
        xRotate += (y-mouseY)*0.5f;
        yRotate = int(yRotate)%360;
        xRotate = int(xRotate)%360;
        printf("xRotate=%f, yRotate=%f\n",xRotate,yRotate);
    }else if (mousetype == GLUT_MIDDLE_BUTTON)
    {
        xTranslate += (x-mouseX)*0.005f;
        yTranslate += (mouseY-y)*0.005f;
        printf("xTranslate=%f, yTranslate=%f, zTranslate=%f\n",xTranslate,yTranslate,zTranslate);
    }
    mouseX = x;
    mouseY = y;   
}
void mouseButton(int button, int state, int x , int y){
    printf("mouse button(%d) x=%d, y=%d\n",button,x,y);
    if (button == GLUT_LEFT_BUTTON)
    {
        //add response when left mouse button is pressed.
        printf("Left mouse button clicked!\n");
    }else if (button == GLUT_MIDDLE_BUTTON)
    {
        //add response when right mouse button is pressed.
        printf("Middle mouse button clicked!\n");
    }else if (button == GLUT_RIGHT_BUTTON)
    {
        //add response when right mouse button is pressed.
        printf("Right mouse button clicked!\n");
    }

    mouseX = x; mouseY = y;
    mousetype = button;
}
void mouseWheel(int button, int dir, int x, int y){
    if (dir > 0)
    {
        // Zoom in
        scale *= 0.8f;
    }
    else
    {
        // Zoom out
        scale /= 0.8f;
    }
   
    cout << "scale "<<scale<<endl;
    return;
}
bool initGL(){
    glewInit();
    if (! glewIsSupported(
        "GL_VERSION_2_0 " 
        "GL_ARB_pixel_buffer_object "
        "GL_EXT_framebuffer_object "
        ))
    {
        fprintf(stderr, "ERROR: Support for necessary OpenGL extensions missing.");
        fflush(stderr);
        return false;
    }
    glClearColor(0,0,0,1.0);

    glViewport(0,0,window_width, window_height);

    //Load CLaMS data.
    clamsPuyehue = shared_ptr<CLaMS>(new CLaMS());
    if (clamsPuyehue)
    {
        clamsPuyehue->load(clamsPuyehueFilePath);
    }
    return true;
}
void reshape(int w, int h){
    window_width = w; window_height = h;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, (float)w/h, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void display(){
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
        glTranslatef(xTranslate,yTranslate,zTranslate);
        glRotatef(xRotate, 1,0,0);
        glRotatef(yRotate, 0,1,0);
        glScalef(scale, scale, scale);

        glLineWidth(1.0);
        glutWireCube(2);
        glColor3f(1,0,0);
        clamsPuyehue->draw();

    glutSwapBuffers();
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    QApplication a(argc, argv);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("Simple GLUT");

    if (!initGL())
    {
        return 0;
    }
    //register callbacks
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMotion);
    glutMouseWheelFunc(mouseWheel);

    glutMainLoop();

    return 0;
}