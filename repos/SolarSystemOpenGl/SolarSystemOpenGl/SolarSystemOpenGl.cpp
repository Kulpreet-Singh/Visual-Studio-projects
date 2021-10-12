// SolarSystemOpenGl.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<stdio.h>
#include<stdlib.h>
#include <GL/glut.h>
#include<math.h>
#include<time.h>
#include <vector>
#include<windows.h>
#define PI 3.14

float angleMoon = 0.0, angleEarth = 0.0, angleAstroid = 0.0,
angleMars = 0.0,
angleMercury = 0.0,
angleVenus = 0.0,
angleJupiter = 0.0,
angleSaturn = 0.0,
angleUranus = 30.0,
angleNeptune = 60.0;
GLfloat sx = 0.2, sy = 0.2, sz = 0.2;
int planet1;
GLfloat black[] = { 0.0f,0.0f,0.0f,1.0f };
GLfloat white[] = { 1.0f,1.0f,1.0f,1.0f };
GLfloat blue[] = { 0.0f,0.0f,0.9f,1.0f };
GLfloat er[] = { 0.0f,5.0f,0.9f,1.0f };
GLfloat yellow[] = { 0.7f,0.2f,0.0f,1.0f };
GLfloat qAmb[] = { 0.1,0.1,0.1,1.0 };
GLfloat qDif[] = { 1.0,1.0,1.0,1.0 };
GLfloat qSpec[] = { .50,.50,.50,.10 };
GLfloat qPos[] = { 0,0,0,0.1 };
GLfloat sc[8] = { 0.295 , 0.40,0.50, 0.60,0.80,1.0,1.05,1.13 };
double ang = 2 * PI / 300;
double angular = 2 * PI / 50;
GLfloat pntX[] = { 0,0,0 };
GLfloat pntY[] = { 0,0,0 };

void initLighting()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT7);

    glLightfv(GL_LIGHT7, GL_AMBIENT, qAmb);
    glLightfv(GL_LIGHT7, GL_DIFFUSE, qDif);
    glLightfv(GL_LIGHT7, GL_SPECULAR, qSpec);

}


void myinit()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glPointSize(1.0);
    glLineWidth(2.0);

}

void drawSphere(double r, int lats, int longs) {
    int i, j;
    for (i = 0; i <= lats; i++) {
        double lat0 = PI * (-0.5 + (double)(i - 1) / lats);
        double z0 = sin(lat0);
        double zr0 = cos(lat0);

        double lat1 = PI * (-0.5 + (double)i / lats);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for (j = 0; j <= longs; j++) {
            double lng = 2 * PI * (double)(j - 1) / longs;
            double x = cos(lng);
            double y = sin(lng);

            glNormal3f(x * zr0, y * zr0, z0);
            glVertex3f(r * x * zr0, r * y * zr0, r * z0);
            glNormal3f(x * zr1, y * zr1, z1);
            glVertex3f(r * x * zr1, r * y * zr1, r * z1);
        }
        glEnd();
    }
}

void update(int value) {

    if ((angleMoon >= 0 && angleMoon < 180))
    {
        sx -= 0.0003; sy -= 0.0003; sz -= 0.0003;
    }
    else { sx += 0.0003; sy += 0.0003; sz += 0.0003; }


    angleMoon += 2;
    if (angleMoon > 360) {
        angleMoon -= 360;
    }
    angleEarth += 0.7;
    if (angleEarth > 360) {
        angleEarth -= 360;
    }
    angleMercury += 2;
    if (angleMercury > 360) {
        angleMercury -= 360;
    }
    angleVenus += 0.9;
    if (angleVenus > 360) {
        angleVenus -= 360;
    }
    angleMars += 0.5;
    if (angleMars > 360) {
        angleMars -= 360;
    }
    angleJupiter += 0.2;
    if (angleJupiter > 360) {
        angleJupiter -= 360;
    }
    angleSaturn += 0.1;
    if (angleSaturn > 360) {
        angleSaturn -= 360;
    }


    angleUranus += 0.05;
    if (angleUranus > 360) {
        angleUranus -= 360;
    }


    angleNeptune += 0.02;
    if (angleNeptune > 360) {
        angleNeptune -= 360;
    }


    angleAstroid += 0.002;
    if (angleAstroid > 360) {
        angleAstroid -= 360;
    }


    glutPostRedisplay();
    glutTimerFunc(20, update, 0);
}


void background()
{
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.00, 0.00);
    glVertex3f(-01.00, 01.00, 1);
    glColor3f(.20, 0.0, 0.70);
    glVertex3f(01.00, 1.00, 1);
    glColor3f(0, 0.0, 0.0);
    glVertex3f(1.00, -1.00, 1);
    glColor3f(.70, .10, .20);
    glVertex3f(-1.00, -1.00, 1);
    glEnd();
}
void rotating(float x, float a, float b, float c) {
    glRotatef(x, a, b, c);
    return;
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0.0);
    for (int i = 0; i < 3; i++)
    {
        glVertex2i((pntX[i] * cos(x)) - (pntY[i] * sin(x)), ((pntX[i] * sin(x)) + (pntY[i] * cos(x))));
    }
    glEnd();

}

void orbit()
{
    glColor3f(0.5, 0.5, 0.5);
    int i = 0;
    for (i = 0; i < 8; i++) {
        glPushMatrix();
        if (i == 5)
        {
            glRotatef(45, 1.0, 0.0, 0.0);
        }
        else
        {
            rotating(63, 1.0, 0.0, 0.0);
        }
        glScalef(sc[i], sc[i], sc[i]);
        glBegin(GL_POINTS);
        double ang1 = 0.0;
        int i = 0;
        for (i = 0; i < 300; i++)
        {
            glVertex2d(cos(ang1), sin(ang1));
            ang1 += ang;
        }
        glEnd();
        glPopMatrix();
    }
}


void draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    background();
    orbit();
    glLoadIdentity();
    glPushMatrix();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glPushMatrix();
    glColor3f(0.7, 0.5, 0.0);
    glScalef(sx, sy, sz);
    glLightfv(GL_LIGHT7, GL_POSITION, qPos);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, yellow);
    drawSphere(1, 50, 50);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
    glPopMatrix();

    glScalef(0.2, 0.2, 0.2);
    glPushMatrix();
    rotating(angleMercury, 0.0, 1.0, -0.5);
    glTranslatef(1.5, 0.0, 0.0);
    glColor3f(1.0, 0.9, 0.0);
    drawSphere(0.08, 50, 50);
    glPopMatrix();

    glPushMatrix();
    rotating(angleVenus, 0.0, 1.0, -0.5);
    glTranslatef(2.0, 0.0, 0.0);
    glColor3f(0.9, 0.1, 0.0);
    drawSphere(0.1, 50, 50);
    glPopMatrix();

    glPushMatrix();
    rotating(angleEarth, 0.0, 1.0, -0.5);
    glTranslatef(2.5, 0.0, 0.0);
    glColor3f(0.0, 0.1, 0.7);
    drawSphere(0.23, 50, 50);
    glPopMatrix();

    glPushMatrix();
    rotating(angleMars, 0.0, 1.0, -0.5);
    glTranslatef(-3.0, 0.0, 0.0);
    glColor3f(0.05, 0.05, 0.01);
    drawSphere(0.17, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glColor3f(165, 42, 42);
    rotating(63, 1.0, 0.0, 0.0);
    int j = 0, i = 0, div = 90; float siz = 2;
    float scl[4] = { 3.3,3.4,3.35,3.2 };
    for (j = 0; j < 4; j++)
    {
        glPushMatrix(); siz -= 0.3;
        glPointSize(siz);
        glScalef(scl[j], scl[j], scl[j]);
        glBegin(GL_POINTS);
        double ang1 = 0.0 - angleAstroid, a = (2 * PI) / div;
        for (i = 0; i < div; i++)
        {
            glVertex2d(cos(ang1), sin(ang1));
            ang1 += a;
        }
        div += 10;
        glEnd();
        glPopMatrix();
    }
    glPopMatrix();

    glPushMatrix();
    rotating(angleJupiter, 0.0, 1.0, -0.5);
    glTranslatef(-4.0, 0.0, 0.0);
    glColor3f(0.4, 0.2, 0.0);
    drawSphere(0.5, 50, 50);
    glPopMatrix();

    glPushMatrix();
    rotating(angleSaturn, 0.0, 1.0, -1.0);
    glTranslatef(-5.0, 0.0, 0.0);
    glColor3f(0.9, 0.0, 0.0);
    glScalef(0.4, 0.4, 0.4);
    glutSolidSphere(1, 50, 50);
    glPushMatrix();
    glRotatef(45, 1.0, 0.0, 0.0);
    glPointSize(3);
    glColor3f(5.0, 3.0, 1.0);
    glScalef(1.2, 1.2, 1.2);
    glBegin(GL_POINTS);
    double ang1 = 0.0;
    i = 0;
    for (i = 0; i < 50; i++)
    {
        glVertex2d(cos(ang1), sin(ang1));
        ang1 += angular;
    }
    glEnd();

    glPointSize(2);
    glPopMatrix();
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    rotating(angleUranus, 0.0, 1.0, -0.5);
    glTranslatef(5.2, 0.0, 0.0);
    glColor3f(0.0, 0.5, 0.9);
    drawSphere(0.23, 50, 50);
    glPopMatrix();

    glPushMatrix();
    rotating(angleNeptune, 0.0, 1.0, -0.5);
    glTranslatef(-5.7, 0.0, 0.0);
    glColor3f(0.0, 0.0, 0.9);
    drawSphere(0.2, 50, 50);
    glPopMatrix();


    glPopMatrix();
    glFlush();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(700, 700);
    glutCreateWindow("Solar System");
    initLighting();
    myinit();
    glutDisplayFunc(draw);
    glutTimerFunc(25, update, 0);
    glutMainLoop();
    return 0;
}

