#pragma once

class Maps
{
public:
	GLuint map_sp[1];

	//����
	int map[map_length][map_length];

	//�Լ�
	void draw();
	void light_draw();
};