#define _USE_MATH_DEFINES

#include "MainForm.h"
#include <cmath>
#include <limits>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "geometry.h"
#include "raytracer.h"
#include "poly.h"
#include "taskmanager.h"

using namespace EyeVizPro;

System::Void MainForm::btn_mov_Click(System::Object^ sender, System::EventArgs^ e)
{
    // move camera task
    MoveCameraTask^ movtask = gcnew MoveCameraTask(7, 7, 0);
    manageTask(movtask);

    // render scene task
    RenderSceneTask^ rendtask = gcnew RenderSceneTask(bitmap);
    manageTask(rendtask);

    panel->Refresh();

}

System::Void MainForm::btn_rot_Click(System::Object^ sender, System::EventArgs^ e)
{
    // rotate camera task
    RotateCameraTask^ rottask = gcnew RotateCameraTask(0, -M_PI / 5, 0);
    manageTask(rottask);

    // render scene task
    RenderSceneTask^ rendtask = gcnew RenderSceneTask(bitmap);
    manageTask(rendtask);
    
    panel->Refresh();
}

System::Void MainForm::MainForm_Load(System::Object^ sender, System::EventArgs^ e)
{
    initGraphics();

    // render scene task
    RenderSceneTask^ rendtask = gcnew RenderSceneTask(bitmap);
    manageTask(rendtask);
}

System::Void MainForm::initGraphics()
{
    bitmap = gcnew Drawing::Bitmap(panel->Width, panel->Height);
    graphics = Graphics::FromImage(bitmap);
    panel->BackgroundImage = bitmap;
}

int main() {

    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    MainForm form;
    Application::Run(% form);

    return 0;
} 