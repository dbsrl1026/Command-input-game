#include "stdafx.h"
#include "Scene_Ingame.h"
#include "Framework.h"


CIngameScene::CIngameScene()
{

}
CIngameScene::~CIngameScene()
{

}
CIngameScene::CIngameScene(SceneTag tag, CFramework * pFramework) : CScene(tag, pFramework) //프레임워크 포인터 활성화
{

}

bool CIngameScene::OnCreate()
{	
	srand((unsigned int)time(NULL));
	_time = 0.f;
	player1Score = 0;
	player2Score = 0;

	arduino.init(port_name);
	assert(arduino.isConnected());

	level = m_pFramework->level;

	Arrow[0].Load(L"Graphic\\Arrow\\GL.png");
	Arrow[1].Load(L"Graphic\\Arrow\\YR.png");
	Arrow[2].Load(L"Graphic\\Arrow\\RU.png");
	Arrow[3].Load(L"Graphic\\Arrow\\BD.png");

	for (int i = 0; i < 50; i++)
	{
		player1Pattern[i] = rand() % (2 * level);
		player2Pattern[i] = rand() % (2 * level);
	}
	return true;
}

void CIngameScene::BuildObjects()
{
	
}

void CIngameScene::KeyState()
{
	//if (GetAsyncKeyState(0x41) & 0x8000) // p1 스킬
	//{
	//	keydownList[11] = TRUE;

	//	isp1LockDown = TRUE;
	//}
	//else if (GetAsyncKeyState(0x53) & 0x8000) // p1 공격
	//{
	//	keydownList[12] = TRUE;

	//	isp1LockDown = TRUE;
	//}
	//else if (GetAsyncKeyState(0x44) & 0x8000) // p1 대시
	//{
	//	if (m_pFramework->GetPlayer(1)->DashCoolTimer <= 0)
	//	{
	//		keydownList[13] = TRUE;

	//		isp1LockDown = TRUE;
	//	}
	//}
	//else
	//{
	//	if (GetAsyncKeyState(0x46) & 0x8000) // f
	//	{
	//		keydownList[7] = TRUE;

	//	}
	//	if (GetAsyncKeyState(0x54) & 0x8000) // t
	//	{
	//		keydownList[8] = TRUE;

	//	}
	//	if (GetAsyncKeyState(0x48) & 0x8000) // h
	//	{
	//		keydownList[9] = TRUE;

	//	}
	//	if (GetAsyncKeyState(0x47) & 0x8000) // g
	//	{
	//		keydownList[10] = TRUE;

	//	}
	//}
	arduino.readSerialPort(incomingData, MAX_DATA_LENGTH);

	if (level == 1)
	{
		if (strncmp(incomingData, "a", 1) == 0)
		{
			if (player1Pattern[0] == 0)
				isp1LockDown = TRUE;
		}
		else if (Lock[0] == TRUE)
		{
			isp1LockDown = FALSE;
		}
		if (strncmp(incomingData, "d", 1) == 0)
		{
			if (player1Pattern[0] == 1)
				isp1LockDown = TRUE;
		}
		else if (Lock[0] == TRUE)
		{
			isp1LockDown = FALSE;
		}

		if (strncmp(incomingData, "e", 1) == 0)
		{
			if (player2Pattern[0] == 0)
				isp2LockDown = TRUE;
		}
		else if (Lock[1] == TRUE)
		{
			isp2LockDown = FALSE;
		}
		if (strncmp(incomingData, "h", 1) == 0)
		{
			if (player2Pattern[0] == 1)
				isp2LockDown = TRUE;
		}
		else if (Lock[1] == TRUE)
		{
			isp2LockDown = FALSE;
		}
	}
	else
	{
		if (strncmp(incomingData, "a", 1) == 0)
		{
			if (player1Pattern[0] == 0)
				isp1LockDown = TRUE;
		}
		else if (Lock[0] == TRUE)
		{
			isp1LockDown = FALSE;
		}
		if (strncmp(incomingData, "b", 1) == 0)
		{
			if (player1Pattern[0] == 3)
				isp1LockDown = TRUE;
		}
		else if (Lock[0] == TRUE)
		{
			isp1LockDown = FALSE;
		}

		if (strncmp(incomingData, "c", 1) == 0)
		{
			if (player1Pattern[0] == 2)
				isp1LockDown = TRUE;
		}
		else if (Lock[0] == TRUE)
		{
			isp1LockDown = FALSE;
		}
		if (strncmp(incomingData, "d", 1) == 0)
		{
			if (player1Pattern[0] == 1)
				isp1LockDown = TRUE;
		}
		else if (Lock[0] == TRUE)
		{
			isp1LockDown = FALSE;
		}
		if (strncmp(incomingData, "e", 1) == 0)
		{
			if (player2Pattern[0] == 0)
				isp2LockDown = TRUE;
		}
		else if (Lock[1] == TRUE)
		{
			isp2LockDown = FALSE;
		}
		if (strncmp(incomingData, "f", 1) == 0)
		{
			if (player2Pattern[0] == 3)
				isp2LockDown = TRUE;
		}
		else if (Lock[1] == TRUE)
		{
			isp2LockDown = FALSE;
		}

		if (strncmp(incomingData, "g", 1) == 0)
		{
			if (player2Pattern[0] == 2)
				isp2LockDown = TRUE;
		}
		else if (Lock[1] == TRUE)
		{
			isp2LockDown = FALSE;
		}
		if (strncmp(incomingData, "h", 1) == 0)
		{
			if (player2Pattern[0] == 1)
				isp2LockDown = TRUE;
		}
		else if (Lock[1] == TRUE)
		{
			isp2LockDown = FALSE;
		}
	}
}

void CIngameScene::Update(float fTimeElapsed)
{
	KeyState();
	if (isp1LockDown && Lock[0] == FALSE)
	{
		memcpy(&player1Pattern[0], &player1Pattern[1], sizeof(int) * 49);
		Lock[0] = TRUE; 
		player1Score += 1000;
	}
	else if (isp1LockDown == FALSE)
	{
		Lock[0] = FALSE;
	}

	if (isp2LockDown && Lock[0] == FALSE)
	{
		memcpy(&player2Pattern[0], &player2Pattern[1], sizeof(int) * 49);
		Lock[1] = TRUE;
		player2Score += 1000;
	}
	else if (isp2LockDown == FALSE)
	{
		Lock[1] = FALSE;
	}


	_time += fTimeElapsed;

		if (player1Score > 49999 || player2Score > 49999)
	{
		isGameEnd = true;
	}

	if (isGameEnd)
	{
		if (player1Score > player2Score)
		{
			MessageBox(NULL, L"Player 1 우승!", L"Game over", NULL);
			exit(0);
		}
		else if (player1Score < player2Score)
		{
			MessageBox(NULL, L"Player 2 우승!", L"Game over", NULL);
			exit(0);
		}
	}
}

void CIngameScene::AngleRender(HDC hdc) 
{

}

void CIngameScene::Render(HDC hdc)
{

	hBrush = CreateSolidBrush(RGB(34, 34, 34));
	oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	Rectangle(hdc,0, 0, windowX, windowY);
	SelectObject(hdc, oldBrush);
	DeleteObject(hBrush);

	for (int i = 0; i < 50-(player1Score/1000); i++)
	{
		Arrow[player1Pattern[i]].Draw(hdc, 90 + 120 * i, windowY / 2 - 200);
	}
	for (int i = 0; i < 50 - (player2Score / 1000); i++)
	{
		Arrow[player2Pattern[i]].Draw(hdc, 90 + 120 * i, windowY / 2 + 100);
	}

	hBrush = CreateSolidBrush(RGB(255, 0, 0));
	oldBrush = (HBRUSH) SelectObject (hdc, hBrush);

	if (player1Score < 50000)
	{
		Rectangle(hdc, 50, 150,
			windowX - 100 - (windowX - 200)*((1.f / 50.f)*(player1Score / 1000.f)),
			200);
	}

	SelectObject(hdc, oldBrush);
	DeleteObject(hBrush);

	hBrush = CreateSolidBrush(RGB(0, 0, 255));
	oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	if (player2Score < 50000)
	{
		Rectangle(hdc, 50, windowY - 150,
			windowX - 100 - (windowX - 200)*((1.f / 50.f)*(player2Score / 1000.f)),
			windowY - 100);
	}

	SelectObject(hdc, oldBrush);
	DeleteObject(hBrush);

}


