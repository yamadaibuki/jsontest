#include "DxLib.h"
#include<fstream>
//#include<nlohmann/json.hpp>
#include <iostream>

void DrawHP(int hp, int hpMax, VECTOR initPosition)
{
	int color = GetColor(255, 255, 255);
	DrawBox(initPosition.x, initPosition.y,
		initPosition.x + 200, initPosition.y + 20, color, FALSE);	//�g��`��
	DrawBox(initPosition.x, initPosition.y,
		initPosition.x + 200 * hp / hpMax, initPosition.y + 20, color, TRUE);	//HP�Q�[�W��`��
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�;

	using json = nlohmann::json;
	using namespace std;

	//json j2 = {
	//	{"hpmax",180},
	//	//{"initPos",{"x":100.0,"y" : 100.0,"z" : 100.0}}
	//};

	ifstream stream("data.json");//json�t�@�C�����J��

	if (!stream.is_open())
		throw new std::exception("Failed open file.");

	if (!json::accept(stream))
		throw new std::exception("json�̃t�H�[�}�b�g���s��");

	stream.seekg(0, ios::beg);		//�Ȃ񂩐擪�ɖ߂��炵��(�Ȃ��ƃo�O��)
	json j = json::parse(stream);	//parse��json�t�@�C������C++�Ŏg����悤�ɕϊ��������
	stream.close();					//�p�[�X��������Ă���

	int hp = 0;

	ifstream inFile("output.json");
	json fileJson;
	inFile >> fileJson;
	VECTOR loadedVector = fileJson.get<VECTOR>();

	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !CheckHitKey(KEY_INPUT_ESCAPE)) 
	{
		DrawHP(hp, j.at("hpmax").get<int>(), loadedVector);//.at�͗v�f�����w�肷����́Bget�Ń|�C���^�[�n���݂����Ȃ�B<>�Ō^���w��B
		hp++;
		if (hp >= j.at("hpmax").get<int>())
		{
			hp = 0;
		}
	}

	DxLib_End(); // DX���C�u�����I������
	return 0;
}