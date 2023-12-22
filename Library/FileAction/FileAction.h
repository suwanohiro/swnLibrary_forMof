#pragma once

#include <string>
#include <vector>

using CSVData = std::vector<std::vector<std::string>>;

class FileAction {
public:
    // �t�@�C���p�X�̕ϊ����s���֐�
    static std::string ConvertFileLink(const std::string& currentFilePath);

    // �t�@�C���̓ǂݍ��݂��s���֐�
    static std::string Read(const std::string& currentFilePath);

    // CSV�t�@�C���̓ǂݍ��݂��s���֐�
    static CSVData ReadCSV(const std::string& currentFilePath);

    // �t�@�C���̏������݂��s���֐�
    static void Write(const std::string& currentFilePath, const std::string& writestring, const std::string& fileReadMode);

    // �t�@�C���ɒǋL����֐�
    static void WriteAdd(const std::string& currentFilePath, const std::string& writestring);

    // �t�@�C���ɐV�K�������݂���֐�
    static void WriteNew(const std::string& currentFilePath, const std::string& writestring);

    // �t�@�C�����N���A����֐�
    static void Clear(const std::string& currentFilePath);
};
