// Programmer: Mihalis Tsoukalos
// Date: Wednesday 04 June 2014
//
// A simple OpenGL program that draws a colorful cube
// that rotates as you move the arrow keys!
//
// g++ cube.cc -lm -lglut -lGL -lGLU -o cube

#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>
#include "PermutationMap.h"
#include "Permutation.h"


// Rotate X
double rX=30;
// Rotate Y
double rY=30;

/*
Permutation Pf("(13 14 15 16)(134 145 156 136)(31 41 51 61)(314 415 516 613)(316 413 514 615)","f");
Permutation Px("(23 24 25 26)(234 245 256 236)(32 42 52 62)(324 425 526 623)(326 423 524 625)","x");
Permutation Pr("(41 43 42 45)(413 423 425 415)(14 34 24 54)(134 324 245 514)(145 314 234 524)","r");
Permutation Pl("(61 63 62 65)(613 623 625 615)(16 36 26 56)(136 326 256 516)(156 316 236 526)","l");
Permutation Pt("(31 36 32 34)(314 316 326 324)(13 63 23 43)(134 613 236 423)(136 623 234 413)", "t");
Permutation Pb("(51 56 52 54)(514 516 526 524)(15 65 25 45)(145 615 256 425)(156 625 245 415)", "b");
*/

Permutation ICrBase("(1 3 2 5)","r");
Permutation ICfBase("(3 4 5 6)","f");
Permutation ICtBase("(1 4 2 6)","t");

Permutation PERMs[24];
int CurrentPerm;

//Permutation PERM("","");
//Permutation PERM_real("","");  // before cycling index's

//TransTable transtable;

//std::vector<Permutation> index_cycles;
int current_index_cycle = 0;

// The coordinates for the vertices of the cube
double x = 0.6;
double y = 0.6;
double z = 0.6;

struct Color {
    float r;
    float g;
    float b;
};

Color colors[6] = { { 1, 1, 1},  // white
		    { 0, 0, 1},  // blue
		    { 0, 1, 0},  // green
		    { 1, .5, 0},  // orange
		    { 1, 1, 0},  // yellow
		    { 1, 0, 0} };  // red



float facesz = .4;
float facegap = 0;

struct FaceDef {
    float ox, oy, oz;
    float xx, xy, xz;
    float yx, yy, yz;
};

FaceDef facedefs[6] = {
    { -1, -1, 1,   1,0,0,   0,1,0 },
    { 1,-1, -1,    -1,0,0,   0,1,0 },
    { -1,1,-1,      0,0,1,  1,0,0 },
    { 1,-1,1,      0,0,-1,  0,1,0 },
    { -1,-1,1,     0,0,-1,  1,0,0 },
    { -1,-1,1,     0,1,0,    0,0,-1 }
};



void drawFace(int cube, int idx, float deltax, float deltay) {
    Face &face = DisplayFaces[idx];

    int sfid = PERMs[cube].getSourcePosition(face.id);

    //printf("(%d %d %d)\n", idx, face.id, sfid);
    
    int coloridx = ((sfid > 100) ? sfid/100 : ((sfid > 10) ? sfid/10 : sfid)) - 1;
    
    int faceidx = ((face.id > 100) ? face.id/100 : ((face.id > 10) ? face.id/10 : face.id)) - 1;
    //printf("[%d] id=%d face=%d\n", idx, face.id, faceidx+1);
    
    FaceDef &fd = facedefs[faceidx];


    
    float ox = (fd.ox * (facesz*3.0/2.0)) + facesz * (face.xpos * fd.xx + face.ypos * fd.yx) + deltax;
    float oy = (fd.oy * (facesz*3.0/2.0)) + facesz * (face.xpos * fd.xy + face.ypos * fd.yy) + deltay;
    float oz = (fd.oz * (facesz*3.0/2.0)) + facesz * (face.xpos * fd.xz + face.ypos * fd.yz);

    float p1x = ox + (facesz-facegap) * fd.xx;
    float p1y = oy + (facesz-facegap) * fd.xy;
    float p1z = oz + (facesz-facegap) * fd.xz;
	
    float p2x = p1x + (facesz-facegap) * fd.yx;
    float p2y = p1y + (facesz-facegap) * fd.yy;
    float p2z = p1z + (facesz-facegap) * fd.yz;


    float p3x = ox + (facesz-facegap) * fd.yx;
    float p3y = oy + (facesz-facegap) * fd.yy;
    float p3z = oz + (facesz-facegap) * fd.yz;


    glColor3f(colors[coloridx].r,colors[coloridx].g, colors[coloridx].b); 
    glBegin(GL_QUADS);
    glVertex3f(ox,oy,oz);
    glVertex3f(p3x,p3y,p3z);
    glVertex3f(p2x,p2y,p2z);
    glVertex3f(p1x,p1y,p1z);
    glEnd();
}

void drawText(const char *txt) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 1000, 0, 1000);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(1,1,1);
    glRasterPos2i(10,950);
    glutBitmapString(GLUT_BITMAP_9_BY_15, (unsigned char *)txt);

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

void reshape(int x, int y) {
    printf("call reshape\n");
    glutPostRedisplay();
}


void drawCube()
{
    static int first = 1000;
    printf("draw cube called\n");
    
    // Set Background Color
    glClearColor(0.4, 0.4, 0.4, 1.0);
    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    
    
    //glOrtho(-1,1,-1,1,-2,2);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0,0,16,0,0,0,0,1,0);
    glRotatef(rX,1,0,0);
    glRotatef(rY,0,-1,0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50,1,.1,50);
    
    int c = 0;

    for(int cube = 0;cube<24;cube++) {
	for(int i=0;i<9*6;i++) drawFace(cube, i, (-6 + (cube%6)*2), -3 + (cube/6) * 2);
    }
    
    drawText("hi there\n does the newline work?\n\nPerhaps?");
    
    glFlush();
    glutSwapBuffers();
}

void mykeys(unsigned char key, int x, int y) {
    static int d1 = -1;
    static int d2 = -1;
    printf("key = %d %d %d\n", key,x,y);
    //PERM = PERM_real;
    
    // if(key == 'C') {
    // 	current_index_cycle++;
    // 	current_index_cycle %= transtable.nFacePermutations();
    // 	PERM = transtable.getFacePermutation(current_index_cycle) * PERM;
    // }
    // else if (key == 'c') {
    // 	if(current_index_cycle == 0) current_index_cycle = transtable.nFacePermutations();
    // 	current_index_cycle--;
    // 	PERM = transtable.getFacePermutation(current_index_cycle) * PERM;
    // }
    // else {
    switch(key) {
    case 'f':
	PERMs[CurrentPerm] = (Permutation::Pf * PERMs[CurrentPerm]);
	break;
    case 'F':
	PERMs[CurrentPerm] = -Permutation::Pf * PERMs[CurrentPerm];
	break;
    case 'x':
	PERMs[CurrentPerm] = Permutation::Px * PERMs[CurrentPerm];
	break;
    case 'X':
	PERMs[CurrentPerm] = -Permutation::Px * PERMs[CurrentPerm];
	break;
    case 'r':
	PERMs[CurrentPerm] = Permutation::Pr * PERMs[CurrentPerm];
	break;
    case 'R':
	PERMs[CurrentPerm] = -Permutation::Pr * PERMs[CurrentPerm];
	break;
    case 'l':
	PERMs[CurrentPerm] = Permutation::Pl * PERMs[CurrentPerm];
	break;
    case 'L':
	PERMs[CurrentPerm] = -Permutation::Pl * PERMs[CurrentPerm];
	break;
    case 't':
	PERMs[CurrentPerm] = Permutation::Pt * PERMs[CurrentPerm];
	break;
    case 'T':
	PERMs[CurrentPerm] = -Permutation::Pt * PERMs[CurrentPerm];
	break;
    case 'b':
	PERMs[CurrentPerm] = Permutation::Pb * PERMs[CurrentPerm];
	break;
    case 'B':
	PERMs[CurrentPerm] = -Permutation::Pb * PERMs[CurrentPerm];
	break;
	
    case 'I':
	{
	    Permutation x("","I");
	    current_index_cycle = 0;
	    PERMs[CurrentPerm] = x;
	    break;
	}

    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '0':
	{
	    if(d1 == -1) d1 = key-'0';
	    else if(d2 == -1) d2 = key-'0';
	    else {
		d1 = d2;
		d2 = key -'0';
	    }
	    
	    printf("d1 = %d d2 = %d\n", d1, d2);
	}
	break;
    case '\r':
	{
	    printf("return...\n");
	    if(d1 == -1) d1 = 0;
	    int x = 0;
	    if(d2 == -1) x = d1;
	    else {
		x = d1 * 10 + d2 -1;
	    }
	    
	    if(x >= 0 && x< 24)
		CurrentPerm = x;
	    
	}
	break;
    }
    
	//   }

    printf("cycle idx: %d\n", current_index_cycle);
    PERMs[CurrentPerm].reduceName();
    PERMs[CurrentPerm].dump();
    
    glutPostRedisplay();
}

void keyboard(int key, int x, int y)
{
    printf("key wss=%d\n", key);
    static int d1 = -1;
    static int d2 = -1;
    if (key == GLUT_KEY_RIGHT)
        {
                rY += 15;
        }
    else if (key == GLUT_KEY_LEFT)
        {
                rY -= 15;
        }
    else if (key == GLUT_KEY_DOWN)
        {
                rX -= 15;
        }
    else if (key == GLUT_KEY_UP)
        {
                rX += 15;
        }
 
    //printf("key=%d x=%d y=%d\n", key, x, y);
	
    
    // Request display update
    glutPostRedisplay();
}



int main(int argc, char **argv)
{
    //readTransTable("face_permutations.txt", index_cycles);
    CurrentPerm = 0;
    
    // Initialize GLUT and process user parameters
    glutInit(&argc, argv);

    // Request double buffered true color window with Z-buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700,700);
    glutInitWindowPosition(100, 100);

    // Create window
    glutCreateWindow("Linux Journal OpenGL Cube");


    // Enable Z-buffer depth test
    glEnable(GL_DEPTH_TEST);

    // Callback functions
    glutDisplayFunc(drawCube);
    glutSpecialFunc(keyboard);
    glutKeyboardFunc(mykeys);
    glutReshapeFunc(reshape);
    
    //PERM = PERM * Permutation("(1 2)", "flip center");
    //PERM.dump();
    // Pass control to GLUT for events
    glutMainLoop();

    return 0;
}
