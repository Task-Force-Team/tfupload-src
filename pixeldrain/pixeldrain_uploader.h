#ifndef PIXELDRAIN_UPLOADER_H
#define PIXELDRAIN_UPLOADER_H

#include <string>

class PixelDrainUploader {
public:
    bool upload(const std::string& file_path);
};

#endif // PIXELDRAIN_UPLOADER_H
