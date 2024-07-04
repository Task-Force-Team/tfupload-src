#include <iostream>
#include <string>
#include "api/api_management.h"
#include "gofile/gofile_uploader.h"
#include "pixeldrain/pixeldrain_uploader.h"

void printBanner() {
    std::cout << R"(
 _______               _      _______                                _     _         _                    _               
(_______)             | |    (_______)                              | |   | |       | |                  | |              
 _         ____   ___ | |  _  _____     ___    ____   ____   ____   | |   | | ____  | |  ___    ____   _ | |  ____   ____ 
| |       / _  | /___)| | / )|  ___)   / _ \  / ___) / ___) / _  )  | |   | ||  _ \ | | / _ \  / _  | / || | / _  ) / ___)
| |_____ ( ( | ||___ || |< ( | |      | |_| || |    ( (___ ( (/ /   | |___| || | | || || |_| |( ( | |( (_| |( (/ / | |    
 \______) \_||_|(___/ |_| \_)|_|       \___/ |_|     \____) \____)   \______|| ||_/ |_| \___/  \_||_| \____| \____)|_|    
                                                                             |_|
)";
}

int main(int argc, char* argv[]) {
    printBanner();
    std::cout << "-Open Source Implent of Task Force Uploader-" << std::endl;
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " [set pd_api <api_key> | upload <service> <file_path>]" << std::endl;
        return 1;
    }

    std::string command = argv[1];

    if (command == "upload") {
        if (argc < 4) {
            std::cerr << "Usage: " << argv[0] << " upload <service> <file_path>" << std::endl;
            return 1;
        }
        std::string service = argv[2];
        std::string file_path = argv[3];

        if (service == "gofile") {
            GofileUploader uploader;
            if (uploader.upload(file_path)) {
                std::cout << "File uploaded successfully." << std::endl;
            } else {
                std::cerr << "Failed to upload file." << std::endl;
            }
        } else if (service == "pixeldrain") {
            PixelDrainUploader uploader;
            if (uploader.upload(file_path)) {
                std::cout << "File uploaded successfully." << std::endl;
            } else {
                std::cerr << "Failed to upload file." << std::endl;
            }
        } else {
            std::cerr << "Unknown service." << std::endl;
            return 1;
        }
    } else {
        std::cerr << "Unknown command." << std::endl;
        return 1;
    }

    return 0;
}
