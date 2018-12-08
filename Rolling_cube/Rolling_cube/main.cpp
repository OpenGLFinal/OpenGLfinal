#include "basic.h"
#include "main_cube.h"
#include "enemy_cube.h"
#include "camera.h"

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLUquadricObj *glu_fill;
GLUquadricObj *glu_line;

Main_cube main_cube;//주인공 큐브
Enemy_cube enemy_cube;//적 큐브
Camera camera;//카메라

int map[10][10];
int poss = -900;
int bounce = 0;//팅기기 시작할때 0 돌아올때 1
int before_move = 9;//적 큐브가 전에 어딜 갔을려나?

int a = 0;//임시로 테스트 카메라 시점전환////////////////


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

	//주인공 큐브 움직임
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

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//적 큐브 어디로 갈까나
	int trues = 1;
	if (enemy_cube.move_time == 0 && enemy_cube.move_w == 0 && enemy_cube.move_s == 0 && enemy_cube.move_a == 0 && enemy_cube.move_d == 0)
	{
		do
		{
			enemy_cube.next_move = rand() % 4;
			if (enemy_cube.next_move == 0)
			{
				if (map[(enemy_cube.z - 180) / 180 + 5][enemy_cube.x / 180 + 5] == 0)
				{
					if (before_move != 1 || (map[(enemy_cube.z + 180) / 180 + 5][enemy_cube.x / 180 + 5] == 1 &&
						map[enemy_cube.z / 180 + 5][(enemy_cube.x - 180) / 180 + 5] == 1 && map[enemy_cube.z / 180 + 5][(enemy_cube.x + 180) / 180 + 5] == 1))
					{
						trues = 0;
						enemy_cube.move_w = 1;
						enemy_cube.move_time = 90;
						before_move = 0;
					}
				}
			}
			else if (enemy_cube.next_move == 1)
			{
				if (map[(enemy_cube.z + 180) / 180 + 5][enemy_cube.x / 180 + 5] == 0)
				{
					if (before_move != 0 || (map[(enemy_cube.z - 180) / 180 + 5][enemy_cube.x / 180 + 5] == 1 &&
						map[enemy_cube.z / 180 + 5][(enemy_cube.x - 180) / 180 + 5] == 1 && map[enemy_cube.z / 180 + 5][(enemy_cube.x + 180) / 180 + 5] == 1))
					{
						trues = 0;
						enemy_cube.move_s = 1;
						enemy_cube.move_time = 90;
						before_move = 1;
					}
				}
			}
			else if (enemy_cube.next_move == 2)
			{
				if (map[enemy_cube.z / 180 + 5][(enemy_cube.x - 180) / 180 + 5] == 0)
				{
					if (before_move != 3 || (map[(enemy_cube.z - 180) / 180 + 5][enemy_cube.x / 180 + 5] == 1 &&
						map[(enemy_cube.z + 180) / 180 + 5][enemy_cube.x / 180 + 5] == 1 && map[enemy_cube.z / 180 + 5][(enemy_cube.x + 180) / 180 + 5] == 1))
					{
						trues = 0;
						enemy_cube.move_a = 1;
						enemy_cube.move_time = 90;
						before_move = 2;
					}
				}
			}
			else if (enemy_cube.next_move == 3)
			{
				if (map[enemy_cube.z / 180 + 5][(enemy_cube.x + 180) / 180 + 5] == 0)
				{
					if (before_move != 2 || (map[(enemy_cube.z - 180) / 180 + 5][enemy_cube.x / 180 + 5] == 1 &&
						map[(enemy_cube.z + 180) / 180 + 5][enemy_cube.x / 180 + 5] == 1 && map[enemy_cube.z / 180 + 5][(enemy_cube.x - 180) / 180 + 5] == 1))
					{
						trues = 0;
						enemy_cube.move_d = 1;
						enemy_cube.move_time = 90;
						before_move = 3;
					}
				}
			}
		} while (trues);
	}

	//적 큐브 움직임
	if (enemy_cube.move_w == 1)
	{
		if (enemy_cube.move_time != 0)
		{
			enemy_cube.x_ro -= 3;
			enemy_cube.move_time -= 3;
			enemy_cube.light_z -= 6;
		}
		else
		{
			enemy_cube.move_w = 0;
			enemy_cube.z -= 180;
			enemy_cube.x_ro = 0;
		}
	}
	else if (enemy_cube.move_s == 1)
	{
		if (enemy_cube.move_time != 0)
		{
			enemy_cube.x_ro += 3;
			enemy_cube.move_time -= 3;
			enemy_cube.light_z += 6;
		}
		else
		{
			enemy_cube.move_s = 0;
			enemy_cube.z += 180;
			enemy_cube.x_ro = 0;
		}
	}
	else if (enemy_cube.move_a == 1)
	{
		if (enemy_cube.move_time != 0)
		{
			enemy_cube.z_ro += 3;
			enemy_cube.move_time -= 3;
			enemy_cube.light_x -= 6;
		}
		else
		{
			enemy_cube.move_a = 0;
			enemy_cube.x -= 180;
			enemy_cube.z_ro = 0;
		}
	}
	else if (enemy_cube.move_d == 1)
	{
		if (enemy_cube.move_time != 0)
		{
			enemy_cube.z_ro -= 3;
			enemy_cube.move_time -= 3;
			enemy_cube.light_x += 6;
		}
		else
		{
			enemy_cube.move_d = 0;
			enemy_cube.x += 180;
			enemy_cube.z_ro = 0;
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


	///////////////임시들//////////////
	case '1':
		if (a == 1)
			a = 0;
		else
			a = 1;
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
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_LIGHTING);

		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

		GLfloat gray[] = { 0.75f, 0.75f, 0.75f, 1.0f };
		GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
		glMateriali(GL_FRONT, GL_SHININESS, 64);


		float x_ro = cos(float(camera.ro) * 3.141592 / 180);
		float z_ro = sin(float(camera.ro) * 3.141592 / 180);

	
		if (a == 0)
		{
			gluLookAt(
				(300.0 * x_ro) + camera.x, 300.0, (300.0 * z_ro) + camera.z, //EYE
				camera.x, 0.0, camera.z, //AT
				0.0, 1.0, 0.0); //UP
		}
		else
		{
			gluLookAt(
				0, 2000, 0, //EYE
				0, 0.0, -1, //AT
				0.0, 1.0, 0.0); //UP
		}


		enemy_cube.light_draw();


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

		main_cube.draw();//메인큐브
		enemy_cube.draw();//적큐브

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