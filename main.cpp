
#include<GL/glut.h>
#include<stdio.h>
#include<iostream>
using namespace std;

int xc, yc, r;
float borderColor[3] = {1.0, 0.0, 0.0};
float fillColor[3] = {0.0, 1.0, 0.0};

void setPixel(int x, int y, float color[3])
{
    glBegin(GL_POINTS);
    glColor3fv(color);
    glVertex2i(x,y);
    glEnd();
    glFlush();
}

void getPixel(int x, int y, float pixels[3])
{
    glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,pixels);
}

Tareq Rahman Khukon
void plotPoint(int x, int y)
{
    glBegin(GL_POINTS);

    glVertex2i(xc+x, yc+y);
    glVertex2i(xc-x, yc+y);
    glVertex2i(xc+x, yc-y);
    glVertex2i(xc-x, yc-y);
    glVertex2i(xc+y, yc+x);
    glVertex2i(xc-y, yc+x);
    glVertex2i(xc+y, yc-x);
    glVertex2i(xc-y, yc-x);

    glEnd();
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

bool colorMatch(float firstColor[3], float secondColor[3]){
    if(firstColor[0]==secondColor[0] && firstColor[1]==secondColor[1] && firstColor[2]==secondColor[2])
        return true;
    else
        return false;
}

void boundaryFill4(int x, int y, float fColor[3], float border[3])
{
    float currentPixelColor[3];
    getPixel(x, y, currentPixelColor);
//    if(currentPixelColor[0]!=fColor[0] && currentPixelColor[1]!=fColor[1] && currentPixelColor[2]!=fColor[2] &&
//       currentPixelColor[0]!=border[0] && currentPixelColor[1]!=border[1] && currentPixelColor[2]!=border[2])
    if (!colorMatch(currentPixelColor, fColor) && !colorMatch(currentPixelColor, border))
    {
        setPixel(x, y, fColor);
        boundaryFill4(x, y-1, fColor, border);
        boundaryFill4(x, y+1, fColor, border);
        boundaryFill4(x-1, y, fColor, border);
        boundaryFill4(x+1, y, fColor, border);
    }
}

void draw_circle()
{
    int x = 0;
    int y = r;
    int d = 3 - 2*r;
    plotPoint(x, y);
    while(y>x)
    {
        if(d<0)
        {
            x++;
            d = d + 4*x + 6;
        }
        else
        {
            x++;
            y--;
            d = d + 4*(x-y)+10;
        }
        plotPoint(x, y);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3fv(borderColor);
    draw_circle();
    boundaryFill4(xc, yc, fillColor, borderColor);
    glFlush();
}


int main(int argc, char **argv)
{
    cout << "Enter the coordinate of the circle [x, y]: ";
    cin >> xc;
    cin >> yc;
    cout << "Enter your radious: "; cin >> r;

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Boundary Fill");
    init();
    glutDisplayFunc(display);
//    glutMouseFunc(mouseEvent);
    glutMainLoop();
}
