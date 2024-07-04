#include <iostream>
#include <cstdlib>
#include <string>

void runCommand(const std::string& command) {
    int result = system(command.c_str());
    if (result != 0) {
        std::cerr << "Command failed: " << command << std::endl;
        exit(1);
    }
}

void installUploader() {
    std::cout << "Installing..." << std::endl;

    // Update package list
    //runCommand("sudo apt-get update");

    // Install dependencies
    //runCommand("sudo apt-get install -y python3 python3-requests");


    // Make the script executable
    runCommand("chmod +rwx Files/upload_app");
    runCommand("chmod +rwx Files/get_gofile_server.py");
    runCommand("chmod +rwx Files/parse_json.py");
    runCommand("chmod +rwx Files/get_gofile_dlink.py");
    
    // Move the script to a directory in the PATH
    runCommand("sudo mv Files/upload_app /usr/local/bin/upload_app");
    runCommand("sudo mv Files/get_gofile_server.py /usr/local/bin/get_gofile_server.py");
    runCommand("sudo mv Files/parse_json.py /usr/local/bin/parse_json.py"); 
    runCommand("sudo mv Files/get_gofile_dlink.py /usr/local/bin/get_gofile_dlink.py");
    

    std::cout << "Task-Force Uploader installed successfully!" << std::endl;
}

int main() {
    installUploader();
    return 0;
}
