#define _CRT_SECURE_NO_WARNINGS

#include "basic.h"
#include "main_cube.h"
#include "enemy_cube.h"
#include "camera.h"
#include "maps.h"
#include "alpha_light.h"

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLUquadricObj *glu_fill;
GLUquadricObj *glu_line;

GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;

	// 바이너리 읽기 모드로 파일을 연다 
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;
	// 비트맵 파일 헤더를 읽는다. 
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1)
	{
		fclose(fp);
		return NULL;
	}
	// 파일이 BMP 파일인지 확인한다. 
	if (header.bfType != 'MB')
	{
		fclose(fp);
		return NULL;
	}
	// BITMAPINFOHEADER 위치로 간다. 
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// 비트맵 이미지 데이터를 넣을 메모리 할당을 한다. 
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL)
	{
		fclose(fp);
		exit(0);
		return NULL;
	}
	// 비트맵 인포 헤더를 읽는다. 
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize)
	{
		free(*info);
		fclose(fp);
		return NULL;
	}
	// 비트맵의 크기 설정 
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth*(*info)->bmiHeader.biBitCount + 7) / 8.0 *  abs((*info)->bmiHeader.biHeight);
	// 비트맵의 크기만큼 메모리를 할당한다. 
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL)
	{
		free(*info);
		fclose(fp);
		return NULL;
	}
	// 비트맵 데이터를 bit(GLubyte 타입)에 저장한다. 
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize)
	{
		free(*info);
		free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}

GLubyte *TexBits; // 데이터를 가리킬 포인터
BITMAPINFO *info; // 비트맵 헤더 저장할 변수
GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);


Main_cube main_cube;//주인공 큐브
Enemy_cube enemy_cube;//적 큐브
Camera camera;//카메라
Maps maps;//맵
Alpha_light alpha_light;//투명빛


int bounce = 0;//팅기기 시작할때 0 돌아올때 1
int before_move = 9;//적 큐브가 전에 어딜 갔을려나?

int a = 0;//임시로 테스트 카메라 시점전환////////////////


void SetupRC()
{
	snd.pSound[0]->release();
	snd.Add_sound();
	snd.Play(0);

	glGenTextures(1, main_cube.main_cube_sp);

	glGenTextures(1, maps.map_sp);

	glBindTexture(GL_TEXTURE_2D, main_cube.main_cube_sp[0]);
	TexBits = LoadDIBitmap("image\\main_cube.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 90, 90, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, TexBits);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, maps.map_sp[0]);
	TexBits = LoadDIBitmap("image\\map.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 180, 180, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, TexBits);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 텍스처 모드 설정
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);


	alpha_light.x[0] = 0;
	alpha_light.z[0] = 0;
	alpha_light.x[1] = 900;
	alpha_light.z[1] = 900;
	alpha_light.x[2] = -900;
	alpha_light.z[2] = -900;

	ifstream in("map.txt");

	int i = 0;
	int j = 0;
	char c;

	if (in.fail()) { cout << "파일을 여는 데 실패했습니다." << endl;}

	for (int i = 0; i < map_length; i++)
	{
		for (int j = 0; j < map_length; j++)
		{
			in.get(c);
			maps.map[i][j] = c - 48;
		}
		in.get(c);
	}

	in.close();

	srand(time(NULL));
}

void Timer(int value)
{
	for (int i = 0; i < 100; i++)
	{
		if (main_cube.cookie_active[i] == 1)
		{
			if (main_cube.cookie_time[i] >= 1)
				main_cube.cookie_time[i]--;
			else
				main_cube.cookie_active[i] = 0;
		}
	}
	

	camera.timer();

	//주인공 큐브 움직임//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (main_cube.move_w == 1)
	{
		int crash = 0;
		for (int i = 0; i < map_length; i++)
		{
			for (int j = 0; j < map_length; j++)
			{
				if (maps.map[i][j] == 1)
				{
					if (main_cube.x >= -90 * map_length + j * 180 - 90 && main_cube.x <= -90 * map_length + j * 180 + 90 &&
						main_cube.z - 90 >= -90 * map_length + i * 180 - 90 && main_cube.z - 90 <= -90 * map_length + i * 180 + 90)
					{
						crash = 1;
						i = map_length;
						j = map_length;
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
				main_cube.cookie_make();
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
		for (int i = 0; i < map_length; i++)
		{
			for (int j = 0; j < map_length; j++)
			{
				if (maps.map[i][j] == 1)
				{
					if (main_cube.x >= -90 * map_length + j * 180 - 90 && main_cube.x <= -90 * map_length + j * 180 + 90 &&
						main_cube.z + 90 >= -90 * map_length + i * 180 - 90 && main_cube.z + 90 <= -90 * map_length + i * 180 + 90)
					{
						crash = 1;
						i = map_length;
						j = map_length;
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
				main_cube.cookie_make();
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
		for (int i = 0; i < map_length; i++)
		{
			for (int j = 0; j < map_length; j++)
			{
				if (maps.map[i][j] == 1)
				{
					if (main_cube.x - 90 >= -90 * map_length + j * 180 - 90 && main_cube.x - 90 <= -90 * map_length + j * 180 + 90 &&
						main_cube.z >= -90 * map_length + i * 180 - 90 && main_cube.z <= -90 * map_length + i * 180 + 90)
					{
						crash = 1;
						i = map_length;
						j = map_length;
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
				main_cube.cookie_make();
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
		for (int i = 0; i < map_length; i++)
		{
			for (int j = 0; j < map_length; j++)
			{
				if (maps.map[i][j] == 1)
				{
					if (main_cube.x + 90 >= -90 * map_length + j * 180 - 90 && main_cube.x + 90 <= -90 * map_length + j * 180 + 90 &&
						main_cube.z >= -90 * map_length + i * 180 - 90 && main_cube.z <= -90 * map_length + i * 180 + 90)
					{
						crash = 1;
						i = map_length;
						j = map_length;
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
				main_cube.cookie_make();
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

	//주인공 큐브 은신
	int on = 0;
	for (int i = 0; i < 3; i++)
	{
		if (main_cube.x == alpha_light.x[i] && main_cube.z == alpha_light.z[i])
			on = 1;
	}
	if (on == 1)
		main_cube.invisibl = 1;
	else
		main_cube.invisibl = 0;


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//적 큐브 어디로 갈까나
	int cookie_choose = 0;
	int cookie_time = 0;
	int cookie_x = 0;
	int cookie_z = 0;

	if (enemy_cube.move_time == 0 && enemy_cube.move_w == 0 && enemy_cube.move_s == 0 && enemy_cube.move_a == 0 && enemy_cube.move_d == 0)//다 움직였을때
	{
		for (int i = 0; i < 100; i++)//근처에 쿠키가 떨어져 있는지 확인
		{
			if (main_cube.cookie_active[i] == 1 &&((enemy_cube.x == main_cube.cookie_x[i] && enemy_cube.z >= main_cube.cookie_z[i] - 180 && enemy_cube.z <= main_cube.cookie_z[i] + 180) || 
				(enemy_cube.z == main_cube.cookie_z[i] && enemy_cube.x >= main_cube.cookie_x[i] - 180 && enemy_cube.x <= main_cube.cookie_x[i] + 180)))
			{
				cookie_choose = 1;
				if (main_cube.cookie_time[i] > cookie_time)
				{
					cookie_time = main_cube.cookie_time[i];
					cookie_x = main_cube.cookie_x[i];
					cookie_z = main_cube.cookie_z[i];
				}
			}
		}

		if (cookie_choose == 1)//근처에 쿠키가 있을(O)! 경우
		{
			if (enemy_cube.x == cookie_x && enemy_cube.z > cookie_z)
			{
				enemy_cube.move_w = 1;
				enemy_cube.move_time = 90;
				before_move = 0;
			}
			else if(enemy_cube.x == cookie_x && enemy_cube.z < cookie_z)
			{
				enemy_cube.move_s = 1;
				enemy_cube.move_time = 90;
				before_move = 1;
			}
			else if (enemy_cube.z == cookie_z && enemy_cube.x > cookie_x)
			{
				enemy_cube.move_a = 1;
				enemy_cube.move_time = 90;
				before_move = 2;
			}
			else if (enemy_cube.z == cookie_z && enemy_cube.x < cookie_x)
			{
				enemy_cube.move_d = 1;
				enemy_cube.move_time = 90;
				before_move = 3;
			}
		}
		else if (cookie_choose == 0)//근처에 쿠키가 없을(X)! 경우
		{
			int trues = 1;
			do
			{
				enemy_cube.next_move = rand() % 4;
				if (enemy_cube.next_move == 0)
				{
					if (maps.map[(enemy_cube.z - 180) / 180 + 5][enemy_cube.x / 180 + 5] == 0)
					{
						if (before_move != 1 || (maps.map[(enemy_cube.z + 180) / 180 + 5][enemy_cube.x / 180 + 5] == 1 &&
							maps.map[enemy_cube.z / 180 + 5][(enemy_cube.x - 180) / 180 + 5] == 1 && maps.map[enemy_cube.z / 180 + 5][(enemy_cube.x + 180) / 180 + 5] == 1))
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
					if (maps.map[(enemy_cube.z + 180) / 180 + 5][enemy_cube.x / 180 + 5] == 0)
					{
						if (before_move != 0 || (maps.map[(enemy_cube.z - 180) / 180 + 5][enemy_cube.x / 180 + 5] == 1 &&
							maps.map[enemy_cube.z / 180 + 5][(enemy_cube.x - 180) / 180 + 5] == 1 && maps.map[enemy_cube.z / 180 + 5][(enemy_cube.x + 180) / 180 + 5] == 1))
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
					if (maps.map[enemy_cube.z / 180 + 5][(enemy_cube.x - 180) / 180 + 5] == 0)
					{
						if (before_move != 3 || (maps.map[(enemy_cube.z - 180) / 180 + 5][enemy_cube.x / 180 + 5] == 1 &&
							maps.map[(enemy_cube.z + 180) / 180 + 5][enemy_cube.x / 180 + 5] == 1 && maps.map[enemy_cube.z / 180 + 5][(enemy_cube.x + 180) / 180 + 5] == 1))
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
					if (maps.map[enemy_cube.z / 180 + 5][(enemy_cube.x + 180) / 180 + 5] == 0)
					{
						if (before_move != 2 || (maps.map[(enemy_cube.z - 180) / 180 + 5][enemy_cube.x / 180 + 5] == 1 &&
							maps.map[(enemy_cube.z + 180) / 180 + 5][enemy_cube.x / 180 + 5] == 1 && maps.map[enemy_cube.z / 180 + 5][(enemy_cube.x - 180) / 180 + 5] == 1))
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
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glu_fill = gluNewQuadric();
	glu_line = gluNewQuadric();
	gluQuadricDrawStyle(glu_fill, GLU_FILL);
	gluQuadricDrawStyle(glu_line, GLU_LINE);

	glPushMatrix();
	{
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
		alpha_light.light_draw();

		main_cube.draw();//메인큐브
		main_cube.cookie_draw();
		enemy_cube.draw();//적큐브
		maps.draw();
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