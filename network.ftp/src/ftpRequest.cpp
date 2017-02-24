#include "ftpRequest.h"


ftpRequest::ftpRequest() {}

ftpRequest::ftpRequest(string cmd)
{
	m_cmd = cmd;
	m_arg = string("");
}

ftpRequest::ftpRequest(string cmd, string arg)
{
	m_cmd = cmd;
	m_arg =  arg;
}

/// input: string containing request from socket
/// output: ftpRequest object
ftpRequest ftpRequest::parseFtpRequest(string s)
{
	int i = 0;
	string cmd,arg;
	cmd = "";
	while(s[i] != ' ' && s[i] != '\r')
	{
		cmd += s[i];
		i++;
	}
	arg = "";
	if(s[i] == '\r')	return ftpRequest(cmd,arg);
	for(i += 1; s[i] != '\r'; i++)
	{
		arg += s[i];
	}
	if(cmd == "PORT")
	{
		arg = combinePortArg(arg);
	}
	return ftpRequest(cmd,arg);
}

string ftpRequest::toString()
{
	if(m_arg == "")
	{
		return m_cmd + "\r\n";
	}
	else if(m_cmd == "PORT")
	{
		return m_cmd + " " + splitPortArg(m_arg) + "\r\n";
	}
	else
	{
		return m_cmd + " " + m_arg + "\r\n";
	}
}

/// input: xx.yy.zz.ww:1234
/// output: xx,yy,zz,ww,high_byte(1234),low_byte(1234)
string ftpRequest::splitPortArg(string portArg)
{
	int port;
	stringstream convert;
	for(int i=0;i<portArg.length();i++)
	{
		if(portArg[i]=='.')	portArg[i] = ',';
		if(portArg[i]==':')
		{
			portArg[i] = ',';
			port = atoi(portArg.substr(i+1,portArg.length()-1-i).c_str());
			portArg = portArg.substr(0,i+1);
			convert << port/256 << "," << port%256;
			portArg += convert.str();
			break;
		}
	}
	return portArg;
}

/// input: xx,yy,zz,ww,high_byte(1234),low_byte(1234)
/// output: xx.yy.zz.ww:1234
string ftpRequest::combinePortArg(string portArg)
{
	int cnt = 0,port = 0, portTemp=0;
	stringstream convert;
	for(int i=0;i<portArg.length();i++)
	{
		if(portArg[i]==',')
		{
			cnt++;
			if(cnt < 4)
			{
				portArg[i] = '.';
			}
			else if(cnt == 4)
			{
				portArg[i] = ':';
				for(int j=i+1;j<portArg.length();j++)
				{
					if(portArg[j]==',')
					{
						port = port*256 + portTemp;
						portTemp=0;
					}
					else if (isdigit(portArg[j]))
					{
						portTemp = portTemp*10 + (portArg[j]-'0');
					}
					else
					{
						port = port*256 + portTemp;
						portTemp=0;
						break;
					}
				}
				port = port*256 + portTemp;
				portTemp=0;
				
				portArg = portArg.substr(0,i+1);
				convert << port;
				portArg += convert.str();
				break;
			}
		}
	}
	return portArg;
}

string ftpRequest::getCmd()
{
	return m_cmd; 
}

string ftpRequest::getArg()
{
	return m_arg; 
}

void ftpRequest::setCmd(string cmd)
{
	m_cmd = cmd; 
}

void ftpRequest::setArg(string arg)
{
	m_arg = arg; 
}

