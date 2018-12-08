#include "basic.h"
#include "main_cube.h"

void Main_cube::draw()
{
	glPushMatrix();
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

		glEnable(GL_TEXTURE_2D);
		glColor3f(0.3, 0.3, 0.3);
		glBindTexture(GL_TEXTURE_2D, main_cube_sp[0]);

		glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3f(-45.0, 45.0, 45.0);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3f(-45.0, -45.0, 45.0);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3f(45.0, -45.0, 45.0);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3f(45.0, 45.0, 45.0);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3f(45.0, 45.0, 45.0);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3f(45.0, -45.0, 45.0);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3f(45.0, -45.0, -45.0);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3f(45.0, 45.0, -45.0);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3f(-45.0, 45.0, -45.0);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3f(45.0, 45.0, -45.0);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3f(45.0, -45.0, -45.0);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3f(-45.0, -45.0, -45.0);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3f(-45.0, 45.0, 45.0);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3f(-45.0, 45.0, -45.0);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3f(-45.0, -45.0, -45.0);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3f(-45.0, -45.0, 45.0);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3f(-45.0, -45.0, 45.0);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3f(-45.0, -45.0, -45.0);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3f(45.0, -45.0, -45.0);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3f(45.0, -45.0, 45.0);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3f(-45.0, 45.0, 45.0);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3f(45.0, 45.0, 45.0);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3f(45.0, 45.0, -45.0);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3f(-45.0, 45.0, -45.0);
		glEnd();

		glDisable(GL_TEXTURE_2D);
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
				glColor3ub(132, 104, 155);
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