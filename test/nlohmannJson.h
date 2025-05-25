#pragma once
#include <string>
#include <fstream>
#include<nlohmann/json.hpp>

// 書き直し必須！！

//templateでどの型でも使えるようにする
template<typename T>

//inlineでmainに埋め込む。型はtemplateのやつにする。引数はjsonデータのファイル名が入る
inline T LoadData(const std::string& fileName)
{
	//jsonファイルを開く
	std::ifstream stream(fileName);

	//エラー処理
	if (!stream.is_open())
		throw new std::exception("Failed open file.");
	if (!nlohmann::json::accept(stream))
		throw new std::exception("jsonのフォーマットが不正");

	/*nlohmann::json j;
	stream >> j;*/

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
		stream.close();	//パースしたら閉じておｋ
		return T{};
	}
}
