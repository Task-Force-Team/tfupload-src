#include <iostream>
#include <curl/curl.h>
#include <string>
#include <iomanip>
#include <mutex>

#define PROGRESS_BAR_WIDTH 50

std::mutex mtx;

int progress_callback(void* clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow) {
    if (ultotal <= 0) return 0;

    double progress = static_cast<double>(ulnow) / ultotal;
    int bar_length = static_cast<int>(progress * PROGRESS_BAR_WIDTH);

    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "\rUploading: [" << std::string(bar_length, '#') << std::string(PROGRESS_BAR_WIDTH - bar_length, ' ') << "] "
              << std::fixed << std::setprecision(2) << (progress * 100) << "% "
              << ulnow << " / " << ultotal << " bytes"
              << std::flush;

    if (ulnow == ultotal) {
        std::cout << std::endl;
    }

    return 0;
}
