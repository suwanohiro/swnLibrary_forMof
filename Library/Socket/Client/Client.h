#pragma once

#include "../Socket.h"

class Client : public Socket
{
private:
	/// <summary>
	/// IP�A�h���X
	/// </summary>
	const char*			_ipAddress;

	/// <summary>
	/// �|�[�g�ԍ�
	/// </summary>
	unsigned short		_port;

	/// <summary>
	/// �ڑ����Ă��邩�ǂ���
	/// </summary>
	bool				_isConnect;

	/// <summary>
	/// �ڑ����s���������ǂ���
	/// </summary>
	bool				_isTryConnect;

	/// <summary>
	/// �ڑ����s�X���b�h
	/// </summary>
	std::thread			_tryConnect;

	/// <summary>
	/// ��M�p�X���b�h
	/// </summary>
	std::thread			_receiveThread;

	/// <summary>
	/// ��M���Ɏ��s���鏈�� (char* ��M�����f�[�^)
	/// </summary>
	std::function<void(char*)>	__recvFunc;

	/// <summary>
	/// �ڑ����s���鏈�� (�X���b�h����p)
	/// </summary>
	void __tryConnectThread();

	/// <summary>
	/// ��M�X���b�h�̏���
	/// </summary>
	void __recvThread();

	/// <summary>
	/// �\�P�b�g�����
	/// </summary>
	void __closeSocket();

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="ip">�T�[�o�[��IP�A�h���X</param>
	/// <param name="port">�|�[�g�ԍ�</param>
	/// <param name="recvFunc">��M���̏���</param>
	Client(
		const char* ip, 
		const unsigned short port,
		std::function<void(char*)> recvFunc
	);
	~Client();

	/// <summary>
	/// �T�[�o�[�ɐڑ�
	/// </summary>
	/// <returns>�ڑ��������������ǂ���</returns>
	bool connectServer();

	/// <summary>
	/// �ڑ����Ă��邩�ǂ������擾����
	/// </summary>
	/// <returns>�ڑ����Ă��邩�ǂ���</returns>
	bool isConnect();

	/// <summary>
	/// �f�[�^�𑗐M
	/// </summary>
	/// <param name="data">���M����f�[�^</param>
	void sendData(char* data);
};

