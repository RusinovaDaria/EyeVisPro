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
			this->SuspendLayout();
			// 
			// panel
			// 
			this->panel->Location = System::Drawing::Point(12, 12);
			this->panel->Name = L"panel";
			this->panel->Size = System::Drawing::Size(972, 570);
			this->panel->TabIndex = 0;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(998, 596);
			this->Controls->Add(this->panel);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void initGraphics();
	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e);
	//private: System::Void Draw(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);
	};
}
