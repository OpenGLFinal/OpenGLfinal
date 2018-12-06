#include "basic.h"
#include "enemy_cube.h"

void Enemy_cube::draw()
{
	glPushMatrix();//Àû Å¥ºê
	{
		glTranslatef(x, 90, z);

		if (move_w == 1)
		{
			glTranslatef(0, -90, -90);
			glRotatef(x_ro, 1, 0, 0);
			glTranslatef(0, 90, 90);
		}
		if (move_s == 1)
		{
			glTranslatef(0, -90, 90);
			glRotatef(x_ro, 1, 0, 0);
			glTranslatef(0, 90, -90);
		}
		if (move_a == 1)
		{
			glTranslatef(-90, -90, 0);
			glRotatef(z_ro, 0, 0, 1);
			glTranslatef(90, 90, 0);
		}
		if (move_d == 1)
		{
			glTranslatef(90, -90, 0);
			glRotatef(z_ro, 0, 0, 1);
			glTranslatef(-90, 90, 0);
		}

		glColor3ub(0, 0, 255);
		glutSolidCube(180);
		glColor3ub(0, 0, 0);
		glutWireCube(180);
	}
	glPopMatrix();
}