#include "basic.h"
#include "enemy_cube.h"

void Enemy_cube::draw()
{
	glPushMatrix();//�� ť��
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

void Enemy_cube::light_draw()
{
	GLfloat AmbientLight[] = { 0, 0, 0, 0 };//�ֺ� ����
	GLfloat DiffuseLight[] = { 50.0f, 50.0f, 50.0f, 0.0f };//��� �ݻ� ����
	GLfloat SpecularLight[] = { 0.0f, 0.0f, 0.0f, 0.0f };//�ſ�ݻ� ����
	GLfloat lightPos[] = {light_x, 2000, light_z, 1 };
	float spotlightDirection[] = { 0.0f, -1.0f, -0.0f };              // ����Ʈ����Ʈ ����
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 50.0f);                  // 90�� ����
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 100.0f);                 // ���� ����
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotlightDirection);   // ���� ����

	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glEnable(GL_LIGHT0);
}