#pragma once
#include <string>
#include <fstream>
#include<nlohmann/json.hpp>

//template�łǂ̌^�ł��g����悤�ɂ���
template<typename T>

//inline��main�ɖ��ߍ��ށB�^��template�̂�ɂ���B������json�f�[�^�̃t�@�C����������
inline T LoadData(const std::string& fileName)
{
	//json�t�@�C�����J��
	std::ifstream stream(fileName);

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
		//�G���[����(trychach���̒��ɓ����)
		if (!stream.is_open())
			throw std::runtime_error("Failed open file.");
		if (!nlohmann::json::accept(stream))
			throw std::runtime_error("json�̃t�H�[�}�b�g���s��");
	}
}
