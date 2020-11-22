#include "taskmanager.h"
#include "raytracer.h"
#include "transform.h"
#include "eye.h"

int manageTask(Task^ task)
{
   static Scene scene(Camera(Vec3f(0, 0, 0), Vec3f(0, 0, 0)), std::vector<Light>(
       {
           Light(Vec3f(-20, 20, 20), 1.5),
           Light(Vec3f(30, 50, -25), 1.8),
           Light(Vec3f(30, 20, 30), 1.7)
       }),
       std::vector<std::shared_ptr<Solid>>({std::shared_ptr<Solid>(new Eye(Vec3f(0, 2, -15), 4, Rotation(Vec3f(0, 2, -15), Vec3f(0, -M_PI/5, 0))))})
   );

    task->execute(scene);
    int i = 0;
	return 0;
}