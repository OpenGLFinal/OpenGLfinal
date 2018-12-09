#include "basic.h"
#include "alpha_light.h"

void Alpha_light::light_draw(int crash1, int crash2, int crash3, int crash4, int crash5)
{ 
	GLfloat AmbientLight[] = { 0, 0, 0, 0 };//주변 조명
	GLfloat DiffuseLight1[] = { 30 - crash1 * 30.0f, 30.0f, 0.0f, 0.0f };//산란 반사 조명
	GLfloat DiffuseLight2[] = { 30 - crash2 * 30.0f, 30.0f, 0.0f, 0.0f };//산란 반사 조명
	GLfloat DiffuseLight3[] = { 30 - crash3 * 30.0f, 30.0f, 0.0f, 0.0f };//산란 반사 조명
	GLfloat DiffuseLight4[] = { 30 - crash4 * 30.0f, 30.0f, 0.0f, 0.0f };//산란 반사 조명
	GLfloat DiffuseLight5[] = { 30 - crash5 * 30.0f, 30.0f, 0.0f, 0.0f };//산란 반사 조명
	GLfloat SpecularLight[] = { 0.0f, 0.0f, 0.0f, 0.0f };//거울반사 조명
	GLfloat lightPos1[] = { x[0], 720, z[0] + 90, 1 };
	GLfloat lightPos2[] = { x[1], 720, z[1] + 90, 1 };
	GLfloat lightPos3[] = { x[2], 720, z[2] + 90, 1 };
	GLfloat lightPos4[] = { x[3], 720, z[3] + 90, 1 };
	GLfloat lightPos5[] = { x[4], 720, z[4] + 90, 1 };
	float spotlightDirection[] = { 0.0f, -1.0f, 0.0f };              // 스포트라이트 방향

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 50.0f);                  // 90도 원뿔
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT,  50.0f);                 // 초점 설정
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotlightDirection);   // 방향 설정
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 50.0f);                  // 90도 원뿔
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 100.0f);                 // 초점 설정
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotlightDirection);   // 방향 설정
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 50.0f);                  // 90도 원뿔
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 100.0f);                 // 초점 설정
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spotlightDirection);   // 방향 설정
	glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 50.0f);                  // 90도 원뿔
	glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 100.0f);                 // 초점 설정
	glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, spotlightDirection);   // 방향 설정
	glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 50.0f);                  // 90도 원뿔
	glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 100.0f);                 // 초점 설정
	glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, spotlightDirection);   // 방향 설정

	glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	glLightfv(GL_LIGHT2, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, DiffuseLight2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);
	glLightfv(GL_LIGHT3, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, DiffuseLight3);
	glLightfv(GL_LIGHT3, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT3, GL_POSITION, lightPos3);
	glLightfv(GL_LIGHT4, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, DiffuseLight4);
	glLightfv(GL_LIGHT4, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT4, GL_POSITION, lightPos4);
	glLightfv(GL_LIGHT5, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, DiffuseLight5);
	glLightfv(GL_LIGHT5, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT5, GL_POSITION, lightPos5);

	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);
	glEnable(GL_LIGHT5);
}