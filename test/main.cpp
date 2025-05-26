#include "DxLib.h"
#include "nlohmannJson.h"

//hp�`��֐�
void DrawHP(int hp, int hpMax, VECTOR initPosition)
{
	int color = GetColor(255, 255, 255);
	DrawBoxAA(initPosition.x, initPosition.y,
		initPosition.x + 200, initPosition.y + 20, color, FALSE);	//�g��`��
	DrawBoxAA(initPosition.x, initPosition.y,
		initPosition.x + 200 * hp / hpMax, initPosition.y + 20, color, TRUE);	//HP�Q�[�W��`��
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�;

	int currentHp = 0;

	//json�f�[�^�p�̍\���̕ϐ��Ƀf�[�^��ǂݍ��݁Btemplate��<>�Ō^��json�f�[�^�p�̍\���̂ɂ���
	JsonData jsonData = LoadData<JsonData>("data.json");

	VECTOR position = VGet(jsonData.initUIPositionX, jsonData.initUIPositionY, 0.0);

	//���C�����[�v
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !CheckHitKey(KEY_INPUT_ESCAPE)) 
	{
		DrawHP(currentHp, jsonData.hpMax, position);
		currentHp++;
		if (currentHp >= jsonData.hpMax)
		{
			currentHp = 0;
		}
	}

	DxLib_End(); // DX���C�u�����I������
	return 0;
}