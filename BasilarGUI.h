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
			this->SuspendLayout();
			// 
			// BasilarGUI
			// 
			this->ClientSize = System::Drawing::Size(292, 212);
			this->Name = L"BasilarGUI";
			this->Load += gcnew System::EventHandler(this, &BasilarGUI::BasilarGUI_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void BasilarGUI_Load(System::Object^ sender, System::EventArgs^ e) {
	}


	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		BasilarAutoMain();
	}
	private: System::Void dataGridView1_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
	}
	};
}
