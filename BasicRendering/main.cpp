/*******************************************************
 * Homework 2: OpenGL                                  *
 * CS 148 (Summer 2016), Stanford University           *
 *-----------------------------------------------------*
 * First, you should fill in problem1(), problem2(),   *
 * and problem3() as instructed in the written part of *
 * the problem set.  Then, express your creativity     *
 * with problem4()!                                    *
 *                                                     *
 * Note: you will only need to add/modify code where   *
 * it says "TODO".                                     *
 *                                                     *
 * The left mouse button rotates, the right mouse      *
 * button zooms, and the keyboard controls which       *
 * problem to display.                                 *
 *                                                     *
 * For Linux/OS X:                                     *
 * To compile your program, just type "make" at the    *
 * command line.  Typing "make clean" will remove all  *
 * computer-generated files.  Run by typing "./hw2"    *
 *                                                     *
 * For Visual Studio:                                  *
 * You can create a project with this main.cpp and     *
 * build and run the executable as you normally would. *
 *******************************************************/

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#if __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

using namespace std;

#define PI 3.14159265

bool leftDown = false, rightDown = false;
int lastPos[2];
float cameraPos[4] = {0,1,4,1};
int windowWidth = 640, windowHeight = 480;
double yRot = 0;
int curProblem = 1; // TODO: change this number to try different examples

float specular[] = { 1.0, 1.0, 1.0, 1.0 };
float shininess[] = { 50.0 };

void problem1() {

	// Load the identity translation matrix and our viewpoint matrix
	gluLookAt(0,0,10,0,0,0,0,1,0);

	/* 
	 * Initialize the rotation angle for movement along the circle
	 * and also initialize the radius of the circle
	 */
	float rotation_angle = 0;
	float radius = 3;

	// Draw the teapots along the circle
	for (int i=0; i <= 10; i++)
	{
		/*
		 * Reinitialize the modelview matrix before drawing a new
		 * teapot
		 */
		glPushMatrix();
			/*
			 * Translate the new teapot according to movement along the circle
			 */
			glTranslatef(radius * cos((PI*rotation_angle)/180),radius * sin((PI*rotation_angle)/180),0);
			// Rotate the teapot.
			glRotatef(rotation_angle,0,0,1);
			glutSolidTeapot(.5);
		glPopMatrix();
		// Increment the rotation angle.
		rotation_angle+=36;
	}
}

void problem2() {

	// Load our viewpoint matrix
	gluLookAt(0,0,1,0,0,0,0,1,0);

	// Keep track of the scaling factor
    float scale_factor = 1;
    // Keep track of the size of the current cube
    float curr_cube_size = .15;
    // Keep track of the size of the old cube
    float old_cube_size = curr_cube_size;
    /*
     * First translate the image to the left to make
     * space for the cubes.
     */ 
    glPushMatrix();
	    glTranslatef(-1.5,0,0);
		    // Draw 15 cubes next to eachother
		    for (int i=0; i < 15; i++)
		    {
		    	/*
		    	 * Translate the current cube to the
		    	 * right.
		    	 */
		    	glTranslatef(curr_cube_size,0,0);
		    	/*
		    	 * Scale the cube to make it larger
		    	 */
		    	glScalef(1,scale_factor,1);
		    	/*
		    	 * Need to translate the new cube so that
		    	 * all of the cubes start on the same position
		    	 * in the y axis - even if they differ in size.
		    	 */
				old_cube_size = curr_cube_size;
		    	curr_cube_size*=scale_factor;
		    	glTranslatef(0,(curr_cube_size - old_cube_size),0);
		    	// Draw the cube and update the matrix.
		    	glutSolidCube(curr_cube_size);
			    // Increment the scaling factor for the next cube.
			    scale_factor += .007;
		    }
	glPopMatrix();

}

void problem3() {

	/*
	 * Load our viewpoint matrix
	 */
	gluLookAt(0,10,30,0,0,0,0,1,0);


	/* 
	 * Keep track of the number of teapots and the spacing
	 * between teapots.
	 */
	int current_num_teapots = 1;
	double teapot_spacing = 4;
	double teapot_size = 1;

	/*
	 * Keep track of the current row and column of the teapots
	 * via translations
	 */
	double current_translation_x = -1;
	double current_translation_y = 7;

	 // Draw the teapots row by row for 6 rows
	 for (current_num_teapots=1; current_num_teapots <= 6; current_num_teapots++)
	 {
	 	/*
		 * Reinitialize the modelview matrix before drawing a new
		 * teapot row
		 */
		 glPushMatrix();
	 
		 	// Translate the teapots upwards to get proper rows.
		 	glTranslatef(0, current_translation_y, 0);
			glTranslatef(current_translation_x, 0, 0);
			for (int teapot = 0; teapot < current_num_teapots; teapot++)
			{
				glutSolidTeapot(teapot_size);
				glTranslatef(teapot_spacing,0,0);
			}

			// Set new translation amounts for the next row of teapots
			current_translation_y-=teapot_spacing/2;
			current_translation_x-=teapot_spacing/2;

		glPopMatrix();
	 }
}

/* Drawing a hand - the right palm facing inwards */
void problem4() {
	/*
	 * Load our viewpoint matrix
	 */
	glLoadIdentity();
	gluLookAt(0,-1,20,0,0,0,0,1,0);


	/* Create the palm of the hand */
	glPushMatrix();
		glBegin(GL_TRIANGLES);
	        // glColor3d(1,0,0);
	        glVertex3f(0,-20,1);
	        // glColor3d(1,0,0);
	        glVertex3f(4,3,1);
	        // glColor3d(1,0,0);
	        glVertex3f(-4,3,1);
	    glEnd();
	glPopMatrix();

	/* Crate the wrist and arm extension */
	glPushMatrix();

		glBegin(GL_QUADS);
	        // glColor3d(1,0,1);
	        glVertex3f(-2,-2,7);
	        // glColor3d(1,0,1);
	        glVertex3f(2,-2,7);
	        // glColor3d(1,0,1);
	        glVertex3f(2,-30,7);
	        // glColor3d(1,0,1);
	        glVertex3f(-2,-30,7);
	    glEnd();
	glPopMatrix();

	/* Create the 4 fingers */
	glPushMatrix();
		glRotatef(-10,1,0,0);


		glBegin(GL_QUADS);
	        // glColor3d(1,0,1);
	        glVertex3f(-2.8,.55,7);
	        // glColor3d(1,0,1);
	        glVertex3f(-2.2,.55,7);
	        // glColor3d(1,0,1);
	        glVertex3f(-2.2,2.3,7);
	        // glColor3d(1,0,1);
	        glVertex3f(-2.8,2.3,7);
	    glEnd();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-10,1,0,0);

		glBegin(GL_QUADS);
	        // glColor3d(1,0,1);
	        glVertex3f(-1.8,.55,7);
	        // glColor3d(1,0,1);
	        glVertex3f(-.8,.55,7);
	        // glColor3d(1,0,1);
	        glVertex3f(-.8,4,7);
	        // glColor3d(1,0,1);
	        glVertex3f(-1.8,4,7);
	    glEnd();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-10,1,0,0);

		glBegin(GL_QUADS);
	        // glColor3d(1,0,1);
	        glVertex3f(0,.55,7);
	        // glColor3d(1,0,1);
	        glVertex3f(0,5,7);
	        // glColor3d(1,0,1);
	        glVertex3f(1.2,5,7);
	        // glColor3d(1,0,1);
	        glVertex3f(1.2,.55,7);
	    glEnd();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-10,1,0,0);


		glBegin(GL_QUADS);
	        // glColor3d(1,0,1);
	        glVertex3f(1.8,.55,7);
	        // glColor3d(1,0,1);
	        glVertex3f(1.8,4,7);
	        // glColor3d(1,0,1);
	        glVertex3f(2.8,4,7);
	        // glColor3d(1,0,1);
	        glVertex3f(2.8,.55,7);
	    glEnd();
	glPopMatrix();

	/* Create the two joints of the thumb */
	glPushMatrix();
		glTranslatef(0,-3.0,0);
		glPushMatrix();
			glRotatef(-20,1,0,1);

			glPushMatrix();
				glBegin(GL_QUADS);
			        // glColor3d(1,0,1);
			        glVertex3f(1,.5,7);
			        // glColor3d(1,0,1);
			        glVertex3f(1,3.0,7);
			        // glColor3d(1,0,1);
			        glVertex3f(2,3.0,7);
			        // glColor3d(1,0,1);
			        glVertex3f(2,.5,7);
			    glEnd();
			glPopMatrix();
		glPopMatrix();
    glPopMatrix();

  glPushMatrix();
		glTranslatef(-1,-1.75,0);
		glPushMatrix();
			glRotatef(-20,1,0,1);

			glPushMatrix();
				glBegin(GL_QUADS);
			        // glColor3d(1,0,1);
			        glVertex3f(1,.5,7);
			        // glColor3d(1,0,1);
			        glVertex3f(1,2.0,7);
			        // glColor3d(1,0,1);
			        glVertex3f(2.5,2.0,7);
			        // glColor3d(1,0,1);
			        glVertex3f(2.5,.5,7);
			    glEnd();
			glPopMatrix();
		glPopMatrix();
    glPopMatrix();


}

void display() {
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glBegin(GL_LINES);
		glColor3f(1,0,0); glVertex3f(0,0,0); glVertex3f(1,0,0); // x axis
		glColor3f(0,1,0); glVertex3f(0,0,0); glVertex3f(0,1,0); // y axis
		glColor3f(0,0,1); glVertex3f(0,0,0); glVertex3f(0,0,1); // z axis
	glEnd(/*GL_LINES*/);

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glEnable(GL_LIGHT0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,windowWidth,windowHeight);

	float ratio = (float)windowWidth / (float)windowHeight;
	gluPerspective(50, ratio, 1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 0, 0, 0, 0, 1, 0);

	glLightfv(GL_LIGHT0, GL_POSITION, cameraPos);

	glRotatef(yRot,0,1,0);

	if (curProblem == 1) problem1();
	if (curProblem == 2) problem2();
	if (curProblem == 3) problem3();
	if (curProblem == 4) problem4();

	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) leftDown = (state == GLUT_DOWN);
	else if (button == GLUT_RIGHT_BUTTON) rightDown = (state == GLUT_DOWN);

	lastPos[0] = x;
	lastPos[1] = y;
}

void mouseMoved(int x, int y) {
	if (leftDown) yRot += (x - lastPos[0])*.1;
	if (rightDown) {
		for (int i = 0; i < 3; i++)
			cameraPos[i] *= pow(1.1,(y-lastPos[1])*.1);
	}


	lastPos[0] = x;
	lastPos[1] = y;
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	curProblem = key-'0';
    if (key == 'q' || key == 'Q' || key == 27){
        exit(0);
    }
	glutPostRedisplay();
}

void reshape(int width, int height) {
	windowWidth = width;
	windowHeight = height;
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("HW2");

	glutDisplayFunc(display);
	glutMotionFunc(mouseMoved);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}
