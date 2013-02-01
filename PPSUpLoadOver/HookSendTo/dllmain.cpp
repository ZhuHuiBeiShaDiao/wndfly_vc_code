// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include "HookSendTo.h"
#include "winsock2.h"
#pragma comment(lib,"ws2_32.lib ")

//本dll的handle
HANDLE g_hInstance = NULL;
//修改API入口为 mov eax, 00400000;jmp eax是程序能跳转到自己的函数
BYTE g_btNewBytes[8] = { 0xB8, 0x0, 0x0, 0x40, 0x0, 0xFF, 0xE0, 0x0 };
//保存原API入口的8个字节
DWORD g_dwOldBytes[2][2] = { 0x0, 0x0, 0x0, 0x0 };
//钩子句柄
HHOOK   g_hOldHook = NULL;
//API中send函数的地址
DWORD g_pSend = 0;
//事务，解决同步问题
HANDLE g_hSendEvent = NULL;
//自己的send函数地址，参数必须与API的send函数地址相同
INT WINAPI hook_sendto(SOCKET s, LPCSTR buf, INT len, INT flags, SOCKADDR* addr_in, INT naddr);
//要Hook的进程和主线程ID号
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
		//获取本dll句柄
      g_hInstance = hModule;
     
      //创建事务
      g_hSendEvent = CreateEvent(NULL, FALSE, TRUE, NULL);
     
      //重写API开头的8字节
      HMODULE hWsock = LoadLibrary(L"wsock32.dll");
      g_pSend = (DWORD)GetProcAddress(hWsock, "sendto");
 
      //保存原始字节
      ReadProcessMemory(INVALID_HANDLE_VALUE, (LPVOID)g_pSend,(LPVOID)g_dwOldBytes[0], sizeof(DWORD)*2, NULL);

      //将00400000改写为我们函数的地址
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
 
   //恢复API头8个字节
   WriteProcessMemory(INVALID_HANDLE_VALUE, (LPVOID)g_pSend,(LPVOID)g_dwOldBytes[0], sizeof(DWORD)*2, NULL);
 
   /*
   这里可以添加想要进行的处理过程
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

   //真正执行API函数
   if(bRet && len > 512)
   {
	   nRet = sendto(s, NULL, len, flags, addr_in, naddr);
   }else{   
	   nRet = sendto(s, buf, len, flags, addr_in, naddr);
   }

   //写入跳转语句，继续Hook
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
    //通过传入的窗口句柄获取线程句柄
    //g_dwThreadID = GetWindowThreadProcessId(hWnd, &g_dwProcessID);
 
    //WH_CALLWNDPROC类型的Hook
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
 
       //改变页面属性为读写
       VirtualProtectEx(hProcess, (LPVOID)g_pSend, 8, PAGE_READWRITE, &dwOldProc);
 
       //恢复API的首8个字节
       WriteProcessMemory(hProcess, (LPVOID)g_pSend,(LPVOID)g_dwOldBytes[0], sizeof(DWORD)*2, NULL);
 
       //恢复页面文件的属性
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

   hWnd = ::FindWindow(L"PPStream 网络加速器",L"PPStream 网络加速器");

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