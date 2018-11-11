#include "basic.h"
#include "main_cube.h"
#include "camera.h"

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLUquadricObj *glu_fill;
GLUquadricObj *glu_line;

Main_cube main_cube;//���ΰ� ť��
Camera camera;//ī�޶�

int map[10][10];
int poss = -900;

void SetupRC()
{
	ifstream in("map.txt");

	int i = 0;
	int j = 0;
	char c;

	if (in.fail()) { cout << "������ ���� �� �����߽��ϴ�." << endl;}

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
	RECT windowRECT;                
	windowRECT.top = 0;                                         
	windowRECT.left = 0;
	windowRECT.bottom = 1080;
	windowRECT.right = 1920;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1920, 1080);
	AdjustWindowRectEx(&windowRECT, WS_POPUP, 0, WS_EX_APPWINDOW);
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

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (map[i][j] == 1)
				{
					glPushMatrix();//����
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

		/*
		glPushMatrix();

		// 0�� ���� ��ġ.

		glEnable(GL_COLOR_MATERIAL);

		glEnable(GL_LIGHTING);

		glEnable(GL_LIGHT0);


		GLfloat lightpos[] = { 0, -300, 0, 1 };

		glLightfv(GL_LIGHT0, GL_POSITION, lightpos);


		GLfloat ambient[4] = { 1,1,1,1 };

		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

		glPopMatrix();


		/////////////////////////


		glEnable(GL_COLOR_MATERIAL);

		glEnable(GL_LIGHTING);                                        //���� Ȱ��ȭ

		glEnable(GL_LIGHT0);                                           //���� on


		float AmbientColor[] = { 0.0f, 0.0f, 0.2f, 0.0f };         //�ֺ���

		float DiffuseColor[] = { 0.5f, 0.5f, 0.5f, 0.0f };          //�л걤

		float SpecularColor[] = { 0.5f, 0.5f, 0.5f, 0.0f };        //��籤

		float Position[] = { 0.0f, 50.0f, 0.0f, 1.0f };  //���� ��ġ


		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);                 // ���������� ȭ�� ����

		glShadeModel(GL_SMOOTH);                              // �Ų����� ���̵� ���

		glEnable(GL_DEPTH_TEST);                              // ������ �� ����

		glEnable(GL_CULL_FACE);                               // �ĸ� ����

		glFrontFace(GL_CCW);                                  // �ٰ����� �ݽð�������� ���´�.


		glEnable(GL_LIGHTING);                                // ���� Ȱ��ȭ



		// LIGHT0 ����

		glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientColor);       // �ֺ��� ���� ����

		glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseColor);       // �л걤 ���� ����

		glLightfv(GL_LIGHT0, GL_POSITION, Position);     // ���� ��ġ ����


															  // LIGHT0�� �Ҵ�.

		glEnable(GL_LIGHT0);


		float spotlightDirection[] = { 0.0f, 0.0f, -1.0f };              // ����Ʈ����Ʈ ����

		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 80.0f);                  // 80�� ����

		glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 80.0f);                 // ���� ����

		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotlightDirection);   // ���� ����
		*/


		GLfloat AmbientLight[] = { 0.1f, 0.1f, 0.1f, 0.0f };//�ֺ� ����
		GLfloat DiffuseLight[] = { 1.5f, 1.5f, 1.5f, 0.0f };//��� �ݻ� ����
		GLfloat SpecularLight[] = { 0.5f, 0.5f, 0.5f, 0.0f };//�ſ�ݻ� ����
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
	float view_ratio = 16.f / 9.f;//����� ����:����
	gluPerspective(60.0, view_ratio, 1.0, 10000.0);

	glMatrixMode(GL_MODELVIEW);
}