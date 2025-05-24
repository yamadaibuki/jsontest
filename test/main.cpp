#include "DxLib.h"
#include<fstream>
//#include<nlohmann/json.hpp>
#include <iostream>

void DrawHP(int hp, int hpMax, VECTOR initPosition)
{
	int color = GetColor(255, 255, 255);
	DrawBox(initPosition.x, initPosition.y,
		initPosition.x + 200, initPosition.y + 20, color, FALSE);	//枠を描画
	DrawBox(initPosition.x, initPosition.y,
		initPosition.x + 200 * hp / hpMax, initPosition.y + 20, color, TRUE);	//HPゲージを描画
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定;

	using json = nlohmann::json;
	using namespace std;

	//json j2 = {
	//	{"hpmax",180},
	//	//{"initPos",{"x":100.0,"y" : 100.0,"z" : 100.0}}
	//};

	ifstream stream("data.json");//jsonファイルを開く

	if (!stream.is_open())
		throw new std::exception("Failed open file.");

	if (!json::accept(stream))
		throw new std::exception("jsonのフォーマットが不正");

	stream.seekg(0, ios::beg);		//なんか先頭に戻すらしい(ないとバグる)
	json j = json::parse(stream);	//parseはjsonファイルからC++で使えるように変換するもの
	stream.close();					//パースしたら閉じておｋ

	int hp = 0;

	ifstream inFile("output.json");
	json fileJson;
	inFile >> fileJson;
	VECTOR loadedVector = fileJson.get<VECTOR>();

	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !CheckHitKey(KEY_INPUT_ESCAPE)) 
	{
		DrawHP(hp, j.at("hpmax").get<int>(), loadedVector);//.atは要素数を指定するもの。getでポインター渡しみたいなやつ。<>で型を指定。
		hp++;
		if (hp >= j.at("hpmax").get<int>())
		{
			hp = 0;
		}
	}

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}