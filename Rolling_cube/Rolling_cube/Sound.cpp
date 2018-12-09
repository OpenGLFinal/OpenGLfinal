#include "stdafx.h"
#include "Sound.h"


CSound::CSound()
{
	FMOD::System_Create(&pSystem);
	pSystem->init(
		SOUND_NUM
		, FMOD_INIT_NORMAL
		, nullptr
	);
	for (auto& p : pSound) p = nullptr;
}


CSound::~CSound()
{
	for (int i = 0; i < SOUND_NUM; ++i)
	{
		pSound[i]->release();
	}

	pSystem->release();
	pSystem->close();
}

void CSound::Add_sound()
{
	pSystem->createStream(
		"Sound\\bgm.mp3"
		, FMOD_2D | FMOD_LOOP_NORMAL
		, nullptr
		, &pSound[0]
	); // 배경음 사운드

	pSystem->createStream(
		"Sound\\main_move.mp3"
		, FMOD_2D | FMOD_LOOP_OFF
		, nullptr
		, &pSound[1]
	);
	
	pSystem->createStream(
		"Sound\\enemy_move.mp3"
		, FMOD_2D | FMOD_LOOP_OFF
		, nullptr
		, &pSound[2]
	);

	pSystem->createStream(
		"Sound\\door_sound.mp3"
		, FMOD_2D | FMOD_LOOP_OFF
		, nullptr
		, &pSound[3]
	);

	pSystem->createStream(
		"Sound\\fire_sound2.mp3"
		, FMOD_2D | FMOD_LOOP_OFF
		, nullptr
		, &pSound[4]
	);
}

void CSound::Play(int n)
{
	pSystem->update();

	pSystem->playSound(pSound[n]
		, nullptr, false, &pChannel[n]);

}
