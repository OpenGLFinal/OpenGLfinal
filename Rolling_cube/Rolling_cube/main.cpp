#include <GL/freeglut.h>
#include <gl/glut.h> 
#include <time.h>
#include <iostream>
#include <math.h>
using namespace std;
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLUquadricObj *glu_fill;
GLUquadricObj *glu_line;

class Main_cube
{
public:
	int x = 0;
	int z = 0;

	int move_w = 0;
	int move_w_time = 0;
	int move_s = 0;
	int move_s_time = 0;
	int move_a = 0;
	int move_a_time = 0;
	int move_d = 0;
	int move_d_time = 0;
	
	int x_ro = 0;
	int z_ro = 0;
};

int camera_x = 0;
int camera_z = 0;
int camera_ro = 90;
int camera_ro_left = 0;
int camera_ro_right = 0;
int camera_ro_big = 0;

Main_cube main_cube;

void SetupRC()
{

	srand(time(NULL));
}

void Timer(int value)
{
	if (camera_ro < 0)
		camera_ro += 360;
	else if (camera_ro > 270)
		camera_ro -= 360;

	if (main_cube.move_w == 1)
	{
		if (main_cube.move_w_time != 0)
		{
			main_cube.x_ro -= 5;
			main_cube.move_w_time -= 5;
			camera_z -= 5;
		}
		else
		{
			main_cube.move_w = 0;
			main_cube.z -= 90;
			main_cube.x_ro = 0;
		}
	}

	if (main_cube.move_s == 1)
	{
		if (main_cube.move_s_time != 0)
		{
			main_cube.x_ro += 5;
			main_cube.move_s_time -= 5;
			camera_z += 5;
		}
		else
		{
			main_cube.move_s = 0;
			main_cube.z += 90;
			main_cube.x_ro = 0;
		}
	}

	if (main_cube.move_a == 1)
	{
		if (main_cube.move_a_time != 0)
		{
			main_cube.z_ro += 5;
			main_cube.move_a_time -= 5;
			camera_x -= 5;
		}
		else
		{
			main_cube.move_a = 0;
			main_cube.x -= 90;
			main_cube.z_ro = 0;
		}
	}

	if (main_cube.move_d == 1)
	{
		if (main_cube.move_d_time != 0)
		{
			main_cube.z_ro -= 5;
			main_cube.move_d_time -= 5;
			camera_x += 5;
		}
		else
		{
			main_cube.move_d = 0;
			main_cube.x += 90;
			main_cube.z_ro = 0;
		}
	}


	if (camera_ro_left == 1)
	{
		if (camera_ro_big != 0)
		{
			camera_ro -= 5;
			camera_ro_big -= 5;
		}
		else
		{
			camera_ro_left = 0;
		}
	}

	if (camera_ro_right == 1)
	{
		if (camera_ro_big != 0)
		{
			camera_ro += 5;
			camera_ro_big -= 5;
		}
		else
		{
			camera_ro_right = 0;
		}
	}


	glutPostRedisplay();
	glutTimerFunc(20, Timer, 1);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		if (main_cube.move_w == 0 && main_cube.move_s == 0 && main_cube.move_a == 0 && main_cube.move_d == 0 && camera_ro_left == 0 && camera_ro_right == 0)
		{
			switch ((camera_ro - 90) / 90)
			{
			case 0:
				main_cube.move_w = 1;
				main_cube.move_w_time = 90;
				break;

			case 1:
				main_cube.move_d = 1;
				main_cube.move_d_time = 90;
				break;

			case 2:
				main_cube.move_s = 1;
				main_cube.move_s_time = 90;
				break;

			case -1:
				main_cube.move_a = 1;
				main_cube.move_a_time = 90;
				break;
			}
		}
		break;

	case 's':
		if (main_cube.move_w == 0 && main_cube.move_s == 0 && main_cube.move_a == 0 && main_cube.move_d == 0 && camera_ro_left == 0 && camera_ro_right == 0)
		{
			switch ((camera_ro - 90) / 90)
			{
			case 0:
				main_cube.move_s = 1;
				main_cube.move_s_time = 90;
				break;

			case 1:
				main_cube.move_a = 1;
				main_cube.move_a_time = 90;
				break;

			case 2:
				main_cube.move_w = 1;
				main_cube.move_w_time = 90;
				break;

			case -1:
				main_cube.move_d = 1;
				main_cube.move_d_time = 90;
				break;
			}
		}
		break;

	case 'a':
		if (main_cube.move_w == 0 && main_cube.move_s == 0 && main_cube.move_a == 0 && main_cube.move_d == 0 && camera_ro_left == 0 && camera_ro_right == 0)
		{
			switch ((camera_ro - 90) / 90)
			{
			case 0:
				main_cube.move_a = 1;
				main_cube.move_a_time = 90;
				break;

			case 1:
				main_cube.move_w = 1;
				main_cube.move_w_time = 90;
				break;

			case 2:
				main_cube.move_d = 1;
				main_cube.move_d_time = 90;
				break;

			case -1:
				main_cube.move_s = 1;
				main_cube.move_s_time = 90;
				break;
			}
		}
		break;

	case 'd':
		if (main_cube.move_w == 0 && main_cube.move_s == 0 && main_cube.move_a == 0 && main_cube.move_d == 0 && camera_ro_left == 0 && camera_ro_right == 0)
		{
			switch ((camera_ro - 90) / 90)
			{
			case 0:
				main_cube.move_d = 1;
				main_cube.move_d_time = 90;
				break;

			case 1:
				main_cube.move_s = 1;
				main_cube.move_s_time = 90;
				break;

			case 2:
				main_cube.move_a = 1;
				main_cube.move_a_time = 90;
				break;

			case -1:
				main_cube.move_w = 1;
				main_cube.move_w_time = 90;
				break;
			}
		}
		break;

	case 'q':
		if (main_cube.move_w == 0 && main_cube.move_s == 0 && main_cube.move_a == 0 && main_cube.move_d == 0 && camera_ro_left == 0 && camera_ro_right == 0)
		{
			camera_ro_left = 1;
			camera_ro_big = 90;
		}
		break;

	case 'e':
		if (main_cube.move_w == 0 && main_cube.move_s == 0 && main_cube.move_a == 0 && main_cube.move_d == 0 && camera_ro_left == 0 && camera_ro_right == 0)
		{
			camera_ro_right = 1;
			camera_ro_big = 90;
		}
		break;
	}
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

	}
}

void Motion(int x, int y)
{

}


void main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1920, 1080);
	glutCreateWindow("기말 컴그!");

	SetupRC();

	glutDisplayFunc(drawScene);
	glutTimerFunc(0, Timer, 1);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

void drawScene()
{
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glu_fill = gluNewQuadric();
	glu_line = gluNewQuadric();
	gluQuadricDrawStyle(glu_fill, GLU_FILL);
	gluQuadricDrawStyle(glu_line, GLU_LINE);

	glPushMatrix();
	{
		float x_ro = cos(float(camera_ro) * 3.141592 / 180);
		float z_ro = sin(float(camera_ro) * 3.141592 / 180);

		gluLookAt(
			(300.0 * x_ro) + camera_x, 300.0, (300.0 * z_ro) + camera_z, //EYE
			camera_x, 0.0, camera_z, //AT
			0.0, 1.0, 0.0); //UP


		glPushMatrix();//바닥 판
		{
			glColor3ub(255, 255, 255);
			glBegin(GL_POLYGON);
			glVertex3f(-900, 0, -900);
			glVertex3f(-900, 0, 900);
			glVertex3f(900, 0, 900);
			glVertex3f(900, 0, -900);
			glEnd();
		}
		glPopMatrix();
			
		glPushMatrix();//주인공 사각형
		{
			glTranslatef(main_cube.x, 45, main_cube.z);

			if (main_cube.move_w == 1)
			{
				glTranslatef(0, -45, -45);
				glRotatef(main_cube.x_ro, 1, 0, 0);
				glTranslatef(0, 45, 45);
			}
			if (main_cube.move_s == 1)
			{
				glTranslatef(0, -45, 45);
				glRotatef(main_cube.x_ro, 1, 0, 0);
				glTranslatef(0, 45, -45);
			}
			if (main_cube.move_a == 1)
			{
				glTranslatef(-45, -45, 0);
				glRotatef(main_cube.z_ro, 0, 0, 1);
				glTranslatef(45, 45, 0);
			}
			if (main_cube.move_d == 1)
			{
				glTranslatef(45, -45, 0);
				glRotatef(main_cube.z_ro, 0, 0, 1);
				glTranslatef(-45, 45, 0);
			}

			
			glColor3ub(120, 55, 18);
			glutSolidCube(90);
			glColor3ub(0, 0, 0);
			glutWireCube(90);
		}
		glPopMatrix();
	}
	glPopMatrix();
	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float view_ratio = 16.f / 9.f;//모니터 가로:세로
	gluPerspective(60.0, view_ratio, 1.0, 10000.0);

	glMatrixMode(GL_MODELVIEW);
}