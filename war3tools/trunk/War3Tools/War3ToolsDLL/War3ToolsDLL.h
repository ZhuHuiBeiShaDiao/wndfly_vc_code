// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� WAR3TOOLSDLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// WAR3TOOLSDLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef WAR3TOOLSDLL_EXPORTS
#define WAR3TOOLSDLL_API __declspec(dllexport)
#else
#define WAR3TOOLSDLL_API __declspec(dllimport)
#endif

// �����Ǵ� War3ToolsDLL.dll ������
/*class WAR3TOOLSDLL_API CWar3ToolsDLL {
public:
	CWar3ToolsDLL(void);
	// TODO: �ڴ�������ķ�����
};*/

//extern WAR3TOOLSDLL_API int nWar3ToolsDLL;

//WAR3TOOLSDLL_API int fnWar3ToolsDLL(void);

// ��������
WAR3TOOLSDLL_API BOOL ReadReg(LPCWSTR lpRegKeyName, LPWSTR lpValue);
WAR3TOOLSDLL_API BOOL WriteReg(LPCWSTR lpRegKeyName, LPCWSTR lpValue);
WAR3TOOLSDLL_API BOOL DelReg(LPCWSTR lpRegKeyName);
