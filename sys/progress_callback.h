#ifndef PROGRESS_CALLBACK_H
#define PROGRESS_CALLBACK_H

#include <curl/curl.h>

int progress_callback(void* clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow);

#endif // PROGRESS_CALLBACK_H
