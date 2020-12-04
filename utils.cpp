#include "utils.h"

void MarshalString(System::String^ s, std::string& os) {
    using namespace System::Runtime::InteropServices;
    const char* chars =
        (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
    os = chars;
    Marshal::FreeHGlobal(System::IntPtr((void*)chars));
}

float dot(const Vec3f& v1, const Vec3f& v2)
{
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}