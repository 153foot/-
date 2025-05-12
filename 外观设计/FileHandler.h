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
    char delimiter;           // 分隔符（窄字符）
    std::string filePath;     // 文件路径
    std::vector<std::vector<std::wstring>> data;  // 宽字符数据存储（无表头，纯数据行）

    // 字符串转换工具
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

    // 窄字符串转宽字符串
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

    // 宽字符串转窄字符串
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
    // 构造函数：指定文件路径和分隔符
    FileHandler(const std::string& filePath, char delimiter = ',')
        : filePath(filePath), delimiter(delimiter) {
    }

    // 获取数据（加载后返回数据引用）
    std::vector<std::vector<std::wstring>>& getData() {
        static std::vector<std::vector<std::wstring>> emptyData;  // 避免返回未定义引用
        if (!Load_data()) return emptyData;
        return data;
    }
    void setData(std::vector<std::vector<std::wstring>>& other) {
        this->data = other;
        if (Store_data()) {

            std::cerr << "数据存储成功" << std::endl;
        }
        else {

            std::cerr << "数据存储失败" << std::endl;

        }
    }
    
    
    //}bool Load_data() {
    //    try {
    //        data.clear();

    //        // 配置rapidcsv参数（禁用表头，所有行都是数据行）
    //        rapidcsv::LabelParams labelParams(-1);  // -1表示没有表头行
    //        rapidcsv::SeparatorParams separatorParams(delimiter);

    //        // 关键：使用文件流打开并指定UTF-8编码
    //        std::ifstream fileStream(filePath, std::ios::binary);
    //        if (!fileStream.is_open()) {
    //            throw std::runtime_error("无法打开文件");
    //        }

    //        // 检查BOM（可选）
    //        char bom[3] = { 0 };
    //        fileStream.read(bom, 3);
    //        bool hasBom = (bom[0] == '\xEF' && bom[1] == '\xBB' && bom[2] == '\xBF');

    //        // 如果有BOM，跳过；否则回退3字节
    //        if (!hasBom) {
    //            fileStream.seekg(0);
    //        }

    //        // 创建rapidcsv文档（从流加载）
    //        rapidcsv::Document doc(fileStream, labelParams, separatorParams);

    //        // 读取所有数据行
    //        for (size_t i = 1; i < doc.GetRowCount(); ++i) {
    //            std::vector<std::string> row = doc.GetRow<std::string>(i);
    //            std::vector<std::wstring> wideRow;
    //            for (const auto& cell : row) {
    //                // 关键：显式将UTF-8转换为宽字符
    //                wideRow.push_back(utf8_to_wstring(cell));
    //            }
    //            data.push_back(wideRow);
    //        }

    //        return true;
    //    }
    //    catch (const std::exception& e) {
    //        std::cerr << "加载文件失败: " << e.what() << std::endl;
    //        data.clear();
    //        return false;
    //    }
    //}

    //// 辅助函数：UTF-8字符串转宽字符
    //std::wstring utf8_to_wstring(const std::string& utf8Str) {
    //    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    //    try {
    //        return converter.from_bytes(utf8Str);
    //    }
    //    catch (const std::exception&) {
    //        // 错误处理：返回空字符串或替换非法字符
    //        return L"";
    //    }
    //}
    // 加载数据（跳过所有表头，直接读取数据行）
    bool Load_data() {
        try {
            data.clear();

            // 配置 rapidcsv 参数（禁用表头，所有行都是数据行）
            rapidcsv::LabelParams labelParams(-1);  // -1 表示没有表头行
            rapidcsv::SeparatorParams separatorParams(delimiter);

            // 创建 rapidcsv 文档
            rapidcsv::Document doc(filePath, labelParams, separatorParams);

            // 直接读取所有数据行（不再处理表头）
            for (size_t i = 1; i < doc.GetRowCount(); ++i) {//不从0开始 0为csv表头 是英文 直接用于数据库 类型不必中英文转换
                                                            //从1开始 自己输入对应中文表头  
                std::vector<std::string> row = doc.GetRow<std::string>(i);
                std::vector<std::wstring> wideRow;
                for (const auto& cell : row) {
                    wideRow.push_back(toWide(cell));
                }
                data.push_back(wideRow);  // 直接添加数据行（无表头）
            }

            return true;
        }
        catch (const std::exception& e) {
            std::cerr << "加载文件失败: " << e.what() << std::endl;
            data.clear();  // 清空错误数据
            return false;
        }
    }
    
    // 存储数据（不添加任何表头，直接写入数据行）


    bool Store_data() {
        try {
            if (data.empty()) {
                std::cerr << "没有数据可保存" << std::endl;
                return false;
            }

            // 创建 rapidcsv 文档（禁用表头，纯数据行）
            rapidcsv::Document doc(
                "",                          // 空路径表示新建文档
                rapidcsv::LabelParams(-1),   // 没有表头行
                rapidcsv::SeparatorParams(delimiter)
            );

            // 关键：显式设置 UTF-8 编码转换（避免依赖系统默认）
            std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8Converter;

            // 收集所有数据行（使用显式编码转换）
            std::vector<std::vector<std::string>> allRows;
            for (const auto& row : data) {
                std::vector<std::string> narrowRow;
                for (const auto& cell : row) {
                    // 显式转换为 UTF-8 编码的 string
                    narrowRow.push_back(utf8Converter.to_bytes(cell));
                }
                allRows.push_back(narrowRow);
            }

            // 逐行设置数据（兼容 rapidcsv 的 SetRow 接口）
            for (size_t i = 0; i < allRows.size(); ++i) {
                doc.SetRow(i, allRows[i]);
            }

            // 保存文件前，手动写入 UTF-8 BOM（解决 Excel 乱码问题）
            std::ofstream file(filePath, std::ios::out | std::ios::binary);
            if (file.is_open()) {
                // 写入 UTF-8 BOM（可选，用于 Excel 正确识别编码）
                file << "\xEF\xBB\xBF";  // BOM 字节序列
                doc.Save(file);  // 通过流保存，确保编码一致
                file.close();
            }
            else {
                throw std::runtime_error("无法打开文件进行保存");
            }

            return true;
        }
        catch (const std::exception& e) {
            std::cerr << "保存文件失败: " << e.what() << std::endl;
            return false;
        }
    }
   
    // 添加一行数据（宽字符，直接添加到数据行）
    void addRow(const std::vector<std::wstring>& row) {
        data.push_back(row);
    }

    // 清空数据
    void clear() {
        data.clear();
    }
};