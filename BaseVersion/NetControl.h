#ifndef NET_CONTROL_H
#define NET_CONTROL_H

#include "FormatChange.h"

class  net_control : public FormatChange
{
public:
	net_control();
	~net_control();

	CString net_control::get_pcname(void);
	CString net_control::get_localip(void);
	CString net_control::get_netip(void);
	CString net_control::get_mac(void);
	CString net_control::CreatePawword(void);
};

#endif
