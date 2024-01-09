#include "Socket.h"

// �G���[����ǉ�
void Socket::__addError(char* msg)
{
	_error.push_back(msg);
}

// �f�o�b�O����ǉ�
void Socket::__addDebug(char* msg)
{
	_debug.push_back(msg);
}

// Winsock�̏�����
bool Socket::__initWinsock()
{
    WSAData wsaData;

    // Winsock�̏����������݂�
    bool result = (WSAStartup(MAKEWORD(2, 0), &wsaData) == 0);

    if (result) __addDebug("WinSock�̏������ɐ������܂���");
    else __addError("WinSock�̏������Ɏ��s���܂���");

    return result;
}

bool Socket::__makeSocket()
{
    // �\�P�b�g���쐬
    _tsock = socket(AF_INET, SOCK_STREAM, 0);
    
    // �\�P�b�g�̍쐬�ɐ����������ǂ���
    bool result = (_tsock != INVALID_SOCKET);
    
    // �\�P�b�g�̍쐬���s���ʂ����ꂼ��̃��O�ɒǉ�����
    if (result) __addDebug("�\�P�b�g�̍쐬�ɐ������܂���");
    else __addError("�\�P�b�g�̍쐬�Ɏ��s���܂���");
    
    return result;
}

// �R���X�g���N�^
Socket::Socket()
    : _tsock(INVALID_SOCKET)
{
}

// �G���[�����擾����
std::vector<char*> Socket::getErrors()
{
    return _error;
}

// �f�o�b�O�����擾����
std::vector<char*> Socket::getDebugs()
{
    return _debug;
}
