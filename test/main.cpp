#include "DxLib.h"
#include "nlohmannJson.h"

struct JsonData
{
	int hpMax;
	int hpLimiteOver;

	float initUIPositionX;
	float initUIPositionY;
};

inline void from_json(const nlohmann::json& json, JsonData& jsondata)
{
	json.at("hp_max").get_to(jsondata.hpMax);
	json.at("hp_limite_over").get_to(jsondata.hpLimiteOver);
	json.at("init_ui_position_x").get_to(jsondata.initUIPositionX);
	json.at("init_ui_position_y").get_to(jsondata.initUIPositionY);
}

void DrawHP(int hp, int hpMax, VECTOR initPosition)
{
	int color = GetColor(255, 255, 255);
	DrawBoxAA(initPosition.x, initPosition.y,
		initPosition.x + 200, initPosition.y + 20, color, FALSE);	//�g��`��
	DrawBoxAA(initPosition.x, initPosition.y,
		initPosition.x + 200 * hp / hpMax, initPosition.y + 20, color, TRUE);	//HP�Q�[�W��`��
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�;

	int currentHp = 0;

	std::ifstream stream("data.json");
	JsonData jsonData = nlohmann::json::parse(stream).get<JsonData>();
	//JsonData jsonData = LoadData<JsonData>("data.json");
	VECTOR position;
	position.x = jsonData.initUIPositionX;
	position.y = jsonData.initUIPositionY;
	position.z = 0.0f;

	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !CheckHitKey(KEY_INPUT_ESCAPE)) 
	{
		DrawHP(currentHp, jsonData.hpMax, position);//.at�͗v�f�����w�肷����́Bget�Ń|�C���^�[�n���݂����Ȃ�B<>�Ō^���w��B
		currentHp++;
		if (currentHp >= jsonData.hpMax)
		{
			currentHp = 0;
		}
	}

	DxLib_End(); // DX���C�u�����I������
	return 0;
}