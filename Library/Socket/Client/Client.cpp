#include "Client.h"

// �ڑ����s���鏈�� (�X���b�h����p)
void Client::__tryConnectThread()
{
    // �\�P�b�g�̍쐬�Ɏ��s�����珈���I��
    if (!__makeSocket()) return;

    struct sockaddr_in tmp_addr;
    memset(&tmp_addr, 0, sizeof(struct sockaddr_in));
    tmp_addr.sin_family = AF_INET;
    tmp_addr.sin_port = htons(_port);
    tmp_addr.sin_addr.s_addr = inet_addr(_ipAddress);

    // �T�[�o�[�ɐڑ�
    __addDebug("�ڑ����s���J�n���܂���");
    if (connect(_tsock, (struct sockaddr*)&tmp_addr, sizeof(struct sockaddr_in)) == SOCKET_ERROR) {
        __addError("�ڑ��Ɏ��s���܂���");
        __closeSocket();
        return;
    }

    __addDebug("�ڑ��ɐ������܂���");
    sendData("test");

    // ��M�p�X���b�h���J�n���ăo�b�N�O���E���h�Ŏ��s
    _receiveThread = std::thread(&Client::__recvThread, this);
    _receiveThread.detach();

    // �ڑ���Ԃ��X�V
    _isConnect = true;
}

// ��M�X���b�h�̏���
void Client::__recvThread()
{
    while (true)
    {
        char* msg;

        // �f�[�^����M
        int s = recv(_tsock, (char*)&msg, sizeof(msg), 0);
        if (s <= 0) {
            // �ڑ��I�����̏���
            break;
        }

        // ��M���̏��������s
        __recvFunc(msg);
    }

    /// �X���b�h�I����A�\�P�b�g�����Winsock���N���[���A�b�v
    __closeSocket();
}

// �\�P�b�g�����
void Client::__closeSocket()
{
    // ���ڑ���ԂȂ�΂����ŏ����I��
    if (!_isConnect) return;

    // �\�P�b�g�����
    closesocket(_tsock);
    __addDebug("�\�P�b�g����܂���");

    // WinSock�̃N���[���A�b�v
    WSACleanup();
    __addDebug("WinSock���N���[���A�b�v���܂���");

    // �ڑ���Ԃ��X�V
    _isConnect = false;

}

// �R���X�g���N�^
Client::Client(
        const char* ip,
        unsigned short port,
        std::function<void(char*)> recvFunc
    )
    : _isConnect(false)
{
    // IP�A�h���X�E�|�[�g�ԍ���ݒ肷��
    _ipAddress = ip;
    _port = port;

    // ��M���̏�����ݒ肷��
    __recvFunc = recvFunc;
}

// �f�X�g���N�^
Client::~Client() {
    // �\�P�b�g�����
    __closeSocket();

    if (!_isTryConnect) return;

    _tryConnect.join();
}

// �T�[�o�[�ɐڑ�
bool Client::connectServer()
{
    // �ڑ����Ȃ珈���I��
    if (isConnect()) {
        __addError("�ڑ����̂��ߐڑ������𒆒f���܂���");
        return false;
    }

    __addDebug("�ڑ��������J�n���܂���");

    _isTryConnect = true;

    // WinSock�̏�����
    if (!__initWinsock()) return false;

    _tryConnect = std::thread(&Client::__tryConnectThread, this);
    // _tryConnect.detach();

    return true;
}

// �ڑ����Ă��邩�ǂ������擾����
bool Client::isConnect()
{
    return _isConnect;
}


// �f�[�^�𑗐M
void Client::sendData(char* data) {
    // �ڑ����łȂ���΂����ŏ����I��
    if (!_isConnect) return;

    // �T�[�o�[�Ƀf�[�^�𑗐M
    send(_tsock, (char*)&data, sizeof(data), 0);
}
