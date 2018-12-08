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
				glPushMatrix();//����
				{
					glTranslatef(-90 * map_length + (j * 180), 90, -90 * map_length + (i * 180));
					glColor3ub(30, 30, 30);

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
				}
				glPopMatrix();
			}
		}
	}

	glPushMatrix();//�ٴ� ��
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
}