#include "CBackGroundObject.h"
#include "enum.h"
#include "YDEngine.h"
#include "AnimationManager.h"
#include "CSprite.h"
#include "Camera.h"
#include "CObjectManager.h"
#include "CPlayerObject.h"
#include "CWallObject.h"

CBackGroundObject::CBackGroundObject()
	:CObjectBase(CVector2D(0, 0), eObjectKind::ETC)//, isCollided(false)
{
	pEngine = AnimationManager::GetInstance()->m_pEngine;
	//std::fill_n(m_Board, 4 * 24 * 26, 0);
	/*CBackGroundObject::readingCSV();*/
}

CBackGroundObject::~CBackGroundObject()
{
}

void CBackGroundObject::InitMap()
{
	LoadBackGround();
	ChangeSprite();
	//CBackGroundObject::readingCSV(); 망함
	SetBackGroundCollider();
	PushRECT();
}

void CBackGroundObject::LoadBackGround()
{
	pEngine->LoadMapSpriteSheet(L"../Resourse/SpriteSheet/Stage/Title.png"); // 타이틀
	pEngine->LoadMapSpriteSheet(L"../Resourse/SpriteSheet/Stage/Stage00.png"); // 튜톨
	pEngine->LoadMapSpriteSheet(L"../Resourse/SpriteSheet/Stage/Stage01.png"); // 1번 스테이지
	pEngine->LoadMapSpriteSheet(L"../Resourse/SpriteSheet/Stage/Stage02.png"); // 2번 스테이지
	pEngine->LoadMapSpriteSheet(L"../Resourse/SpriteSheet/Stage/Stage03.png"); // 3번 스테이지
	pEngine->LoadMapSpriteSheet(L"../Resourse/SpriteSheet/Stage/Stage03.png"); // 엔딩

}

void CBackGroundObject::ChangeSprite()
{
	m_backgroundSprite[0] = pEngine->LoadMapSpriteFromData(0, 1920, 1080);	// 타이틀
	m_backgroundSprite[1] = pEngine->LoadMapSpriteFromData(1, 1379, 860);	// 튜톨
	m_backgroundSprite[2] = pEngine->LoadMapSpriteFromData(2, 4130, 2925);	// 1번
	m_backgroundSprite[3] = pEngine->LoadMapSpriteFromData(3, 1895, 3098);	// 2번
	m_backgroundSprite[4] = pEngine->LoadMapSpriteFromData(4, 2236, 4472);	// 3번
	m_backgroundSprite[5] = pEngine->LoadMapSpriteFromData(5, 2236, 4472);	// 엔딩
}

void CBackGroundObject::DrawBackGround()
{

	// 나중에 씬매니저를 받아서 관리해주자.
	//pEngine->DrawMapSprite(m_backgroundSprite[0], 0, 0, 0, 0, 1, Camera::GetInsance()->GetCameraVector()); //인덱스,무쓸모,무쓸모,타겟x좌표,타겟y좌표, 투명도
	//pEngine->DrawMapSprite(m_backgroundSprite[1], 0, 0, 0, 0, 1, Camera::GetInsance()->GetCameraVector()); //인덱스,무쓸모,무쓸모,타겟x좌표,타겟y좌표, 투명도
	//pEngine->DrawMapSprite(m_backgroundSprite[2], 0, 0, 0, 0, 1, Camera::GetInsance()->GetCameraVector()); //인덱스,무쓸모,무쓸모,타겟x좌표,타겟y좌표, 투명도
	//pEngine->DrawMapSprite(m_backgroundSprite[3], 0, 0, 0, 0, 1, Camera::GetInsance()->GetCameraVector()); //인덱스,무쓸모,무쓸모,타겟x좌표,타겟y좌표, 투명도
}

void CBackGroundObject::SetBackGroundCollider()
{

	/// csv망해서 수동으로 찍음 ㅜㅜ

	// 	for (int i = 0; i < 7; ++i)
	// 	{
	// 		static int j = 0;
	// 		Stage0BGC[i] = MakeRect(vlocationList, 4 * j);
	// 		j++;
	// 	}
	// 
	// 	for (int i = 0; i < 25; ++i)
	// 	{
	// 		static int j = 7;
	// 
	// 		Stage1BGC[i] = MakeRect(vlocationList, 4 * j);
	// 		j++;
	// 	}
	// 
	// 	for (int i = 0; i < 20; ++i)
	// 	{
	// 		static int j = 32;
	// 
	// 		Stage2BGC[i] = MakeRect(vlocationList, 4 * j);
	// 		j++;
	// 	}
	// 
	// 	for (int i = 0; i < 14; ++i)
	// 	{
	// 		static int j = 52;
	// 
	// 		Stage3BGC[i] = MakeRect(vlocationList, 4 * j);
	// 		j++;
	// 	}

	Stage0BGC[0] = MakeRect(0, 0, 1065, 370);
	Stage0BGC[1] = MakeRect(0, 493, 1064, 859);
	Stage0BGC[2] = MakeRect(1088, 169, 1240, 290);
	Stage0BGC[3] = MakeRect(1088, 579, 1238, 699);
	Stage0BGC[4] = MakeRect(1167, 0, 1377, 285);
	Stage0BGC[5] = MakeRect(1167, 583, 1375, 860);
	Stage0BGC[6] = MakeRect(1166, 288, 1375, 586);

	Stage00.push_back(Stage0BGC[0]);
	Stage00.push_back(Stage0BGC[1]);
	Stage00.push_back(Stage0BGC[2]);
	Stage00.push_back(Stage0BGC[3]);
	Stage00.push_back(Stage0BGC[4]);
	Stage00.push_back(Stage0BGC[5]);
	Stage00.push_back(Stage0BGC[6]);	// 깨져야하는문


	Stage1BGC[0] = MakeRect(830, 132, 1051, 336);
	Stage1BGC[1] = MakeRect(135, 1308, 344, 1603);
	Stage1BGC[2] = MakeRect(845, 2581, 1063, 2788);
	Stage1BGC[3] = MakeRect(3074, 139, 3294, 346);
	Stage1BGC[4] = MakeRect(3785, 1350, 3993, 1568);
	Stage1BGC[5] = MakeRect(3077, 2581, 3295, 2788);
	Stage1BGC[6] = MakeRect(75, 135, 833, 345);
	Stage1BGC[7] = MakeRect(1052, 135, 1819, 345);
	Stage1BGC[8] = MakeRect(75, 345, 345, 1309);
	Stage1BGC[9] = MakeRect(75, 1603, 345, 2579);
	Stage1BGC[10] = MakeRect(75, 2579, 845, 2790);
	Stage1BGC[11] = MakeRect(1063, 2580, 1819, 2790);
	Stage1BGC[12] = MakeRect(1549, 1721, 1819, 2579);
	Stage1BGC[13] = MakeRect(1549, 345, 1819, 1205);
	Stage1BGC[14] = MakeRect(1820, 997, 2312, 1205);
	Stage1BGC[15] = MakeRect(1820, 1721, 2312, 1930);
	Stage1BGC[16] = MakeRect(2312, 1721, 2580, 2578);
	Stage1BGC[17] = MakeRect(2312, 345, 2580, 1205);
	Stage1BGC[18] = MakeRect(2312, 135, 3075, 345);
	Stage1BGC[19] = MakeRect(3293, 135, 4055, 345);
	Stage1BGC[20] = MakeRect(3785, 345, 4055, 1349);
	Stage1BGC[21] = MakeRect(3785, 1569, 4055, 2581);
	Stage1BGC[22] = MakeRect(2312, 2579, 3075, 2790);
	Stage1BGC[23] = MakeRect(3295, 2581, 4055, 2790);
	Stage1BGC[24] = MakeRect(3112, 1388, 3234, 1541);

	// Door
	Stage01.push_back(Stage1BGC[0]);
	Stage01.push_back(Stage1BGC[1]);
	Stage01.push_back(Stage1BGC[2]);
	Stage01.push_back(Stage1BGC[3]);
	Stage01.push_back(Stage1BGC[4]);
	Stage01.push_back(Stage1BGC[5]);
	Stage01.push_back(Stage1BGC[6]);
	//


	Stage01.push_back(Stage1BGC[7]);
	Stage01.push_back(Stage1BGC[8]);
	Stage01.push_back(Stage1BGC[9]);
	Stage01.push_back(Stage1BGC[10]);
	Stage01.push_back(Stage1BGC[11]);
	Stage01.push_back(Stage1BGC[12]);
	Stage01.push_back(Stage1BGC[13]);
	Stage01.push_back(Stage1BGC[14]);
	Stage01.push_back(Stage1BGC[15]);
	Stage01.push_back(Stage1BGC[16]);
	Stage01.push_back(Stage1BGC[17]);
	Stage01.push_back(Stage1BGC[18]);
	Stage01.push_back(Stage1BGC[19]);
	Stage01.push_back(Stage1BGC[20]);
	Stage01.push_back(Stage1BGC[21]);
	Stage01.push_back(Stage1BGC[22]);
	Stage01.push_back(Stage1BGC[23]);
	Stage01.push_back(Stage1BGC[24]);


	Stage2BGC[0] = MakeRect(708, 2, 1182, 343);
	Stage2BGC[1] = MakeRect(1549, 497, 1756, 715);
	Stage2BGC[2] = MakeRect(838, 2754, 1056, 2960);
	Stage2BGC[3] = MakeRect(141, 2104, 347, 2322);
	Stage2BGC[4] = MakeRect(140, 500, 348, 720);
	Stage2BGC[5] = MakeRect(130, 0, 740, 344);
	Stage2BGC[6] = MakeRect(1182, 0, 1765, 344);
	Stage2BGC[7] = MakeRect(1548, 344, 1765, 497);
	Stage2BGC[8] = MakeRect(1548, 714, 1765, 2753);
	Stage2BGC[9] = MakeRect(1057, 2753, 1765, 3096);
	Stage2BGC[10] = MakeRect(130, 2753, 838, 3095);
	Stage2BGC[11] = MakeRect(130, 2322, 347, 2754);
	Stage2BGC[12] = MakeRect(130, 720, 347, 2103);
	Stage2BGC[13] = MakeRect(130, 343, 348, 500);
	Stage2BGC[14] = MakeRect(527, 690, 676, 1029);
	Stage2BGC[15] = MakeRect(1215, 690, 1364, 1029);
	Stage2BGC[16] = MakeRect(527, 1205, 676, 1545);
	Stage2BGC[17] = MakeRect(1216, 1205, 1365, 1546);
	Stage2BGC[18] = MakeRect(527, 1724, 676, 2060);
	Stage2BGC[19] = MakeRect(1216, 1726, 1364, 2062);

	//Door
	Stage02.push_back(Stage2BGC[0]);
	Stage02.push_back(Stage2BGC[1]);
	Stage02.push_back(Stage2BGC[2]);
	Stage02.push_back(Stage2BGC[3]);
	Stage02.push_back(Stage2BGC[4]);
	//

	Stage02.push_back(Stage2BGC[5]);
	Stage02.push_back(Stage2BGC[6]);
	Stage02.push_back(Stage2BGC[7]);
	Stage02.push_back(Stage2BGC[8]);
	Stage02.push_back(Stage2BGC[9]);
	Stage02.push_back(Stage2BGC[10]);
	Stage02.push_back(Stage2BGC[11]);
	Stage02.push_back(Stage2BGC[12]);
	Stage02.push_back(Stage2BGC[13]);

	//기둥
	Stage02.push_back(Stage2BGC[14]);
	Stage02.push_back(Stage2BGC[15]);
	Stage02.push_back(Stage2BGC[16]);
	Stage02.push_back(Stage2BGC[17]);
	Stage02.push_back(Stage2BGC[18]);
	Stage02.push_back(Stage2BGC[19]);

	Stage3BGC[0] = MakeRect(129, 0, 2102, 683);
	Stage3BGC[1] = MakeRect(1891, 684, 2103, 4469);
	Stage3BGC[2] = MakeRect(130, 685, 343, 4469);
	Stage3BGC[3] = MakeRect(342, 4127, 876, 4469);
	Stage3BGC[4] = MakeRect(1351, 4128, 1892, 4472);
	Stage3BGC[5] = MakeRect(876, 4129, 1352, 4470);
	Stage3BGC[6] = MakeRect(699, 2236, 849, 2577);
	Stage3BGC[7] = MakeRect(1387, 2236, 1537, 2577);
	Stage3BGC[8] = MakeRect(700, 2753, 849, 3093);
	Stage3BGC[9] = MakeRect(1387, 2752, 1536, 3094);
	Stage3BGC[10] = MakeRect(700, 3268, 849, 3609);
	Stage3BGC[11] = MakeRect(1387, 3268, 1536, 3610);
	Stage3BGC[12] = MakeRect(700, 3784, 849, 4125);
	Stage3BGC[13] = MakeRect(1388, 3784, 1536, 4126);
	//Stage3BGC[14] = MakeRect(345, 2237, 1891, 2230);
}

RECT CBackGroundObject::MakeRect(std::vector<int> vlo, int index)
{

	m_backGroundCollider.left = vlo.at(index);
	m_backGroundCollider.top = vlo.at(index + 1);
	m_backGroundCollider.right = vlo.at(index + 2);
	m_backGroundCollider.bottom = vlo.at(index + 3);

	return 	m_backGroundCollider;
}

RECT CBackGroundObject::MakeRect(int left, int top, int right, int bottom)
{
	m_backGroundCollider.left = left;
	m_backGroundCollider.top = top;
	m_backGroundCollider.right = right;
	m_backGroundCollider.bottom = bottom;

	return 	m_backGroundCollider;
}

void CBackGroundObject::readingCSV()
{
	//std::string str_buf;
	//std::fstream fs;
	////std::ifstream fin(L"../Resourse/SpriteSheet/MapLoca.csv");
	//fs.open(L"../Resourse/SpriteSheet/MapLoca.csv", std::ios::in);

	//std::string tempStr;

	//while (!fs.eof())
	//{
	//	while (getline(fs, str_buf, ','))
	//	{
	//		if (str_buf.find("\n") != std::string::npos && !fs.eof())
	//		{
	//			// 흐정이의 실험실에서 나온 끔찍한 결과물
	//			char tempstring[50] = { ' ', };		// 어쨋거나 임시로 공간을 만든다.	
	//			char temtempstr[50] = { ' ', };

	//			// 복사할 공간에 , 얼마만큼까지 길이, 시작할 위치(첫번째 인덱스)
	//			str_buf.copy(temtempstr, str_buf.find("\n"), 0);	// 문자열의 처음부터 "\n"을 찾을때의 길이만까지

	//			str_buf.copy(tempstring, 3, str_buf.find("\n") + 1); // 

	//			//치환을 했다! 찾을문자,대상의 시작주소, 치환할문자
	//			//str_buf.replace(str_buf.find("\n"), 1, ",");

	//			std::string temtemtemString = temtempstr;

	//			int temp = std::stoi(temtemtemString);
	//			vlocationList.push_back(temp);

	//			temtemtemString = tempstring;
	//			temp = std::stoi(temtemtemString);
	//			vlocationList.push_back(temp);

	//			tempstring[49] = '\0';
	//			temtempstr[49] = '\0';
	//		}
	//		else
	//		{
	//			int temp = std::stoi(str_buf);
	//			vlocationList.push_back(temp);
	//		}
	//	}
	//}
	//fs.close();
}


void CBackGroundObject::PushRECT()
{
	CWallObject* wallobject;

	for (int i = 0; i < 7; i++)
	{
		wallobject = new CWallObject(CVector2D(0, 0), Stage0BGC[i]);
		wallobject->Initialize();
		m_stage00V.push_back(wallobject);
	}

	for (int i = 0; i < 25; i++)
	{
		wallobject = new CWallObject(CVector2D(0, 0), Stage1BGC[i]);
		wallobject->Initialize();
		m_stage01V.push_back(wallobject);
	}

	for (int i = 0; i < 20; i++)
	{
		wallobject = new CWallObject(CVector2D(0, 0), Stage2BGC[i]);
		wallobject->Initialize();
		m_stage02V.push_back(wallobject);
	}

	for (int i = 0; i < 14; i++)
	{
		wallobject = new CWallObject(CVector2D(0, 0), Stage3BGC[i]);
		wallobject->Initialize();
		m_stage03V.push_back(wallobject);
	}
}

void CBackGroundObject::Update()
{
	//pEngine->DrawTextFormat(0, 0, "%d", isCollided);

}

void CBackGroundObject::Render(CVector2D cvector)
{
	// 	for (int i = 0; i < 7; ++i)
	// 	{
	// 		pEngine->DrawRect(Stage0BGC[i], 0, 0, 123);
	// 	}

	//for (int i = 0; i < 25; ++i)
	//{
	//	pEngine->DrawRect(Stage1BGC[i], 123, 0, 0);
	//}

	// 	for (int i = 0; i < 20; ++i)
	// 	{
	// 		pEngine->DrawRect(Stage2BGC[i], 0, 123, 0);
	// 	}

}

void CBackGroundObject::Initialize()
{
}

RECT CBackGroundObject::GetRECT()
{
	RECT r{ 1,2,3,4 };
	return r;
}

void CBackGroundObject::HPDown(int damage)
{

}

void CBackGroundObject::SetCollidertRect(CVector2D pos, CVector2D resize)
{

}
