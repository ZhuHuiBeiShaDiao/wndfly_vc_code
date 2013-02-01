// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 WAR3TOOLSDLL_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// WAR3TOOLSDLL_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef WAR3TOOLSDLL_EXPORTS
#define WAR3TOOLSDLL_API __declspec(dllexport)
#else
#define WAR3TOOLSDLL_API __declspec(dllimport)
#endif

// 此类是从 War3ToolsDLL.dll 导出的
/*class WAR3TOOLSDLL_API CWar3ToolsDLL {
public:
	CWar3ToolsDLL(void);
	// TODO: 在此添加您的方法。
};*/

//extern WAR3TOOLSDLL_API int nWar3ToolsDLL;

//WAR3TOOLSDLL_API int fnWar3ToolsDLL(void);

// 导出函数
WAR3TOOLSDLL_API BOOL ReadReg(LPCWSTR lpRegKeyName, LPWSTR lpValue);
WAR3TOOLSDLL_API BOOL WriteReg(LPCWSTR lpRegKeyName, LPCWSTR lpValue);
WAR3TOOLSDLL_API BOOL DelReg(LPCWSTR lpRegKeyName);
