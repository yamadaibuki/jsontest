#include "DxLib.h"
#include "nlohmannJson.h"

//jsonデータ用の構造体
struct JsonData
{
	int		hpMax;
	int		hpLimitOver;
	float	initUIPositionX;
	float	initUIPositionY;
};

//任意の型変換(第一引数→nlohmannjson、第二引数→jsonのデータ)
inline void from_json(const nlohmann::json& json, JsonData& jsondata)
{
	//at("")でデータの要素を指定してget_toで指定した要素の中身（数値など)をget_toの引数の変数に代入する
	json.at("hp_max").get_to(jsondata.hpMax);
	json.at("hp_limit_over").get_to(jsondata.hpLimitOver);
	json.at("init_ui_position_x").get_to(jsondata.initUIPositionX);
	json.at("init_ui_position_y").get_to(jsondata.initUIPositionY);
}

//hp描画関数
void DrawHP(int hp, int hpMax, VECTOR initPosition)
{
	int color = GetColor(255, 255, 255);
	DrawBoxAA(initPosition.x, initPosition.y,
		initPosition.x + 200, initPosition.y + 20, color, FALSE);	//枠を描画
	DrawBoxAA(initPosition.x, initPosition.y,
		initPosition.x + 200 * hp / hpMax, initPosition.y + 20, color, TRUE);	//HPゲージを描画
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定;

	int currentHp = 0;


	//不具合:LoadDataを使わずにこっちを使うと正常に動く。なんで？？？？
	std::ifstream stream("data.json");
	JsonData jsonData = nlohmann::json::parse(stream).get<JsonData>();

	//不具合:正常に動かずプログラムの途中で落ちる。parseエラー。nlohmannJson.hがどっかおかしいんやろな
	//jsonデータ用の構造体変数にデータを読み込み。templateの<>で型をjsonデータ用の構造体にする
	//JsonData jsonData = LoadData<JsonData>("data.json");

	VECTOR position = VGet(jsonData.initUIPositionX, jsonData.initUIPositionY, 0.0);

	//メインループ
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !CheckHitKey(KEY_INPUT_ESCAPE)) 
	{
		DrawHP(currentHp, jsonData.hpMax, position);
		currentHp++;
		if (currentHp >= jsonData.hpMax)
		{
			currentHp = 0;
		}
	}

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}