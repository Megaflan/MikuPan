#ifndef MIKUPAN_FILE_LOADING_H
#define MIKUPAN_FILE_LOADING_H
#include <cstdint>
#include <typedefs.h>

extern "C" void LoadImgHdFile();
extern "C" void ReadFullFile(const char *filename, char* buffer);
extern "C" void ReadFileInArchive(int sector, int size, u_int *address);

#endif //MIKUPAN_FILE_LOADING_H