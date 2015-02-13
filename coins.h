#ifndef __COINS_INCLUDED_H__
#define __COINS_INCLUDED_H__
#ifdef __APPLE__
#include<OpenGL/OpenGL.h>
#include<GLUT/glut.h>
#else
#include<GL/glut.h>
#endif
#include<cmath>
#include "board.h"
#include "common.h"
#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)
#define RAD2DEG(rad) ((180 / PI) * rad)
class Striker
{
    public:
    float radius;
    float x;
    float y;
    float velx;
    float vely;
    float dec;
    float mass;
    Striker();
    void drawStriker(Flag f);
};

class Power
{
    public:
    float length;
    float x;
    float y;
    int angle;

    Power();
    void updateLength();
    void updateDirection(int val);
    void updatePosition(Striker s);
    void drawPower(Flag f, Striker s);
    void updateDirMouse(float x, float y);
};

class Power2
{
    public:
    float width;
    float length;
    float level;
    float x, y;

    Power2();
    void drawPower2();
    void updateLevel(float val);
};
class Play
 {
     public:
     float x;
     float y;
     float velx;
     float vely;
     float radius;
     int type;
     int status;
     int stata;
     float mass;
     void initi(float x1, float y1, int t);
     void drawCoin();
 };
Power2::Power2()
{
    width = 0.05f;
    length = 0.5f;
    level = 0.0f;

}

void Power2::drawPower2()
{
    float temp = 0.0f;
    glPushMatrix();
    glTranslatef(0.75f, -0.6f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-width/2, 0.0f);
    glVertex2f(width/2, 0.0f);
    glVertex2f(width/2, level);
    glVertex2f(-width/2, level);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-width/2, 0.0f);
    glVertex2f(width/2, 0.0f);
    glVertex2f(width/2, length);
    glVertex2f(-width/2, length);
    glEnd();
    for(int i = 0; i < 10; i++)
    {
        glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 0.0f);    
        glVertex2f(width/2, temp);
        glVertex2f(-width/2, temp);
        temp += 0.05f;
        glEnd();
    }
    
    glPopMatrix();
}

void Power2::updateLevel(float val)
{
    level += val;
    if(abs(level) > 0.45f)
        level = 0.50f;
    else if(level < 0.05f )
        level = 0.0f;
}
Striker::Striker()
{
    y = -(0.4f - (0.04f)/2);
    x = 0.0f;
    radius = 0.04f;
    velx = 0.0f;
    vely = 0.0f;
    dec = 0.005f;
    mass = 2000;
}

void Striker::drawStriker(Flag f)
{
    if(f.strikerLine == 0)
{    if(x < -(0.6f)/2)
        x = -0.59/2;
    if(x > (0.6f)/2)
        x = 0.59/2;
}
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.5f, 0.1f, 0.0f);
    createFilledCircle(radius, 0, 360);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 0.0f, 0.0f); 
    createFilledCircle(radius, 0, 360);
    glEnd();
    glPopMatrix();
}

Power::Power()
{
    x = 0.0f;
    y = -(0.4f - (0.04f)/2);
    angle = 90;
    length = 0.15f;
}

void Power::drawPower(Flag f, Striker s)
{
    if(f.strikerLine == 0)
    {
        glPushMatrix();
        glTranslatef(s.x, s.y, 0.0f);
        glBegin(GL_LINES);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(length * cos(DEG2RAD(angle)), length * sin(DEG2RAD(angle)));
        glEnd();
        glPopMatrix();
    }
}
void Power::updateDirection(int val)
{
    if(angle <= 0)
        angle = 0;
    if(angle >= 180)
        angle = 180;
    angle += val;
}
void Power::updateDirMouse(float x1, float y1)
{
    float now = atan(y1 - y / x1 - x);
    if(now < 0)
        now = now + PI ;
    angle = RAD2DEG(now);
}
    
void Power::updatePosition(Striker s)
{
    x = s.x;
    y = s.y;
}     



void Play::initi(float x1, float y1, int t)
{
    x = x1;
    y = y1;
    radius = 0.02f;
    velx = 0.0f;
    vely = 0.0f;
    type = t;
    status = 0;
    stata = 0;
    mass = 1000;
}

void Play::drawCoin()
{
    float r, g, b;
    if(type == 1)
    {
        r = 0.0f;
        g = 0.0f;
        b = 0.0f;
    }
    else if(type == 2)
    {
        r = 1.0f;
        g = 1.0f;
        b = 1.0f;
    }
    else if(type == 3)
    {
        r = 0.7f;
        g = 0.0f;
        b = 0.0f;
    }
    
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(r, g, b);
    createFilledCircle(radius, 0, 360);
    glEnd();
    glPopMatrix();
}

#endif    
