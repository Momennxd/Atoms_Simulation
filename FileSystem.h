#pragma once

#include "main_includes.h"
#include "core.h"

using namespace std;

class FileSystem
{

public:


    static std::vector<std::string> split(const std::string& line, char seperator) {

        std::vector<std::string> result;

        std::stringstream ss(line);

        std::string token;

        while (std::getline(ss, token, seperator)) {
            result.push_back(token);
        }

        return result;
    }



    static std::vector<std::string> GetFileContent(const std::string& filePath, const char& RowSeparator) {
        std::ifstream file(filePath);
        std::vector<std::string> vecResult;

        // Check if the file is open
        if (!file.is_open()) {
            throw std::runtime_error("Unable to open file");
        }

        std::string line;

        // Read each line from the file
        while (std::getline(file, line)) {
            std::vector<std::string> splittedLine = split(line, RowSeparator);

            // Add the split content to the result vector
            vecResult.insert(vecResult.end(), splittedLine.begin(), splittedLine.end());
        }

        file.close();

        return vecResult;
    }


    static string GetConfigSetting(const vector<string>& FileContent, const string& setting_name)
    {
       
        vector<vector<string>> vFileSettingsKeyVal;

        for (const auto& row : FileContent)
        {

            vector<string> vec = (split(row, TEXTFILE_SETTING_NAME_VALUE_SEPERATOR));

            if (vec.size() < 2)
                 continue;

            if (vec[0] == setting_name)
                return vec[1];

        }

        throw runtime_error("Setting does not exist");

    }
   

    static unordered_map<string, string> GetConfigSettingsMap(const std::string& filePath)
    {
        vector<string> FileContent = GetFileContent(filePath, TEXTFILE_ROW_SEPERATOR);
        unordered_map<string, string> map;

        vector<vector<string>> vFileSettingsKeyVal;

        for (const auto& row : FileContent)
        {

            vector<string> vec = (split(row, TEXTFILE_SETTING_NAME_VALUE_SEPERATOR));

            if (vec.size() < 2)
                continue;

            map.insert_or_assign(vec[0], vec[1]);

        }

        return map;
    }






};

