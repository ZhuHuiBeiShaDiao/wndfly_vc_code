// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� WDYNSIS_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// WDYNSIS_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef WDYNSIS_EXPORTS
#define WDYNSIS_API __declspec(dllexport)
#else
#define WDYNSIS_API __declspec(dllimport)
#endif

WDYNSIS_API BOOL WriteVersion(HWND hwndParent, int string_size, char *variables, stack_t **stacktop, extra_parameters *extra);
