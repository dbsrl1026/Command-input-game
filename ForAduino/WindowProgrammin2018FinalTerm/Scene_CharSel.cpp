#include "stdafx.h"
#include "Scene_CharSel.h"
#include "Framework.h"

Scene_Charsel::Scene_Charsel()
{


}

Scene_Charsel::~Scene_Charsel()
{
}

Scene_Charsel::Scene_Charsel(SceneTag tag, CFramework * pFramework) : CScene(tag, pFramework) //프레임워크 포인터 활성화
{

}

void Scene_Charsel::OnDestroy()
{

}

//생성될때 뭔가
bool Scene_Charsel::OnCreate()
{
	I_BG.Load(L"Graphic\\New\\ForTitle\\배경.png");

	e.Load(L"Graphic\\New\\ForTitle\\easy.png");
	//n.Load(L"Graphic\\New\\ForTitle\\normal.png");
	h.Load(L"Graphic\\New\\ForTitle\\hard.png");
	//i.Load(L"Graphic\\New\\ForTitle\\insane.png");
	choice1 = 1;
	Finish = false;

	//이미지 크기와 관련하여 작성합니다.
	//이미지 크기가 변경될 시 재작성이 필요합니다.
	//모든 이미지 크기는 CalcImage()를 통해 재정의됨
	//bottom과 Right 는 크기를 넣으면 됩니다.

	arduino.init(port_name);
	assert(arduino.isConnected());

	return false;
}

void Scene_Charsel::BuildObjects()
{

}



//키 상태를 입력받음.
void Scene_Charsel::KeyState() {

	arduino.readSerialPort(incomingData, MAX_DATA_LENGTH);

	//레디
	if (strncmp(incomingData, "d", 1) == 0) {
		ready1 = true;
	}
	if (!ready1) {
		// f
		if (strncmp(incomingData, "b", 1) == 0) {
			if (!P1_L) {
				switch (choice1) {
				case 1:
					choice1 = 2;
					break;
				}
			}
			P1_L = true;
		}
		else {
			P1_L = false;
		}
		// h
		if (strncmp(incomingData, "c", 1) == 0) {
			if (!P1_R) {
				switch (choice1) {
				case 2:
					choice1 = 1;
					break;
				}
			}
			P1_R = true;
		}
		else {
			P1_R = false;
		}
	}
}

// 1/60으로 업데이트됨
void Scene_Charsel::Update(float fTimeElapsed)
{
	KeyState();
	//종료되지 않아야지 계속 실행한다.
	if (!Finish) {
		//매 프레임 체크
		if (count == 0) {
			count = 60;
			timer--;
		}
		else {
			count--;
		}

		//finish == true
		if (ready1)
		{
			m_pFramework->BuildPlayer(choice1);
			m_pFramework->ChangeScene(CScene::SceneTag::Ingame);
			m_pFramework->curSceneCreate();
			Scene_Charsel::OnDestroy();
		}


	}
}

void Scene_Charsel::Render(HDC hdc)
{
	//그려주는 순서
	//배경
	//난이도
	//선택난이도

	I_BG.Draw(hdc, 0, 0, windowX, windowY);

	e.Draw(hdc, windowX / 2 - 300, windowY / 2 - 300, 600, 130);
	//n.Draw(hdc, windowX / 2 - 300, windowY / 2 - 100, 600, 130);
	h.Draw(hdc, windowX / 2 - 300, windowY / 2 + 100, 600, 130);
	//i.Draw(hdc, windowX / 2 - 300, windowY / 2 + 300, 600, 130);

	switch (choice1) {
	case 1:
		e.Draw(hdc, windowX / 2 - 350, windowY / 2 - 350, 700, 180);
		break;
	case 3:
		//n.Draw(hdc, windowX / 2 - 350, windowY / 2 - 150, 700, 180);
		break;
	case 2:
		h.Draw(hdc, windowX / 2 - 350, windowY / 2 + 50, 700, 180);
		break;
	case 4:
		//i.Draw(hdc, windowX / 2 - 350, windowY / 2 + 250, 700, 180);
		break;
	}


}


//이미지의 크기를 계산합니다.
RECT Scene_Charsel::CalcImage(RECT input) {
	//=======================================
	//        기능 안내
	// top과 left는 화면 비율에 맞게 계산하여 정하고
	// bottom과 right는 화면 크기에 맞게 계산하여 정한다.
	//===========================================

	RECT calc;

	float X = 1920.0, Y = 1080.0;

	//1080일때 기준으로 개발하고, 윈도우의 크기로 나눠서 위치를 맞춘다.
	calc.top = input.top*(windowY / Y);
	//1920일때 기준으로 개발하고, 윈도우의 크기로 나눠서 위치를 정합시다.
	calc.left = input.left*(windowX / X);

	//가로와 세로중 어떤 비율이 더 작은지 정하고 더 작은 비율로 정하여 비율 유지하여 그림 크기를 정한다.
	//세로가 더 크므로 가로 기준으로 맞춘다.
	if ((windowY / Y) >= (windowX / X)) {
		calc.bottom = calc.top + input.bottom * (windowX / X);
		calc.right = calc.left + input.right * (windowX / X);
	}
	//가로가 더 크므로 세로 기준으로 맞춘다.
	else {
		calc.bottom = calc.top + input.bottom*(windowY / Y);
		calc.right = calc.left + input.right*(windowY / Y);
	}

	printf("top : %d, bottom : %d, left : %d, right : %d\n", calc.top, calc.bottom, calc.left, calc.right);
	//계산된 결과를 리턴한다.
	return calc;
}

