#include "MainForm.h"
#include <Windows.h>
#include <iostream>
using namespace EyeVisPro;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    
    MainForm form;
    Application::Run(% form);

    return 0;
}


System::Void MainForm::MainForm_Load(System::Object^ sender, System::EventArgs^ e)
{
    auto start = std::chrono::system_clock::now();
    auto start_t = std::chrono::system_clock::to_time_t(start);

    std::ofstream logfile;
    logfile.open("logfile.txt", std::ios_base::app);
    logfile << "SESSION STARTED AT " << std::ctime(&start_t);
    logfile.close();
}

System::Void MainForm::MainForm_Closed(System::Object^ sender, System::EventArgs^ e)
{
    auto end = std::chrono::system_clock::now();
    auto end_t = std::chrono::system_clock::to_time_t(end);

    std::ofstream logfile;
    logfile.open("logfile.txt", std::ios_base::app);
    logfile << "SESSION ENDED AT " << std::ctime(&end_t) << std::endl;
    logfile.close();
}

void MainForm::initWidgets() {}
void MainForm::initGraphics() 
{
    graphics = panel->CreateGraphics();
    graphics->TranslateTransform(panel->Width / 2, panel->Height / 2);
    graphics->ScaleTransform(1, -1);
}

void render()
{
    std::ofstream logfile;
    logfile.open("logfile.txt", std::ios_base::app);
    logfile << "entered : " << __TIMESTAMP__ << " : " << __FILE__ << " : " << __FUNCTION__ << " : " << __LINE__ << std::endl;
    logfile.close();
}

System::Void MainForm::button_Click(System::Object^ sender, System::EventArgs^ e)
{
    std::ofstream logfile;
    logfile.open("logfile.txt", std::ios_base::app);
    logfile << "entered : " << __TIMESTAMP__ << " : " << __FILE__ << " : " << __FUNCTION__ << " : " << __LINE__ << std::endl;
    logfile.close();

    render();
}