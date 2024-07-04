#ifndef GOFILE_UPLOADER_H
#define GOFILE_UPLOADER_H

#include "uploader.h"
#include <string>

class GofileUploader : public Uploader {
public:
    bool upload(const std::string& file_path) override;
private:
    std::string getServer();
};

#endif // GOFILE_UPLOADER_H
