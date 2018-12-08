#pragma once

class Maps
{
public:
	GLuint map_sp[1];

	//변수
	int map[map_length][map_length];

	//함수
	void draw();
	void light_draw();
};