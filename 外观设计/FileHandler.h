#pragma once
#include "rapidcsv.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <locale>
#include <codecvt>

class FileHandler {
private:
    char delimiter;           // �ָ�����խ�ַ���
    std::string filePath;     // �ļ�·��
    std::vector<std::vector<std::wstring>> data;  // ���ַ����ݴ洢���ޱ�ͷ���������У�

    // �ַ���ת������
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

    // խ�ַ���ת���ַ���
    std::wstring toWide(const std::string& str) {
        try {
            return converter.from_bytes(str);
        }
        catch (const std::exception&) {
            std::wstring result;
            for (char c : str) {
                result += static_cast<wchar_t>(c);
            }
            return result;
        }
    }

    // ���ַ���תխ�ַ���
    std::string toNarrow(const std::wstring& wstr) {
        try {
            return converter.to_bytes(wstr);
        }
        catch (const std::exception&) {
            std::string result;
            for (wchar_t wc : wstr) {
                result += static_cast<char>(wc);
            }
            return result;
        }
    }

public:
    // ���캯����ָ���ļ�·���ͷָ���
    FileHandler(const std::string& filePath, char delimiter = ',')
        : filePath(filePath), delimiter(delimiter) {
    }

    // ��ȡ���ݣ����غ󷵻��������ã�
    std::vector<std::vector<std::wstring>>& getData() {
        static std::vector<std::vector<std::wstring>> emptyData;  // ���ⷵ��δ��������
        if (!Load_data()) return emptyData;
        return data;
    }
    void setData(std::vector<std::vector<std::wstring>>& other) {
        this->data = other;
        if (Store_data()) {

            std::cerr << "���ݴ洢�ɹ�" << std::endl;
        }
        else {

            std::cerr << "���ݴ洢ʧ��" << std::endl;

        }
    }
    
    
    //}bool Load_data() {
    //    try {
    //        data.clear();

    //        // ����rapidcsv���������ñ�ͷ�������ж��������У�
    //        rapidcsv::LabelParams labelParams(-1);  // -1��ʾû�б�ͷ��
    //        rapidcsv::SeparatorParams separatorParams(delimiter);

    //        // �ؼ���ʹ���ļ����򿪲�ָ��UTF-8����
    //        std::ifstream fileStream(filePath, std::ios::binary);
    //        if (!fileStream.is_open()) {
    //            throw std::runtime_error("�޷����ļ�");
    //        }

    //        // ���BOM����ѡ��
    //        char bom[3] = { 0 };
    //        fileStream.read(bom, 3);
    //        bool hasBom = (bom[0] == '\xEF' && bom[1] == '\xBB' && bom[2] == '\xBF');

    //        // �����BOM���������������3�ֽ�
    //        if (!hasBom) {
    //            fileStream.seekg(0);
    //        }

    //        // ����rapidcsv�ĵ����������أ�
    //        rapidcsv::Document doc(fileStream, labelParams, separatorParams);

    //        // ��ȡ����������
    //        for (size_t i = 1; i < doc.GetRowCount(); ++i) {
    //            std::vector<std::string> row = doc.GetRow<std::string>(i);
    //            std::vector<std::wstring> wideRow;
    //            for (const auto& cell : row) {
    //                // �ؼ�����ʽ��UTF-8ת��Ϊ���ַ�
    //                wideRow.push_back(utf8_to_wstring(cell));
    //            }
    //            data.push_back(wideRow);
    //        }

    //        return true;
    //    }
    //    catch (const std::exception& e) {
    //        std::cerr << "�����ļ�ʧ��: " << e.what() << std::endl;
    //        data.clear();
    //        return false;
    //    }
    //}

    //// ����������UTF-8�ַ���ת���ַ�
    //std::wstring utf8_to_wstring(const std::string& utf8Str) {
    //    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    //    try {
    //        return converter.from_bytes(utf8Str);
    //    }
    //    catch (const std::exception&) {
    //        // ���������ؿ��ַ������滻�Ƿ��ַ�
    //        return L"";
    //    }
    //}
    // �������ݣ��������б�ͷ��ֱ�Ӷ�ȡ�����У�
    bool Load_data() {
        try {
            data.clear();

            // ���� rapidcsv ���������ñ�ͷ�������ж��������У�
            rapidcsv::LabelParams labelParams(-1);  // -1 ��ʾû�б�ͷ��
            rapidcsv::SeparatorParams separatorParams(delimiter);

            // ���� rapidcsv �ĵ�
            rapidcsv::Document doc(filePath, labelParams, separatorParams);

            // ֱ�Ӷ�ȡ���������У����ٴ����ͷ��
            for (size_t i = 1; i < doc.GetRowCount(); ++i) {//����0��ʼ 0Ϊcsv��ͷ ��Ӣ�� ֱ���������ݿ� ���Ͳ�����Ӣ��ת��
                                                            //��1��ʼ �Լ������Ӧ���ı�ͷ  
                std::vector<std::string> row = doc.GetRow<std::string>(i);
                std::vector<std::wstring> wideRow;
                for (const auto& cell : row) {
                    wideRow.push_back(toWide(cell));
                }
                data.push_back(wideRow);  // ֱ����������У��ޱ�ͷ��
            }

            return true;
        }
        catch (const std::exception& e) {
            std::cerr << "�����ļ�ʧ��: " << e.what() << std::endl;
            data.clear();  // ��մ�������
            return false;
        }
    }
    
    // �洢���ݣ�������κα�ͷ��ֱ��д�������У�


    bool Store_data() {
        try {
            if (data.empty()) {
                std::cerr << "û�����ݿɱ���" << std::endl;
                return false;
            }

            // ���� rapidcsv �ĵ������ñ�ͷ���������У�
            rapidcsv::Document doc(
                "",                          // ��·����ʾ�½��ĵ�
                rapidcsv::LabelParams(-1),   // û�б�ͷ��
                rapidcsv::SeparatorParams(delimiter)
            );

            // �ؼ�����ʽ���� UTF-8 ����ת������������ϵͳĬ�ϣ�
            std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8Converter;

            // �ռ����������У�ʹ����ʽ����ת����
            std::vector<std::vector<std::string>> allRows;
            for (const auto& row : data) {
                std::vector<std::string> narrowRow;
                for (const auto& cell : row) {
                    // ��ʽת��Ϊ UTF-8 ����� string
                    narrowRow.push_back(utf8Converter.to_bytes(cell));
                }
                allRows.push_back(narrowRow);
            }

            // �����������ݣ����� rapidcsv �� SetRow �ӿڣ�
            for (size_t i = 0; i < allRows.size(); ++i) {
                doc.SetRow(i, allRows[i]);
            }

            // �����ļ�ǰ���ֶ�д�� UTF-8 BOM����� Excel �������⣩
            std::ofstream file(filePath, std::ios::out | std::ios::binary);
            if (file.is_open()) {
                // д�� UTF-8 BOM����ѡ������ Excel ��ȷʶ����룩
                file << "\xEF\xBB\xBF";  // BOM �ֽ�����
                doc.Save(file);  // ͨ�������棬ȷ������һ��
                file.close();
            }
            else {
                throw std::runtime_error("�޷����ļ����б���");
            }

            return true;
        }
        catch (const std::exception& e) {
            std::cerr << "�����ļ�ʧ��: " << e.what() << std::endl;
            return false;
        }
    }
   
    // ���һ�����ݣ����ַ���ֱ����ӵ������У�
    void addRow(const std::vector<std::wstring>& row) {
        data.push_back(row);
    }

    // �������
    void clear() {
        data.clear();
    }
};