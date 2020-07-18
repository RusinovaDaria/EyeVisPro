#include "MainForm.h"
#include <Windows.h>
using namespace EyeVisPro;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    MainForm form;
    Application::Run(% form);
    return 0;
}