#include <iostream>
#include <fstream>
#include <string>
#include "api_management.h"
// Function to set the API key
void setApiKey(const std::string& apiKey) {
    std::ofstream outFile(".pd_api_key");
    if (outFile.is_open()) {
        outFile << apiKey;
        outFile.close();
        std::cout << "API key set successfully." << std::endl;
    } else {
        std::cerr << "Unable to save API key." << std::endl;
    }
}

// Function to get the API key
std::string getApiKey() {
    std::ifstream inFile(".pd_api_key");
    std::string apiKey;
    if (inFile.is_open()) {
        std::getline(inFile, apiKey);
        inFile.close();
    } else {
        std::cerr << "Unable to read API key." << std::endl;
    }
    return apiKey;
}
