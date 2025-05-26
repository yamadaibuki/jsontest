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
