#pragma once
#include <string>
#include <fstream>
#include<nlohmann/json.hpp>

// 書き直し！！

template<typename T>
inline T LoadData(const std::string& fileName)
{
	std::ifstream stream(fileName);//jsonファイルを開く

	if (!stream.is_open())
		throw new std::exception("Failed open file.");

	if (!nlohmann::json::accept(stream))
		throw new std::exception("jsonのフォーマットが不正");

	nlohmann::json j;
	stream >> j;

	try
	{
		T data = nlohmann::json::parse(stream).get<T>();	//parseはjsonファイルからC++で使えるように変換するもの
		//stream.close();	//パースしたら閉じておｋ

		return data;
	}
	catch (const std::exception&)
	{
		stream.close();	//パースしたら閉じておｋ
		return T{};
	}
}