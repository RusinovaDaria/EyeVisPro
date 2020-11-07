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


using namespace EyeVizPro;

System::Void MainForm::MainForm_Load(System::Object^ sender, System::EventArgs^ e)
{
    initGraphics();

    std::vector<Solid *> scene;
    Vec3f c(0, 0, -15);
    float r = 3;

    scene.push_back(new Eye(c, r));
    scene[0]->set_rotation(c, 0, -M_PI / 2, 0);
    
    std::vector<Light>  lights;
    lights.push_back(Light(Vec3f(-20, 20, 20), 1.5));
    lights.push_back(Light(Vec3f(30, 50, -25), 1.8));
    lights.push_back(Light(Vec3f(30, 20, 30), 1.7));
    //lights.push_back(Light(Vec3f(0, 0, 0), 1.7));

    
    render(bitmap, scene, lights);
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

    // creating new form 
    // with default constructor
    MainForm form;

    // run application with form
    Application::Run(% form);

    // The function returns an int value. The return value is !!not!! used by the operating system.
    return 0;

    //Vec2f eq1(6, 7);
    //Vec2f s1;
    //
    //std::cout << SolveP2(eq1, s1) << std::endl;
    //
    //Vec2f eq2(2, 1);
    //Vec2f s2;
    //std::cout << SolveP2(eq2, s2) << " : " << s2[0] << std::endl;
    //
    //Vec2f eq3(-2, -15);
    //Vec2f s3;
    //std::cout << SolveP2(eq3, s3) << " : " << s3[0] << ", " << s3[1] << std::endl;
    //
    ////----------------
    //
    //Vec3f eq4(5, 6, 7);
    //Vec3f s4;
    //std::cout << SolveP3(eq4, s4) << " : " << s4[0] << std::endl;
    //
    //Vec3f eq5(-5, 8, -4);
    //Vec3f s5;
    //std::cout << SolveP3(eq5, s5) << " : " << s5[0] << ", " << s5[1] << ", " << s5[2] << std::endl;
    //
    //Vec3f eq6(4/3, 1, 0);
    //Vec3f s6;
    //std::cout << SolveP3(eq6, s6) << " : " << s6[0] << std::endl;
    //
    //Vec3f eq7(-5, 6, 4.5);
    //Vec3f s7;
    //std::cout << SolveP3(eq7, s7) << " : " << s7[0] << std::endl;
    //
    //Vec3f eq8(-1, -1, 1);
    //Vec3f s8;
    //std::cout << SolveP3(eq8, s8) << " : " << s8[0] << ", " << s8[1] << ", " << s8[2] << std::endl;



    //Material      ivory(1.0, Vec4f(0.6, 0.3, 0.1, 0.0), Vec3f(0.4, 0.4, 0.3), 50.);
    //Material      glass(1.5, Vec4f(0.0, 0.5, 0.1, 0.8), Vec3f(0.6, 0.7, 0.8), 125.);
    //Material red_rubber(1.0, Vec4f(0.9, 0.1, 0.0, 0.0), Vec3f(0.3, 0.1, 0.1), 10.);
    //Material     mirror(1.0, Vec4f(0.0, 10.0, 0.8, 0.0), Vec3f(1.0, 1.0, 1.0), 1425.);
    //
    //std::vector<Solid*> spheres;
    ////spheres.push_back(new Torus(Vec3f(-3, 0, -16), 3, 1, red_rubber));
    //spheres.push_back(new Sphere(Vec3f(-3, 0, -16), 2, red_rubber));
    //
    ////spheres.push_back(new Sphere(Vec3f(-3, 0, -16), 2, ivory));
    ////spheres.push_back(new Sphere(Vec3f(-1.0, -1.5, -12), 2, glass));
    ////spheres.push_back(new Sphere(Vec3f(1.5, -0.5, -18), 3, red_rubber));
    ////spheres.push_back(new Sphere(Vec3f(7, 5, -18), 4, mirror));
    //
    //std::vector<Light>  lights;
    //lights.push_back(Light(Vec3f(-20, 20, 20), 1.5));
    //lights.push_back(Light(Vec3f(30, 50, -25), 1.8));
    //lights.push_back(Light(Vec3f(30, 20, 30), 1.7));
    //
    //render(graphics, spheres, lights);
    //
    //char key;
    //std::cout << "Check out file. Input any char to exit: ";
    //std::cin >> key;
    //
    //return 0;
}