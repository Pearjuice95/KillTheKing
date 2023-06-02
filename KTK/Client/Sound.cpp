#include "Sound.h"

void SoundSystem()
{
	System_Create(&pSystem);

	pSystem->init(32, FMOD_INIT_NORMAL, 0);

	// �÷��̾� ����
	pSystem->createSound("../Resourse/Sound/PlayerWalk.mp3", FMOD_LOOP_NORMAL, 0, &pSound[0]); // �÷��̾� �̵�
	pSystem->createSound("../Resourse/Sound/PlayerDash.mp3", FMOD_DEFAULT, 0, &pSound[1]); // �÷��̾� ��� O
	pSystem->createSound("../Resourse/Sound/PlayerAttack1.mp3", FMOD_DEFAULT, 0, &pSound[2]); // �÷��̾� �⺻���� O
	pSystem->createSound("../Resourse/Sound/PlayerAttack2.mp3", FMOD_DEFAULT, 0, &pSound[3]); // �÷��̾� 2Ÿ���� O
	pSystem->createSound("../Resourse/Sound/PlayerHit.mp3", FMOD_DEFAULT, 0, &pSound[4]); // �÷��̾� �ǰ� O
	pSystem->createSound("../Resourse/Sound/PlayerDeath.mp3", FMOD_DEFAULT, 0, &pSound[5]); // �÷��̾� ��� O
	pSystem->createSound("../Resourse/Sound/PowerBoom.mp3", FMOD_DEFAULT, 0, &pSound[6]); // �÷��̾� �ʻ�� O
	pSystem->createSound("../Resourse/Sound/PowerAttack1.mp3", FMOD_DEFAULT, 0, &pSound[7]); // �÷��̾� �ʻ�� �⺻���� O
	pSystem->createSound("../Resourse/Sound/PowerAttack2.mp3", FMOD_DEFAULT, 0, &pSound[8]); // �÷��̾� �ʻ�� 2Ÿ���� O

	// BGM
	pSystem->createSound("../Resourse/Sound/Title.mp3", FMOD_LOOP_NORMAL, 0, &pSound[9]); // Ÿ��Ʋ
	pSystem->createSound("../Resourse/Sound/Stagoe00.mp3", FMOD_LOOP_NORMAL, 0, &pSound[10]); // �������� 0
	pSystem->createSound("../Resourse/Sound/StageBGM.mp3", FMOD_LOOP_NORMAL, 0, &pSound[11]); // �������� 1,2
	pSystem->createSound("../Resourse/Sound/Stage03_Start.mp3", FMOD_DEFAULT, 0, &pSound[12]); // �������� 3 ����
	pSystem->createSound("../Resourse/Sound/Stage03.mp3", FMOD_LOOP_NORMAL, 0, &pSound[13]); // �������� 3 ����

	// ���� ����
	pSystem->createSound("../Resourse/Sound/EnemyAttack.mp3", FMOD_DEFAULT, 0, &pSound[14]); // ������ ���� O
	pSystem->createSound("../Resourse/Sound/ArrowFire.mp3", FMOD_DEFAULT, 0, &pSound[15]); // ���Ÿ� ���� O
	pSystem->createSound("../Resourse/Sound/EnemyHit.mp3", FMOD_DEFAULT, 0, &pSound[16]); // ���� �ǰ� ??
	pSystem->createSound("../Resourse/Sound/EnemyDie.mp3", FMOD_DEFAULT, 0, &pSound[17]); // ���� ��� ??

	// ���� ����
	pSystem->createSound("../Resourse/Sound/BossJump.mp3", FMOD_DEFAULT, 0, &pSound[18]); // ���� ����
	pSystem->createSound("../Resourse/Sound/BossDrop.mp3", FMOD_DEFAULT, 0, &pSound[19]); // ���� ����
	pSystem->createSound("../Resourse/Sound/BossAttack.mp3", FMOD_DEFAULT, 0, &pSound[20]); // ���� ����
	pSystem->createSound("../Resourse/Sound/FinalScene.mp3", FMOD_DEFAULT, 0, &pSound[21]); // ���� HP 0
	pSystem->createSound("../Resourse/Sound/BossDeath.mp3", FMOD_DEFAULT, 0, &pSound[22]); // ���̳ν� ���� ���

	// ETC
	pSystem->createSound("../Resourse/Sound/SUIReady.mp3", FMOD_DEFAULT, 0, &pSound[23]); // �ʻ�� ������ á����
	pSystem->createSound("../Resourse/Sound/DoorHit.mp3", FMOD_DEFAULT, 0, &pSound[24]); // ���� �ǰ�
	pSystem->createSound("../Resourse/Sound/DoorDestroy.mp3", FMOD_DEFAULT, 0, &pSound[25]); // ���� �ı�
	pSystem->createSound("../Resourse/Sound/DoorOpenClose.mp3", FMOD_DEFAULT, 0, &pSound[26]); // ���� �ı�
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