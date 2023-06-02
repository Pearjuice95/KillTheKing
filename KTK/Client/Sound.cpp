#include "Sound.h"

void SoundSystem()
{
	System_Create(&pSystem);

	pSystem->init(32, FMOD_INIT_NORMAL, 0);

	// 플레이어 사운드
	pSystem->createSound("../Resourse/Sound/PlayerWalk.mp3", FMOD_LOOP_NORMAL, 0, &pSound[0]); // 플레이어 이동
	pSystem->createSound("../Resourse/Sound/PlayerDash.mp3", FMOD_DEFAULT, 0, &pSound[1]); // 플레이어 대시 O
	pSystem->createSound("../Resourse/Sound/PlayerAttack1.mp3", FMOD_DEFAULT, 0, &pSound[2]); // 플레이어 기본공격 O
	pSystem->createSound("../Resourse/Sound/PlayerAttack2.mp3", FMOD_DEFAULT, 0, &pSound[3]); // 플레이어 2타공격 O
	pSystem->createSound("../Resourse/Sound/PlayerHit.mp3", FMOD_DEFAULT, 0, &pSound[4]); // 플레이어 피격 O
	pSystem->createSound("../Resourse/Sound/PlayerDeath.mp3", FMOD_DEFAULT, 0, &pSound[5]); // 플레이어 사망 O
	pSystem->createSound("../Resourse/Sound/PowerBoom.mp3", FMOD_DEFAULT, 0, &pSound[6]); // 플레이어 필살기 O
	pSystem->createSound("../Resourse/Sound/PowerAttack1.mp3", FMOD_DEFAULT, 0, &pSound[7]); // 플레이어 필살기 기본공격 O
	pSystem->createSound("../Resourse/Sound/PowerAttack2.mp3", FMOD_DEFAULT, 0, &pSound[8]); // 플레이어 필살기 2타공격 O

	// BGM
	pSystem->createSound("../Resourse/Sound/Title.mp3", FMOD_LOOP_NORMAL, 0, &pSound[9]); // 타이틀
	pSystem->createSound("../Resourse/Sound/Stagoe00.mp3", FMOD_LOOP_NORMAL, 0, &pSound[10]); // 스테이지 0
	pSystem->createSound("../Resourse/Sound/StageBGM.mp3", FMOD_LOOP_NORMAL, 0, &pSound[11]); // 스테이지 1,2
	pSystem->createSound("../Resourse/Sound/Stage03_Start.mp3", FMOD_DEFAULT, 0, &pSound[12]); // 스테이지 3 입장
	pSystem->createSound("../Resourse/Sound/Stage03.mp3", FMOD_LOOP_NORMAL, 0, &pSound[13]); // 스테이지 3 전투

	// 몬스터 사운드
	pSystem->createSound("../Resourse/Sound/EnemyAttack.mp3", FMOD_DEFAULT, 0, &pSound[14]); // 근접병 공격 O
	pSystem->createSound("../Resourse/Sound/ArrowFire.mp3", FMOD_DEFAULT, 0, &pSound[15]); // 원거리 공격 O
	pSystem->createSound("../Resourse/Sound/EnemyHit.mp3", FMOD_DEFAULT, 0, &pSound[16]); // 몬스터 피격 ??
	pSystem->createSound("../Resourse/Sound/EnemyDie.mp3", FMOD_DEFAULT, 0, &pSound[17]); // 몬스터 사망 ??

	// 보스 사운드
	pSystem->createSound("../Resourse/Sound/BossJump.mp3", FMOD_DEFAULT, 0, &pSound[18]); // 보스 점프
	pSystem->createSound("../Resourse/Sound/BossDrop.mp3", FMOD_DEFAULT, 0, &pSound[19]); // 보스 착지
	pSystem->createSound("../Resourse/Sound/BossAttack.mp3", FMOD_DEFAULT, 0, &pSound[20]); // 보스 공격
	pSystem->createSound("../Resourse/Sound/FinalScene.mp3", FMOD_DEFAULT, 0, &pSound[21]); // 보스 HP 0
	pSystem->createSound("../Resourse/Sound/BossDeath.mp3", FMOD_DEFAULT, 0, &pSound[22]); // 파이널신 이후 출력

	// ETC
	pSystem->createSound("../Resourse/Sound/SUIReady.mp3", FMOD_DEFAULT, 0, &pSound[23]); // 필살기 게이지 찼을때
	pSystem->createSound("../Resourse/Sound/DoorHit.mp3", FMOD_DEFAULT, 0, &pSound[24]); // 성문 피격
	pSystem->createSound("../Resourse/Sound/DoorDestroy.mp3", FMOD_DEFAULT, 0, &pSound[25]); // 성문 파괴
	pSystem->createSound("../Resourse/Sound/DoorOpenClose.mp3", FMOD_DEFAULT, 0, &pSound[26]); // 성문 파괴
}

void SoundPlay(int Sound_num)
{
	pSystem->update();
	pSystem->playSound(pSound[Sound_num], 0, 0, pEFFECT);
}

void BGM(int Sound_num)
{
	pSystem->update();
	pSystem->playSound(pSound[Sound_num], 0, 0, pBGM);
}

void BGMPause()
{
	for (int i = 0; i < 5; i++)
	{
		pBGM[i]->setPaused(true);
	}
}

void NextBGM()
{

}

void SoundStop(int idx)
{
	pSystem->update();
	pEFFECT[idx]->stop();
}

void PlayStop()
{
	pSystem->update();
	pWalkSound[0]->stop();
}

void PlayWalk()
{
	pSystem->update();
	pSystem->playSound(pSound[0], 0, 0, &pWalkSound[0]);
	//pEFFECT[0]->getPaused(isPaused);
}