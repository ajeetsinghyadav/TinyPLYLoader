#ifndef PLY_LOADER_C_H
#define PLY_LOADER_C_H

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "tinyply.h"

class PlyLoader_C {
public:
    static void LoadPLY(const std::string& filename);
};

#endif // PLY_LOADER_C_H
