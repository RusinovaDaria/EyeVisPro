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
	private: System::Collections::Generic::List<Bitmap^>^ bmps;
	private: System::Windows::Forms::DomainUpDown^ cameras_ud;
















	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;






	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::NumericUpDown^ nud_posx;
	private: System::Windows::Forms::NumericUpDown^ nud_posy;
	private: System::Windows::Forms::NumericUpDown^ nud_posz;

	private: System::Windows::Forms::NumericUpDown^ nud_angz;




	private: System::Windows::Forms::NumericUpDown^ nud_angy;

	private: System::Windows::Forms::NumericUpDown^ nud_angx;

	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::NumericUpDown^ nud_movz;

	private: System::Windows::Forms::NumericUpDown^ nud_movy;

	private: System::Windows::Forms::NumericUpDown^ nud_movx;



	private: System::Windows::Forms::NumericUpDown^ nud_roty;

	private: System::Windows::Forms::NumericUpDown^ nud_rotx;


	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::Button^ btn_add_camera;

	private: System::Windows::Forms::Button^ btn_rot;

	private: System::Windows::Forms::Button^ btn_mov;

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::NumericUpDown^ nud_rotz;
	private: System::Windows::Forms::Button^ btn_delete_cam;
	private: System::Windows::Forms::Label^ active_camera_label;
































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
			this->cameras_ud = (gcnew System::Windows::Forms::DomainUpDown());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->nud_posx = (gcnew System::Windows::Forms::NumericUpDown());
			this->nud_posy = (gcnew System::Windows::Forms::NumericUpDown());
			this->nud_posz = (gcnew System::Windows::Forms::NumericUpDown());
			this->nud_angz = (gcnew System::Windows::Forms::NumericUpDown());
			this->nud_angy = (gcnew System::Windows::Forms::NumericUpDown());
			this->nud_angx = (gcnew System::Windows::Forms::NumericUpDown());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->nud_movz = (gcnew System::Windows::Forms::NumericUpDown());
			this->nud_movy = (gcnew System::Windows::Forms::NumericUpDown());
			this->nud_movx = (gcnew System::Windows::Forms::NumericUpDown());
			this->nud_roty = (gcnew System::Windows::Forms::NumericUpDown());
			this->nud_rotx = (gcnew System::Windows::Forms::NumericUpDown());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->btn_add_camera = (gcnew System::Windows::Forms::Button());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->btn_delete_cam = (gcnew System::Windows::Forms::Button());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->nud_rotz = (gcnew System::Windows::Forms::NumericUpDown());
			this->btn_rot = (gcnew System::Windows::Forms::Button());
			this->btn_mov = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->active_camera_label = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nud_posx))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nud_posy))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nud_posz))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nud_angz))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nud_angy))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nud_angx))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nud_movz))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nud_movy))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nud_movx))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nud_roty))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nud_rotx))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nud_rotz))->BeginInit();
			this->SuspendLayout();
			// 
			// panel
			// 
			this->panel->Location = System::Drawing::Point(12, 12);
			this->panel->Name = L"panel";
			this->panel->Size = System::Drawing::Size(780, 420);
			this->panel->TabIndex = 0;
			// 
			// cameras_ud
			// 
			this->cameras_ud->Location = System::Drawing::Point(6, 31);
			this->cameras_ud->Name = L"cameras_ud";
			this->cameras_ud->ReadOnly = true;
			this->cameras_ud->Size = System::Drawing::Size(231, 22);
			this->cameras_ud->TabIndex = 1;
			this->cameras_ud->Text = L"domainUpDown1";
			this->cameras_ud->SelectedItemChanged += gcnew System::EventHandler(this, &MainForm::cameras_ud_SelectedItemChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(809, 297);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(18, 17);
			this->label2->TabIndex = 12;
			this->label2->Text = L"x:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(807, 325);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(19, 17);
			this->label3->TabIndex = 13;
			this->label3->Text = L"y:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(807, 353);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(19, 17);
			this->label4->TabIndex = 14;
			this->label4->Text = L"z:";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(839, 276);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(61, 17);
			this->label8->TabIndex = 21;
			this->label8->Text = L"position:";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(154, 25);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(47, 17);
			this->label9->TabIndex = 22;
			this->label9->Text = L"angle:";
			// 
			// nud_posx
			// 
			this->nud_posx->DecimalPlaces = 2;
			this->nud_posx->Location = System::Drawing::Point(841, 297);
			this->nud_posx->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
			this->nud_posx->Name = L"nud_posx";
			this->nud_posx->Size = System::Drawing::Size(80, 22);
			this->nud_posx->TabIndex = 27;
			// 
			// nud_posy
			// 
			this->nud_posy->DecimalPlaces = 2;
			this->nud_posy->Location = System::Drawing::Point(841, 325);
			this->nud_posy->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
			this->nud_posy->Name = L"nud_posy";
			this->nud_posy->Size = System::Drawing::Size(80, 22);
			this->nud_posy->TabIndex = 28;
			// 
			// nud_posz
			// 
			this->nud_posz->DecimalPlaces = 2;
			this->nud_posz->Location = System::Drawing::Point(842, 353);
			this->nud_posz->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
			this->nud_posz->Name = L"nud_posz";
			this->nud_posz->Size = System::Drawing::Size(80, 22);
			this->nud_posz->TabIndex = 29;
			// 
			// nud_angz
			// 
			this->nud_angz->DecimalPlaces = 2;
			this->nud_angz->Location = System::Drawing::Point(158, 102);
			this->nud_angz->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
			this->nud_angz->Name = L"nud_angz";
			this->nud_angz->Size = System::Drawing::Size(80, 22);
			this->nud_angz->TabIndex = 32;
			// 
			// nud_angy
			// 
			this->nud_angy->DecimalPlaces = 2;
			this->nud_angy->Location = System::Drawing::Point(157, 74);
			this->nud_angy->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
			this->nud_angy->Name = L"nud_angy";
			this->nud_angy->Size = System::Drawing::Size(80, 22);
			this->nud_angy->TabIndex = 31;
			// 
			// nud_angx
			// 
			this->nud_angx->DecimalPlaces = 2;
			this->nud_angx->Location = System::Drawing::Point(157, 46);
			this->nud_angx->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
			this->nud_angx->Name = L"nud_angx";
			this->nud_angx->Size = System::Drawing::Size(80, 22);
			this->nud_angx->TabIndex = 30;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(13, 157);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(19, 17);
			this->label5->TabIndex = 35;
			this->label5->Text = L"z:";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(13, 129);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(19, 17);
			this->label6->TabIndex = 34;
			this->label6->Text = L"y:";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(15, 101);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(18, 17);
			this->label7->TabIndex = 33;
			this->label7->Text = L"x:";
			// 
			// nud_movz
			// 
			this->nud_movz->DecimalPlaces = 2;
			this->nud_movz->Location = System::Drawing::Point(35, 155);
			this->nud_movz->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
			this->nud_movz->Name = L"nud_movz";
			this->nud_movz->Size = System::Drawing::Size(81, 22);
			this->nud_movz->TabIndex = 38;
			// 
			// nud_movy
			// 
			this->nud_movy->DecimalPlaces = 2;
			this->nud_movy->Location = System::Drawing::Point(34, 127);
			this->nud_movy->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
			this->nud_movy->Name = L"nud_movy";
			this->nud_movy->Size = System::Drawing::Size(81, 22);
			this->nud_movy->TabIndex = 37;
			// 
			// nud_movx
			// 
			this->nud_movx->DecimalPlaces = 2;
			this->nud_movx->Location = System::Drawing::Point(35, 99);
			this->nud_movx->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
			this->nud_movx->Name = L"nud_movx";
			this->nud_movx->Size = System::Drawing::Size(81, 22);
			this->nud_movx->TabIndex = 36;
			// 
			// nud_roty
			// 
			this->nud_roty->DecimalPlaces = 2;
			this->nud_roty->Location = System::Drawing::Point(160, 127);
			this->nud_roty->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
			this->nud_roty->Name = L"nud_roty";
			this->nud_roty->Size = System::Drawing::Size(77, 22);
			this->nud_roty->TabIndex = 43;
			// 
			// nud_rotx
			// 
			this->nud_rotx->DecimalPlaces = 2;
			this->nud_rotx->Location = System::Drawing::Point(161, 99);
			this->nud_rotx->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
			this->nud_rotx->Name = L"nud_rotx";
			this->nud_rotx->Size = System::Drawing::Size(76, 22);
			this->nud_rotx->TabIndex = 42;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(119, 128);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(42, 17);
			this->label11->TabIndex = 40;
			this->label11->Text = L"pitch:";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(129, 101);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(31, 17);
			this->label12->TabIndex = 39;
			this->label12->Text = L"roll:";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->btn_add_camera);
			this->groupBox1->Controls->Add(this->nud_angy);
			this->groupBox1->Controls->Add(this->nud_angx);
			this->groupBox1->Controls->Add(this->label9);
			this->groupBox1->Controls->Add(this->nud_angz);
			this->groupBox1->Location = System::Drawing::Point(798, 251);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(243, 181);
			this->groupBox1->TabIndex = 45;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"add new camera";
			// 
			// btn_add_camera
			// 
			this->btn_add_camera->Location = System::Drawing::Point(12, 139);
			this->btn_add_camera->Name = L"btn_add_camera";
			this->btn_add_camera->Size = System::Drawing::Size(225, 32);
			this->btn_add_camera->TabIndex = 47;
			this->btn_add_camera->Text = L"add";
			this->btn_add_camera->UseVisualStyleBackColor = true;
			this->btn_add_camera->Click += gcnew System::EventHandler(this, &MainForm::btn_add_camera_Click);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->btn_delete_cam);
			this->groupBox2->Controls->Add(this->label10);
			this->groupBox2->Controls->Add(this->nud_rotz);
			this->groupBox2->Controls->Add(this->nud_roty);
			this->groupBox2->Controls->Add(this->btn_rot);
			this->groupBox2->Controls->Add(this->btn_mov);
			this->groupBox2->Controls->Add(this->cameras_ud);
			this->groupBox2->Controls->Add(this->nud_rotx);
			this->groupBox2->Controls->Add(this->nud_movy);
			this->groupBox2->Controls->Add(this->label7);
			this->groupBox2->Controls->Add(this->label11);
			this->groupBox2->Controls->Add(this->label6);
			this->groupBox2->Controls->Add(this->label12);
			this->groupBox2->Controls->Add(this->label5);
			this->groupBox2->Controls->Add(this->nud_movx);
			this->groupBox2->Controls->Add(this->nud_movz);
			this->groupBox2->Location = System::Drawing::Point(798, 12);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(243, 233);
			this->groupBox2->TabIndex = 46;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"active camera";
			// 
			// btn_delete_cam
			// 
			this->btn_delete_cam->Location = System::Drawing::Point(6, 59);
			this->btn_delete_cam->Name = L"btn_delete_cam";
			this->btn_delete_cam->Size = System::Drawing::Size(231, 32);
			this->btn_delete_cam->TabIndex = 49;
			this->btn_delete_cam->Text = L"delete selected camera";
			this->btn_delete_cam->UseVisualStyleBackColor = true;
			this->btn_delete_cam->Click += gcnew System::EventHandler(this, &MainForm::btn_delete_cam_Click);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(122, 157);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(36, 17);
			this->label10->TabIndex = 48;
			this->label10->Text = L"yaw:";
			// 
			// nud_rotz
			// 
			this->nud_rotz->DecimalPlaces = 2;
			this->nud_rotz->Location = System::Drawing::Point(160, 155);
			this->nud_rotz->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
			this->nud_rotz->Name = L"nud_rotz";
			this->nud_rotz->Size = System::Drawing::Size(77, 22);
			this->nud_rotz->TabIndex = 47;
			// 
			// btn_rot
			// 
			this->btn_rot->Location = System::Drawing::Point(135, 187);
			this->btn_rot->Name = L"btn_rot";
			this->btn_rot->Size = System::Drawing::Size(102, 32);
			this->btn_rot->TabIndex = 46;
			this->btn_rot->Text = L"rotate";
			this->btn_rot->UseVisualStyleBackColor = true;
			this->btn_rot->Click += gcnew System::EventHandler(this, &MainForm::btn_rot_Click);
			// 
			// btn_mov
			// 
			this->btn_mov->Location = System::Drawing::Point(13, 187);
			this->btn_mov->Name = L"btn_mov";
			this->btn_mov->Size = System::Drawing::Size(103, 32);
			this->btn_mov->TabIndex = 45;
			this->btn_mov->Text = L"move ";
			this->btn_mov->UseVisualStyleBackColor = true;
			this->btn_mov->Click += gcnew System::EventHandler(this, &MainForm::btn_mov_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(9, 435);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(127, 17);
			this->label1->TabIndex = 47;
			this->label1->Text = L"active camera info:";
			// 
			// active_camera_label
			// 
			this->active_camera_label->AutoSize = true;
			this->active_camera_label->Location = System::Drawing::Point(148, 435);
			this->active_camera_label->Name = L"active_camera_label";
			this->active_camera_label->Size = System::Drawing::Size(92, 17);
			this->active_camera_label->TabIndex = 48;
			this->active_camera_label->Text = L"(camera info)";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1055, 467);
			this->Controls->Add(this->active_camera_label);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->panel);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->nud_posx);
			this->Controls->Add(this->nud_posy);
			this->Controls->Add(this->nud_posz);
			this->Controls->Add(this->groupBox1);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nud_posx))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nud_posy))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nud_posz))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nud_angz))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nud_angy))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nud_angx))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nud_movz))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nud_movy))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nud_movx))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nud_roty))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nud_rotx))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nud_rotz))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void initGraphics();
	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e);
	//private: System::Void btn_show_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void btn_mov_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void btn_rot_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void btn_add_camera_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void btn_delete_cam_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void cameras_ud_SelectedItemChanged(System::Object^ sender, System::EventArgs^ e);
};
}
