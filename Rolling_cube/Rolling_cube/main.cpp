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

		/*
		glPushMatrix();

		// 0번 광원 배치.

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

		glEnable(GL_LIGHTING);                                        //조명 활성화

		glEnable(GL_LIGHT0);                                           //조명 on


		float AmbientColor[] = { 0.0f, 0.0f, 0.2f, 0.0f };         //주변광

		float DiffuseColor[] = { 0.5f, 0.5f, 0.5f, 0.0f };          //분산광

		float SpecularColor[] = { 0.5f, 0.5f, 0.5f, 0.0f };        //방사광

		float Position[] = { 0.0f, 50.0f, 0.0f, 1.0f };  //조명 위치


		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);                 // 검은색으로 화면 지움

		glShadeModel(GL_SMOOTH);                              // 매끄러운 세이딩 사용

		glEnable(GL_DEPTH_TEST);                              // 가려진 면 제거

		glEnable(GL_CULL_FACE);                               // 후면 제거

		glFrontFace(GL_CCW);                                  // 다각형을 반시계방향으로 감는다.


		glEnable(GL_LIGHTING);                                // 조명 활성화



		// LIGHT0 설정

		glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientColor);       // 주변광 성분 설정

		glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseColor);       // 분산광 성분 설정

		glLightfv(GL_LIGHT0, GL_POSITION, Position);     // 광원 위치 설정


															  // LIGHT0을 켠다.

		glEnable(GL_LIGHT0);


		float spotlightDirection[] = { 0.0f, 0.0f, -1.0f };              // 스포트라이트 방향

		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 80.0f);                  // 80도 원뿔

		glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 80.0f);                 // 초점 설정

		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotlightDirection);   // 방향 설정
		*/


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