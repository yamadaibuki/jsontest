#include "DxLib.h"
#include "nlohmannJson.h"

//json�f�[�^�p�̍\����
struct JsonData
{
	int		hpMax;
	int		hpLimitOver;
	float	initUIPositionX;
	float	initUIPositionY;
};

//�C�ӂ̌^�ϊ�(��������nlohmannjson�A��������json�̃f�[�^)
inline void from_json(const nlohmann::json& json, JsonData& jsondata)
{
	//at("")�Ńf�[�^�̗v�f���w�肵��get_to�Ŏw�肵���v�f�̒��g�i���l�Ȃ�)��get_to�̈����̕ϐ��ɑ������
	json.at("hp_max").get_to(jsondata.hpMax);
	json.at("hp_limit_over").get_to(jsondata.hpLimitOver);
	json.at("init_ui_position_x").get_to(jsondata.initUIPositionX);
	json.at("init_ui_position_y").get_to(jsondata.initUIPositionY);
}

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


	//�s�:LoadData���g�킸�ɂ��������g���Ɛ���ɓ����B�Ȃ�ŁH�H�H�H
	std::ifstream stream("data.json");
	JsonData jsonData = nlohmann::json::parse(stream).get<JsonData>();

	//�s�:����ɓ������v���O�����̓r���ŗ�����Bparse�G���[�BnlohmannJson.h���ǂ����������������
	//json�f�[�^�p�̍\���̕ϐ��Ƀf�[�^��ǂݍ��݁Btemplate��<>�Ō^��json�f�[�^�p�̍\���̂ɂ���
	//JsonData jsonData = LoadData<JsonData>("data.json");

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