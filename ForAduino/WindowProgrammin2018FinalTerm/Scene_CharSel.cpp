#include "stdafx.h"
#include "Scene_CharSel.h"
#include "Framework.h"

Scene_Charsel::Scene_Charsel()
{


}

Scene_Charsel::~Scene_Charsel()
{
}

Scene_Charsel::Scene_Charsel(SceneTag tag, CFramework * pFramework) : CScene(tag, pFramework) //�����ӿ�ũ ������ Ȱ��ȭ
{

}

void Scene_Charsel::OnDestroy()
{

}

//�����ɶ� ����
bool Scene_Charsel::OnCreate()
{
	I_BG.Load(L"Graphic\\New\\ForTitle\\���.png");

	e.Load(L"Graphic\\New\\ForTitle\\easy.png");
	//n.Load(L"Graphic\\New\\ForTitle\\normal.png");
	h.Load(L"Graphic\\New\\ForTitle\\hard.png");
	//i.Load(L"Graphic\\New\\ForTitle\\insane.png");
	choice1 = 1;
	Finish = false;

	//�̹��� ũ��� �����Ͽ� �ۼ��մϴ�.
	//�̹��� ũ�Ⱑ ����� �� ���ۼ��� �ʿ��մϴ�.
	//��� �̹��� ũ��� CalcImage()�� ���� �����ǵ�
	//bottom�� Right �� ũ�⸦ ������ �˴ϴ�.

	arduino.init(port_name);
	assert(arduino.isConnected());

	return false;
}

void Scene_Charsel::BuildObjects()
{

}



//Ű ���¸� �Է¹���.
void Scene_Charsel::KeyState() {

	arduino.readSerialPort(incomingData, MAX_DATA_LENGTH);

	//����
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

// 1/60���� ������Ʈ��
void Scene_Charsel::Update(float fTimeElapsed)
{
	KeyState();
	//������� �ʾƾ��� ��� �����Ѵ�.
	if (!Finish) {
		//�� ������ üũ
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
	//�׷��ִ� ����
	//���
	//���̵�
	//���ó��̵�

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


//�̹����� ũ�⸦ ����մϴ�.
RECT Scene_Charsel::CalcImage(RECT input) {
	//=======================================
	//        ��� �ȳ�
	// top�� left�� ȭ�� ������ �°� ����Ͽ� ���ϰ�
	// bottom�� right�� ȭ�� ũ�⿡ �°� ����Ͽ� ���Ѵ�.
	//===========================================

	RECT calc;

	float X = 1920.0, Y = 1080.0;

	//1080�϶� �������� �����ϰ�, �������� ũ��� ������ ��ġ�� �����.
	calc.top = input.top*(windowY / Y);
	//1920�϶� �������� �����ϰ�, �������� ũ��� ������ ��ġ�� ���սô�.
	calc.left = input.left*(windowX / X);

	//���ο� ������ � ������ �� ������ ���ϰ� �� ���� ������ ���Ͽ� ���� �����Ͽ� �׸� ũ�⸦ ���Ѵ�.
	//���ΰ� �� ũ�Ƿ� ���� �������� �����.
	if ((windowY / Y) >= (windowX / X)) {
		calc.bottom = calc.top + input.bottom * (windowX / X);
		calc.right = calc.left + input.right * (windowX / X);
	}
	//���ΰ� �� ũ�Ƿ� ���� �������� �����.
	else {
		calc.bottom = calc.top + input.bottom*(windowY / Y);
		calc.right = calc.left + input.right*(windowY / Y);
	}

	printf("top : %d, bottom : %d, left : %d, right : %d\n", calc.top, calc.bottom, calc.left, calc.right);
	//���� ����� �����Ѵ�.
	return calc;
}

