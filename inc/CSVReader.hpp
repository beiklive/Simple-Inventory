// Copyright (c) RealCoolEngineer. 2024. All rights reserved.
// Author: beiklive
// Date: 2024-04-25
#ifndef INC_CSVREADER_HPP_
#define INC_CSVREADER_HPP_
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "ItemManager.h"
using namespace std;
using string_t = std::string;



// CSVReader 类
class CSVReader {
private:
    string_t filename;
    char delimiter;
    vector<Item> items;

public:
    CSVReader(const string_t& filename, char delimiter = ',') : filename(filename), delimiter(delimiter) {}

    // 读取 CSV 文件
    vector<Item> readCSV() {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "无法打开文件：" << filename << endl;
            return items;
        }

        string_t line;
        getline(file, line); // 跳过第一行标题行
        while (getline(file, line)) {
            cout << "读取到的行内容：" << line << endl; // 打印读取到的每一行内容

            istringstream iss(line);
            string_t field;
            vector<string_t> fields;
            while (getline(iss, field, delimiter)) {
                fields.push_back(field);
            }

            if (fields.size() != 6) {
                cerr << "错误的 CSV 格式：" << line << endl;
                continue;
            }

            Item item;
            try {

                item.id = stoi(fields[0]);
                item.name = fields[1];
                item.value = stoi(fields[2]);
                item.weight = stoi(fields[3]);
                item.quantity = stoi(fields[4]);
                item.type = fields[5];

            } catch (const exception& e) {
                cerr << "转换失败：" << e.what() << endl;
                continue;
            }

            items.push_back(item);
        }

        file.close();
        return items;
    }
};

#endif  // INC_CSVREADER_HPP_
