1.zipOpen 함수를 사용하여 압축 파일을 엽니다.
2.zipOpenNewFileInZip 함수를 사용하여 압축 파일에 새로운 파일을 추가합니다.
3.zipWriteInFileInZip 함수를 사용하여 파일 데이터를 씁니다.
4.zipCloseFileInZip 함수를 사용하여 현재 파일을 닫습니다.
5.2 ~ 4 과정을 반복하여 압축 파일에 모든 파일을 추가합니다.
6.zipClose 함수를 사용하여 압축 파일을 닫습니다.

zipOpen: 새로운 zip 파일을 생성하거나, 기존의 zip 파일을 엽니다.
zipOpenNewFileInZip: zip 파일에 새로운 파일을 추가합니다.
zipWriteInFileInZip: zip 파일 내의 현재 파일에 데이터를 씁니다.
zipCloseFileInZip: zip 파일 내의 현재 파일을 닫습니다.
zipClose: zip 파일을 닫습니다.

#include <minizip/zip.h>

void compressFiles(const std::vector<std::wstring>& fileNames, const std::wstring& zipFileName)
{
    // Step 1: Open zip file
    zipFile zip = zipOpen(zipFileName.c_str(), APPEND_STATUS_CREATE);

    // Step 2-5: Add files to zip file
    for (const auto& fileName : fileNames)
    {
        // Open file
        FILE* file = _wfopen(fileName.c_str(), L"rb");
        if (!file)
        {
            // Handle file open error
            continue;
        }

        // Get file size
        fseek(file, 0, SEEK_END);
        uLong fileSize = ftell(file);
        rewind(file);

        // Create zip file entry
        std::string entryName(fileName.begin(), fileName.end());
        zip_fileinfo fileInfo = { 0 };
        zipOpenNewFileInZip(zip, entryName.c_str(), &fileInfo, NULL, 0, NULL, 0, NULL, Z_DEFLATED, Z_DEFAULT_COMPRESSION);

        // Write file data to zip file
        std::vector<char> buffer(fileSize);
        fread(buffer.data(), 1, fileSize, file);
        zipWriteInFileInZip(zip, buffer.data(), fileSize);

        // Close zip file entry
        zipCloseFileInZip(zip);
        fclose(file);
    }

    // Step 6: Close zip file
    zipClose(zip, NULL);
}
