#include "gofile_uploader.h"
#include <curl/curl.h>
#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <array>
#include <memory>
#include "progress_callback.h"

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

std::string GofileUploader::getServer() {
    std::string cmd = "python3 /usr/local/bin/get_gofile_server.py";
    std::string server = exec(cmd.c_str());
    if (server.empty()) {
        std::cerr << "Failed to get server from Gofile API" << std::endl;
        return "";
    }
    // Remove any trailing newline characters
    server.erase(std::remove(server.begin(), server.end(), '\n'), server.end());
    return server;
}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t realsize = size * nmemb;
    std::string* response = (std::string*)userp;
    response->append((char*)contents, realsize);
    return realsize;
}

bool GofileUploader::upload(const std::string& file_path) {
    std::string server = getServer();
    if (server.empty()) {
        std::cerr << "Failed to get server for upload" << std::endl;
        return false;
    }

    std::string uploadUrl = "https://" + server + ".gofile.io/uploadFile";

    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize curl" << std::endl;
        curl_global_cleanup();
        return false;
    }

    curl_easy_setopt(curl, CURLOPT_URL, uploadUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 60L); // 60 seconds connection timeout
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 600L); // 600 seconds total timeout for the transfer

    // Use curl_mime for modern approach
    curl_mime* mime = curl_mime_init(curl);
    if (!mime) {
        std::cerr << "Failed to initialize mime" << std::endl;
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return false;
    }

    curl_mimepart* part = curl_mime_addpart(mime);
    if (!part) {
        std::cerr << "Failed to add mime part" << std::endl;
        curl_mime_free(mime);
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return false;
    }

    curl_mime_name(part, "file");
    curl_mime_filedata(part, file_path.c_str());

    curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);

    // Set the progress callback function
    curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, progress_callback);
    curl_easy_setopt(curl, CURLOPT_XFERINFODATA, NULL);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);

    // Capture the JSON response
    std::string jsonResponse;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &jsonResponse);

    res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
    } else {
        std::cout << "\nUpload complete!" << std::endl;

    

        // Execute the Python script to parse the JSON response and get the download link
        std::string pythonCmd = "python3 /usr/local/bin/get_gofile_dlink.py parse '" + jsonResponse + "'";
        std::string downloadLink = exec(pythonCmd.c_str());
        std::cout << "Download link: " << downloadLink << std::endl;
    }

    curl_easy_cleanup(curl);
    curl_mime_free(mime);
    curl_global_cleanup();
    return res == CURLE_OK;
}
