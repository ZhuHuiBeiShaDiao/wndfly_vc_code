hResource   =   BeginUpdateResource(lpszFile,   FALSE);
                        if   (NULL   !=   hResource)
{
UINT   uTemp;

TCHAR strSubBlock[256];
LPTSTR     pValueBuffer;

_stprintf(strSubBlock,   _T( "\\StringFileInfo\\%04x%04x\\CompanyName "),
                                      lpTranslate-> wLanguage,  
                                      lpTranslate-> wCodePage);

if   (VerQueryValue(lpBuffer,   (LPTSTR)   ((LPCTSTR)   strSubBlock),   (LPVOID   *)   &pValueBuffer,   &uTemp)   !=   FALSE)
{
_tcscpy(pValueBuffer,   _T( "My   Corp "));

if   (UpdateResource(hResource,   RT_VERSION,   MAKEINTRESOURCE(VS_VERSION_INFO),   lpTranslate-> wLanguage,   lpBuffer,   dwSize)   !=   FALSE)
                                        {
                                                if   (EndUpdateResource(hResource,   FALSE)   ==   FALSE)
                                                        dwResult   =   GetLastError();
                                        }
                                        else
                                                dwResult   =   GetLastError();
}

}