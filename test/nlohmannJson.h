#pragma once
#include <string>
#include <fstream>
#include<nlohmann/json.hpp>

// ���������I�I

template<typename T>
inline T LoadData(const std::string& fileName)
{
	std::ifstream stream(fileName);//json�t�@�C�����J��

	if (!stream.is_open())
		throw new std::exception("Failed open file.");

	if (!nlohmann::json::accept(stream))
		throw new std::exception("json�̃t�H�[�}�b�g���s��");

	nlohmann::json j;
	stream >> j;

	try
	{
		T data = nlohmann::json::parse(stream).get<T>();	//parse��json�t�@�C������C++�Ŏg����悤�ɕϊ��������
		//stream.close();	//�p�[�X��������Ă���

		return data;
	}
	catch (const std::exception&)
	{
		stream.close();	//�p�[�X��������Ă���
		return T{};
	}
}