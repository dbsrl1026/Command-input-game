#pragma once
#include "Scene.h"
#include "SerialPort.h"
#include <assert.h>

class SerialPort;

class CIngameScene : public CScene
{
public:
	CIngameScene();
	~CIngameScene();
	CIngameScene(SceneTag tag, CFramework * pFramework);

	bool OnCreate() override;
	void BuildObjects() override;
	void Render(HDC hdc) override;				// FrameAdvanced
	void Update(float fTimeElapsed) override;	// m_pCurrScene->Update();
												// m_pCurrScene->Render(m_hdc);

	void KeyState();
	void AngleRender(HDC hdc);
private:
	const char *port_name = "\\\\.\\COM5";
	SerialPort arduino;
	char incomingData[MAX_DATA_LENGTH];

	CImage Arrow[4];		//타일 이미지
	CImage Back;

	HANDLE hFile;
	HBRUSH hBrush, oldBrush;
	int windowX = ::GetSystemMetrics(SM_CXSCREEN);  //모니터 x길이
	int windowY = ::GetSystemMetrics(SM_CYSCREEN);  //모니터 y길이

	BOOL keydownList[8] = { 0 };
	BOOL isp1LockDown = FALSE;		// 공격 등 이동할 수 없는 상태
	BOOL isp2LockDown = FALSE;		// 공격 등 이동할 수 없는 상태
	BOOL Lock[2] = { FALSE };
	BOOL isGameEnd    = FALSE;

	int player1Pattern[50];
	int player1Score;
	int player2Pattern[50];
	int player2Score;

	int level;

	float _time;
	const int timeLimit = 20;
};