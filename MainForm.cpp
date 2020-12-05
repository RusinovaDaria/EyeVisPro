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


System::Void MainForm::cameras_ud_SelectedItemChanged(System::Object^ sender, System::EventArgs^ e)
{
    // listen to events only after loading bmps
    if (bmps == nullptr)
        return;

    // set selected item as current active camera
    try
    {
        manageTask(gcnew SetActiveCameraTask(cameras_ud->SelectedIndex, active_camera_label));

        panel->BackgroundImage = bmps[cameras_ud->SelectedIndex];
    }
    catch (const std::exception & err)
    {
        MessageBox::Show(gcnew System::String(err.what()), "Error while handling render task",
            MessageBoxButtons::OK, MessageBoxIcon::Error);
        exit(-1);
    }

}

System::Void MainForm::btn_delete_cam_Click(System::Object^ sender, System::EventArgs^ e)
{
    if (cameras_ud->Items->Count < 2)
        MessageBox::Show(gcnew System::String("At least one camera should be in scene"), "Failed to delete camera",
            MessageBoxButtons::OK, MessageBoxIcon::Error);
    else
    {
        manageTask(gcnew DeleteCameraTask(cameras_ud, bmps));
    }
}

System::Void MainForm::btn_mov_Click(System::Object^ sender, System::EventArgs^ e)
{

    try
    {
        // move active camera
        float x = System::Decimal::ToSingle(nud_movx->Value);
        float y = System::Decimal::ToSingle(nud_movy->Value);
        float z = System::Decimal::ToSingle(nud_movz->Value);

        manageTask(gcnew MoveCameraTask(x, y, z, active_camera_label));
        manageTask(gcnew RenderSceneTask(bmps[cameras_ud->SelectedIndex]));

        panel->BackgroundImage = bmps[cameras_ud->SelectedIndex];
        panel->Refresh();
    }
    catch (const std::exception& err)
    {
        MessageBox::Show(gcnew System::String(err.what()), "Error while handling move task",
            MessageBoxButtons::OK, MessageBoxIcon::Error);
        exit(-1);
    }
}

System::Void MainForm::btn_rot_Click(System::Object^ sender, System::EventArgs^ e)
{
    try
    {
        // move active camera
        float x = System::Decimal::ToSingle(nud_rotx->Value) * 0.01745;
        float y = System::Decimal::ToSingle(nud_roty->Value) * 0.01745;
        float z = System::Decimal::ToSingle(nud_rotz->Value) * 0.01745;

        manageTask(gcnew RotateCameraTask(x, y, z, active_camera_label));
        manageTask(gcnew RenderSceneTask(bmps[cameras_ud->SelectedIndex]));

        panel->BackgroundImage = bmps[cameras_ud->SelectedIndex];
        panel->Refresh();
    }
    catch (const std::exception & err)
    {
        MessageBox::Show(gcnew System::String(err.what()), "Error while handling rotate task",
            MessageBoxButtons::OK, MessageBoxIcon::Error);
        exit(-1);
    }
}

System::Void MainForm::btn_add_camera_Click(System::Object^ sender, System::EventArgs^ e)
{
    try
    {
        float x_pos = System::Decimal::ToSingle(nud_posx->Value);
        float y_pos = System::Decimal::ToSingle(nud_posy->Value);
        float z_pos = System::Decimal::ToSingle(nud_posz->Value);

        float x_ang = System::Decimal::ToSingle(nud_angx->Value) * 0.01745;
        float y_ang = System::Decimal::ToSingle(nud_angy->Value) * 0.01745;
        float z_ang = System::Decimal::ToSingle(nud_angz->Value) * 0.01745;


        manageTask(gcnew AddCameraTask(x_pos, y_pos, z_pos, x_ang, y_ang, z_ang, 
            cameras_ud, panel, bmps, active_camera_label));
    }
    catch (const std::exception & err)
    {
        MessageBox::Show(gcnew System::String(err.what()), "Error while handling add camera task",
            MessageBoxButtons::OK, MessageBoxIcon::Error);
        exit(-1);
    }
}

//System::Void MainForm::btn_show_Click(System::Object^ sender, System::EventArgs^ e)
//{
//    try
//    {
//        SetActiveCameraTask^ setcamtask = gcnew SetActiveCameraTask(cameras_ud->SelectedIndex);
//        manageTask(setcamtask);
//
//        panel->BackgroundImage = bmps[cameras_ud->SelectedIndex];
//    }
//    catch (const std::exception & err)
//    {
//        MessageBox::Show(gcnew System::String(err.what()), "Error while handling render task",
//            MessageBoxButtons::OK, MessageBoxIcon::Error);
//        exit(-1);
//    }
//}



System::Void MainForm::MainForm_Load(System::Object^ sender, System::EventArgs^ e)
{
    try {
        // read scene
        LoadFromFileTask^ loadtask = gcnew LoadFromFileTask(CONFIG_PATH);
        manageTask(loadtask);
    }
    catch (const std::exception & err)
    {
        MessageBox::Show(gcnew System::String(err.what()), "Error while handling load task",
            MessageBoxButtons::OK, MessageBoxIcon::Error);
        exit(-1);
    }


    FillWidgetsTask^ widtask = gcnew FillWidgetsTask(cameras_ud, active_camera_label);
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