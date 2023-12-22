#pragma once

#include <string>
#include <vector>
#include "./json.hpp"


using JSON = nlohmann::json;
using CSVData = std::vector<std::vector<std::string>>;

class FileAction {
public:
    /// <summary>
    /// ���s�t�@�C������̑��΃p�X���΃p�X�ɕύX����
    /// </summary>
    /// <param name="currentFilePath">���s�t�@�C������̑��΃p�X</param>
    /// <returns></returns>
    static std::string ConvertFileLink(const std::string& currentFilePath);

    /// <summary>
    /// �t�@�C����ǂݍ���
    /// </summary>
    /// <param name="currentFilePath">���s�t�@�C������̑��΃p�X</param>
    /// <returns>�ǂݍ��񂾕�����f�[�^</returns>
    static std::string Read(const std::string& currentFilePath);

    /// <summary>
    /// CSV�t�@�C����ǂݎ��2�����z���Ԃ�
    /// </summary>
    /// <param name="currentFilePath">���s�t�@�C������̑��΃p�X</param>
    /// <returns>CSV�f�[�^��2�����z��</returns>
    static CSVData ReadCSV(const std::string& currentFilePath);

    /// <summary>
    /// JSON�t�@�C����ǂݍ���
    /// </summary>
    /// <param name="currentFilePath">���s�t�@�C������̑��΃p�X</param>
    /// <returns>JSON�f�[�^</returns>
    static JSON ReadJSON(const std::string& currentFilePath);

    /// <summary>
    /// �f�[�^����������
    /// </summary>
    /// <param name="currentFilePath">���s�t�@�C������̑��΃p�X</param>
    /// <param name="writestring">�������ޕ�����</param>
    /// <param name="fileReadMode">�������݃��[�h</param>
    static void Write(const std::string& currentFilePath, const std::string& writestring, const std::string& fileReadMode);

    /// <summary>
    /// �f�[�^���������� (�ǋL)
    /// </summary>
    /// <param name="currentFilePath">���s�t�@�C������̑��΃p�X</param>
    /// <param name="writestring">�������ޕ�����</param>
    static void WriteAdd(const std::string& currentFilePath, const std::string& writestring);

    /// <summary>
    /// �f�[�^���������� (�㏑��)
    /// </summary>
    /// <param name="currentFilePath">���s�t�@�C������̑��΃p�X</param>
    /// <param name="writestring">�������ޕ�����</param>
    static void WriteNew(const std::string& currentFilePath, const std::string& writestring);

    /// <summary>
    /// �f�[�^���폜����
    /// </summary>
    /// <param name="currentFilePath">���s�t�@�C������̑��΃p�X</param>
    static void Clear(const std::string& currentFilePath);
};
