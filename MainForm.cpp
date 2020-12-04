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
    // move active camera
    float x = System::Decimal::ToSingle(nud_movx->Value);
    float y = System::Decimal::ToSingle(nud_movy->Value);
    float z = System::Decimal::ToSingle(nud_movz->Value);
    
    MoveCameraTask^ movtask = gcnew MoveCameraTask(x, y, z);
    manageTask(movtask);

    RenderSceneTask^ rendtask = gcnew RenderSceneTask(bmps[cameras_ud->SelectedIndex]);
    manageTask(rendtask);

    panel->BackgroundImage = bmps[cameras_ud->SelectedIndex];
    panel->Refresh();
}

System::Void MainForm::btn_rot_Click(System::Object^ sender, System::EventArgs^ e)
{
    // move active camera
    float x = System::Decimal::ToSingle(nud_rotx->Value) * 0.01745;
    float y = System::Decimal::ToSingle(nud_roty->Value) * 0.01745;
    float z = System::Decimal::ToSingle(nud_rotz->Value) * 0.01745;

    RotateCameraTask^ rottask = gcnew RotateCameraTask(x, y, z);
    manageTask(rottask);

    RenderSceneTask^ rendtask = gcnew RenderSceneTask(bmps[cameras_ud->SelectedIndex]);
    manageTask(rendtask);

    panel->BackgroundImage = bmps[cameras_ud->SelectedIndex];
    panel->Refresh();
}

System::Void MainForm::btn_add_camera_Click(System::Object^ sender, System::EventArgs^ e)
{
    float x_pos = System::Decimal::ToSingle(nud_posx->Value);
    float y_pos = System::Decimal::ToSingle(nud_posy->Value);
    float z_pos = System::Decimal::ToSingle(nud_posz->Value);

    float x_ang = System::Decimal::ToSingle(nud_angx->Value) * 0.01745;
    float y_ang = System::Decimal::ToSingle(nud_angy->Value) * 0.01745;
    float z_ang = System::Decimal::ToSingle(nud_angz->Value) * 0.01745;


    AddCameraTask^ camtask = gcnew AddCameraTask(x_pos, y_pos, z_pos, x_ang, y_ang, z_ang, cameras_ud);
    manageTask(camtask);

    bmps->Add(gcnew Drawing::Bitmap(panel->Width, panel->Height));
       
    RenderSceneTask^ rendtask = gcnew RenderSceneTask(bmps[cameras_ud->SelectedIndex]);
    manageTask(rendtask);

    panel->BackgroundImage = bmps[cameras_ud->SelectedIndex];
    panel->Refresh();
}

System::Void MainForm::btn_show_Click(System::Object^ sender, System::EventArgs^ e)
{
    SetActiveCameraTask^ setcamtask = gcnew SetActiveCameraTask(cameras_ud->SelectedIndex);
    manageTask(setcamtask);

    panel->BackgroundImage = bmps[cameras_ud->SelectedIndex];
}



System::Void MainForm::MainForm_Load(System::Object^ sender, System::EventArgs^ e)
{
    // read scene
    LoadFromFileTask^ loadtask = gcnew LoadFromFileTask(CONFIG_PATH);
    manageTask(loadtask);

    FillWidgetsTask^ widtask = gcnew FillWidgetsTask(cameras_ud);
    manageTask(widtask);

    // justify interface
    initGraphics();

    // render scene task
    RenderAllTask^ rendtask = gcnew RenderAllTask(bmps);
    manageTask(rendtask);
}

System::Void MainForm::initGraphics()
{
    bmps = gcnew System::Collections::Generic::List<Bitmap^>();
    
    for (int i = 0; i < cameras_ud->Items->Count; i++)
        bmps->Add(gcnew Drawing::Bitmap(panel->Width, panel->Height));

    panel->BackgroundImage = bmps[0];
}

int main() {

    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    MainForm form;
    Application::Run(% form);

    return 0;
} 