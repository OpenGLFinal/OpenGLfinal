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
				glPushMatrix();//ÁöÇü
				{
					glTranslatef(-90 * map_length + (j * 180), 90, -90 * map_length + (i * 180));
					glColor3ub(30, 30, 30);

					glBegin(GL_QUADS);
					glVertex3f(-90, 90, -90);
					glVertex3f(-90, 90, 90);
					glVertex3f(90, 90, 90);
					glVertex3f(90, 90, -90);
					glEnd();

					glBegin(GL_QUADS);
					glVertex3f(90, -90, -90);
					glVertex3f(90, -90, 90);
					glVertex3f(-90, -90, 90);
					glVertex3f(-90, -90, -90);
					glEnd();

					glBegin(GL_QUADS);
					glVertex3f(-90, 90, -90);
					glVertex3f(-90, -90, -90);
					glVertex3f(-90, -90, 90);
					glVertex3f(-90, 90, 90);
					glEnd();

					glBegin(GL_QUADS);
					glVertex3f(90, 90, 90);
					glVertex3f(90, -90, 90);
					glVertex3f(90, -90, -90);
					glVertex3f(90, 90, -90);
					glEnd();

					glBegin(GL_QUADS);
					glVertex3f(-90, 90, 90);
					glVertex3f(-90, -90, 90);
					glVertex3f(90, -90, 90);
					glVertex3f(90, 90, 90);
					glEnd();
					
					glBegin(GL_QUADS);
					glVertex3f(90, 90, -90);
					glVertex3f(90, -90, -90);
					glVertex3f(-90, -90, -90);
					glVertex3f(-90, 90, -90);
					glEnd();
				}
				glPopMatrix();
			}
		}
	}

	glPushMatrix();//¹Ù´Ú ÆÇ
	{
		glColor3ub(50, 50, 50);

		glBegin(GL_QUADS);
		glVertex3f(-1000, 1, -1000);
		glVertex3f(-1000, 1, 1000);
		glVertex3f(1000, 0, 1000);
		glVertex3f(1000, 0, -1000);
		glEnd();
	}
	glPopMatrix();
}