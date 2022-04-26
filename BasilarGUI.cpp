#include "BasilarGUI.h"

using namespace System;
using namespace System::Windows::Forms;
[STAThread]

void main(array<String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    BasilarProbe::BasilarGUI form;
    Application::Run(% form);
}