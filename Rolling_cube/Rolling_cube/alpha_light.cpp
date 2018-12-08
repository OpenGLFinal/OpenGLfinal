#include "basic.h"
#include "alpha_light.h"

void Alpha_light::light_draw()
{
	GLfloat AmbientLight[] = { 0, 0, 0, 0 };//�ֺ� ����
	GLfloat DiffuseLight[] = { 50.0f, 50.0f, 0.0f, 0.0f };//��� �ݻ� ����
	GLfloat SpecularLight[] = { 0.0f, 0.0f, 0.0f, 0.0f };//�ſ�ݻ� ����
	GLfloat lightPos1[] = { x[0], 1000, z[0], 1 };
	GLfloat lightPos2[] = { x[1], 1000, z[1], 1 };
	GLfloat lightPos3[] = { x[2], 1000, z[2], 1 };
	float spotlightDirection[] = { 0.0f, -1.0f, 0.0f };              // ����Ʈ����Ʈ ����

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 50.0f);                  // 90�� ����
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 100.0f);                 // ���� ����
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotlightDirection);   // ���� ����
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 50.0f);                  // 90�� ����
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 100.0f);                 // ���� ����
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotlightDirection);   // ���� ����
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 50.0f);                  // 90�� ����
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 100.0f);                 // ���� ����
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spotlightDirection);   // ���� ����

	glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	glLightfv(GL_LIGHT2, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT2, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);
	glLightfv(GL_LIGHT3, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT3, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT3, GL_POSITION, lightPos3);

	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
}