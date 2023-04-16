// file compress use  snappy c++
#include <snappy.h>
#include <fstream>

// Snappy를 사용하여 파일을 압축합니다.
void compressFile(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream input(inputFile, std::ios::binary);
    std::ofstream output(outputFile, std::ios::binary);

    // 입력 파일의 크기를 결정합니다.
    input.seekg(0, std::ios::end);
    size_t inputSize = input.tellg();
    input.seekg(0, std::ios::beg);

    // 압축된 데이터를 위한 버퍼를 할당합니다.
    std::vector<char> compressedData(snappy::MaxCompressedLength(inputSize));

    // 입력 데이터를 압축합니다.
    snappy::RawCompress(inputData, inputSize, compressedData.data(), &compressedSize);

    // 압축된 데이터를 출력 파일에 씁니다.
    output.write(compressedData.data(), compressedSize);
}

// Snappy를 사용하여 파일을 해제합니다.
void decompressFile(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream input(inputFile, std::ios::binary);
    std::ofstream output(outputFile, std::ios::binary);

    // 입력 파일의 크기를 결정합니다.
    input.seekg(0, std::ios::end);
    size_t inputSize = input.tellg();
    input.seekg(0, std::ios::beg);

    // 압축 해제된 데이터를 위한 버퍼를 할당합니다.
    std::vector<char> uncompressedData(inputSize);

    // 입력 데이터를 압축 해제합니다.
    snappy::RawUncompress(inputData, inputSize, uncompressedData.data());

    // 압축 해제된 데이터를 출력 파일에 씁니다.
    output.write(uncompressedData.data(), uncompressedData.size());
}

// folder compress use  snappy c++
#include <snappy.h>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <vector>

namespace fs = std::filesystem;

// 폴더를 압축합니다.
void compressFolder(const std::string& folderPath, const std::string& outputFilePath) {
    std::vector<std::string> filePaths;

    // 폴더의 모든 파일 경로를 수집합니다.
    for (const auto& entry : fs::recursive_directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            filePaths.push_back(entry.path().string());
        }
    }

    // 압축된 데이터를 출력 파일에 씁니다.
    std::ofstream output(outputFilePath, std::ios::binary);

    for (const auto& filePath : filePaths) {
        std::ifstream input(filePath, std::ios::binary);

        // 입력 파일의 크기를 결정합니다.
        input.seekg(0, std::ios::end);
        size_t inputSize = input.tellg();
        input.seekg(0, std::ios::beg);

        // 압축된 데이터를 위한 버퍼를 할당합니다.
        std::vector<char> compressedData(snappy::MaxCompressedLength(inputSize));

        // 입력 데이터를 압축합니다.
        snappy::RawCompress(inputData, inputSize, compressedData.data(), &compressedSize);

        // 압축된 데이터의 크기와 경로를 출력 파일에 씁니다.
        size_t compressedSize = compressedData.size();
        output.write(reinterpret_cast<const char*>(&compressedSize), sizeof(compressedSize));
        output.write(filePath.c_str(), filePath.size() + 1);

        // 압축된 데이터를 출력 파일에 씁니다.
        output.write(compressedData.data(), compressedSize);
    }
}

// 폴더를 해제합니다.
void decompressFolder(const std::string& inputFilePath, const std::string& outputFolderPath) {
    // 입력 파일을 엽니다.
    std::ifstream input(inputFilePath, std::ios::binary);

    while (true) {
        // 압축된 데이터의 크기를 읽습니다.
        size_t compressedSize;
        input.read(reinterpret_cast<char*>(&compressedSize), sizeof(compressedSize));

        if (input.eof()) {
            break;
        }

        // 파일 경로를 읽습니다.
        std::string filePath;
        std::getline(input, filePath, '\0');

        // 압축 해제된 데이터를 위한 버퍼를 할당합니다.
        std::vector<char> uncompressedData(filePath.size());

        // 입력 데이터를 압축 해제합니다.
        snappy::RawUncompress(inputData, compressedSize, uncompressedData.data());

        // 출력 폴더에 파일을 생성하고 압축 해제된 데이터를 씁니다.
        fs::create_directories(fs::path(outputFolderPath) / fs::

// get  compress size before compress using snappy c++
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

// 파일의 압축되지 않은 크기를 반환합니다.
size_t getFileSize(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    file.seekg(0, std::ios::end);
    return file.tellg();
}

// 파일의 압축된 크기를 반환합니다.
size_t getCompressedFileSize(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    size_t compressedSize;
    file.read(reinterpret_cast<char*>(&compressedSize), sizeof(compressedSize));
    return compressedSize;
}

int main() {
    // 압축할 파일의 경로
    std::string filePath = "example.txt";

    // 압축 전 파일의 크기 출력
    std::cout << "File size: " << getFileSize(filePath) << " bytes\n";

    // Snappy 압축을 사용하여 파일 압축
    std::ifstream input(filePath, std::ios::binary);
    std::ofstream output("example.snappy", std::ios::binary);
    std::vector<char> compressedData(snappy::MaxCompressedLength(inputSize));
    snappy::RawCompress(inputData, inputSize, compressedData.data(), &compressedSize);
    output.write(reinterpret_cast<const char*>(&compressedSize), sizeof(compressedSize));
    output.write(compressedData.data(), compressedSize);

    // 압축 후 파일의 크기 출력
    std::cout << "Compressed file size: " << getCompressedFileSize("example.snappy") << " bytes\n";

    return 0;
}

// get compress folder size before compress

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

// 디렉토리 트리를 재귀적으로 순회하며 모든 파일의 크기를 합산합니다.
size_t getDirectorySize(const fs::path& dirPath) {
    size_t size = 0;
    for (const auto& entry : fs::recursive_directory_iterator(dirPath)) {
        if (fs::is_regular_file(entry)) {
            size += fs::file_size(entry.path());
        }
    }
    return size;
}

int main() {
    // 압축할 디렉토리의 경로
    fs::path dirPath = "example_dir";

    // 압축 전 디렉토리 크기 출력
    std::cout << "Directory size: " << getDirectorySize(dirPath) << " bytes\n";

    // Snappy 압축을 사용하여 디렉토리 압축
    // ...

    // 압축 후 디렉토리 크기 출력
    // ...

    return 0;
}
