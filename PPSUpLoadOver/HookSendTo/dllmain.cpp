// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
#include "stdafx.h"
#include "HookSendTo.h"
#include "winsock2.h"
#pragma comment(lib,"ws2_32.lib ")

//��dll��handle
HANDLE g_hInstance = NULL;
//�޸�API���Ϊ mov eax, 00400000;jmp eax�ǳ�������ת���Լ��ĺ���
BYTE g_btNewBytes[8] = { 0xB8, 0x0, 0x0, 0x40, 0x0, 0xFF, 0xE0, 0x0 };
//����ԭAPI��ڵ�8���ֽ�
DWORD g_dwOldBytes[2][2] = { 0x0, 0x0, 0x0, 0x0 };
//���Ӿ��
HHOOK   g_hOldHook = NULL;
//API��send�����ĵ�ַ
DWORD g_pSend = 0;
//���񣬽��ͬ������
HANDLE g_hSendEvent = NULL;
//�Լ���send������ַ������������API��send������ַ��ͬ
INT WINAPI hook_sendto(SOCKET s, LPCSTR buf, INT len, INT flags, SOCKADDR* addr_in, INT naddr);
//ҪHook�Ľ��̺����߳�ID��
DWORD g_dwProcessID = 0;
DWORD g_dwThreadID = 0;

BOOL TestProcess(LPWSTR pszProcessName);

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		//��ȡ��dll���
      g_hInstance = hModule;
     
      //��������
      g_hSendEvent = CreateEvent(NULL, FALSE, TRUE, NULL);
     
      //��дAPI��ͷ��8�ֽ�
      HMODULE hWsock = LoadLibrary(L"wsock32.dll");
      g_pSend = (DWORD)GetProcAddress(hWsock, "sendto");
 
      //����ԭʼ�ֽ�
      ReadProcessMemory(INVALID_HANDLE_VALUE, (LPVOID)g_pSend,(LPVOID)g_dwOldBytes[0], sizeof(DWORD)*2, NULL);

      //��00400000��дΪ���Ǻ����ĵ�ַ
      *(LPDWORD)(g_btNewBytes + 1) = (DWORD)hook_sendto;
      WriteProcessMemory(INVALID_HANDLE_VALUE, (LPVOID)g_pSend,(LPVOID)g_btNewBytes, sizeof(DWORD)*2, NULL);
	  break;
	}
	return TRUE;
}

INT WINAPI hook_sendto(SOCKET s, LPCSTR buf, INT len, INT flags, SOCKADDR* addr_in, INT naddr)
{
   INT nRet = 0;
   WaitForSingleObject(g_hSendEvent, INFINITE);
 
   //�ָ�APIͷ8���ֽ�
   WriteProcessMemory(INVALID_HANDLE_VALUE, (LPVOID)g_pSend,(LPVOID)g_dwOldBytes[0], sizeof(DWORD)*2, NULL);
 
   /*
   ������������Ҫ���еĴ������
   */
 
   DWORD dwNum = MultiByteToWideChar (CP_ACP, 0, buf, -1, NULL, 0);
   LPWSTR pwText;
   pwText = new WCHAR[dwNum];
   if(!pwText)
   {
	  delete []pwText;
   }
   MultiByteToWideChar (CP_ACP, 0, buf, -1, pwText, dwNum);
   delete []pwText;
   //LPWSTR pszPathName = new WCHAR[MAX_PATH];

   BOOL bRet = TestProcess(L"ppstream.exe");

   //����ִ��API����
   if(bRet && len > 512)
   {
	   nRet = sendto(s, NULL, len, flags, addr_in, naddr);
   }else{   
	   nRet = sendto(s, buf, len, flags, addr_in, naddr);
   }

   //д����ת��䣬����Hook
   WriteProcessMemory( INVALID_HANDLE_VALUE, (LPVOID)g_pSend,(LPVOID)g_btNewBytes, sizeof(DWORD)*2, NULL);
 
   SetEvent(g_hSendEvent);
 
   return nRet;
}
 
static LRESULT WINAPI HookProc(INT nCode, WPARAM wParam, LPARAM lParam)
{
    return CallNextHookEx(g_hOldHook, nCode, wParam, lParam);
}

HOOKSENDTO_API BOOL StartHook(VOID)
{
	//STARTUPINFO si = { sizeof(si) };
	//PROCESS_INFORMATION pi;

	//LONG lRet = ::CreateProcess(NULL, lpFileName, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);
	//HWND hWnd;
    //ͨ������Ĵ��ھ����ȡ�߳̾��
    //g_dwThreadID = GetWindowThreadProcessId(hWnd, &g_dwProcessID);
 
    //WH_CALLWNDPROC���͵�Hook
    g_hOldHook = SetWindowsHookEx(WH_CALLWNDPROC, HookProc,(HINSTANCE)g_hInstance, 0);

    if( g_hOldHook == NULL )
        return FALSE;

    return TRUE;
}
 
 
HOOKSENDTO_API VOID StopHook(VOID)
{
   if(g_hOldHook != NULL)
   {
       WaitForSingleObject(g_hSendEvent, INFINITE);

       HANDLE hProcess = NULL;
       hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, g_dwProcessID);

       DWORD dwOldProc;
       DWORD dwNewProc;
 
       //�ı�ҳ������Ϊ��д
       VirtualProtectEx(hProcess, (LPVOID)g_pSend, 8, PAGE_READWRITE, &dwOldProc);
 
       //�ָ�API����8���ֽ�
       WriteProcessMemory(hProcess, (LPVOID)g_pSend,(LPVOID)g_dwOldBytes[0], sizeof(DWORD)*2, NULL);
 
       //�ָ�ҳ���ļ�������
       VirtualProtectEx(hProcess, (LPVOID)g_pSend, 8, dwOldProc, &dwNewProc);
  
       CloseHandle(g_hSendEvent);
  
       UnhookWindowsHookEx(g_hOldHook);
    }
}

BOOL TestProcess(LPWSTR pszProcessName)
{
   //LPWSTR pszPathName = L"ppsteam.exe";
   //LPWSTR pszDriveName = new WCHAR[MAX_PATH];
   //LPWSTR pszDirName = new WCHAR[MAX_PATH];
   //LPWSTR pszFileName = new WCHAR[MAX_PATH];
   //LPWSTR pszExtName = new WCHAR[MAX_PATH];

   //::GetModuleFileName(NULL,pszPathName,MAX_PATH);
   //::_wsplitpath_s(pszPathName,pszDriveName,MAX_PATH,pszDirName,MAX_PATH,pszFileName,MAX_PATH,pszExtName,MAX_PATH);

   LPWSTR pszPathName = new WCHAR[MAX_PATH];
   LPWSTR pszDriveName = new WCHAR[MAX_PATH];
   LPWSTR pszDirName = new WCHAR[MAX_PATH];
   LPWSTR pszFileName = new WCHAR[MAX_PATH];
   LPWSTR pszExtName = new WCHAR[MAX_PATH];

   ::GetModuleFileName(NULL,pszPathName,MAX_PATH);
   ::_wsplitpath_s(pszPathName,pszDriveName,MAX_PATH,pszDirName,MAX_PATH,pszFileName,MAX_PATH,pszExtName,MAX_PATH);

   ::wcscat_s(pszFileName,MAX_PATH,pszExtName);
   //INT a = ::wcscmp(pszFileName,pszProcessName);
   //INT a = sizeof(pszProcessName);
   //::wsprintfW(pszFileName,L"%d",a);
   //pszFileName = ::wcsstr(pszFileName,pszProcessName);
   //::MessageBox(NULL,pszFileName,pszProcessName,MB_OK);strnicmp

   /*HWND hWnd;
   HANDLE hProcess;
   DWORD dwThreadId,dwTid;

   hWnd = ::FindWindow(L"PPStream ���������",L"PPStream ���������");

   if(hWnd)
   {
	   dwTid = ::GetWindowThreadProcessId(hWnd,&dwThreadId);
	   hProcess = ::OpenProcess(PROCESS_ALL_ACCESS,FALSE,dwThreadId);
	   ::TerminateProcess(hProcess,0);
   }*/

   if(::_wcsnicmp(pszFileName,pszProcessName,MAX_PATH) == 0 || ::_wcsnicmp(pszFileName,L"PPSAP.exe",MAX_PATH) == 0)
   {
	   MessageBox(NULL,pszFileName,L"PPSAP.exe",MB_OK);
	   return TRUE;
   }

   return FALSE;

}