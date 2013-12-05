#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <iostream>
#include <vector>

#include "extra.h"
#include "camera.h"
#include "vecmath.h"
#include "Boid.h"
#include "Rules.h"

using namespace std;

// Globals here.
namespace
{
    Rules* rules;
    Camera camera;
    float CAMERA_DISTANCE = 60;
    float NUM_BOIDS = 50;
    bool birdseye = false;

    #define groundImageWidth 64
    #define groundImageHeight 64
    static GLubyte groundImage[groundImageHeight][groundImageWidth][4];
    static GLuint groundTexture;
    #define skyImageWidth 64
    #define skyImageHeight 64
    static GLubyte skyImage[skyImageHeight][skyImageWidth][4];
    static GLuint skyTexture;

    // static GLuint groundTex;
    // static GLubyte groundImage[imageWidth][imageHeight][4];

    void initSystem(int argc, char * argv[])
    {
        rules = new Rules;
        for(int i=0; i < NUM_BOIDS; i++)
        {
            Vector3f p = Vector3f(rand() % (MAX_X * 2) - MAX_X, rand() % (MAX_Y * 2) - MAX_Y, rand() % (MAX_Z * 2) - MAX_Z);
            Vector3f v = Vector3f(((float)rand() / RAND_MAX / RAND_MAX), ((float)rand() / RAND_MAX / RAND_MAX), ((float)rand() / RAND_MAX / RAND_MAX));
            rules->boids.push_back(new Boid(p, v.normalized()));
        }
        rules->N = rules->boids.size();
    }

void makeGroundImage(void)
{
   int i, j, c;
    
   for (i = 0; i < groundImageHeight; i++) {
      for (j = 0; j < groundImageWidth; j++) {
         // c = ((((i&0x8)==0)^((j&0x8))==0))*255;
         groundImage[i][j][0] = (GLubyte) 0;
         groundImage[i][j][1] = (GLubyte) 153;
         groundImage[i][j][2] = (GLubyte) 0;
         groundImage[i][j][3] = (GLubyte) 255;
      }
   }
}

void makeSkyImage(void)
{
   int i, j, c;
    
   for (i = 0; i < groundImageHeight; i++) {
      for (j = 0; j < groundImageWidth; j++) {
         // c = ((((i&0x8)==0)^((j&0x8))==0))*255;
         skyImage[i][j][0] = (GLubyte) 0;
         skyImage[i][j][1] = (GLubyte) 0;
         skyImage[i][j][2] = (GLubyte) 153;
         skyImage[i][j][3] = (GLubyte) 255;
      }
   }
}

void init(void)
{    
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   glEnable(GL_DEPTH_TEST);

   makeGroundImage();
   makeSkyImage();

   // Ground

   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   glGenTextures(1, &groundTexture);
   glBindTexture(GL_TEXTURE_2D, groundTexture);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
                   GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                   GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, groundImageWidth, 
                groundImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 
                groundImage);

   // Sky

   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   glGenTextures(1, &skyTexture);
   glBindTexture(GL_TEXTURE_2D, skyTexture);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
                   GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                   GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, skyImageWidth, 
                skyImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 
                skyImage);
}



  // Draw the current particle positions
  void drawSystem()
  {

    // Base material colors (they don't change)
    GLfloat particleColor[] = {0.4f, 0.7f, 1.0f, 1.0f};
    GLfloat floorColor[] = {1.0f, 0.0f, 0.0f, 1.0f};
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, particleColor);
    
    // CALL DRAW STUFF HERE
    for(int i=0; i < rules->N; i++)
    {
        if (!birdseye || i != 0) {
            if (i == 0) 
            {
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, floorColor);
                rules->boids.at(i)->draw();
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, particleColor);
            } 
            else
            {
                rules->boids.at(i)->draw();
            }
        }
    }

    glBegin(GL_LINES);
    glVertex3f(30,30,30);
    glVertex3f(30,30,-30);
    glVertex3f(30,-30,30);
    glVertex3f(30,-30,-30);
    glVertex3f(-30,30,30);
    glVertex3f(-30,30,-30);
    glVertex3f(-30,-30,30);
    glVertex3f(-30,-30,-30);
    glVertex3f(30,30,30);
    glVertex3f(30,-30,30);
    glVertex3f(30,30,30);
    glVertex3f(-30,30,30);
    glVertex3f(30,30,-30);
    glVertex3f(-30,30,-30);
    glVertex3f(30,30,-30);
    glVertex3f(30,-30,-30);
    glVertex3f(30,-30,30);
    glVertex3f(-30,-30,30);
    glVertex3f(-30,-30,-30);
    glVertex3f(-30,30,-30);
    glVertex3f(-30,30,30);
    glVertex3f(-30,-30,30);
    glVertex3f(-30,-30,-30);
    glVertex3f(30,-30,-30);
    glEnd();

    // glEnable(GL_TEXTURE_2D);
    // glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    // glBindTexture(GL_TEXTURE_2D, texName);
    // glBegin(GL_QUADS);
    // glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, -1.0, 0.0);
    // glTexCoord2f(0.0, 1.0); glVertex3f(-2.0, 1.0, 0.0);
    // glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 1.0, 0.0);
    // glTexCoord2f(1.0, 0.0); glVertex3f(0.0, -1.0, 0.0);
    // glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -1.0, 0.0);
    // glTexCoord2f(0.0, 1.0); glVertex3f(1.0, 1.0, 0.0);
    // glTexCoord2f(1.0, 1.0); glVertex3f(2.41421, 1.0, -1.41421);
    // glTexCoord2f(1.0, 0.0); glVertex3f(2.41421, -1.0, -1.41421);
    // glEnd();
    // glFlush();
    // glDisable(GL_TEXTURE_2D);


    float groundEdge = 600;
    float cubeHeight = 200;

    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, groundTexture);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-groundEdge, -cubeHeight, -groundEdge);
    glTexCoord2f(0.0, 1.0); glVertex3f(-groundEdge, -cubeHeight, groundEdge);
    glTexCoord2f(1.0, 1.0); glVertex3f(groundEdge, -cubeHeight, groundEdge);
    glTexCoord2f(1.0, 0.0); glVertex3f(groundEdge, -cubeHeight, -groundEdge);

    glEnd();
    glFlush();

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, skyTexture);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-groundEdge, -cubeHeight, -groundEdge);
    glTexCoord2f(0.0, 1.0); glVertex3f(groundEdge, -cubeHeight, -groundEdge);
    glTexCoord2f(1.0, 1.0); glVertex3f(groundEdge, groundEdge, -groundEdge);
    glTexCoord2f(1.0, 0.0); glVertex3f(-groundEdge, groundEdge, -groundEdge);

    glTexCoord2f(0.0, 0.0); glVertex3f(groundEdge, -cubeHeight, -groundEdge);
    glTexCoord2f(0.0, 1.0); glVertex3f(groundEdge, -cubeHeight, groundEdge);
    glTexCoord2f(1.0, 1.0); glVertex3f(groundEdge, groundEdge, groundEdge);
    glTexCoord2f(1.0, 0.0); glVertex3f(groundEdge, groundEdge, -groundEdge);

    glTexCoord2f(0.0, 0.0); glVertex3f(-groundEdge, -cubeHeight, groundEdge);
    glTexCoord2f(0.0, 1.0); glVertex3f(-groundEdge, -cubeHeight, -groundEdge);
    glTexCoord2f(1.0, 1.0); glVertex3f(-groundEdge, groundEdge, -groundEdge);
    glTexCoord2f(1.0, 0.0); glVertex3f(-groundEdge, groundEdge, groundEdge);

    glTexCoord2f(0.0, 0.0); glVertex3f(groundEdge, -cubeHeight, groundEdge);
    glTexCoord2f(0.0, 1.0); glVertex3f(-groundEdge, -cubeHeight, groundEdge);
    glTexCoord2f(1.0, 1.0); glVertex3f(-groundEdge, groundEdge, groundEdge);
    glTexCoord2f(1.0, 0.0); glVertex3f(groundEdge, groundEdge, groundEdge);

    glTexCoord2f(0.0, 0.0); glVertex3f(groundEdge, groundEdge, -groundEdge);
    glTexCoord2f(0.0, 1.0); glVertex3f(groundEdge, groundEdge, groundEdge);
    glTexCoord2f(1.0, 1.0); glVertex3f(-groundEdge, groundEdge, groundEdge);
    glTexCoord2f(1.0, 0.0); glVertex3f(-groundEdge, groundEdge, -groundEdge);

    glEnd();
    glFlush();
    glDisable(GL_TEXTURE_2D);

    
    // glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, floorColor);
    // glPushMatrix();
    // glTranslatef(0.0f,-30.0f,0.0f);
    // glScaled(60.0f,0.01f,60.0f);
    // glutSolidCube(1);
    // glPopMatrix();
    // glPushMatrix();
    // glTranslatef(0.0f,30.0f,0.0f);
    // glScaled(60.0f,0.01f,60.0f);
    // glutSolidCube(1);
    // glPopMatrix();
    
  }
    //-------------------------------------------------------------------
    
    

void stepSystem()
  {
    rules->update_boids();
    
    /*cout << "Start" << endl;
    cout << "Start Position" << endl;
    for(int i=0; i < 10; i++)
    {
        Boid* b = rules->boids.at(i);
        cout << b->getPosition().x() << "," << b->getPosition().y() << "," << b->getPosition().z() << endl;
    }
    cout << "Start Velocity" << endl;
    for(int i=0; i < 10; i++)
    {
        Boid* b = rules->boids.at(i);
        cout << b->getVelocity().x() << "," << b->getVelocity().y() << "," << b->getVelocity().z() << endl;
    }*/
  }

  void toggleBirdseye()
  {
    birdseye = !birdseye;
  }

    // These are state variables for the UI
    bool g_mousePressed = false;

    // Declarations of functions whose implementations occur later.
    void arcballRotation(int endX, int endY);
    void keyboardFunc( unsigned char key, int x, int y);
    void specialFunc( int key, int x, int y );
    void mouseFunc(int button, int state, int x, int y);
    void motionFunc(int x, int y);
    void reshapeFunc(int w, int h);
    void drawScene(void);
    void initRendering();

    // This function is called whenever a "Normal" key press is
    // received.
    void keyboardFunc( unsigned char key, int x, int y )
    {
        switch ( key )
        {
        case 27: // Escape key
            exit(0);
            break;
        case ' ':
        {
            camera.SetCenter( Vector3f::ZERO );
            camera.SetDistance( CAMERA_DISTANCE );
            break;
        }
        case 'b':
        {
            toggleBirdseye();
            break;
        }
        default:
            cout << "Unhandled key press " << key << "." << endl;        
        }

        glutPostRedisplay();
    }

    // This function is called whenever a "Special" key press is
    // received.  Right now, it's handling the arrow keys.
    void specialFunc( int key, int x, int y )
    {
        switch ( key )
        {

        }
        //glutPostRedisplay();
    }

    //  Called when mouse button is pressed.
    void mouseFunc(int button, int state, int x, int y)
    {
        if (state == GLUT_DOWN)
        {
            g_mousePressed = true;
            
            switch (button)
            {
            case GLUT_LEFT_BUTTON:
                camera.MouseClick(Camera::LEFT, x, y);
                break;
            case GLUT_MIDDLE_BUTTON:
                camera.MouseClick(Camera::MIDDLE, x, y);
                break;
            case GLUT_RIGHT_BUTTON:
                camera.MouseClick(Camera::RIGHT, x,y);
            default:
                break;
            }                       
        }
        else
        {
            camera.MouseRelease(x,y);
            g_mousePressed = false;
        }
        glutPostRedisplay();
    }

    // Called when mouse is moved while button pressed.
    void motionFunc(int x, int y)
    {
        camera.MouseDrag(x,y);        
    
        glutPostRedisplay();
    }

    // Called when the window is resized
    // w, h - width and height of the window in pixels.
    void reshapeFunc(int w, int h)
    {
        camera.SetDimensions(w,h);

        camera.SetViewport(0,0,w,h);
        camera.ApplyViewport();

        // Set up a perspective view, with square aspect ratio
        glMatrixMode(GL_PROJECTION);

        camera.SetPerspective(100);
        glLoadMatrixf( camera.projectionMatrix() );
    }

    // Initialize OpenGL's rendering modes
    void initRendering()
    {
        glEnable(GL_DEPTH_TEST);   // Depth testing must be turned on
        glEnable(GL_LIGHTING);     // Enable lighting calculations
        glEnable(GL_LIGHT0);       // Turn on light #0.

        glEnable(GL_NORMALIZE);

        // Setup polygon drawing
        glShadeModel(GL_SMOOTH);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        // Clear to black
        glClearColor(0,0,0,1);
    }

    // This function is responsible for displaying the object.
    void drawScene(void)
    {
        // Clear the rendering window
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode( GL_MODELVIEW );  
        glLoadIdentity();              

        // Light color (RGBA)
        GLfloat Lt0diff[] = {1.0,1.0,1.0,1.0};
        GLfloat Lt0pos[] = {3.0,3.0,5.0,1.0};
        glLightfv(GL_LIGHT0, GL_DIFFUSE, Lt0diff);
        glLightfv(GL_LIGHT0, GL_POSITION, Lt0pos);

        if (birdseye) 
        {
            Vector3f pos = rules->boids[0]->getPosition();
            Vector3f vel = rules->boids[0]->getVelocity();
            gluLookAt(pos[0], pos[1], pos[2], pos[0]+vel[0], pos[1]+vel[1], pos[2]+vel[2], 0, 1, 0);
        }
        else {
            glLoadMatrixf( camera.viewMatrix() );
        }

        // THIS IS WHERE THE DRAW CODE GOES.

        drawSystem();

        // This draws the coordinate axes when you're rotating, to
        // keep yourself oriented.
        if( g_mousePressed )
        {
            glPushMatrix();
            Vector3f eye = camera.GetCenter();
            glTranslatef( eye[0], eye[1], eye[2] );

            // Save current state of OpenGL
            glPushAttrib(GL_ALL_ATTRIB_BITS);

            // This is to draw the axes when the mouse button is down
            glDisable(GL_LIGHTING);
            glLineWidth(3);
            glPushMatrix();
            // glScaled(5.0,5.0,5.0);
            glBegin(GL_LINES);
            glColor4f(1,0.5,0.5,1); glVertex3f(0,0,0); glVertex3f(1,0,0);
            glColor4f(0.5,1,0.5,1); glVertex3f(0,0,0); glVertex3f(0,1,0);
            glColor4f(0.5,0.5,1,1); glVertex3f(0,0,0); glVertex3f(0,0,1);

            glColor4f(0.5,0.5,0.5,1);
            glVertex3f(0,0,0); glVertex3f(-1,0,0);
            glVertex3f(0,0,0); glVertex3f(0,-1,0);
            glVertex3f(0,0,0); glVertex3f(0,0,-1);

            glEnd();
            glPopMatrix();

            glPopAttrib();
            glPopMatrix();
        }
                 
        // Dump the image to the screen.
        glutSwapBuffers();
    }

    void timerFunc(int t)
    {
        stepSystem(); //CALL SYSTEM STEP HERE

        glutPostRedisplay();

        glutTimerFunc(t, &timerFunc, t);
    }

}


// Main routine.
// Set up OpenGL, define the callbacks and start the main loop
int main( int argc, char* argv[] )
{
    glutInit( &argc, argv );

    // We're going to animate it, so double buffer 
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

    // Initial parameters for window position and size
    glutInitWindowPosition( 60, 60 );
    glutInitWindowSize( 1200, 1200 );
    
    camera.SetDimensions( 2000, 2000 );

    camera.SetCenter( Vector3f::ZERO );
    camera.SetDistance( CAMERA_DISTANCE );
    
    glutCreateWindow("Boids");

    // Initialize OpenGL parameters.
    initRendering();

    // Setup particle system
    initSystem(argc,argv);

    // Set up callback functions for key presses
    glutKeyboardFunc(keyboardFunc); // Handles "normal" ascii symbols
    glutSpecialFunc(specialFunc);   // Handles "special" keyboard keys

    // Set up callback functions for mouse
    glutMouseFunc(mouseFunc);
    glutMotionFunc(motionFunc);

    // Set up the callback function for resizing windows
    glutReshapeFunc( reshapeFunc );

    // Call this whenever window needs redrawing
    glutDisplayFunc( drawScene );

    // Trigger timerFunc every 20 msec
    glutTimerFunc(100, timerFunc, 100);

    init();

    // Start the main loop.  glutMainLoop never returns.
    glutMainLoop();

    return 0;    // This line is never reached.
}


