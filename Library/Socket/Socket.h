#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <string>
#include <thread>
#include <vector>
#include <functional>
#include <winsock2.h>

class Socket
{
protected:
	/// <summary>
	/// �G���[���e
	/// </summary>
	std::vector<char*>	_error;

	/// <summary>
	/// �f�o�b�O���
	/// </summary>
	std::vector<char*>	_debug;

	/// <summary>
	/// �\�P�b�g
	/// </summary>
	SOCKET				_tsock;

	/// <summary>
	/// �G���[����ǉ�
	/// </summary>
	/// <param name="msg">�G���[������</param>
	void __addError(char* msg);

	/// <summary>
	/// �f�o�b�O����ǉ�
	/// </summary>
	/// <param name="msg">�f�o�b�O������</param>
	void __addDebug(char* msg);

	/// <summary>
	/// Winsock�����������鏈��
	/// </summary>
	/// <returns>����ɏ������������������ǂ���</returns>
	bool __initWinsock();

	/// <summary>
	/// �\�P�b�g���쐬����
	/// </summary>
	/// <returns>�\�P�b�g�̍쐬�ɐ����������ǂ���</returns>
	bool __makeSocket();

	/// <summary>
	/// �\�P�b�g�����
	/// </summary>
	virtual void __closeSocket() = 0;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Socket();

	/// <summary>
	/// �G���[�����擾����
	/// </summary>
	/// <returns>�G���[���</returns>
	std::vector<char*> getErrors();

	/// <summary>
	/// �f�o�b�O�����擾����
	/// </summary>
	/// <returns>�f�o�b�O���</returns>
	std::vector<char*> getDebugs();
};

