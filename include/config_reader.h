//
// Created by cwl on 19-3-17.
//

#ifndef STUDY_CONFIG_READER_H
#define STUDY_CONFIG_READER_H

#include <map>
#include <iostream>
#include <fstream>

namespace config_reader {

    using std::map;
    using std::string;
    using std::cin;
    using std::cout;
    using std::endl;
    using std::make_pair;
    using std::pair;

    string string_trim(char *str, int l, int r) {
        string ret_string;
        while(l <= r) {
            if(str[l] == ' ' || str[l] == '\t') {
                l++;
                continue;
            }
            else if(str[r] == ' ' || str[r] == '\t') {
                r--;
                continue;
            } else {
                break;
            }
        }
        str[++r] = '\0';
        ret_string = str + l;
        str[r] = '*';
        return ret_string;
    }

    pair<string, string> get_key_value(const string& line) {
        char *str = new char[line.length() + 1];
        int pos = 0;
        for (int i = 0; i < line.length(); i++ ) {
            str[i] = line[i];
            if (str[i] == '=') { pos = i; }
        }
        string key = string_trim(str, 0, pos - 1);
        string value = string_trim(str, pos + 1, line.length() - 1);
        delete [] str;
        return make_pair(key, value);
    }

    void init_config(map<string, string>&mp, const string& file_name = "main.conf") {
        string path = PROJECT_PATH + "config/" + file_name;
        std::ifstream fp(path);
        string line;
        while (getline(fp, line)) {
            if(line.size() == 0 || line[0] == '#' || line[0] == '[') {
                continue;
            }
            mp.insert(get_key_value(line));
        }
    }

}

#endif //STUDY_CONFIG_READER_H
