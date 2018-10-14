#pragma once

#include <string>
typedef void *HANDLE;
class CFileMapping
{
public:
	CFileMapping();
	CFileMapping(const std::string& FileName);
	~CFileMapping(void);
	void Open(const std::string& FileName);

	const unsigned char* GetStart() const{ return m_pStart;}
	const unsigned char* GetEnd() const{ return m_pEnd;}
private:
	HANDLE m_hFile;//�򿪵��ļ����
	HANDLE m_hMapFile;//�ļ�ӳ����
	const unsigned char* m_pStart;//�ļ������ӳ���������ڴ��λ��
	const unsigned char* m_pEnd;//�ļ����յ�ӳ���������ڴ��λ��
};
