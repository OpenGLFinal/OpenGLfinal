#include "basic.h"
#include "main_cube.h"
#include "camera.h"

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLUquadricObj *glu_fill;
GLUquadricObj *glu_line;

Main_cube main_cube;//���ΰ� ť��
Camera camera;//ī�޶�

void SetupRC()
{

	srand(time(NULL));
}

void Timer(int value)
{
	camera.timer();

	if (main_cube.move_w == 1)
	{
		if (main_cube.move_w_time != 0)
		{
			main_cube.x_ro -= 5;
			main_cube.move_w_time -= 5;
			camera.z -= 5;
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
			camera.z += 5;
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
			camera.x -= 5;
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
			camera.x += 5;
		}
		else
		{
			main_cube.move_d = 0;
			main_cube.x += 90;
			main_cube.z_ro = 0;
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
		if (main_cube.move_w == 0 && main_cube.move_s == 0 && main_cube.move_a == 0 && main_cube.move_d == 0 && camera.ro_left == 0 && camera.ro_right == 0)
		{
			switch ((camera.ro - 90) / 90)
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
		if (main_cube.move_w == 0 && main_cube.move_s == 0 && main_cube.move_a == 0 && main_cube.move_d == 0 && camera.ro_left == 0 && camera.ro_right == 0)
		{
			switch ((camera.ro - 90) / 90)
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
		if (main_cube.move_w == 0 && main_cube.move_s == 0 && main_cube.move_a == 0 && main_cube.move_d == 0 && camera.ro_left == 0 && camera.ro_right == 0)
		{
			switch ((camera.ro - 90) / 90)
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
		if (main_cube.move_w == 0 && main_cube.move_s == 0 && main_cube.move_a == 0 && main_cube.move_d == 0 && camera.ro_left == 0 && camera.ro_right == 0)
		{
			switch ((camera.ro - 90) / 90)
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
		if (main_cube.move_w == 0 && main_cube.move_s == 0 && main_cube.move_a == 0 && main_cube.move_d == 0 && camera.ro_left == 0 && camera.ro_right == 0)
		{
			camera.ro_left = 1;
			camera.ro_big = 90;
		}
		break;

	case 'e':
		if (main_cube.move_w == 0 && main_cube.move_s == 0 && main_cube.move_a == 0 && main_cube.move_d == 0 && camera.ro_left == 0 && camera.ro_right == 0)
		{
			camera.ro_right = 1;
			camera.ro_big = 90;
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
	glutCreateWindow("�⸻ �ı�!");

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
		float x_ro = cos(float(camera.ro) * 3.141592 / 180);
		float z_ro = sin(float(camera.ro) * 3.141592 / 180);

		gluLookAt(
			(300.0 * x_ro) + camera.x, 300.0, (300.0 * z_ro) + camera.z, //EYE
			camera.x, 0.0, camera.z, //AT
			0.0, 1.0, 0.0); //UP


		glPushMatrix();//�ٴ� ��
		{
			glColor3ub(150, 150, 150);
			glBegin(GL_POLYGON);
			glVertex3f(-900, 0, -900);
			glVertex3f(-900, 0, 900);
			glVertex3f(900, 0, 900);
			glVertex3f(900, 0, -900);
			glEnd();
		}
		glPopMatrix();
			
		main_cube.draw();

		glPushMatrix();//����
		{
			glTranslatef(0, 90, 0);
			glColor3ub(30, 30, 30);
			glutSolidCube(180);
			glColor3ub(0, 0, 0);
			glutWireCube(180);
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
	float view_ratio = 16.f / 9.f;//����� ����:����
	gluPerspective(60.0, view_ratio, 1.0, 10000.0);

	glMatrixMode(GL_MODELVIEW);
}