#ifndef __COLLISION_INCLUDED_H__
#define __COLLISION_INCLUDED_H__
#ifdef __APPLE__
#include<OpenGL/OpenGL.h>
#include<GLUT/glut.h>
#else
#include<GL/glut.h>
#endif
#include<cmath>
#include "board.h"
#include "common.h"
#include "coins.h"
#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)
int checkPocketed(Play arr[], Box mybox, int i, Flag *f)
{
    if((arr[i].x <= 0.5f) && (arr[i].x >= 0.5f - 0.08f) && (arr[i].y <= 0.5f) && (arr[i].y >= 0.5f - 0.08f))
    {
        arr[i].x = -1.0f;
        arr[i].y = f->coinLevel;
        arr[i].velx = 0.0f;
        arr[i].vely = 0.0f;
        arr[i].status = 1;
        f->coinLevel -= 0.10f;
        return 1;
    }
    if((arr[i].x <= -0.5f + 0.08f) && (arr[i].x >= -0.5f) && (arr[i].y <= 0.5f) && (arr[i].y >= 0.5f - 0.08f))
    {
        arr[i].x = -1.0f;
        arr[i].y = f->coinLevel;
        arr[i].velx = 0.0f;
        arr[i].vely = 0.0f;
        arr[i].status = 1;
        f->coinLevel -= 0.10f;
        return 1;
    }
    if((arr[i].x <= -0.5f + 0.08f) && (arr[i].x >= -0.5f) && (arr[i].y <= -0.5f + 0.08f) && (arr[i].y >= -0.5f))
    {
        arr[i].x = -1.0f;
        arr[i].y = f->coinLevel;
        arr[i].velx = 0.0f;
        arr[i].vely = 0.0f;
        arr[i].status = 1;
        f->coinLevel -= 0.10f;
        return 1;
    }
    if((arr[i].x <= 0.5f) && (arr[i].x >= 0.5f - 0.08f) && (arr[i].y <= -0.5f + 0.08f) && (arr[i].y >= -0.5f))
    {
        arr[i].x = -1.0f;
        arr[i].y = f->coinLevel;
        arr[i].velx = 0.0f;
        arr[i].vely = 0.0f;
        arr[i].status = 1;
        f->coinLevel -= 0.10f;
        return 1;
    }
    return 0;
}    
void strikeStriker(Striker *s, Power p, Power2 *p2, Flag *f)
{
    float factor = p2->level / 20;
    s->velx = cos(DEG2RAD(p.angle)) * (factor);
    s->vely = sin(DEG2RAD(p.angle)) * (factor);
    f->strikerLine = 1;
    p2->level = 0.0f;
}

void detectWallCollision(Striker *s, Box mybox, Flag *f, Play arr[])
{

    if(s->radius + s->x > mybox.boxInnerLen/2 || s->x - s->radius < -mybox.boxInnerLen/2)
        s->velx *= -1;
    if(s->radius + s->y > mybox.boxInnerLen/2 || s->y - s->radius < -mybox.boxInnerLen/2)
        s->vely *= -1;
    
    if(((s->x <= 0.5f) && (s->x >= 0.5f - 0.08f) && (s->y <= 0.5f) && (s->y >= 0.5f - 0.08f)) || ((s->x <= -0.5f + 0.08f) && (s->x >= -0.5f) && (s->y <= 0.5f) && (s->y >= 0.5f - 0.08f))|| ((s->x <= -0.5f + 0.08f) && (s->x >= -0.5f) && (s->y <= -0.5f + 0.08f) && (s->y >= -0.5f)) || ((s->x <= 0.5f) && (s->x >= 0.5f - 0.08f) && (s->y <= -0.5f + 0.08f) && (s->y >= -0.5f)))
    {
        s->velx = 0;
        s->vely = 0;
        s->x = 0.0f;
        s->y = -(0.4f - (0.04f)/2);
        f->points -= 5;
        f->display = "Comment : OH NO! You hit the striker in the pocket, so you lose some points";
    }       
    s->x += s->velx;
    s->y += s->vely;

    s->velx *= 0.983;
    s->vely *= 0.983;

        

    if(((s->velx < 0.0001f) && (s->velx > -0.0001f)) && ((s->vely < 0.0001f) && (s->vely > -0.0001f)))
    {
        if(f->strikerLine == 1)
        {
            s->velx = s->vely = 0.0f;
            s->x = 0.0f;
            s->y = -(0.4f - (0.04f)/2);
            f->strikerLine = 0;
            f->hit = 0;
        }
    }

    
}
void detectCoinCollision(Play arr[], Striker *s, Box mybox, Flag *f)
{
    float distance;
    int i, j;

    for(i = 0; i < 9; i++)
    {
        distance = sqrt(pow(s->x - arr[i].x, 2) + pow(s->y - arr[i].y, 2));
        if(distance < s->radius + arr[i].radius)
        {
           float xdistance = s->x - arr[i].x;
           float ydistance = s->y - arr[i].y;
           float normalx = xdistance / distance;
           float normaly = ydistance / distance;
           float tangenty = normalx;
           float tangentx = -normaly;
           float ball1ScalarNormal = (normalx * (s->velx)) + (normaly * (s->vely));
           float ball2ScalarNormal = (normalx * (arr[i].velx)) + (normaly * (arr[i].vely));
           float ball1ScalarTangential = (tangentx * (s->velx)) + (tangenty * (s->vely));
           float ball2ScalarTangential = (tangentx * (arr[i].velx)) + (tangenty * (arr[i].vely));
           float ball1ScalarNormalAfter = (ball1ScalarNormal * (s->mass - arr[i].mass) + 2 * arr[i].mass * ball2ScalarNormal) / (arr[i].mass + s->mass);
           float ball2ScalarNormalAfter = (ball2ScalarNormal * (arr[i].mass - s->mass) + 2 * s->mass * ball1ScalarNormal) / (arr[i].mass + s->mass);
           s->velx = normalx*ball1ScalarNormalAfter + tangentx*ball1ScalarTangential;
           s->vely = normaly*ball1ScalarNormalAfter + tangenty*ball1ScalarTangential;
           arr[i].velx = normalx*ball2ScalarNormalAfter + tangentx*ball2ScalarTangential;
           arr[i].vely = normaly*ball2ScalarNormalAfter + tangenty*ball2ScalarTangential;
           arr[i].velx *= 1.1;
           arr[i].vely *= 1.1;
           s->velx *= 0.99;
           s->vely *= 0.99;
           if(f->mode == 0)
           {
               if(arr[i].type == 1)
                   f->display = "Comment : You just hit a black piece :)";
               else if(arr[i].type == 2)
                   f->display = "Comment : You just hit a white piece :)";
               else if(arr[i].type == 3)
                   f->display = "Comment : You just hit The Red Queen :o";
           }
           else if(f->mode == 1)
           {
               if(f->hit == 0)
               {
                   f->hit = 1;
                   if(arr[i].type == 1)
                       f->display = "Comment : You hit the black piece :)";
                   if(arr[i].type == 2)
                   {
                       f->display = "Comment : You hit the wrong piece, white, you lose few points :(";
                       f->points -= 3;
                   }
                   if(arr[i].type == 3)
                       f->display = "Comment : You just hit The red Queen :o";
               }
           }
           else if(f->mode == 2)
           {
               if(f->hit == 0)
               {
                   f->hit = 1;
                   if(arr[i].type == 1)
                   {
                       f->display = "Comment : You hit the wrong piece, black piece :(";
                       f->points -= 3;
                   }
                   if(arr[i].type == 2)
                       f->display = "Comment : You hit the white piece :)";
                   if(arr[i].type == 3)
                       f->display = "Comment : You just hit The red Queen :o";
               }
           }
                   
        }
    }
    for(i = 0; i < 9; i++)
    {

        for(j = 0; j < 9; j++)
        {
            if(i != j)
            {
                distance = sqrt(pow(arr[i].x - arr[j].x, 2) + pow(arr[i].y - arr[j].y, 2));
                if(distance < arr[i].radius + arr[j].radius)
                {
                float xdistance = arr[i].x - arr[j].x;
                float ydistance = arr[i].y - arr[j].y;
                float normalx = xdistance / distance;
                float normaly = ydistance / distance;
                float tangenty = normalx;
                float tangentx = -normaly;
                float ball1ScalarNormal = (normalx * (arr[i].velx)) + (normaly * (arr[i].vely));
                float ball2ScalarNormal = (normalx * (arr[j].velx)) + (normaly * (arr[j].vely));
                float ball1ScalarTangential = (tangentx * (arr[i].velx)) + (tangenty * (arr[i].vely));
                float ball2ScalarTangential = (tangentx * (arr[j].velx)) + (tangenty * (arr[j].vely));
                float ball1ScalarNormalAfter = (ball1ScalarNormal * (arr[i].mass - arr[j].mass) + 2 * arr[j].mass * ball2ScalarNormal) / (arr[i].mass + arr[j].mass);
                float ball2ScalarNormalAfter = (ball2ScalarNormal * (arr[j].mass - arr[i].mass) + 2 * arr[i].mass * ball1ScalarNormal) / (arr[i].mass + arr[j].mass);
                arr[i].velx = normalx*ball1ScalarNormalAfter + tangentx*ball1ScalarTangential;
                arr[i].vely = normaly*ball1ScalarNormalAfter + tangenty*ball1ScalarTangential;
                arr[j].velx = normalx*ball2ScalarNormalAfter + tangentx*ball2ScalarTangential;
                arr[j].vely = normaly*ball2ScalarNormalAfter + tangenty*ball2ScalarTangential;
                arr[i].velx *= 1.1;
                arr[i].vely *= 1.1;
                arr[j].velx *= 0.99;
                arr[j].vely *= 0.99;
                }
            }
        }
        int check = checkPocketed(arr, mybox, i, f);
        if(check == 1)
        {
            if(f->mode == 0)
            {
                f->count += 1;
                if(arr[i].type == 1)
                {    
                    f->points += 10;
                    f->display = "Comment : You just earned a black piece :)";
                }
                else if(arr[i].type == 2)
                {
                    f->points += 20;
                    f->display = "Comment : You just earned a white piece :)";
                }
                else if(arr[i].type == 3)
                {
                    f->points += 50;
                    f->display = "Comment : You just earned The Red Queen :o";
                }
            }
            else if(f->mode == 1)
            {
               
                if(arr[i].type == 1)
                {
                    f->count += 1;    
                    f->points += 20;
                    f->display = "Comment : You just earned a black piece :)";
                }
                else if(arr[i].type == 2)
                {
                    f->points -= 5;
                    f->display = "Comment : You coined the WRONG PIECE, YOU COINED WHITE :(";
                }
                else if(arr[i].type == 3)
                {
                    f->count += 1;
                    f->points += 50;
                    f->display = "Comment : You just earned The Red Queen :o";
                }
            }
            else if(f->mode == 2)
            {
                if(arr[i].type == 1)
                {    
                    f->points -= 5;
                    f->display = "Comment : You coined the WRONG PIECE, YOU COINED BLACK :(";
                }
                else if(arr[i].type == 2)
                {
                    f->count += 1;
                    f->points += 20;
                    f->display = "Comment : You just earned a white piece :)";
                }
                else if(arr[i].type == 3)
                {
                    f->count += 1;
                    f->points += 50;
                    f->display = "Comment : You just earned The Red Queen :o";
                }
            }

        }
        if(f->count == 9 && f->mode == 0)
            exit(0);
        if(f->count == 5 && (f->mode == 1 || f->mode == 2))
            exit(0);
        if(arr[i].radius + arr[i].x >= mybox.boxInnerLen/2 || arr[i].x - arr[i].radius <= -mybox.boxInnerLen/2)
            arr[i].velx *= -1;
        if(arr[i].radius + arr[i].y >= mybox.boxInnerLen/2 || arr[i].y - arr[i].radius <= -mybox.boxInnerLen/2)
            arr[i].vely *= -1;

        arr[i].x += arr[i].velx;
        arr[i].y += arr[i].vely;
 
        arr[i].velx *= 0.96425;
        arr[i].vely *= 0.96425;

        if(((arr[i].velx < 0.0001f) && (arr[i].velx > -0.0001f)) && ((arr[i].vely < 0.0001f) && (arr[i].vely > -0.0001f)))
        {
            arr[i].velx = 0.0f;
            arr[i].vely = 0.0f;
        }  

    } 
}       
#endif

