#pragma once

namespace EyeVizPro {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();

			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ panel;
	protected:

	private: Graphics^ graphics;
	private: Bitmap^ bitmap;
	private: System::Windows::Forms::NumericUpDown^ ud_dx;
	private: System::Windows::Forms::NumericUpDown^ ud_dy;
	private: System::Windows::Forms::NumericUpDown^ ud_dz;
	private: System::Windows::Forms::NumericUpDown^ ud_ax;
	private: System::Windows::Forms::NumericUpDown^ ud_ay;
	private: System::Windows::Forms::NumericUpDown^ ud_az;






	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Button^ btn_mov;
	private: System::Windows::Forms::Button^ btn_rot;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->panel = (gcnew System::Windows::Forms::Panel());
			this->ud_dx = (gcnew System::Windows::Forms::NumericUpDown());
			this->ud_dy = (gcnew System::Windows::Forms::NumericUpDown());
			this->ud_dz = (gcnew System::Windows::Forms::NumericUpDown());
			this->ud_ax = (gcnew System::Windows::Forms::NumericUpDown());
			this->ud_ay = (gcnew System::Windows::Forms::NumericUpDown());
			this->ud_az = (gcnew System::Windows::Forms::NumericUpDown());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->btn_mov = (gcnew System::Windows::Forms::Button());
			this->btn_rot = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ud_dx))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ud_dy))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ud_dz))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ud_ax))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ud_ay))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ud_az))->BeginInit();
			this->SuspendLayout();
			// 
			// panel
			// 
			this->panel->Location = System::Drawing::Point(12, 12);
			this->panel->Name = L"panel";
			this->panel->Size = System::Drawing::Size(972, 570);
			this->panel->TabIndex = 0;
			// 
			// ud_dx
			// 
			this->ud_dx->Location = System::Drawing::Point(1061, 56);
			this->ud_dx->Name = L"ud_dx";
			this->ud_dx->Size = System::Drawing::Size(120, 22);
			this->ud_dx->TabIndex = 1;
			// 
			// ud_dy
			// 
			this->ud_dy->Location = System::Drawing::Point(1061, 84);
			this->ud_dy->Name = L"ud_dy";
			this->ud_dy->Size = System::Drawing::Size(120, 22);
			this->ud_dy->TabIndex = 2;
			// 
			// ud_dz
			// 
			this->ud_dz->Location = System::Drawing::Point(1061, 112);
			this->ud_dz->Name = L"ud_dz";
			this->ud_dz->Size = System::Drawing::Size(120, 22);
			this->ud_dz->TabIndex = 3;
			// 
			// ud_ax
			// 
			this->ud_ax->Location = System::Drawing::Point(1061, 228);
			this->ud_ax->Name = L"ud_ax";
			this->ud_ax->Size = System::Drawing::Size(120, 22);
			this->ud_ax->TabIndex = 4;
			// 
			// ud_ay
			// 
			this->ud_ay->Location = System::Drawing::Point(1061, 256);
			this->ud_ay->Name = L"ud_ay";
			this->ud_ay->Size = System::Drawing::Size(120, 22);
			this->ud_ay->TabIndex = 5;
			// 
			// ud_az
			// 
			this->ud_az->Location = System::Drawing::Point(1061, 284);
			this->ud_az->Name = L"ud_az";
			this->ud_az->Size = System::Drawing::Size(120, 22);
			this->ud_az->TabIndex = 6;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(991, 36);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(95, 17);
			this->label1->TabIndex = 7;
			this->label1->Text = L"Move Camera";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(991, 208);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(103, 17);
			this->label2->TabIndex = 8;
			this->label2->Text = L"Rotate Camera";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(991, 230);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(64, 17);
			this->label3->TabIndex = 9;
			this->label3->Text = L"angle Ox";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(990, 258);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(65, 17);
			this->label4->TabIndex = 10;
			this->label4->Text = L"angle Oy";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(991, 286);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(65, 17);
			this->label5->TabIndex = 11;
			this->label5->Text = L"angle Oz";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(992, 117);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(23, 17);
			this->label6->TabIndex = 14;
			this->label6->Text = L"dz";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(991, 89);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(23, 17);
			this->label7->TabIndex = 13;
			this->label7->Text = L"dy";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(992, 61);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(22, 17);
			this->label8->TabIndex = 12;
			this->label8->Text = L"dx";
			// 
			// btn_mov
			// 
			this->btn_mov->Location = System::Drawing::Point(995, 152);
			this->btn_mov->Name = L"btn_mov";
			this->btn_mov->Size = System::Drawing::Size(186, 28);
			this->btn_mov->TabIndex = 15;
			this->btn_mov->Text = L"Move!";
			this->btn_mov->UseVisualStyleBackColor = true;
			this->btn_mov->Click += gcnew System::EventHandler(this, &MainForm::btn_mov_Click);
			// 
			// btn_rot
			// 
			this->btn_rot->Location = System::Drawing::Point(994, 323);
			this->btn_rot->Name = L"btn_rot";
			this->btn_rot->Size = System::Drawing::Size(186, 28);
			this->btn_rot->TabIndex = 16;
			this->btn_rot->Text = L"Rotate!";
			this->btn_rot->UseVisualStyleBackColor = true;
			this->btn_rot->Click += gcnew System::EventHandler(this, &MainForm::btn_rot_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1267, 596);
			this->Controls->Add(this->btn_rot);
			this->Controls->Add(this->btn_mov);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->ud_az);
			this->Controls->Add(this->ud_ay);
			this->Controls->Add(this->ud_ax);
			this->Controls->Add(this->ud_dz);
			this->Controls->Add(this->ud_dy);
			this->Controls->Add(this->ud_dx);
			this->Controls->Add(this->panel);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ud_dx))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ud_dy))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ud_dz))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ud_ax))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ud_ay))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ud_az))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void initGraphics();
	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e);
	private: System::Void btn_mov_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void btn_rot_Click(System::Object^ sender, System::EventArgs^ e);
};
}
