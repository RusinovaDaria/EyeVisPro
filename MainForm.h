#pragma once
#include <fstream>
#include <chrono>
#include <ctime>

#include "Sphere.h"

namespace EyeVisPro {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			initWidgets();
			initGraphics();
		}

	protected:
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::ComponentModel::Container ^components;
	    System::Windows::Forms::Panel^ panel;
		System::Windows::Forms::Button^ button;
		Graphics^ graphics;
		Bitmap^ bmp;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->panel = (gcnew System::Windows::Forms::Panel());
			this->button = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// panel
			// 
			this->panel->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->panel->Location = System::Drawing::Point(13, 13);
			this->panel->Name = L"panel";
			this->panel->Size = System::Drawing::Size(768, 436);
			this->panel->TabIndex = 0;
			// 
			// button
			// 
			this->button->Location = System::Drawing::Point(813, 202);
			this->button->Name = L"button";
			this->button->Size = System::Drawing::Size(149, 42);
			this->button->TabIndex = 1;
			this->button->Text = L"draw smth";
			this->button->UseVisualStyleBackColor = true;
			this->button->Click += gcnew System::EventHandler(this, &MainForm::button_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(997, 462);
			this->Controls->Add(this->button);
			this->Controls->Add(this->panel);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->Closed += gcnew System::EventHandler(this, &MainForm::MainForm_Closed);
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: void initWidgets();
	private: void initGraphics();
	private: void render();

	private: Color TraceRay(Ray3D &ray);

	private: System::Void button_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e);
	private: System::Void MainForm_Closed(System::Object^ sender, System::EventArgs^ e);
	};
}
