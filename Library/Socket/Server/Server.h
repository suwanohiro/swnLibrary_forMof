#pragma once

#include "../Socket.h"

class Server : public Socket
{
private:
	/// <summary>
	/// �N���C�A���g���
	/// </summary>
	struct ClientData {
		// �ڑ�����
		bool	isConnect;

		// �\�P�b�g
		SOCKET	socket;
	};

	/// <summary>
	/// �N���C�A���g�z��
	/// </summary>
	std::vector<ClientData*> _clients;

	/// <summary>
	/// �|�[�g�ԍ�
	/// </summary>
	unsigned short _port;

	/// <summary>
	/// �T�[�o�[�������J�n����Ă��邩�ǂ���
	/// </summary>
	bool _isServerStart;

	/// <summary>
	/// �N���C�A���g�ڑ��ҋ@�X���b�h
	/// </summary>
	std::thread _acceptThread;

	/// <summary>
	/// ��M�����f�[�^
	/// </summary>
	std::vector<char*> _receivedData;

	/// <summary>
	/// ��M���Ɏ��s���鏈�� (char* ��M�����f�[�^)
	/// </summary>
	std::function<void(char*)>	__recvFunc;

	/// <summary>
	/// �N���C�A���g�̐ڑ���ҋ@���A�ڑ����ꂽ�ꍇ�ɃX���b�h���N������
	/// </summary>
	void __acceptThread();

	/// <summary>
	/// �N���C�A���g����̃f�[�^����������X���b�h�̃��C���֐�
	/// </summary>
	/// <param name="client">�ΏۃN���C�A���g���̃|�C���^</param>
	void __recvThread(ClientData* client);

	/// <summary>
	/// �\�P�b�g�����
	/// </summary>
	void __closeSocket();

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="port">�|�[�g�ԍ�</param>
	Server(const unsigned short port);

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="port">�|�[�g�ԍ�</param>
	/// <param name="recvFunc">��M���̏���</param>
	Server(const unsigned short port, std::function<void(char*)> recvFunc);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Server();

	/// <summary>
	/// �T�[�o�[��������/�J�n���鏈��
	/// </summary>
	/// <returns>����ɊJ�n�ł������ǂ���</returns>
	bool Start();

	/// <summary>
	/// ��M�������b�Z�[�W���擾���鏈��
	/// </summary>
	/// <returns>��M�������b�Z�[�W</returns>
	std::vector<char*> getReceivedData();
};
