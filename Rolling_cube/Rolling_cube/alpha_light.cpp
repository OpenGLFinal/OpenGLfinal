#include "basic.h"
#include "alpha_light.h"

void Alpha_light::light_draw()
{
	GLfloat AmbientLight[] = { 0, 0, 0, 0 };//주변 조명
	GLfloat DiffuseLight[] = { 50.0f, 50.0f, 0.0f, 0.0f };//산란 반사 조명
	GLfloat SpecularLight[] = { 0.0f, 0.0f, 0.0f, 0.0f };//거울반사 조명
	GLfloat lightPos1[] = { x[0], 1000, z[0], 1 };
	GLfloat lightPos2[] = { x[1], 1000, z[1], 1 };
	GLfloat lightPos3[] = { x[2], 1000, z[2], 1 };
	float spotlightDirection[] = { 0.0f, -1.0f, 0.0f };              // 스포트라이트 방향

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 50.0f);                  // 90도 원뿔
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 100.0f);                 // 초점 설정
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotlightDirection);   // 방향 설정
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 50.0f);                  // 90도 원뿔
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 100.0f);                 // 초점 설정
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotlightDirection);   // 방향 설정
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 50.0f);                  // 90도 원뿔
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 100.0f);                 // 초점 설정
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spotlightDirection);   // 방향 설정

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