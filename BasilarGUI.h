#pragma once
#include "BasilarAutoMain.cpp"

namespace BasilarProbe {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for BasilarGUI
	/// </summary>
	public ref class BasilarGUI : public System::Windows::Forms::Form
	{
	public:
		BasilarGUI(void)
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
		~BasilarGUI()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::Button^ BeginButton;
	private: System::IO::Ports::SerialPort^ serialPort1;
	private: System::IO::Ports::SerialPort^ serialPort2;
	private: System::Windows::Forms::ToolTip^ toolTip1;
	private: System::Windows::Forms::ToolTip^ toolTip2;
	private: System::ComponentModel::IContainer^ components;
	protected:


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->BeginButton = (gcnew System::Windows::Forms::Button());
			this->serialPort1 = (gcnew System::IO::Ports::SerialPort(this->components));
			this->serialPort2 = (gcnew System::IO::Ports::SerialPort(this->components));
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->toolTip2 = (gcnew System::Windows::Forms::ToolTip(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// dataGridView1
			// 
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Location = System::Drawing::Point(101, 112);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersWidth = 102;
			this->dataGridView1->RowTemplate->Height = 40;
			this->dataGridView1->Size = System::Drawing::Size(1116, 394);
			this->dataGridView1->TabIndex = 1;
			// 
			// BeginButton
			// 
			this->BeginButton->Location = System::Drawing::Point(1032, 863);
			this->BeginButton->Name = L"BeginButton";
			this->BeginButton->Size = System::Drawing::Size(185, 70);
			this->BeginButton->TabIndex = 2;
			this->BeginButton->Text = L"Begin";
			this->BeginButton->UseVisualStyleBackColor = true;
			this->BeginButton->Click += gcnew System::EventHandler(this, &BasilarGUI::button1_Click);
			// 
			// BasilarGUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(16, 31);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1392, 973);
			this->Controls->Add(this->BeginButton);
			this->Controls->Add(this->dataGridView1);
			this->Name = L"BasilarGUI";
			this->Text = L"BasilarGUI";
			this->Load += gcnew System::EventHandler(this, &BasilarGUI::BasilarGUI_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void BasilarGUI_Load(System::Object^ sender, System::EventArgs^ e) {
	}


	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		BasilarAutoMain();
	}
	};
}
