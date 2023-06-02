#pragma once

//#pragma comment(lib, "FMOD/fmod_vc.lib")

#include "fmod.hpp"
#include "fmod_errors.h"
//#include <iostream>

using namespace FMOD;

static System* pSystem;
static Sound* pSound[35];
static Channel* pBGM[5];
static Channel* pEFFECT[35];
static Channel* pWalkSound[1];



void SoundSystem();
void SoundStop(int idx);
void PlayWalk();
void SoundPlay(int Sound_num);
void BGM(int Sound_num);
void BGMPause();
void NextBGM();
void PlayStop();

static bool* isPaused;
//void BGM();
//void BGMPasue();
//void BGMPlay();


