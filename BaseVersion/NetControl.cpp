#include "stdafx.h"
#include "resource.h"
#include "NetControl.h"
#include <afxinet.h>


/*以下头文件为MAC准备*/
#include <iphlpapi.h>       // API GetAdaptersInfo 头文件
#pragma comment(lib, "iphlpapi.lib")

net_control::net_control()
{

}

net_control::~net_control()
{

}

CString net_control::get_pcname(void)
{
	CString PCNAME = _T("");
	WSAData wsaData;
	WSAStartup(MAKEWORD(1,1), &wsaData);

	char    HostName[100];
	gethostname(HostName, sizeof(HostName));// 获得本机主机名.
	PCNAME = this->CharToCString(HostName);
	WSACleanup();	//用完记得释放

	return PCNAME;
}

CString net_control::get_localip(void)
{
	CString LocalIp = _T("");
	WSAData wsaData;
	WSAStartup(MAKEWORD(1,1), &wsaData);

	char    HostName[100];
	gethostname(HostName, sizeof(HostName));// 获得本机主机名.

	hostent* hn;
	hn = gethostbyname(HostName);//根据本机主机名得到本机ip

	LocalIp=inet_ntoa(*(struct in_addr *)hn->h_addr_list[0]);//把ip换成字符串形式

	WSACleanup();	//用完记得释放

	return LocalIp;
}

CString net_control::get_netip(void)
{
	CString internetIp = _T("");
 
	char chSource[4096] = {0};
	CString strAddress;
	CInternetSession mySession(NULL,0);
	CHttpFile* myHttpFile=NULL;
 
	strAddress = _T("http://200019.ip138.com/");//ip138网页
 
	TRY
	{
		myHttpFile = (CHttpFile*)mySession.OpenURL(strAddress);//读取网络地址
 
		while(myHttpFile->Read(chSource, 4096))
		{
			//循环读取下载来的网页文本
			int begin = 0;
			// 目前只处理字符集为gb2312的情况
			//begin = CKMP<BYTE*>::Find((BYTE*)chSource, strlen(chSource), (BYTE*)_C("charset=gb2312"), 14);
			//if (begin != -1)
			{
				WCHAR* wchSource = this->GB2312ToUnicode(chSource);
				internetIp = wchSource;
				delete[] wchSource;
			}
 
			begin = internetIp.Find(_T("["), 0);
 
			if(begin !=- 1)//如果找到"["， 则找"]"  中括号内的文本则是 你的外网ip
			{ 
				int end=internetIp.Find(_T("]"));
 
				internetIp = internetIp.Mid(begin+1, end-begin-1);//提取外网ip
 
				break;
			}
		}
 
		myHttpFile->Close();
 
		mySession.Close();
	}
	CATCH(CInternetException,e)
	{
		//internetIp.Format(T_T(_$_STRING_FORMAT_1), e->m_dwError, e->m_dwContext);
	}
	CATCH_ALL(e)
	{
		TCHAR ch[MAX_PATH] = {0};
		e->GetErrorMessage(ch, MAX_PATH);
		//internetIp.Format(T_T(_$_STRING_FORMAT_1), -3, ch);
	}
	END_CATCH_ALL
 
	TRACE(internetIp);
 
	return internetIp;
}


CString net_control::get_mac(void)
{
	//CString strIP,strGateWay,strSubnetMask;
	CString strMac;
	strMac.Format(_T(""));
	u_char pMac[6];
	PIP_ADAPTER_INFO adp = NULL;
	ULONG uLong=0;
	//为适配器申请内存
	GetAdaptersInfo(adp,&uLong);
	adp = (PIP_ADAPTER_INFO)::GlobalAlloc(GPTR,uLong);
 
	//取得本地适配器结构信息
	if(GetAdaptersInfo(adp,&uLong) == ERROR_SUCCESS)
	{
		if(adp != NULL)
		{
			//strMacAdd.Format("%s",adp->Address);
			memcpy(pMac,adp->Address,6);
			strMac.Format(_T("%02x%02x%02x%02x%02x%02x"),pMac[0],pMac[1],pMac[2],pMac[3],pMac[4],pMac[5]);
			//strGateWay.Format(_T("%s"),adp->GatewayList.IpAddress.String);// 网关
			//strIP.Format(_T("%s"),adp->IpAddressList.IpAddress.String);//IP
			//strSubnetMask.Format(_T("%s"),adp->IpAddressList.IpMask.String);//子网掩码
			//MessageBox(strMac);
		}
	}
	return strMac;
}

CString net_control::CreatePawword(void)
{
	net_control NetCHdlr;
	char pcname[128];
	char mac[128];
	char password[9];
	CString passwordCString;
	CString pcnameCString;
	CString macCString;

	pcnameCString = NetCHdlr.get_pcname();
	macCString = NetCHdlr.get_mac();

	this->CStringToChar(pcnameCString, pcname);
	this->CStringToChar(macCString, mac);

	for(int i = 0; i < sizeof(password) - 1; i++) {
		password[i] = (pcname[i] + mac[i] + 10) % 9 + '0';
	}
	password[sizeof(password) - 1] = '\0';

	passwordCString = this->CharToCString(password);

	return passwordCString;
}