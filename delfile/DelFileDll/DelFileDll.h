// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� DELFILEDLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// DELFILEDLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef DELFILEDLL_EXPORTS
#define DELFILEDLL_API __declspec(dllexport)
#else
#define DELFILEDLL_API __declspec(dllimport)
#endif

// �����Ǵ� DelFileDll.dll ������
class DELFILEDLL_API CDelFileDll {
public:
	CDelFileDll(void);
	// TODO: �ڴ�������ķ�����
};

extern DELFILEDLL_API int nDelFileDll;

DELFILEDLL_API int fnDelFileDll(void);
