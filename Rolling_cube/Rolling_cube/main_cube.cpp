#include "basic.h"
#include "main_cube.h"

void Main_cube::draw()
{
	glPushMatrix();//�� �簢��(�� �Ķ���~~!)
	{
		glTranslatef(x, 45, z);

		if (move_w == 1)
		{
			glTranslatef(0, -45, -45);
			glRotatef(x_ro, 1, 0, 0);
			glTranslatef(0, 45, 45);
		}
		if (move_s == 1)
		{
			glTranslatef(0, -45, 45);
			glRotatef(x_ro, 1, 0, 0);
			glTranslatef(0, 45, -45);
		}
		if (move_a == 1)
		{
			glTranslatef(-45, -45, 0);
			glRotatef(z_ro, 0, 0, 1);
			glTranslatef(45, 45, 0);
		}
		if (move_d == 1)
		{
			glTranslatef(45, -45, 0);
			glRotatef(z_ro, 0, 0, 1);
			glTranslatef(-45, 45, 0);
		}

		glColor3ub(120, 55, 18);
		glutSolidCube(90);
		glColor3ub(0, 0, 0);
		glutWireCube(90);
	}
	glPopMatrix();
}

void Main_cube::cookie_draw()
{
	for (int i = 0; i < 100; i++)
	{
		if (cookie_active[i] == 1)
		{
			glPushMatrix();
			{
				glTranslatef(cookie_x[i], 15, cookie_z[i]);
				glColor3ub(232, 204, 255);
				glutSolidCube(30);
				glColor3ub(0, 0, 0);
				glutWireCube(30);
			}
			glPopMatrix();
		}
	}
}

void Main_cube::cookie_make()
{
	cookie_active[cookie_num] = 1;
	cookie_x[cookie_num] = x;
	cookie_z[cookie_num] = z;
	cookie_time[cookie_num] = 500;

	if (cookie_num == 99)
		cookie_num = 0;
	else
		cookie_num++;
}