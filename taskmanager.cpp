#include "taskmanager.h"
#include "raytracer.h"
#include "transform.h"
#include "eye.h"

int manageTask(Task^ task)
{
   static Scene scene;
   return task->execute(scene);
}