#include "FileAction.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
//#include <filesystem>
#include <string>
#include <Windows.h>

//namespace fs = std::filesystem;

std::string FileAction::ConvertFileLink(const std::string& relativePath) {
    char path[MAX_PATH];
    DWORD length = GetModuleFileNameA(NULL, path, MAX_PATH);

    if (length == 0) return std::string("");

    std::string programPath(path, length);

    size_t found = programPath.find_last_of("\\/");
    std::string programDirectory = programPath.substr(0, found + 1);

    std::string fullPath = programDirectory + relativePath;

    // std::string �� LPSTR �ɕϊ�
    int size = fullPath.length() + 1;
    LPSTR lpAbsolutePath = new char[size];
    strcpy_s(lpAbsolutePath, size, fullPath.c_str());

    std::string result(lpAbsolutePath);
    delete[] lpAbsolutePath;

    return result;
}

std::string FileAction::Read(const std::string& currentFilePath) {
    // �t�@�C���p�X��ϊ�
    // �t�@�C�����J���ēǂݍ��݁A���e�𕶎���Ƃ��ĕԂ�
    std::string path = ConvertFileLink(currentFilePath);
    std::ifstream file(path, std::ios::in | std::ios::binary);
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}

CSVData FileAction::ReadCSV(const std::string& currentFilePath) {
    // �w�肳�ꂽCSV�t�@�C����ǂݍ���
    // �ǂݍ��񂾃f�[�^��2�����x�N�^�[�Ɋi�[���ĕԂ�
    std::string textData = Read(currentFilePath);
    CSVData result;
    std::istringstream iss(textData);
    std::string line;

    while (std::getline(iss, line)) {
        std::vector<std::string> work;
        std::istringstream lineStream(line);
        std::string cell;

        while (std::getline(lineStream, cell, ',')) {
            work.push_back(cell);
        }

        result.push_back(work);
    }

    return result;
}

void FileAction::Write(const std::string& currentFilePath, const std::string& writestring, const std::string& fileReadMode) {
    // �t�@�C���p�X��ϊ�
    // �t�@�C�����J���Ďw�肳�ꂽ���[�h�ŏ�������
    std::string path = ConvertFileLink(currentFilePath);
    std::ios_base::openmode mode = (fileReadMode == "a") ? std::ios::app : std::ios::out | std::ios::binary;
    std::ofstream file(path, mode);
    file << writestring;
    file.close();
}

void FileAction::WriteAdd(const std::string& currentFilePath, const std::string& writestring) {
    // �ǋL���[�h�Ńt�@�C���ɏ�������
    Write(currentFilePath, writestring, "a");
}

void FileAction::WriteNew(const std::string& currentFilePath, const std::string& writestring) {
    // �V�K�������݃��[�h�Ńt�@�C���ɏ�������
    Write(currentFilePath, writestring, "w");
}

void FileAction::Clear(const std::string& currentFilePath) {
    // �t�@�C�����N���A���邽�߂ɋ�̕�����Ńt�@�C���ɏ�������
    WriteNew(currentFilePath, "");
}
