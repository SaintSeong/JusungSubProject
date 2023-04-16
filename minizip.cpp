// folder compress use minizip
minizip을 사용하여 폴더를 압축하는 방법은 다음과 같습니다.

먼저, minizip 라이브러리와 zlib 라이브러리를 다운로드하고 설치해야 합니다. 이 라이브러리들은 C 언어로 작성되었으므로, 컴파일러가 필요합니다.

압축할 폴더를 선택합니다.

minizip 라이브러리를 사용하여 폴더를 압축합니다. 이를 위해 다음과 같은 단계를 수행합니다.

a. ZIP 파일을 생성합니다.

b. 압축할 폴더의 내용을 ZIP 파일에 추가합니다.

c. ZIP 파일을 닫습니다.

압축된 ZIP 파일이 생성되었는지 확인합니다.
#include "zip.h"

int main() {
    const char* folder_path = "/path/to/folder";
    const char* zip_file_path = "/path/to/archive.zip";

    // Create a new ZIP archive
    zipFile archive = zipOpen(zip_file_path, ZIP_CREATE);

    // Add the contents of the folder to the archive
    zipAddFolder(archive, folder_path, 0);

    // Close the archive
    zipClose(archive, NULL);

    return 0;
}
// get folder compress size 
#include "zip.h"
#include <stdio.h>

int main() {
    const char* zip_file_path = "/path/to/archive.zip";

    // Open the ZIP archive
    zipFile archive = zipOpen(zip_file_path, 0);

    // Get the size of each file in the ZIP archive and add them together
    long long total_size = 0;
    int num_files = zipGetNumFiles(archive, 0);
    for (int i = 0; i < num_files; i++) {
        zip_fileinfo file_info;
        zip_stat_index(archive, i, 0, &file_info);
        total_size += file_info.size;
    }

    // Close the ZIP archive
    zipClose(archive, NULL);

    printf("Compressed folder size: %lld bytes\n", total_size);

    return 0;
}

// get compress size before compress 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

long long get_folder_size(const char* folder_path);

int main() {
    const char* folder_path = "/path/to/folder";

    long long uncompressed_size = get_folder_size(folder_path);

    printf("Uncompressed folder size: %lld bytes\n", uncompressed_size);

    return 0;
}

long long get_folder_size(const char* folder_path) {
    DIR* dir = opendir(folder_path);
    if (!dir) {
        printf("Error: unable to open directory %s\n", folder_path);
        return 0;
    }

    long long size = 0;
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", folder_path, entry->d_name);

        struct stat info;
        if (stat(path, &info) == -1) {
            printf("Error: unable to get file info for %s\n", path);
            continue;
        }

        if (S_ISREG(info.st_mode)) {
            size += info.st_size;
        } else if (S_ISDIR(info.st_mode)) {
            size += get_folder_size(path);
        }
    }

    closedir(dir);

    return size;
}

// limit 20mb use get_folder_size

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

long long get_folder_size(const char* folder_path);

int main() {
    const char* folder_path = "/path/to/folder";

    long long uncompressed_size = get_folder_size(folder_path);

    if (uncompressed_size > 20 * 1024 * 1024) {
        printf("Error: folder size is larger than 20MB\n");
        return 1;
    }

    printf("Folder size is %lld bytes, which is within the limit.\n", uncompressed_size);

    return 0;
}

long long get_folder_size(const char* folder_path) {
    DIR* dir = opendir(folder_path);
    if (!dir) {
        printf("Error: unable to open directory %s\n", folder_path);
        return 0;
    }

    long long size = 0;
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", folder_path, entry->d_name);

        struct stat info;
        if (stat(path, &info) == -1) {
            printf("Error: unable to get file info for %s\n", path);
            continue;
        }

        if (S_ISREG(info.st_mode)) {
            size += info.st_size;
        } else if (S_ISDIR(info.st_mode)) {
            size += get_folder_size(path);
        }
    }

    closedir(dir);

    return size;
}
