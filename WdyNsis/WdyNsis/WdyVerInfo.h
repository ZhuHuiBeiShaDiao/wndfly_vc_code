#pragma once

#define roundoffs(a, b, r)	(((LPBYTE)(b) - (LPBYTE)(a) + ((r)-1)) & ~((r)-1))
#define roundpos(b, a, r)	(((LPBYTE)(a)) + roundoffs(a,b,r))

typedef struct tagVS_LANGANDCODEPAGE
{
	WORD wLanguage;
	WORD wCodePage;
}VS_LANGANDCODEPAGE;

typedef struct tagVS_VERSIONINFO 
{ 
	WORD wLength; 
	WORD wValueLength; 
	WORD wType; 
	WCHAR szKey[1]; 
	WORD wPadding1[1]; 
	VS_FIXEDFILEINFO Value;
	WORD wPadding2[1]; 
	WORD wChildren[1]; 
}VS_VERSIONINFO;

typedef struct tagVS_STRING{
	WORD  wLength;
	WORD  wValueLength;
	WORD  wType;
	WCHAR szKey[1];
	WORD  Padding[1];
	WORD  Value[1];
}VS_STRING;

typedef struct tagVS_STRINGTABLE{
	WORD wLength;
	WORD wValueLength;
	WORD wType;
	WCHAR szKey[1];
	WORD Padding[1];
	VS_STRING Children[1];
}VS_STRINGTABLE;

typedef struct tagVS_STRINGFILEINFO
{
	WORD wLength;
	WORD wValueLength;
	WORD wType;
	WCHAR szKey[1];
	WORD Padding[1];
	VS_STRINGTABLE Children[1];
}VS_STRINGFILEINFO;

typedef struct tagVS_VER
{ 
	WORD  wLength; 
	WORD  wValueLength; 
	WORD  wType; 
	WCHAR szKey[1]; 
	WORD  Padding[1]; 
	DWORD Value[1]; 
}VS_VER; 

typedef struct tagVS_VERFILEINFO
{ 
	WORD  wLength; 
	WORD  wValueLength; 
	WORD  wType; 
	WCHAR szKey[1]; 
	WORD  Padding[1]; 
	VS_VER   Children[1]; 
}VS_VERFILEINFO; 