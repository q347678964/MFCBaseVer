#include "stdafx.h"
#include "resource.h"
#include "MailClient.h"
#include "string"
#include <ws2tcpip.h>
#include <winsock2.h>
#include "Config.h"
#pragma comment(lib,"ws2_32.lib")


mail_client::mail_client()

{
	strcpy_s(m_strSmtpSrvName, "smtp.163.com");
	strcpy_s(m_strPort, "25");
	strcpy_s(m_szUser, EMAIL_USER);
	strcpy_s(m_szPwd, EMAIL_PASSWORD);
	
	strcpy_s(m_strFrom, EMAIL_USER);
	strcpy_s(m_strTo, EMAIL_USER);
	strcpy_s(m_strSubject, "SubjectTest");
	strcpy_s(m_strMsg, "Nice to see you");
}

mail_client::~mail_client()
{

}


int mail_client::Talk(SOCKET sockid, const char *OkCode, char *pSend)
{     
          const int buflen = 256;
          char buf[buflen];


          if (strlen(pSend)) 				//发送命令
          {       
               ZeroMemory(buf, buflen);
               sprintf_s(buf, "%s\r\n", pSend);
               if (send(sockid, buf, lstrlenA(buf), 0) == SOCKET_ERROR)
               {      
                    TRACE("Send error:%s\n", buf);
                    return 1;
			   } else {
					TRACE("Send done:%s\n", buf);
			   }
		}

wait:
          ZeroMemory(buf, buflen);
          if (recv(sockid, buf, buflen, 0) == SOCKET_ERROR) 	//接收返回信息
          {     
			  Sleep(300);
			  goto wait;
		  } else {
			  TRACE("Recv:%s\n",buf);
		  }
      return 0;
}

void mail_client::Send(void)
{
	const int buflen = 256;
	char buf[buflen];
	WSADATA wsadata;  				//初始化网络环境
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		TRACE((LPCTSTR)"WSAStartup Error!");
		return;
	}
	SOCKET sockid;  				//创建套接字
	if ((sockid = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		TRACE((LPCTSTR)"Sockid Error!");
		WSACleanup();
		return;
	}


	//解析IP地址
	struct addrinfo *answer, hint;
	ZeroMemory(&hint, sizeof(hint));
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_STREAM;
	int ret = getaddrinfo(m_strSmtpSrvName, "smtp", &hint, &answer);

	//使用getaddrinfo，需要#include <ws2tcpip.h>
	struct sockaddr_in addr;
	addr.sin_addr = ((struct sockaddr_in *)(answer->ai_addr))->sin_addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(m_strPort));
	ZeroMemory(&addr.sin_zero, 8);

	//连接服务器
	if (connect(sockid, (struct sockaddr *)&addr, sizeof(struct sockaddr_in))== SOCKET_ERROR)
	{
		TRACE((LPCTSTR)"connect() error !");
		goto STOP;
	}

	if (Talk(sockid, "220", "HELO ALEX-PC"))     	goto STOP;	//交互开始
	
	if (Talk(sockid, "250", "AUTH LOGIN"))   goto STOP;		//授权登录
	
	ZeroMemory(buf, buflen);
	Base64(m_szUser, buf);
	if (Talk(sockid, "334", buf))	  			goto STOP; 	//发送Base64用户名
	
	ZeroMemory(buf, buflen);
	Base64(m_szPwd, buf);
	if (Talk(sockid, "334", buf)) 			goto STOP; 		//发送Base64密码  
	
	ZeroMemory(buf, buflen);
	sprintf_s(buf, "MAIL FROM:<%s>", m_strFrom);        			//发信人
	if (Talk(sockid, "235", buf))   			goto STOP;
	
	ZeroMemory(buf, buflen);
	sprintf_s(buf, "RCPT TO:<%s>", m_strTo);              		//收信人
	if (Talk(sockid, "250", buf))    			goto STOP;
	
	if (Talk(sockid, "250", "DATA"))  		goto STOP;   		//数据
	
	ZeroMemory(buf, buflen);
	sprintf_s(buf, "TO: %s\r\nFROM: %s\r\nSUBJECT: %s\r\n\r\n%s\r\n\r\n.",
		m_strTo, m_strFrom, m_strSubject, m_strMsg);
	if (Talk(sockid, "354", buf))  			goto STOP;
	if (Talk(sockid, "250", "QUIT"))  		goto STOP;   		//结束命令
	if (Talk(sockid, "221", ""))     			goto STOP;

STOP:
	shutdown(sockid, SD_BOTH);
	closesocket(sockid);
	WSACleanup();
	return;
}

void mail_client::Base64(const char* Data, char* chuue)
{
	//编码表
	const char EncodeTable[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	char strEncode[100];
	int j = 0;
	int DataByte = strlen((char*)Data);
	unsigned char Tmp[4] = { 0 };
	int LineLength = 0;
	for (int i = 0; i<(int)(DataByte / 3); i++)
	{
		Tmp[1] = *Data++;
		Tmp[2] = *Data++;
		Tmp[3] = *Data++;
		strEncode[j++] = EncodeTable[Tmp[1] >> 2];
		strEncode[j++] = EncodeTable[((Tmp[1] << 4) | (Tmp[2] >> 4)) & 0x3F];
		strEncode[j++] = EncodeTable[((Tmp[2] << 2) | (Tmp[3] >> 6)) & 0x3F];
		strEncode[j++] = EncodeTable[Tmp[3] & 0x3F];
		if (LineLength += 4, LineLength == 76) 
	{ strEncode[j++] = '\r';strEncode[j++] = '\n'; LineLength = 0; }
	}
	//对剩余数据进行编码
	int Mod = DataByte % 3;
	if (Mod == 1)
	{
		Tmp[1] = *Data++;
		strEncode[j++] = EncodeTable[(Tmp[1] & 0xFC) >> 2];
		strEncode[j++] = EncodeTable[((Tmp[1] & 0x03) << 4)];
		strEncode[j++] = '=';
		strEncode[j++] = '=';
	}
	else if (Mod == 2)
	{
		Tmp[1] = *Data++;
		Tmp[2] = *Data++;
		strEncode[j++] = EncodeTable[(Tmp[1] & 0xFC) >> 2];
		strEncode[j++] = EncodeTable[((Tmp[1] & 0x03) << 4) | ((Tmp[2] & 0xF0) >> 4)];
		strEncode[j++] = EncodeTable[((Tmp[2] & 0x0F) << 2)];
		strEncode[j++] = '=';
	}
	strEncode[j++] = '\0';
	int n = strlen(strEncode) + 1;
	strcpy_s(chuue, n, strEncode);
}


void mail_client::SetMailSubject(CString SubjectCString)
{
	this->CStringToChar(SubjectCString,m_strSubject);
}

void mail_client::SetMailContext(CString MailCstring)
{
	this->CStringToChar(MailCstring,m_strMsg);
}