cmake_minimum_required(VERSION 3.10)
project(UploadApp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the libcurl package
find_package(CURL REQUIRED)

# Add your upload_app executable
add_executable(upload_app
    main.cpp
    gofile/gofile_uploader.cpp
    pixeldrain/pixeldrain_uploader.cpp
    api/api_management.cpp
    sys/progress_callback.cpp
)

# Link the libcurl library to your upload_app executable
target_link_libraries(upload_app ${CURL_LIBRARIES})

# Add include directories to the upload_app target
target_include_directories(upload_app PRIVATE
    ${CMAKE_SOURCE_DIR}/gofile
    ${CMAKE_SOURCE_DIR}/pixeldrain
    ${CMAKE_SOURCE_DIR}/api
    ${CMAKE_SOURCE_DIR}/sys
)

# Add setup executable
add_executable(setup
    Setup/setup.cpp
)

# Add include directories to the setup target
target_include_directories(setup PRIVATE
    ${CMAKE_SOURCE_DIR}/Setup
)

# Define the target directory for the files
set(FILES_DIR ${CMAKE_BINARY_DIR}/Files)
set(OUT_DIR ${CMAKE_BINARY_DIR}/out)

# Ensure the target directories exist
file(MAKE_DIRECTORY ${FILES_DIR})
file(MAKE_DIRECTORY ${OUT_DIR})

