#include "basic.h"
#include "maps.h"

void Maps::draw()
{
	for (int i = 0; i < map_length; i++)
	{
		for (int j = 0; j < map_length; j++)
		{
			if (map[i][j] == 1)
			{
				glPushMatrix();//지형
				{
					glTranslatef(-90 * map_length + (j * 180), 90, -90 * map_length + (i * 180));

					glEnable(GL_TEXTURE_2D);
					glColor3f(0.1, 0.1, 0.1);
					glBindTexture(GL_TEXTURE_2D, map_sp[0]);

					glBegin(GL_QUADS);
					glTexCoord2d(0.0f, 1.0f);
					glVertex3f(-90.0, 90.0, 90.0);
					glTexCoord2d(0.0f, 0.0f);
					glVertex3f(-90.0, -90.0, 90.0);
					glTexCoord2d(1.0f, 0.0f);
					glVertex3f(90.0, -90.0, 90.0);
					glTexCoord2d(1.0f, 1.0f);
					glVertex3f(90.0, 90.0, 90.0);
					glEnd();

					glBegin(GL_QUADS);
					glTexCoord2d(0.0f, 1.0f);
					glVertex3f(90.0, 90.0, 90.0);
					glTexCoord2d(0.0f, 0.0f);
					glVertex3f(90.0, -90.0, 90.0);
					glTexCoord2d(1.0f, 0.0f);
					glVertex3f(90.0, -90.0, -90.0);
					glTexCoord2d(1.0f, 1.0f);
					glVertex3f(90.0, 90.0, -90.0);
					glEnd();

					glBegin(GL_QUADS);
					glTexCoord2d(0.0f, 1.0f);
					glVertex3f(-90.0, 90.0, -90.0);
					glTexCoord2d(0.0f, 0.0f);
					glVertex3f(90.0, 90.0, -90.0);
					glTexCoord2d(1.0f, 0.0f);
					glVertex3f(90.0, -90.0, -90.0);
					glTexCoord2d(1.0f, 1.0f);
					glVertex3f(-90.0, -90.0, -90.0);
					glEnd();

					glBegin(GL_QUADS);
					glTexCoord2d(0.0f, 1.0f);
					glVertex3f(-90.0, 90.0, 90.0);
					glTexCoord2d(0.0f, 0.0f);
					glVertex3f(-90.0, 90.0, -90.0);
					glTexCoord2d(1.0f, 0.0f);
					glVertex3f(-90.0, -90.0, -90.0);
					glTexCoord2d(1.0f, 1.0f);
					glVertex3f(-90.0, -90.0, 90.0);
					glEnd();

					glBegin(GL_QUADS);
					glTexCoord2d(0.0f, 1.0f);
					glVertex3f(-90.0, -90.0, 90.0);
					glTexCoord2d(0.0f, 0.0f);
					glVertex3f(-90.0, -90.0, -90.0);
					glTexCoord2d(1.0f, 0.0f);
					glVertex3f(90.0, -90.0, -90.0);
					glTexCoord2d(1.0f, 1.0f);
					glVertex3f(90.0, -90.0, 90.0);
					glEnd();

					glBegin(GL_QUADS);
					glTexCoord2d(0.0f, 1.0f);
					glVertex3f(-90.0, 90.0, 90.0);
					glTexCoord2d(0.0f, 0.0f);
					glVertex3f(90.0, 90.0, 90.0);
					glTexCoord2d(1.0f, 0.0f);
					glVertex3f(90.0, 90.0, -90.0);
					glTexCoord2d(1.0f, 1.0f);
					glVertex3f(-90.0, 90.0, -90.0);
					glEnd();

					glDisable(GL_TEXTURE_2D);
				}
				glPopMatrix();
			}
			if (map[i][j] == 5)
			{
				glPushMatrix();//캐릭터만 통과 지형
				{
					glTranslatef(-90 * map_length + (j * 180), 0, -90 * map_length + (i * 180));
					glColor3f(0.5, 0.5, 0.5);
					glLineWidth(10);
					glBegin(GL_LINES);
					glVertex3f(-85.0, 120.0, 85.0);
					glVertex3f(85.0, 120.0, 85.0);
					glVertex3f(-85.0, 120.0, -85.0);
					glVertex3f(85.0, 120.0, -85.0);
					glVertex3f(-85.0, 120.0, -85.0);
					glVertex3f(-85.0, 120.0, 85.0);
					glVertex3f(85.0, 120.0, -85.0);
					glVertex3f(85.0, 120.0, 85.0);

					glVertex3f(-85.0, 120.0, -85.0);
					glVertex3f(-85.0, 0.0, -85.0);
					glVertex3f(85.0, 120.0, -85.0);
					glVertex3f(85.0, 0.0, -85.0);
					glVertex3f(-85.0, 120.0, 85.0);
					glVertex3f(-85.0, 0.0, 85.0);
					glVertex3f(85.0, 120.0, 85.0);
					glVertex3f(85.0, 0.0, 85.0);
					glEnd();
					glLineWidth(1);
				}
				glPopMatrix();
			}
		}
	}


	glPushMatrix();//바닥 판
	{
		glColor3ub(50, 50, 50);

		for (int i = 0; i < 200; i++)
		{
			for (int j = 0; j < 200; j++)
			{
				glPushMatrix();
				{
					glTranslatef(i * 20 - 2000, 0, j * 20 - 2000);

					glBegin(GL_QUADS);
					glVertex3f(-10, 0, -10);
					glVertex3f(-10, 0, 10);
					glVertex3f(10, 0, 10);
					glVertex3f(10, 0, -10);
					glEnd();
				}
				glPopMatrix();
			}
		}
	}
	glPopMatrix();


	if (key == 1)
	{
		glPushMatrix();//엸쇠
		{
			glTranslatef(0.0, 140, 0.0);
			//glRotatef(-60.0, 0.0, 0.0, 1.0);

			glColor3f(0.6, 0.6, 0.6);
			glutSolidTorus(20, 40, 10, 10);

			glPushMatrix();
			glTranslatef(0.0, -107.0, 0.0);
			glScalef(1.2, 3.5, 1.0);
			glutSolidCube(30);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(30.0, -107.0, 0.0);
			glScalef(1.0, 1.0, 1.0);
			glutSolidCube(25);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(25.0, -142.0, 0.0);
			glScalef(1.0, 1.0, 1.0);
			glutSolidCube(18);
			glPopMatrix();


			glLineWidth(3.0);
			glColor3f(0.0, 0.0, 0.0);
			glutWireTorus(20, 40, 5, 10);

			glPushMatrix();
			glTranslatef(0.0, -107.0, 0.0);
			glScalef(1.2, 3.5, 1.0);
			glutWireCube(30);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(30.0, -107.0, 0.0);
			glScalef(1.0, 1.0, 1.0);
			glutWireCube(25);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(25.0, -142.0, 0.0);
			glScalef(1.0, 1.0, 1.0);
			glutWireCube(18);
			glPopMatrix();

		}
		glPopMatrix();
	}

	for (int i = 0; i < 4; i++)
	{
		if (fire_active[i] == 1)
		{
			glPushMatrix();//경보
			{
				glTranslatef(fire_x[i], 0, fire_z[i]);


				glPushMatrix();
				{
					glScalef(1.5, 1, 1.5);
					glTranslatef(0.0, 0.0, 0.0);
					glColor3ub(45, 45, 45);;
					//glutSolidCube(60);

					glBegin(GL_QUADS);
					glVertex3f(-50, 1, -50);
					glVertex3f(-50, 1, 50);
					glVertex3f(50, 1, 50);
					glVertex3f(50, 1, -50);
					glEnd();
				}
				glPopMatrix();

				glPushMatrix();
				{
					glScalef(1.5, 1, 1.5);
					glTranslatef(0.0, 1.0, 0.0);
					glColor3ub(65, 25, 25);;
					//glutSolidCube(60);

					glBegin(GL_QUADS);
					glVertex3f(-10, 1, -10);
					glVertex3f(-10, 1, 10);
					glVertex3f(10, 1, 10);
					glVertex3f(10, 1, -10);
					glEnd();
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
	}
}

void Maps::light_draw()
{

}