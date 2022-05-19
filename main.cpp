 #define GL_SILENCE_DEPRECATION
 #include <math.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 #include <unistd.h>
 #include <string.h>
 #include <sstream>
 #include <iostream>
#include<bits/stdc++.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include<windows.h>

using namespace std;

double r,centerX,centerY,x=0,y,p;

void draw_axis(){
    for (int i=-500;i<=500;i++){
        glVertex2d(0,i);
    }
    for (int i=-520;i<=750;i++){
        glVertex2d(i, 0);
    }
}


void init(){
    glClearColor(1.0, 1.0, 1.0, 0);
    glColor3f(0.0f, 1.0f, 0.0f);
    gluOrtho2D(-520, 640, -440, 480);
}


void bresenham_circle_drawing(){
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_POINTS);
    draw_axis();
    glEnd();
    glFlush();
    glColor3f(0.0,0.0,1.0);

    x=0;
    y=r;
    p=3-2*r;
    while(x<=y){

        glBegin(GL_POINTS);
        glVertex2d(centerX+x, centerY+y);
        glVertex2d(centerX+y, centerY+x);

        glVertex2d(centerX-y, centerY+x);
        glVertex2d(centerX-x, centerY+y);

        glVertex2d(centerX-x, centerY-y);
        glVertex2d(centerX-y, centerY-x);

        glVertex2d(centerX+y, centerY-x);
        glVertex2d(centerX+x, centerY-y);
        glEnd();
        glFlush();
        if (p<0){
            p = p + 4*x + 6;
        }else{
            p = p + 4*(x-y) + 10;
            y--;
        }
        x++;
    }
}

void input(){
    cout<<"Enter the Radius"<<endl;
    cin>>r;
    cout<<"Co-ordinate of Center: "<<endl;
    cin>>centerX>>centerY;
}


int main(int argc,char ** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 480);
    input();
    glutCreateWindow("Bresenham Circle Drawing Algorithm");
    init();
    glutDisplayFunc(bresenham_circle_drawing);
    //glutMouseFunc(onMouseClick);
    glutMainLoop();


}


