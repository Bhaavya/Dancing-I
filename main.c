#include <stdlib.h>
#include <stdio.h>

#include <GLUT/glut.h>
#include <OpenGl/gl.h>
#include <OpenGl/glu.h>
#include <math.h>
#include <time.h>
void disp();                                /* Render function */
void redraw(int v);
void keyb(unsigned char key, int x, int y); /* Keboard handler */

static int win;            /* Window identifier */
static float time1=1;         /* Current time */
static int wired_only = 0; /* Render wireframe only */
static int t=0;
static int side=0;
static int rotx=0,roty=0,rotz=0;
static int tr=0;
static float sin_va=0,sin_vb=0,sin_vc=0,sin_vd=0,sin_ha=0,sin_hb=0,sin_hc=0,sin_hd=0;
static int up=0;
int nFPS = 32;
static int c= 0,r,g,b,r1,g1,b1;
clock_t startClock=0,curClock;
long long int prevF=0,curF=0;
int main(int argc, char * argv[]) {
    /* Initialize GLUT */
    glutInit(&argc, argv);
    /* RGBA, Double-buffered, with depth buffer */
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
    /* Initialize the window to be 800x600 at (200,200) */
    glutInitWindowSize(800,600);
    glutInitWindowPosition(100,100);
    /* Create the window; titled 'Dance' */
    win = glutCreateWindow("DANCE!");
    /* Register the display, keyboard, and timer functions */
    glutDisplayFunc(disp);
    glutKeyboardFunc(keyb);
    glutTimerFunc(50,redraw,0);
    /* Set the clear color to blue */
    glClearColor(0.0,0.0,0.8,0.0);
    /* Set orthographic*/
    glOrtho(-4.0,4.0,-4.0,4.0,-4.0,4.0);
    glMatrixMode(GL_MODELVIEW);
    
    
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND); /* (which requires blend mode to be enabled*/
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glLineWidth(2.0); /* Set the line width to 2 for thicker lines*/
    glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);
    /* And use the best available line hinting*/
    
    startClock=clock();
    glutMainLoop(); /* Start the loop */
    
    return 0;
}

void redraw(int v) {
    
    time1+=0.2;

    glutPostRedisplay();
    
    glutTimerFunc(1000/nFPS,redraw,v);
    
}

void draw(int how,float r, float g, float b) {
    
    if(rotx)
        glRotatef(0.5,1.0, 0.0, 0.0);
    if(roty)
        glRotatef(0.5,0.0, 1.0, .0);
    if(rotz)
     glRotatef(0.5,0.0, 0.0, 1.0);
    
   
    if(side)
    {
        sin_ha = sin(time1+1.4);
        sin_hb =  sin(time1+0.4);
        sin_hc = sin(time1-1.4);
        sin_hd =  sin(time1-0.4);
    }
    else
        sin_ha=sin_hb=sin_hc=sin_hd=0;
    if(up)
    {
        sin_va = sin(time1-1.1);
        sin_vb =  sin(time1-0.1);
        sin_vc = sin(time1+0.1);
        sin_vd =  sin(time1+1.1);
    }
    else
        sin_va=sin_vb=sin_vc=sin_vd=0;
    glBegin(how);
    glColor3f(r+0.8,g+0.8,b+0.8);
    glVertex3f(-1.5+sin_ha,2.5+sin_va ,0.0);
    glColor3f(r+0.85,g+0.85,b+0.85);
    glVertex3f(1.5+sin_ha,2.5+sin_vd ,0.0);
    glVertex3f(1.5+sin_hb,1.5+sin_vd,0.0);
    glColor3f(r+0.8,g+0.8,b+0.8);
    glVertex3f(0.5+sin_hb,1.5+sin_vc,0.0);
    glVertex3f(-0.5+sin_hb,1.5+sin_vb,0.0);
    glVertex3f(-1.5+sin_hb,1.5+sin_va,0.0);
    glEnd();
    /*  |  */
    glBegin(how);
    glColor3f(r+0.7,g+0.7,b+0.7);
    glVertex3f(-0.5+sin_hb,1.5+sin_vb,0.0);
    glVertex3f(0.5+sin_hb,1.5+sin_vc,0.0);
    glColor3f(r+0.6,g+0.6,b+0.6);
    glVertex3f(0.5+sin_hc,-1.5+sin_vc ,0.0);
    glVertex3f(-0.5+sin_hc,-1.5+sin_vb,0.0);
    glEnd();
    
    glBegin(how);
    glColor3f(r+0.3,g+0.3,b-0.3);
    glVertex3f(-1.5+sin_hd,-2.5+sin_va,0.0);
    glColor3f(r+0.4,g+0.4,b+0.4);
    glVertex3f(1.5+sin_hd,-2.5+sin_vd ,0.0);
    glVertex3f(1.5+sin_hc,-1.5+sin_vd ,0.0);
    glColor3f(r+0.5,g+0.5,b+0.5);
    glVertex3f(0.5+sin_hc,-1.5+sin_vc ,0.0);
    glVertex3f(-0.5+sin_hc,-1.5+sin_vb ,0.0);
    glVertex3f(-1.5+sin_hc,-1.5+sin_va ,0.0);
    glEnd();
    
    
    /* === */
    
}

void disp() {
    /* Set colors */
    switch (c)
    {     case 0: r=1.2,g=0.0;b=1.2;glClearColor(0.0,0.0,0.8,0.0);
            r1=0.0;g1=0.0,b1=0.8;
            break;
        case 1: r=1.2; g=0.5;b=0.0;glClearColor(0.2,0.4,0.0,0.0);
            r1=0.2;g1=0.4,b1=0.0;
            break;
        case 2: r=0.5; g=1.2;b=0.0;glClearColor(0.5,0.0,0.0,0.0);
            r1=0.5;g1=0.0,b1=0.0;
            break;
        case 3: r=1.2; g=1.2; b=0.5;glClearColor(0.0,0.0,0.8,0.0);
            r1=0.0;g1=0.0,b1=0.8;
            break;
    }
    
    curF++;
    glClear(GL_COLOR_BUFFER_BIT);
    if (!wired_only) {
        /* Render the filled-in polygons */
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
        
        draw(GL_TRIANGLE_FAN,r,g,b);
        /*Render the lines to make the edges smooth*/
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        
        draw(GL_LINE_LOOP,r,g,b);
    } else {
        
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
        
        draw(GL_TRIANGLE_FAN,r,g,b);
        /* Render the wireframe */
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        
        draw(GL_TRIANGLE_FAN,r1,g1,b1);
    }
    /* Flip the back buffer */
    glutSwapBuffers();
    curClock=clock();
    float elapsed=(curClock-startClock)/(float)CLOCKS_PER_SEC;
    if(elapsed>1.0f){
        float fps=(float)(curF-prevF)/elapsed;
        printf("fps:%f\n",fps);
        prevF=curF;
        startClock=curClock;
    }
}

void keyb(unsigned char key, int x, int y) {
    if (key == 27) {
        glutDestroyWindow(win);
        exit(0);}
    else if (key == 'w')
        wired_only = !wired_only;
    
    
    else if(key =='h')
        side=!side;
    else if(key=='v')
        up=!up;
    else if(key=='x')
        rotx=!rotx;
    else if(key=='y')
        roty=!roty;
    else if(key=='z')
        rotz=!rotz;
    else if(key=='t')
        tr=!tr;
    else if(key=='c')
        c=(c+1)%4;
    else if(key=='+')
        nFPS+=20;
    else if(key=='-')
        if(nFPS>21)
        nFPS-=20;
    
    
}
