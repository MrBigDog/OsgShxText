#pragma once
#include <vector>
#include "FileMapping.h"

class CShxFileMapping : public CFileMapping
{
public:
	//ShxFileName���벻��·����Ϣ�����Զ���EXE����Ŀ¼\AutoCAD\FontsĿ¼��Ѱ�ҡ�
	//ÿ�ε��ñ��������������ӶԷ���ֵָ��Ķ�������ã����������ö���������
	//Release()
	static CShxFileMapping* AddRef(const std::string& ShxFileName);
	//�������ü����������ü���Ϊ0ʱ���ӱ���ɾ���ö����ָ�룬����ɾ���ö���
	static void Release(const std::string& ShxFileName);
private:
	//ShxFileName�����ȫ·����Ϣ
	CShxFileMapping(const std::string& ShxFileName);
	~CShxFileMapping(void);
	std::string m_ShxFileName;//����·����Ϣ
	int m_RefCount;//����������ü���
	//�ļ�ӳ����������
	static std::vector<CShxFileMapping*> s_FileMappings;
};
