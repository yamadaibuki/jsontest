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

//json�f�[�^�p�̍\����
struct JsonData
{
	int		hpMax;
	int		hpLimitOver;
	float	initUIPositionX;
	float	initUIPositionY;
};

//�C�ӂ̌^�ϊ�(��������nlohmannjson�A��������json�̃f�[�^)
inline void from_json(const nlohmann::json& json, JsonData& jsondata)
{
	//at("")�Ńf�[�^�̗v�f���w�肵��get_to�Ŏw�肵���v�f�̒��g�i���l�Ȃ�)��get_to�̈����̕ϐ��ɑ������
	json.at("hp_max").get_to(jsondata.hpMax);
	json.at("hp_limit_over").get_to(jsondata.hpLimitOver);
	json.at("init_ui_position_x").get_to(jsondata.initUIPositionX);
	json.at("init_ui_position_y").get_to(jsondata.initUIPositionY);
}