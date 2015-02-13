#ifndef __COMMON_INCLUDED_H__
#define __COMMON_INCLUDED_H__
#ifdef __APPLE__
#include<OpenGL/OpenGL.h>
#include<GLUT/glut.h>
#else
#include<GL/glut.h>
#endif
#include<cmath>
#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)



class Flag
{
   public:
   int strikerLine;
   int start;
   float coinLevel; 
   int points;
   int timer;
   int count;
   int mode;
   int mouseFlag;
   float motionx;
   float motiony;
   int hit;
   string display;
   Flag();
};

Flag::Flag()
{
    strikerLine = 0;
    start = 0;
    coinLevel = 0.45f;
    points = 33;
    timer = 0;
    mouseFlag = 0;
    motionx = 0.0f;
    motiony = 0.0f;
    display = "Comment: Start Playing the Game";
    count = 0;
    mode = 0;
    hit = 0;
}
void createFilledCircle(float rad, int start, int end)
{
    for(int i = start; i <= end; i++)
        glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
}



#endif
