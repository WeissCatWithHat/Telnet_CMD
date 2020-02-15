#include "DNIWForm.h"
#define _AFXDLL

using namespace System;
using namespace DNIW;

int main(array <String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew DNIWForm());
	return 0;
}