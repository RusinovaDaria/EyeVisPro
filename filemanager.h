#pragma once
#include "scene.h"
#include "utils.h"
#include "eye.h"
#include "lense.h"
#include <string>
#include <exception>

// задача файлового менеджера - читать сцену из файла
// задача таск менеджера - выполнять действия над сценой 

// следит за безопасностью файла
class FileManager
{
private:

	static int handle_exception(std::ifstream& file, const char* message)
	{
		if (file.is_open())
			file.close();

		throw std::exception(message);
	};

	// из файла, открытого FileManager'ом
	// может читать только файл менеджер 

	static int read_file_content(std::ifstream& file, Scene& scene)
	{
		if (!file.is_open())
			handle_exception(file, "Can't open file with scene description");

		// читаем глаз
		int is_eye;
		if (file >> is_eye && is_eye)
		{
			// allocate memory for eye
			std::shared_ptr<Eye> eye = std::shared_ptr<Eye>(new Eye());

			// try to read eye
			if (read_eye(file, *eye) == SUCCESS)
				scene.add_solid(eye); // if ok, add eye to scene
			else 
				handle_exception(file, "Error while reading eye description");
		}
		

		// читаем линзу
		int is_lense;
		if (file >> is_lense && is_lense)
		{
			scene.set_max_depth(4);

			// allocate memory for 
			std::shared_ptr<Lense> lense = std::shared_ptr<Lense>(new Lense());

			// try to read eye lense
			if (read_lense(file, *lense) == SUCCESS)
				scene.add_solid(lense); // if ok, add eye to scene
			else
				handle_exception(file, "Error while reading eye description");
		};

		// читаем свет
		int n_lights;
		if (file >> n_lights)
		{
			if (n_lights <= 0)
				handle_exception(file, "Incorrect number of lights in scene - the number should be positive");

			bool failed_read = false;
			for (int i = 0; i < n_lights && !failed_read; i++)
			{

				Light l_i;
				if (read_light(file, l_i) == SUCCESS)
					scene.add_light(l_i);
				else
					handle_exception(file, "Error while reading light description");
			}
		}
		else
			handle_exception(file, "Failed to read number of lights");
	
		// читаем камеры
		int n_cameras;
		if (file >> n_cameras)
		{
			if (n_cameras <= 0)
				handle_exception(file, "Incorrect number of cameras in scene - the number should be positive");

			bool failed_read = false;
			for (int i = 0; i < n_cameras && !failed_read; i++)
			{
				Camera c_i;
				if (read_camera(file, c_i) == SUCCESS)
					scene.add_camera(c_i);
				else
					handle_exception(file, "Error while reading camera description");
			}
		}
		else
			handle_exception(file, "Failed to read number of cameras");

		// читаем задник 
		int is_cubemap;
		if (!(file >> is_cubemap))
			handle_exception(file, "Error while reading cubemap flag");

		if (is_cubemap)
		{
			Cubemap map;
			if (read_cubemap(file, map) == SUCCESS)
				scene.set_back_map(map);
			else
				handle_exception(file, "Error while reading cubmap");
		}
		else
		{
			Vec3f backcolor;
			file >> backcolor;
			scene.set_back_color(backcolor);
		}

		return 0;
	}

	static int read_cubemap(std::ifstream& file, Cubemap& back)
	{
		std::string linebreak;
		std::string px, py, pz, nx, ny, nz;
		if (getline(file, linebreak) && getline(file, px) && getline(file, py) && getline(file, pz) &&
			getline(file, nx) && getline(file, ny) && getline(file, nz))
			back.set_faces({ px, ny, pz, nx, py, nz });
		else
			handle_exception(file, "Error while reading eye description");

		return 0;
	}

	static int read_material(std::ifstream& file, Material& mtrl)
	{
		file >> mtrl.refractive_index;
		file >> mtrl.coeffs[0];
		file >> mtrl.coeffs[1];
		file >> mtrl.coeffs[2];
		file >> mtrl.coeffs[3];
		file >> mtrl.color[0];
		file >> mtrl.color[1];
		file >> mtrl.color[2];

		return 0;
	}

	static int read_eye(std::ifstream& file, Eye& eye)
	{
		Vec3f angle;
		file >> eye.radius >> eye.center;
		file >> angle;
		
		// custom materials
		Material  custom_cryst_glass, custom_cornea_glass, 
			custom_iris, custom_white_glass, custom_red_rubber;

		read_material(file, custom_cryst_glass);
		read_material(file, custom_cornea_glass);
		read_material(file, custom_iris);
		read_material(file, custom_white_glass);
		read_material(file, custom_red_rubber);
		
		// выпуклая оболочка
		eye.border.center = eye.center;
		eye.border.radius = eye.radius * 1.25;
		
		if (!eye.components.empty()) eye.components.clear();
		eye.components.push_back(new Cornea(eye.center - Vec3f(0.37 * eye.radius, 0, 0), 0.9 * eye.radius, custom_cornea_glass));
		eye.components.push_back(new Sclera(eye.center, eye.radius * 7 / 6, custom_white_glass));
		eye.components.push_back(new Iris(eye.center + Vec3f(0.8 * eye.radius, 0, 0), 1.85 * eye.radius, custom_iris));
		eye.components.push_back(new Crystalline(eye.center - Vec3f(0.82 * eye.radius, 0, 0), 0.7 * eye.radius, custom_cryst_glass));
		
		eye.rot.setParameters(eye.center, angle);

		int is_sclera_texture;
		if (file >> is_sclera_texture && is_sclera_texture)
		{
			std::string str;
			std::string linebreak;
			if (getline(file, linebreak) && getline(file, str))
				eye.set_sclera_texture(Texture(gcnew System::String(str.c_str())));
			else
				handle_exception(file, "Error while reading sclera texture");
		}

		int is_sclera_normalmap;
		if (file >> is_sclera_normalmap && is_sclera_normalmap)
		{
			double scale, amount;
			
			file >> scale >> amount;
			eye.set_sclera_normal_map(NormalMap(scale, amount));
		}

		int is_iris_texture;
		if (file >> is_iris_texture && is_iris_texture)
		{
			std::string str;
			std::string linebreak;
			if (getline(file, linebreak) && getline(file, str))
				eye.set_iris_texture(Texture(gcnew System::String(str.c_str())));
			else
				handle_exception(file, "Error while reading iris texture");
		}

		return 0;
	}

	static int read_lense(std::ifstream& file, Lense& lense)
	{
		Vec3f angle;
		file >> lense.d >> lense.center;
		file >> angle;
		lense.rot.setParameters(lense.center, angle);

		float dx = lense.d.x;
		float dy = lense.d.y;
		float dz = lense.d.z;

		lense.dx_2 = dx * dx / 2.; //, dy_2(d.y * d.y), dz_2(d.z * d.z);
		lense.dy_2 = dy * dy / 2.; //, dy_2(d.y * d.y), dz_2(d.z * d.z);
		lense.dz_2 = dz * dz / 2.; //, dy_2(d.y * d.y), dz_2(d.z * d.z);

		Material  custom_lense_glass;
		read_material(file, custom_lense_glass);
		lense.set_material(custom_lense_glass);

		return 0;
	}

	static int read_light(std::ifstream& file, Light& light)
	{
		file >> light.position[0];
		file >> light.position[1];
		file >> light.position[2];
		file >> light.intensity;

		return 0;
		
	}

	static int read_camera(std::ifstream& file, Camera& cam)
	{
		file >> cam.location[0];
		file >> cam.location[1];
		file >> cam.location[2];

		file >> cam.sight[0];
		file >> cam.sight[1];
		file >> cam.sight[2];

		return 0;
	}


public:
	FileManager() = default;
	static int read_scene(System::String^ path, Scene& scene)
	{
		// check if file exists
		if (!System::IO::File::Exists(path))
			throw std::exception("Configured scene file not found");

		std::string file_str;
		MarshalString(path, file_str);

		// открыть файл на чтение 
		std::ifstream scene_file(file_str);
		if (!scene_file.is_open())
			throw std::exception("Failed to open scene file");

		read_file_content(scene_file, scene);
		
		// закрыть файл 
		scene_file.close();
		return 0;
	};

};