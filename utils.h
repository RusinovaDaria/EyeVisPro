#pragma once

#include <iostream>
#include <fstream>
#include <string.h>
#include "geometry.h"

#define SUCCESS 0
#define CONFIG_PATH ("config.txt")

void MarshalString(System::String^ s, std::string& os);
float dot(const Vec3f& v1, const Vec3f& v2);

