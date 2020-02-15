#include "DNIWServerForm.h"

using namespace System;
using namespace DNIWServer;

int main(cli::array <String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew DNIWServerForm());
	return 0;
}