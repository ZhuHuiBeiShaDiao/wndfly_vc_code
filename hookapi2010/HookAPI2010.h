// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� HOOKAPI2010_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// HOOKAPI2010_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef HOOKAPI2010_EXPORTS
#define HOOKAPI2010_API __declspec(dllexport)
#else
#define HOOKAPI2010_API __declspec(dllimport)
#endif

// �����Ǵ� HookAPI2010.dll ������
class HOOKAPI2010_API CHookAPI2010 {
public:
	CHookAPI2010(void);
	// TODO: �ڴ�������ķ�����
};

extern HOOKAPI2010_API int nHookAPI2010;

HOOKAPI2010_API int fnHookAPI2010(void);
HOOKAPI2010_API BOOL StartHook(HWND hWnd);
HOOKAPI2010_API VOID StopHook(VOID);
