#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define NUM_SLICES 24
#define NUM_SLICES2 3
#define CIRCLE_RADIUS 2.0f

float _angle = 0.0f; //for rotating the boat
float xpos = 0.0f; //for moving the boat in the x axis
float ypos = 0.0f; //for moving the boat in the y axis

float cameraHeight = -80.0f; //for zooming the camera

double thetaIncr = 2* (double) (22.0 / 7) / NUM_SLICES; //the angle per sector
double th = 0.0; //angle used to generate the points

void drawEmergencyLight()
{
  glTranslatef(0, 12, 0); //appoximate unit circle
  glColor3f(1.0f ,1.0f, 0.0f);
  glBegin(GL_LINE_LOOP);
    for (int i = 0; i < NUM_SLICES2; i++) {
      glVertex2f(cos(th), sin(th));
      th += thetaIncr;
    }

    glEnd();
}

void handleKeyPress(unsigned char key, int x, int y) {
  switch (key) {
    case 'c': _angle += 5.0f; break; //right rotate scene
    case 'x': _angle -= 5.0f; break; //left rotate scene
    case 's': cameraHeight -= 5.0f; break; //zoom into scene
    case 'w': cameraHeight += 5.0f; break; //zoom out scene
    case 'd': xpos += 1.0f; glPushMatrix(); glTranslatef(10, 50, 0); drawEmergencyLight(); glPopMatrix(); break; //move boats to right of screen
    case 'a': xpos -= 1.0f; break; //move boats to left side of screen
  }
  glutPostRedisplay();
}

//project init

void initRendering(void) {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_COLOR_MATERIAL);
  glClearColor(1, 1, 1, 0);
}

void handleResize (int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, (double) w / (double) h, 0.01, 500.0);
}

void drawBouy(void) {
  glBegin(GL_QUADS); //draw stripe on bouy
    glColor3f(1, 1, 1);
    glVertex3f(-2.25f, 0.5f, 0.0f);
    glVertex3f(0.35f, 0.5f, 0.0f);
    glVertex3f(0.35f, -0.5f, 0.0f);
    glVertex3f(-2.25f, -0.5f, 0.0f);
  glEnd();

  glBegin(GL_QUADS); //draws buoy
    glColor3f(1, 0.25, 0);
    glVertex3f(-2.25f, 1.25f, 0.0f);
    glVertex3f(0.25f, 1.25f, 0.0f);
    glVertex3f(0.25f, -1.25f, 0.0f);
    glVertex3f(-2.25f, -1.25f, 0.0f);
  glEnd();
}

void drawBoat(void) {
  glBegin(GL_QUADS); //draws base of boat
    glColor3f(0.196078, 0.8, 0.196078);
    glVertex3f(-3.75f, 2.0f, 0.0f);
    glVertex3f(8.75f, 2.0f, 0.0f);
    glVertex3f(5.75, -2.0f, 0.0f);
    glVertex3f(-3.75, -2.0f, 0.0f);
  glEnd();

  glBegin(GL_QUADS); //draws top of boat
    glColor3f(0.85824f, 0.439216f, 0.576471f);
    glVertex3f(-2.25f, 4.0f, 0.0f);
    glVertex3f(2.25f, 4.0f, 0.0f);
    glVertex3f(2.2f, -1.0f, 0.0f);
    glVertex3f(-2.25, -1.0f, 0.0f);
  glEnd();

  glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-3.0f, 1.0f, 0.0f);
    glVertex3f(3.0f, 1.0f, 0.0f);
    glVertex3f(3.0f, -1.0f, 0.0f);
    glVertex3f(-3.0f, -1.0f, 0.0f);
  glEnd();

  glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-4.5, 0.35, 0.0f);
    glVertex3f(4.5f, 0.35f, 0.0f);
    glVertex3f(4.5f, -0.35f, 0.0f);
    glVertex3f(-4.5f, -0.35f, 0.0f);
  glEnd();

  glBegin(GL_QUADS); //draws steam pipe on top of boat
    glColor3f(0.184314, 0.0309804, 0.309804);
    glVertex3f(-0.5f, 5.35f, 0.0f);
    glVertex3f(0.5f, 5.35f, 0.0f);
    glVertex3f(0.5f, 5.35f, 0.0f);
    glVertex3f(-0.5f, -0.35f, 0.0f);
  glEnd();
}

void drawBoatTwo(void){
  glBegin(GL_QUADS); //draws base of boat
    glColor3f(0.196078, 0.8, 0.196078);
    glVertex3f(-3.75f, 2.0f, 0.0f);
    glVertex3f(8.875, 2.0f, 0.0f);
    glVertex3f(5.75f, -2.0f, 0.0f);
    glVertex3f(-3.75f, -2.0f, 0.0f);
  glEnd();

  glBegin(GL_QUADS); //draws top of boat
    glColor3f(0.53, 0.12, 0.47);
    glVertex3f(-2.25, 4.0f, 0.0f);
    glVertex3f(4.25f, 4.0f, 0.0f);
    glVertex3f(4.25f, -1.0f, 0.0f);
    glVertex3f(-2.25f, -1.0f, 0.0f);
  glEnd();
}

//draws the scene
void drawBackground(void) {
  glColor3f(0.93f, 0.37f, 0.42f); //sky
  glBegin(GL_QUADS);
    glVertex3f(-1000.0f, 1000.0f, 0.0f);
    glVertex3f(-1000.0f, 0.0f, 0.0f);
    glVertex3f(1000.0f, 0.0f, 0.0f);
    glVertex3f(1000.0f, 1000.0f, 0.0f);
  glEnd();
}

void drawSun() {
  glTranslatef(0, 0, 0); //approximate unit circle with this
    int circle_points = 100;
    double PI = 3.1415926;
    double angle = 2*  PI/circle_points ;
    glPolygonMode( GL_FRONT, GL_FILL );
    glColor3f(1.0f, 1.0f, 0.0f );
    glBegin(GL_POLYGON);

    double angle1 = 0.0;
    glVertex2d( CIRCLE_RADIUS * cos(0.0) , CIRCLE_RADIUS * sin(0.0));

    int i;
    for (i = 0; i < circle_points; i++)
    {
        glVertex2d(CIRCLE_RADIUS * cos(angle1), CIRCLE_RADIUS *sin(angle1));
        angle1 += angle ;
    }
    glEnd();
}

void drawWater() {
  glColor3f(0.15, 0.43, 0.49);
  glBegin(GL_QUADS);
    glVertex3f(-1000.0f, 0.0f, 0.0f);
    glVertex3f(-1000.0f, -1000.0f, 0.0f);
    glVertex3f(1000.0f, -1000.0f, 0.0f);
    glVertex3f(1000.0f, 0.0f, 0.0f);
  glEnd();
}

void drawScene(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glRotatef(-_angle, 0.0f, 0.0f, 1.0f);
  glTranslatef(0.0f, 0.0f, cameraHeight);

  glPushMatrix();
    glTranslatef(0.0f, 15.0f, 0.0f);
    drawBackground();
    drawWater();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.0f, 17.0f, 0.0f);
    drawSun();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(10.0f, 4.0f, 0.0f);
    glTranslatef(xpos * 0.2, 0.2f, 0.0f);
    drawBoatTwo();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(1.0f, 10.0f, 0.0f);
    drawBouy();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(xpos, ypos, 0.0f);
    glTranslatef(-35.0f, 0.0f, 0.0f);
    drawBoat();
  glPopMatrix();

  drawEmergencyLight();

  glutSwapBuffers();
}

void update(int value) {
  _angle += 0.1f;

  if (_angle > 360) _angle -= 360;

  glutPostRedisplay();
  glutTimerFunc(16, update, 0);
}

int main(int argc, char* argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(640, 480);
  glutInitWindowPosition(400,200);

  glutCreateWindow("Boat Adventure");

  glutDisplayFunc(drawScene);
  glutKeyboardFunc(handleKeyPress);
  glutReshapeFunc(handleResize);

  glutMainLoop();
  return 0;
}
