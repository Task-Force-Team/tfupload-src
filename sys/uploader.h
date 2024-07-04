#ifndef UPLOADER_H
#define UPLOADER_H

#include <string>

class Uploader {
public:
    virtual ~Uploader() = default;
    virtual bool upload(const std::string& file_path) = 0;
};

#endif // UPLOADER_H
