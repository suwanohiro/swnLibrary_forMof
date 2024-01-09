#pragma once
#include "Mof.h"

#include <vector>
#include <regex>

class StringAction
{
public:
	/// <summary>
	/// ������̃T�C�Y���擾
	/// </summary>
	/// <param name="pText"></param>
	/// <returns></returns>
	static Vector2 GetStringSize(LPCMofChar pText);
	static Vector2 GetStringSize(LPCMofChar pText, CFont* font);

	/// <summary>
	/// ���K�\�����g�p���Ĕz��ɕϊ�
	/// </summary>
	/// <param name="str">�ϊ�������������</param>
	/// <param name="step">�Ԋu������</param>
	static std::vector<std::string> Split(std::string str, int step);

	/// <summary>
	/// ���K�\�����g�p���Ĕz��ɕϊ�
	/// </summary>
	/// <param name="str">�ϊ�������������</param>
	/// <param name="cutStr">�؂��蕶����</param>
	static std::vector<std::string> Split(std::string str, std::string cutStr);

	/// <summary>
	/// ���K�\�����g�p���Ĕz��ɕϊ�
	/// </summary>
	/// <param name="str">�ϊ�������������</param>
	/// <param name="regex">�ΏۂƂȂ鐳�K�\��</param>
	static std::vector<std::string> Split(std::string str, std::regex regex);
};

