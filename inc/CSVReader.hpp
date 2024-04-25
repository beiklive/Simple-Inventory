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



// CSVReader ��
class CSVReader {
private:
    string_t filename;
    char delimiter;
    vector<Item> items;

public:
    CSVReader(const string_t& filename, char delimiter = ',') : filename(filename), delimiter(delimiter) {}

    // ��ȡ CSV �ļ�
    vector<Item> readCSV() {
        ifstream file(filename);
        if (!file.is_open()) {
            // cerr << "�޷����ļ�:\t" << filename << endl;
            return items;
        }

        string_t line;
        getline(file, line); // ������һ�б�����
        while (getline(file, line)) {
            // cout << "��ȡ����������:\t" << line << endl; // ��ӡ��ȡ����ÿһ������

            istringstream iss(line);
            string_t field;
            vector<string_t> fields;
            while (getline(iss, field, delimiter)) {
                fields.push_back(field);
            }

            if (fields.size() != 6) {
                // cerr << "����� CSV ��ʽ:\t" << line << endl;
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
                // cerr << "ת��ʧ��:\t" << e.what() << endl;
                continue;
            }

            items.push_back(item);
        }

        file.close();
        return items;
    }
};

#endif  // INC_CSVREADER_HPP_
