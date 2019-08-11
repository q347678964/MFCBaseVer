#ifndef MAIL_CLIENT_H
#define MAIL_CLIENT_H

#include "FormatChange.h"

class mail_client : public FormatChange{

public:
	mail_client();
	~mail_client();

private:
	/*login*/
	char m_strSmtpSrvName[32];
    char m_strPort[8];
    char m_szUser[32];
    char m_szPwd[32];
	/*mail*/
	char m_strFrom[128];
	char m_strTo[128];
	char m_strSubject[128];
	char m_strMsg[512];

public:
	void mail_client::SetMailSubject(CString SubjectCString);
	void mail_client::SetMailContext(CString MailCstring);
	void mail_client::Send(void);
	
private:
	int mail_client::Talk(SOCKET sockid, const char *OkCode, char *pSend);
	void mail_client::Base64(const char* Data, char* chuue);
};

#endif