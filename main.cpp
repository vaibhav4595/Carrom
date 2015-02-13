#ifdef __APPLE__
#include <OpenGL/OpenGL.h> 
#include <GLUT/glut.h> 
#else
#include <GL/glut.h>
#endif
#include "board.h"
#include "coins.h"
#include "collision.h"
#include<cmath>
#include<cstring>
#include<iostream>
#include "common.h"
using namespace std;
void update(int);
void handleMouseClick2(int x, int y);
void handleMouseClick3(int x, int y);
void handleMouseClick4(int x, int y);
Box mybox;
Striker str;
Power P;
Power2 P2;
Flag f;
Play pieces[9];
void initGL() 
{
    glEnable(GL_COLOR_MATERIAL);   
    glClearColor(0.5f, 0.5f, 0.5f, 0.0f); 
}
void scoreDraw()
{
    glPushMatrix();
    glTranslatef(-0.1f, 0.7f, 0.0f);
    glColor3f(0.9f, 0.9f, 0.9f);
    glRasterPos2i(0.0f, 0.0f);
    string p;
    if(f.timer % 1000 == 0)
        f.points -= 1;
    int score = f.points;
    int arr[4];
    int j = 0;
    char sign;
    if(score == 0)
        p = "0";
    if(score < 0)
    {    
        sign = '-';
        score = -score;
    } 
    else if(score >= 0)
        sign = ' '; 
    while(score != 0)
    {
        arr[j++] = score%10 + '0';
        score /= 10;
    }
    p = p + sign;
    for(int k = j - 1; k >= 0; k--)
    {
        char ch;
        ch = arr[k];
        p = p + ch;
    }
    string s = "SCORE : " + p; 
    void *font = GLUT_BITMAP_HELVETICA_18;
    for(string::iterator i = s.begin(); i != s.end(); ++i)
    {
        char c = *i;
        glutBitmapCharacter(font, c);
    }
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.3f, 0.85f, 0.0f);
    glColor3f(0.88f, 0.88f, 0.88f);
    glRasterPos2i(0.0f, 0.0f);
    font = GLUT_BITMAP_HELVETICA_18;
    string q = f.display;
    for(string::iterator z = q.begin(); z != q.end(); ++z)
    {
        char c = *z;
        glutBitmapCharacter(font, c);
    }
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.2f, 0.5f, 0.0f);
    glColor3f(0.1f, 0.12f, 0.0f);
    glRasterPos2i(0.0f, 0.0f);
    font = GLUT_BITMAP_HELVETICA_18;
    string pocket = "Your Coins Pocketed";
    for(string::iterator z = pocket.begin(); z != pocket.end(); ++z)
    {
        char c = *z;
        glutBitmapCharacter(font, c);
    }
    glPopMatrix();
    string set;
    if(f.mode == 0)
        set = "MODE : NORMAL";
    if(f.mode == 1)
        set = "MODE : BLACK ONLY";
    if(f.mode == 2)
        set = "MODE : WHITE ONLY";

    glPushMatrix();
    glTranslatef(-1.2f, 0.8f, 0.0f);
    glColor3f(0.22f, 0.22f, 0.22f);
    glRasterPos2i(0.0f, 0.0f);
    font = GLUT_BITMAP_HELVETICA_18;
    for(string::iterator z = set.begin(); z != set.end(); ++z)
    {
        char c = *z;
        glutBitmapCharacter(font, c);
    }
    glPopMatrix();

    
}
void pieceDraw()
{
    if(f.start == 0)
    {
    float pockDis = sqrt((0.06f) * (0.06f));
    pockDis = 0.06 * (cos(DEG2RAD(45)));
    pieces[0].initi(0.06f, 0.0f, 1);
    pieces[1].initi(-0.06f, 0.0f, 1);
    pieces[2].initi(0.0f, 0.06f, 1);
    pieces[3].initi(0.0f, -0.06f, 1);
    pieces[4].initi(pockDis, pockDis, 2);
    pieces[5].initi(pockDis, -pockDis, 2);
    pieces[6].initi(-pockDis, pockDis, 2);
    pieces[7].initi(-pockDis, -pockDis, 2);
    pieces[8].initi(0.0f, 0.0f, 3);
    f.start = 1;
    }
    if(f.start == 1)
    {
        for(int i = 0; i < 9; i++)
            pieces[i].drawCoin();
    }
}
void drawScene() 
{
   glClear(GL_COLOR_BUFFER_BIT); 
   glMatrixMode(GL_MODELVIEW);      
   glLoadIdentity();               
 
   mybox.createOuterBox();
   mybox.createInnerBox();
   mybox.createPockets();

   mybox.createOuterCircle();
   mybox.createInnerCircle();
   mybox.createStrikeArea();

   mybox.createArrowUtil();
   
   P.drawPower(f, str);
   P2.drawPower2();
   str.drawStriker(f);
   pieceDraw();
   scoreDraw();  
   glutSwapBuffers();
}
 
void reshape(GLsizei width, GLsizei height) 
{  
   if (height == 0) height = 1;               
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   glViewport(0, 0, width, height);
 
   glMatrixMode(GL_PROJECTION);  
   glLoadIdentity();
   if (width >= height) 
      gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
   else 
      gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
   
}
 
void handleKeyPress2(int key, int x, int y)
{
    if(f.strikerLine == 0)
    {
    if(key == GLUT_KEY_LEFT)
        P.updateDirection(1);
    if(key == GLUT_KEY_RIGHT)
        P.updateDirection(-1);
    if(key == GLUT_KEY_DOWN)
        P2.updateLevel(-0.05f);
    if(key == GLUT_KEY_UP)
        P2.updateLevel(0.05f);
    }
}
void handleKeyPress(unsigned char key, int x, int y)
{
    if(f.strikerLine == 0)
    {
    if(key == 27)
        exit(0);
    if(key == 97)
    {
        str.x -= 0.005;
        P.updatePosition(str);
    }
    if(key == 100)
    {   
        str.x += 0.005;
        P.updatePosition(str);
    }
    if(key == 32)
    {
        strikeStriker(&str, P, &P2, &f);
    }
    }
}
void update(int value)
{
    detectWallCollision(&str, mybox, &f, pieces);
    detectCoinCollision(pieces, &str, mybox, &f);
    f.timer += 5;
    glutTimerFunc(10, update, 0);
}
void handleMouseclick(int button, int state, int x, int y) 
{
    if(f.strikerLine == 0)
    {
    if (state == GLUT_DOWN)
    { 
        if (button == GLUT_LEFT_BUTTON)
        {   
            glutMotionFunc(handleMouseClick2);
            f.mouseFlag = 1;
        }   
        else if (button == GLUT_RIGHT_BUTTON)
        {    
           glutMotionFunc(handleMouseClick3);
        }
    }
    if(state == GLUT_UP && (f.mouseFlag == 1) )
    {
        
        float gly = 2 * (1-float(y) / glutGet(GLUT_WINDOW_HEIGHT) - 0.5);
        f.mouseFlag = 0;
        f.motionx = 0.0f;
        f.motiony = 0.0f;
        if(gly > 0)
            P2.level = gly;
        if(gly < 0)
            P2.level = -gly;
        strikeStriker(&str, P, &P2, &f);
    }
    }  
}
void handleMouseClick2(int x, int y)
{
    float glx = (3.17)*(float(x)/glutGet(GLUT_WINDOW_WIDTH)- 0.5);
    float gly = 2*(1-float(y)/glutGet(GLUT_WINDOW_HEIGHT)-0.5);
    P.updateDirMouse(glx, gly);
    if(gly < 0)
        gly = 0.0f;
    if(gly > 0.5f)
        gly = 0.5f;
    P2.level = gly;
}
void handleMouseClick3(int x, int y)
{
    float glx = (3.17)*(float(x)/glutGet(GLUT_WINDOW_WIDTH)- 0.5);
    str.x = glx;
    P.updatePosition(str);
}
void handleMouseClick4(int x, int y)
{
    float gly = 2*(1-float(y)/glutGet(GLUT_WINDOW_HEIGHT)-0.5);
    if(gly > 0)
        P2.level = gly;
    if(gly < 0)
        P2.level = -gly;
}
int main(int argc, char** argv) 
{
   if(argc == 2)
   {
       if(strlen(argv[1]) == 1)
       {
           int mode = (int)(argv[1][0]) - '0';
           if(mode == 1 || mode == 2)
               f.mode = mode;
           else
           {
               cout << "WRONG MODE SUPPLIED" << endl;
               exit(0);
           }
       }
   }
   glutInit(&argc, argv);
   glutCreateWindow("Carrom Game");
   glutFullScreen();
   initGL();
   glutDisplayFunc(drawScene);
   glutIdleFunc(drawScene);
   glutKeyboardFunc(handleKeyPress);
   glutSpecialFunc(handleKeyPress2);
   glutMouseFunc(handleMouseclick);
   glutReshapeFunc(reshape);
   glutTimerFunc(10, update, 0);
   glutMainLoop();                
   return 0;
}
