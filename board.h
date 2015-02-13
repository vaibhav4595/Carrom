#ifndef __BOARD_INCLUDED_H__
#define __BOARD_INCLUDED_H__
#include<iostream>
#ifdef __APPLE__
#include<OpenGL/OpenGL.h>
#include<GLUT/glut.h>
#else
#include<GL/glut.h>
#endif
#include<cmath>
#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)
using namespace std;

class Box
{
    public:
    float boxOuterLen;
    float boxInnerLen;
    float pocketRad;
    float center[2];
    float outerRadius;
    float innerRadius;
    float strikeAreaLength;
    float strikeAreaWidth;
    float arrowLength;
    float arrowAngle;

    Box();
    void createCircle(float rad, int start, int end);
    void createOuterBox();
    void createInnerBox();
    void createPockets();
    void createOuterCircle();
    void createInnerCircle();
    void createStrikeArea();
    void createSmallCircle(float arg1, float arg2, int start, int end);
    void createArrowUtil();
    void createArrow(float arg1, float arg2, float start, float end);
    void createTri(float arg1, float arg2, float arg3, float arg4, float arg5, float arg6);
};

Box::Box()
{
    boxOuterLen = 1.2f;
    boxInnerLen = 1.0f;
    pocketRad = 0.08f;
    center[0] = 0.0f;
    center[1] = 0.0f;
    outerRadius = 0.12f;
    innerRadius = 0.02f;
    strikeAreaLength = 0.6f;
    strikeAreaWidth = 0.04f;
    arrowAngle = 45;
    arrowLength = 0.25f;
}

void Box::createOuterBox()
{
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(0.759f,0.550f,0.250f);
    glVertex2f(-boxOuterLen/2, -boxOuterLen/2);
    glVertex2f(boxOuterLen/2, -boxOuterLen/2);
    glVertex2f(boxOuterLen/2, boxOuterLen/2);
    glVertex2f(-boxOuterLen/2, boxOuterLen/2);
    glEnd();
    glPopMatrix();
}
    
void Box::createInnerBox()
{
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(0.872f,0.754f,0.394f);
    glVertex2f(-boxInnerLen/2, -boxInnerLen/2);
    glVertex2f(boxInnerLen/2, -boxInnerLen/2);
    glVertex2f(boxInnerLen/2, boxInnerLen/2);
    glVertex2f(-boxInnerLen/2, boxInnerLen/2);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-boxInnerLen/2, -boxInnerLen/2);
    glVertex2f(boxInnerLen/2, -boxInnerLen/2);
    glVertex2f(boxInnerLen/2, boxInnerLen/2);
    glVertex2f(-boxInnerLen/2, boxInnerLen/2);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPopMatrix();
}

void Box::createPockets()
{
    glPushMatrix();
    glTranslatef(-boxInnerLen/2, -boxInnerLen/2, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0f, 0.0f, 0.0f);
    for(int i = 0 ; i <= 90 ; i++) 
        glVertex2f(pocketRad * cos(DEG2RAD(i)), pocketRad * sin(DEG2RAD(i)));
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(pocketRad, 0.0f);
    glVertex2f(0.0f, pocketRad);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(boxInnerLen/2, -boxInnerLen/2, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0f, 0.0f, 0.0f);
    for(int i = 90 ; i <= 180 ; i++) 
        glVertex2f(pocketRad * cos(DEG2RAD(i)), pocketRad * sin(DEG2RAD(i)));
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(-pocketRad, 0.0f);
    glVertex2f(0.0f, pocketRad);
    glEnd(); 
    glPopMatrix();

    glPushMatrix();
    glTranslatef(boxInnerLen/2, boxInnerLen/2, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0f, 0.0f, 0.0f);
    for(int i = 180 ; i <= 270 ; i++) 
        glVertex2f(pocketRad * cos(DEG2RAD(i)), pocketRad * sin(DEG2RAD(i)));
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(-pocketRad, 0.0f);
    glVertex2f(0.0f, -pocketRad);
    glEnd(); 
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-boxInnerLen/2, boxInnerLen/2, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0f, 0.0f, 0.0f);
    for(int i = 270 ; i <= 360 ; i++) 
        glVertex2f(pocketRad * cos(DEG2RAD(i)), pocketRad * sin(DEG2RAD(i)));
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(pocketRad, 0.0f);
    glVertex2f(0.0f, -pocketRad);
    glEnd(); 
    glPopMatrix();
}

void Box::createOuterCircle()
{
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 0.0f, 0.0f);
    for(int i = 0 ; i <= 360 ; i++)
        glVertex2f(outerRadius * cos(DEG2RAD(i)), outerRadius * sin(DEG2RAD(i)));
    glEnd();
    glLineWidth(1.0f);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i <= 360; i++)
        glVertex2f((outerRadius - 0.02f) * cos(DEG2RAD(i)), (outerRadius - 0.02f) * sin(DEG2RAD(i)));
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0.45678, 0.11234 , 0.66677);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.02f, 0.02f);
    glVertex2f(0.0f, 0.10f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0.11234, 0.23441, 0.44532);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(-0.02f, 0.02f);
    glVertex2f(0.0f, 0.10f); 
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0.45678, 0.11234 , 0.66677);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(-0.02f, 0.02f);
    glVertex2f(-0.10f, 0.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.11234, 0.23441, 0.44532);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(-0.10f, 0.0f);
    glVertex2f(-0.02f, -0.02f); 
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0.45678, 0.11234 , 0.66677);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(-0.02f, -0.02f);
    glVertex2f(0.0f, -0.10f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.11234, 0.23441, 0.44532);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.02f, -0.02f);
    glVertex2f(0.0f, -0.10f); 
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0.45678, 0.11234 , 0.66677);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.02f, -0.02f);
    glVertex2f(0.10f, 0.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.11234, 0.23441, 0.44532);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.02f, 0.02f);
    glVertex2f(0.10f, 0.0f); 
    glEnd();


    glPopMatrix();
}

void Box::createInnerCircle()
{
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 0.0f, 0.0f);
    for(int i = 0; i <= 360; i++)
        glVertex2f(innerRadius * cos(DEG2RAD(i)), innerRadius * sin(DEG2RAD(i)));
    glEnd();
    glPopMatrix();
}

void Box::createStrikeArea()
{
    glPushMatrix();
    glTranslatef(0.0f, -0.4f, 0.0f);
    glLineWidth(1.7f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-strikeAreaLength/2, 0.0f);
    glVertex2f(strikeAreaLength/2, 0.0f);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-strikeAreaLength/2, strikeAreaWidth);
    glVertex2f(strikeAreaLength/2, strikeAreaWidth);
    glEnd();
    glPopMatrix();

    createSmallCircle(-strikeAreaLength/2, -0.4f + (strikeAreaWidth/2), 0, 360);
    createSmallCircle(strikeAreaLength/2, -0.4f + (strikeAreaWidth/2), 0, 360);
    
    glPushMatrix();
    glTranslatef(0.0f, 0.4f, 0.0f);
    glLineWidth(1.7f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-strikeAreaLength/2, 0.0f);
    glVertex2f(strikeAreaLength/2, 0.0f);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-strikeAreaLength/2, -strikeAreaWidth);
    glVertex2f(strikeAreaLength/2, -strikeAreaWidth);
    glEnd();
    glPopMatrix();

    createSmallCircle(-strikeAreaLength/2, 0.4f - (strikeAreaWidth/2), 0, 360);
    createSmallCircle(strikeAreaLength/2, 0.4f - (strikeAreaWidth/2), 0, 360);

    glPushMatrix();
    glTranslatef(0.4f, 0.0f, 0.0f);
    glLineWidth(1.7f);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, -strikeAreaLength/2);
    glVertex2f(0.0f, strikeAreaLength/2);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-strikeAreaWidth, -strikeAreaLength/2);
    glVertex2f(-strikeAreaWidth, strikeAreaLength/2);
    glEnd();
    glPopMatrix();
 
    createSmallCircle(0.4f - (strikeAreaWidth/2), strikeAreaLength/2, 0, 360);
    createSmallCircle(0.4f - (strikeAreaWidth/2), -strikeAreaLength/2, 0, 360);    

    glPushMatrix();
    glTranslatef(-0.4f, 0.0f, 0.0f);
    glLineWidth(1.7f);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, -strikeAreaLength/2);
    glVertex2f(0.0f, strikeAreaLength/2);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(strikeAreaWidth, -strikeAreaLength/2);
    glVertex2f(strikeAreaWidth, strikeAreaLength/2);
    glEnd();
    glPopMatrix();

    createSmallCircle(-0.4f + (strikeAreaWidth/2), strikeAreaLength/2, 0, 360);
    createSmallCircle(-0.4f + (strikeAreaWidth/2), -strikeAreaLength/2, 0, 360);

}

void Box::createArrowUtil()
{
    float len = 0.02f;
    float len2 = 0.01f;
    float arrx = len * cos(DEG2RAD(45));
    float arry = len * cos(DEG2RAD(45));

    createArrow(-0.4f, -0.4f, arrowLength * cos(DEG2RAD(arrowAngle)), arrowLength * sin(DEG2RAD(arrowAngle)));
    glPushMatrix();
    glTranslatef(-0.4f, -0.4f, 0.0f);
    createTri(-arrx, arry, -arrx, -arry, arrx, -arry);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.4f + arrowLength * cos(DEG2RAD(arrowAngle)), -0.4f + arrowLength * sin(DEG2RAD(arrowAngle)), 0.0f);
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 0.0f);
    createCircle(0.04f, -90, 180);
    glEnd();
    createTri(-0.04f - len2, 0.0f, -0.04f + len2, 0.0f, -0.04f, -len2);
    createTri(0.0f, -0.04f - len2, 0.0f, -0.04f + len2, -len2, -0.04f);
    glPopMatrix();
    
    createArrow(0.4f, -0.4f, -arrowLength * cos(DEG2RAD(arrowAngle)), arrowLength * sin(DEG2RAD(arrowAngle)));
    glPushMatrix();
    glTranslatef(0.4f, -0.4f, 0.0f);
    createTri(-arrx, -arry, arrx, -arry, arrx, arry);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.4f -arrowLength * cos(DEG2RAD(arrowAngle)), -0.4f + arrowLength * sin(DEG2RAD(arrowAngle)), 0.0f);
    glBegin(GL_LINE_STRIP);
    createCircle(0.04f, 0, 270);
    glEnd();
    createTri(0.04f - len2, 0.0f, 0.04f + len2, 0.0f, 0.04f, -len2);
    createTri(0.0f, -0.04f + len2, 0.0f, -0.04f - len2, len2, -0.04f);
    glPopMatrix();

    createArrow(0.4f, 0.4f, -arrowLength * cos(DEG2RAD(arrowAngle)), -arrowLength * sin(DEG2RAD(arrowAngle)));
    glPushMatrix();
    glTranslatef(0.4f, 0.4f, 0.0f);
    createTri(arrx, -arry, arrx, arry, -arrx, arry);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.4f - arrowLength * cos(DEG2RAD(arrowAngle)), 0.4f - arrowLength * sin(DEG2RAD(arrowAngle)), 0.0f);
    glBegin(GL_LINE_STRIP);
    createCircle(0.04f, 90, 360);
    glEnd();
    createTri(0.04f - len2, 0.0f, 0.04f + len2, 0.0f, 0.04f, len2);
    createTri(0.0f, 0.04f - len2, 0.0f, 0.04f + len2, len2, 0.04f);
    glPopMatrix();

    createArrow(-0.4f, 0.4f, arrowLength * cos(DEG2RAD(arrowAngle)), -arrowLength * sin(DEG2RAD(arrowAngle)));
    glPushMatrix();
    glTranslatef(-0.4f, 0.4f, 0.0f);
    createTri(arrx, arry, -arrx, arry, -arrx, -arry);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.4f + arrowLength * cos(DEG2RAD(arrowAngle)), 0.4f - arrowLength * sin(DEG2RAD(arrowAngle)), 0.0f);
    glBegin(GL_LINE_STRIP);
    createCircle(0.04f, -180, 90);
    glEnd();
    createTri(-0.04f - len2, 0.0f, -0.04f + len2, 0.0f, -0.04f, len2);
    createTri(0.0f, 0.04f - len2, 0.0f, 0.04f + len2, -len2, 0.04f);
    glPopMatrix();
}
void Box::createTri(float arg1, float arg2, float arg3, float arg4, float arg5, float arg6)
{
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(arg1, arg2);
    glVertex2f(arg3, arg4);
    glVertex2f(arg5, arg6);
    glEnd();
}
void Box::createArrow(float arg1, float arg2, float start, float end)
{
    glPushMatrix();
    glTranslatef(arg1, arg2, 0.0f);
    glLineWidth(1.3f);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(start, end);
    glEnd();
    glPopMatrix();

}
void Box::createSmallCircle(float arg1, float arg2, int start, int end)
{
    glPushMatrix();
    glTranslatef(arg1, arg2, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 0.0f, 0.0f);
    createCircle(strikeAreaWidth/2, 0, 360);
    glEnd();
    glLineWidth(3.0f);
    glBegin(GL_LINE_SMOOTH);
    glColor3f(0.0f, 0.0f, 0.0f);
    createCircle(strikeAreaWidth/2, start, end);
    glEnd();
    glPopMatrix();
}

void Box::createCircle(float rad, int start, int end)
{
    for(int i = start; i <= end; i++)
        glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
}

          
#endif

