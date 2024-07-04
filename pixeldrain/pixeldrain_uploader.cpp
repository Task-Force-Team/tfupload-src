#include "pixeldrain_uploader.h"
#include "api_management.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <cctype>

bool isPrintable(unsigned char ch) {
    return std::isprint(ch) || std::isspace(ch);
}

bool PixelDrainUploader::upload(const std::string& filePath) {
    std::string apiKey = "3f16c164-f46f-4ffb-b422-d1b472e1bb8f";
    if (apiKey.empty()) {
        std::cerr << "API key is not set." << std::endl;
        return false;
    }

    // Use the -s option to suppress progress information
    std::string command = "curl -s -T \"" + filePath + "\" -u :" + apiKey + " https://pixeldrain.com/api/file/ > output.json 2>&1";
    int result = system(command.c_str());

    if (result == 0) {
        std::ifstream outputFile("output.json");
        if (outputFile.is_open()) {
            std::string jsonResponse((std::istreambuf_iterator<char>(outputFile)), std::istreambuf_iterator<char>());
            outputFile.close();

            // Remove non-printable characters
            jsonResponse.erase(std::remove_if(jsonResponse.begin(), jsonResponse.end(), [](unsigned char ch) {
                return !isPrintable(ch);
            }), jsonResponse.end());

            // Trim leading and trailing whitespace
            jsonResponse.erase(jsonResponse.begin(), std::find_if(jsonResponse.begin(), jsonResponse.end(), [](unsigned char ch) {
                return !std::isspace(ch);
            }));
            jsonResponse.erase(std::find_if(jsonResponse.rbegin(), jsonResponse.rend(), [](unsigned char ch) {
                return !std::isspace(ch);
            }).base(), jsonResponse.end());

            // Pass the JSON response to the Python script
            std::string pythonCommand = "python3 /usr/local/bin/parse_json.py '" + jsonResponse + "'";
            int pythonResult = system(pythonCommand.c_str());
            if (pythonResult != 0) {
                std::cerr << "Failed to execute Python script." << std::endl;
                return false;
            }
        } else {
            std::cerr << "Failed to open output file." << std::endl;
            return false;
        }
        std::remove("output.json"); // Clean up the temporary file
        std::cout << "File uploaded successfully." << std::endl;
        return true;
    } else {
        std::cerr << "Failed to upload file." << std::endl;
        return false;
    }
}
