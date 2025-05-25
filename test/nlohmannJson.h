#pragma once
#include <string>
#include <fstream>
#include<nlohmann/json.hpp>

// ���������K�{�I�I

//template�łǂ̌^�ł��g����悤�ɂ���
template<typename T>

//inline��main�ɖ��ߍ��ށB�^��template�̂�ɂ���B������json�f�[�^�̃t�@�C����������
inline T LoadData(const std::string& fileName)
{
	//json�t�@�C�����J��
	std::ifstream stream(fileName);

	//�G���[����
	if (!stream.is_open())
		throw new std::exception("Failed open file.");
	if (!nlohmann::json::accept(stream))
		throw new std::exception("json�̃t�H�[�}�b�g���s��");

	/*nlohmann::json j;
	stream >> j;*/

	//��O����?�炵��
	try
	{
		//parse��json�t�@�C������C++�Ŏg����悤�ɕϊ�������́B
		T data = nlohmann::json::parse(stream).get<T>();
		stream.close();	//�p�[�X��������Ă���

		//�ϊ������f�[�^��Ԃ�
		return data;
	}
	catch (const std::exception&)
	{
		stream.close();	//�p�[�X��������Ă���
		return T{};
	}
}
