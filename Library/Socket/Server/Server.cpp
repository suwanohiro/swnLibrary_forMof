#include "Server.h"

void Server::__acceptThread()
{
	// �T�[�o�[�\�P�b�g���쐬
	if (!__makeSocket()) return;

	struct sockaddr_in tmp_addr;
	memset(&tmp_addr, 0, sizeof(struct sockaddr_in));
	tmp_addr.sin_family = AF_INET;
	tmp_addr.sin_port = htons(_port);
	tmp_addr.sin_addr.s_addr = ADDR_ANY;

	// �\�P�b�g���o�C���h
	if (bind(_tsock, (struct sockaddr*)&tmp_addr, sizeof(struct sockaddr_in)) == SOCKET_ERROR) {
		// �G���[���b�Z�[�W��ݒ�
		__addError("Error: Socket Bind");
		__closeSocket();
		return;
	}

	// �ڑ��ҋ@��Ԃɂ���
	if (listen(_tsock, SOMAXCONN) == SOCKET_ERROR) {
		// �G���[���b�Z�[�W��ݒ�
		__addError("Error: Socket Listen");
		__closeSocket();
		return;
	}

	__addDebug("Socket Listening...");

	while (true)
	{
		SOCKADDR_IN ta;
		int addrin_size = sizeof(SOCKADDR_IN);
		__addDebug("Wait Accept");

		SOCKET ts = accept(_tsock, (struct sockaddr*)&ta, &addrin_size);

		if (ts == INVALID_SOCKET) break;

		std::string msg = std::string("Client IP : " + std::string(inet_ntoa(ta.sin_addr)));
		//__addDebug((char*)msg.c_str());
		__addDebug("Connect Client");

		ClientData tmp;
		tmp.socket = ts;
		_clients.push_back(&tmp);

		// �N���C�A���g����̎�M����������X���b�h���N��
		std::thread recvThread(&Server::__recvThread, this, &tmp);
		recvThread.detach();
	}
	_endthreadex(NULL);
}

void Server::__recvThread(ClientData* client)
{
	client->isConnect = true;
	while (true)
	{
		char* msg;

		// �N���C�A���g����f�[�^����M
		int s = recv(client->socket, (char*)&msg, sizeof(msg), 0);
		if (s <= 0) {
			__addDebug("Exit Client");
			__addDebug("Connection End");
			break;
		}

		__recvFunc(msg);

		// ��M�������b�Z�[�W��z��ɒǉ�
		_receivedData.push_back(msg);

		for (unsigned int cnt = 0; cnt < _clients.size(); cnt++) {
			// �ڑ���ԂłȂ��Ȃ瑗�M�����Ȃ�
			if (!_clients[cnt]->isConnect) continue;

			// ���M��ɂ͑��M�����Ȃ�
			if (_clients[cnt] == client) continue;

			// ���̃N���C�A���g�ɂ����b�Z�[�W�𑗐M
			send(_clients[cnt]->socket, (char*)msg, sizeof(msg), 0);
		}
	}
	client->isConnect = false;
	_endthreadex(NULL);
}

void Server::__closeSocket()
{
	// �T�[�o�[�������J�n����Ă��Ȃ���΂����ŏ����I��
	if (!_isServerStart) return;

	// �\�P�b�g�̃N���[���A�b�v�ƃX���b�h�̒�~�ҋ@
	for (unsigned int cnt = 0; cnt < _clients.size(); cnt++) {
		if (!_clients[cnt]->isConnect) continue;
		closesocket(_clients[cnt]->socket);
	}

	_acceptThread.join();

	WSACleanup();

	_isServerStart = false;
}

Server::Server(const unsigned short port)
{
	_port = port;

	__recvFunc = [=](char*) {};
}

Server::Server(const unsigned short port, std::function<void(char*)> recvFunc)
{
	_port = port;

	__recvFunc = recvFunc;
}

Server::~Server()
{
	__closeSocket();
}

bool Server::Start()
{
	// Winsock�̏�����
	if (!__initWinsock()) return false;

	// �N���C�A���g�ڑ��ҋ@�X���b�h���J�n
	_acceptThread = std::thread(&Server::__acceptThread, this);

	_isServerStart = true;

	return true;
}

std::vector<char*> Server::getReceivedData()
{
	return _receivedData;
}
