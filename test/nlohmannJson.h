#pragma once
#include <string>
#include <fstream>
#include<nlohmann/json.hpp>

//templateでどの型でも使えるようにする
template<typename T>

//inlineでmainに埋め込む。型はtemplateのやつにする。引数はjsonデータのファイル名が入る
inline T LoadData(const std::string& fileName)
{
	//jsonファイルを開く
	std::ifstream stream(fileName);

	//例外処理?らしい
	try
	{
		//parseはjsonファイルからC++で使えるように変換するもの。
		T data = nlohmann::json::parse(stream).get<T>();
		stream.close();	//パースしたら閉じておｋ

		//変換したデータを返す
		return data;
	}
	catch (const std::exception&)
	{
		//エラー処理(trychach文の中に入れる)
		if (!stream.is_open())
			throw std::runtime_error("Failed open file.");
		if (!nlohmann::json::accept(stream))
			throw std::runtime_error("jsonのフォーマットが不正");
	}
}

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