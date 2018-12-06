#include "basic.h"
#include "main_cube.h"

void Main_cube::draw()
{
	glPushMatrix();//적 사각형(명예 파랑이~~!)
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