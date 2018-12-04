#include "basic.h"
#include "main_cube.h"
#include "camera.h"

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLUquadricObj *glu_fill;
GLUquadricObj *glu_line;

Main_cube main_cube;//주인공 큐브
Camera camera;//카메라

int map[10][10];
int poss = -900;
int bounce = 0;//팅기기 시작할때 0 돌아올때 1

void SetupRC()
{
	ifstream in("map.txt");

	int i = 0;
	int j = 0;
	char c;

	if (in.fail()) { cout << "파일을 여는 데 실패했습니다." << endl;}

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			in.get(c);
			map[i][j] = c - 48;
		}
		in.get(c);
	}

	in.close();



	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << map[i][j];
		}
		cout << endl;
	}

	srand(time(NULL));
}

void Timer(int value)
{
	poss += 10;
	if (poss > 900)
		poss = -900;

	camera.timer();

	if (main_cube.move_w == 1)
	{
		int crash = 0;
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (map[i][j] == 1)
				{
					if (main_cube.x >= -900 + j * 180 - 90 && main_cube.x <= -900 + j * 180 + 90 &&
						main_cube.z - 90 >= -900 + i * 180 - 90 && main_cube.z - 90 <= -900 + i * 180 + 90)
					{
						crash = 1;
						i = 10;
						j = 10;
					}
				}
			}
		}
		if (crash == 0)
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
		else if(crash == 1)
		{
			if (bounce == 0 && main_cube.move_w_time != 0)
			{
				main_cube.x_ro -= 5;
				main_cube.move_w_time -= 5;
				camera.z -= 5;
			}
			else if (bounce == 1 && main_cube.move_w_time != 0)
			{
				main_cube.x_ro += 5;
				main_cube.move_w_time += 5;
				camera.z += 5;
			}
			
			if (bounce == 0 && main_cube.move_w_time == 50)
			{
				bounce = 1;
			}
			else if (bounce == 1 && main_cube.move_w_time == 90)
			{
				main_cube.move_w = 0;
				main_cube.x_ro = 0;
				bounce = 0;
			}
		}
	}

	if (main_cube.move_s == 1)
	{
		int crash = 0;
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (map[i][j] == 1)
				{
					if (main_cube.x >= -900 + j * 180 - 90 && main_cube.x <= -900 + j * 180 + 90 &&
						main_cube.z + 90 >= -900 + i * 180 - 90 && main_cube.z + 90 <= -900 + i * 180 + 90)
					{
						crash = 1;
						i = 10;
						j = 10;
					}
				}
			}
		}
		if (crash == 0)
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
		else if (crash == 1)
		{
			if (bounce == 0 && main_cube.move_s_time != 0)
			{
				main_cube.x_ro += 5;
				main_cube.move_s_time -= 5;
				camera.z += 5;
			}
			else if (bounce == 1 && main_cube.move_s_time != 0)
			{
				main_cube.x_ro -= 5;
				main_cube.move_s_time += 5;
				camera.z -= 5;
			}

			if (bounce == 0 && main_cube.move_s_time == 50)
			{
				bounce = 1;
			}
			else if (bounce == 1 && main_cube.move_s_time == 90)
			{
				main_cube.move_s = 0;
				main_cube.x_ro = 0;
				bounce = 0;
			}
		}
	}

	if (main_cube.move_a == 1)
	{
		int crash = 0;
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (map[i][j] == 1)
				{
					if (main_cube.x - 90 >= -900 + j * 180 - 90 && main_cube.x - 90 <= -900 + j * 180 + 90 &&
						main_cube.z >= -900 + i * 180 - 90 && main_cube.z <= -900 + i * 180 + 90)
					{
						crash = 1;
						i = 10;
						j = 10;
					}
				}
			}
		}
		if (crash == 0)
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
		else if (crash == 1)
		{
			if (bounce == 0 && main_cube.move_a_time != 0)
			{
				main_cube.z_ro += 5;
				main_cube.move_a_time -= 5;
				camera.x -= 5;
			}
			else if (bounce == 1 && main_cube.move_a_time != 0)
			{
				main_cube.z_ro -= 5;
				main_cube.move_a_time += 5;
				camera.x += 5;
			}

			if (bounce == 0 && main_cube.move_a_time == 50)
			{
				bounce = 1;
			}
			else if (bounce == 1 && main_cube.move_a_time == 90)
			{
				main_cube.move_a = 0;
				main_cube.z_ro = 0;
				bounce = 0;
			}
		}
	}

	if (main_cube.move_d == 1)
	{
		int crash = 0;
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (map[i][j] == 1)
				{
					if (main_cube.x + 90 >= -900 + j * 180 - 90 && main_cube.x + 90 <= -900 + j * 180 + 90 &&
						main_cube.z >= -900 + i * 180 - 90 && main_cube.z <= -900 + i * 180 + 90)
					{
						crash = 1;
						i = 10;
						j = 10;
					}
				}
			}
		}
		if (crash == 0)
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
		else if (crash == 1)
		{
			if (bounce == 0 && main_cube.move_d_time != 0)
			{
				main_cube.z_ro -= 5;
				main_cube.move_d_time -= 5;
				camera.x += 5;
			}
			else if (bounce == 1 && main_cube.move_d_time != 0)
			{
				main_cube.z_ro += 5;
				main_cube.move_d_time += 5;
				camera.x -= 5;
			}

			if (bounce == 0 && main_cube.move_d_time == 50)
			{
				bounce = 1;
			}
			else if (bounce == 1 && main_cube.move_d_time == 90)
			{
				main_cube.move_d = 0;
				main_cube.z_ro = 0;
				bounce = 0;
			}
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
	RECT windowRECT;                
	windowRECT.top = 0;                                         
	windowRECT.left = 0;
	windowRECT.bottom = 1080;
	windowRECT.right = 1920;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1920, 1080);
	AdjustWindowRectEx(&windowRECT, WS_POPUP, 0, WS_EX_APPWINDOW);
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
	glEnable(GL_CULL_FACE);

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


		glPushMatrix();//바닥 판
		{
			glColor3ub(150, 150, 150);
			glBegin(GL_POLYGON);
			glVertex3f(-1000, 0, -1000);
			glVertex3f(-1000, 0, 1000);
			glVertex3f(1000, 0, 1000);
			glVertex3f(1000, 0, -1000);
			glEnd();
		}
		glPopMatrix();

		main_cube.draw();

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (map[i][j] == 1)
				{
					glPushMatrix();//지형
					{
						glTranslatef(-900 + (j * 180), 90, -900 + (i * 180));
						glColor3ub(30, 30, 30);
						glutSolidCube(180);
						glColor3ub(0, 0, 0);
						glutWireCube(180);
					}
					glPopMatrix();
				}
			}
		}

		//카메라
		GLfloat AmbientLight[] = { 0.1f, 0.1f, 0.1f, 0.0f };//주변 조명
		GLfloat DiffuseLight[] = { 1.5f, 1.5f, 1.5f, 0.0f };//산란 반사 조명
		GLfloat SpecularLight[] = { 0.5f, 0.5f, 0.5f, 0.0f };//거울반사 조명
		GLfloat lightPos[] = { 0, 50, 0, 1 };
		GLfloat specref[] = { 1,1,1,1 };
		glEnable(GL_LIGHTING);

		glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

		glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
		glMateriali(GL_FRONT, GL_SHININESS, 64);


		glEnable(GL_LIGHT0);
		glEnable(GL_COLOR_MATERIAL);

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