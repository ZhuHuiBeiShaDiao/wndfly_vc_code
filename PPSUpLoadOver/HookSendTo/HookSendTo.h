// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� HOOKSENDTO_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// HOOKSENDTO_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef HOOKSENDTO_EXPORTS
#define HOOKSENDTO_API __declspec(dllexport)
#else
#define HOOKSENDTO_API __declspec(dllimport)
#endif

// �����Ǵ� HookSendTo.dll ������
class HOOKSENDTO_API CHookSendTo {
public:
	CHookSendTo(void);
	// TODO: �ڴ�������ķ�����
};

extern HOOKSENDTO_API int nHookSendTo;

HOOKSENDTO_API int fnHookSendTo(void);

HOOKSENDTO_API BOOL StartHook(HWND hWnd);
HOOKSENDTO_API VOID StopHook(VOID);