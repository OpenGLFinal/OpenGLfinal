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
					
					glEnable(GL_TEXTURE_2D);
					glColor3f(1, 1, 1);
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
		}
	}


	glPushMatrix();//¹Ù´Ú ÆÇ
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
}

void Maps::light_draw()
{

}