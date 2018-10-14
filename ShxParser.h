#pragma once

#include <vector>
#include <stack>
#include "IGlyphCallback.h"

enum SHX_TYPE {REGFONT, UNIFONT, BIGFONT, SHAPEFILE, UNKNOWN};
struct EscapeRange
{
	unsigned char start;
	unsigned char end;
};

#pragma push_macro("DrawText")
#undef DrawText

class CShxFileMapping;
class CShxParser
{
public:
	//ShxFileName����Ϊ��Ч��ACAD�����ļ�
	//ShxFileName���벻��·����Ϣ
	CShxParser(const char* ShxFileName);
	CShxParser();
	void Init(const char* ShxFileName);
	void Cleanup();
	~CShxParser(void);
	//����Ҫ���Ƶ��ָ�
	inline void SetTextHeight(double height);
	inline double GetTextHeight();
	//�ڵ�ǰ�ָߺ�������,text�Ŀ��
	inline double GetTextExtent(const char* text);
	inline double GetTextExtent(const wchar_t* text);
	//��(x,y)Ϊ���½ǵ���hdc�ϻ����ı�text.
	double DrawText(IGlyphCallback* pGlyphCallback, const char* text, double x, double y);
	double DrawText(IGlyphCallback* pGlyphCallback, const wchar_t* text, double x, double y);
	SHX_TYPE GetType(){return m_Type;}
private:
	//���㵥���ַ��Ŀ��,���hdc��0�����Ƹ��ַ�
	void ParseGlyph(IGlyphCallback* pGlyphCallback, int character);
	void ParseDefBytes(IGlyphCallback* pGlyphCallback, const unsigned char* pDefBytes, int defbytes);
	void ParseOneCode(IGlyphCallback* pGlyphCallback, const unsigned char*& pDefBytes, int& defbytes);
	bool Case_Code_8(IGlyphCallback* pGlyphCallback, const unsigned char*& pDefBytes, int& defbytes);
	bool Case_Code_C(IGlyphCallback* pGlyphCallback, const unsigned char*& pDefBytes, int& defbytes);
	void ParseLenDirByte(IGlyphCallback* pGlyphCallback, unsigned char thebyte);
	bool IsEscapeChar(unsigned char character);
	void DrawLine(IGlyphCallback* pGlyphCallback);


	double m_TextHeight;//���ֻ���ʱ�ϸ�
	unsigned int m_DescendHeight;//�����ļ��ڲ���¼�������¸�
	unsigned int m_FontHeight;//�����ļ��ڲ���¼������߶�
	double m_Scale;//���ȱ���ϵ��
	SHX_TYPE m_Type;//Shx�ļ�����
	std::vector<EscapeRange> m_Ranges;//�����BIGFONT����,m_Ranges���¼ת���뷶Χ
	bool m_bDrawMode;//�ڷ��������ֽڹ����У������Ƿ���Ƶı�־
	double m_PenX, m_PenY;//��ǰ�ʵ�λ��,�ڱ�������ǰ�����ζ������ǰ����,��ParseOneCode����
	std::stack<double> m_PenPosStack;//��λ��ջ
	const unsigned char* m_pStart;//�ļ������ӳ���������ڴ��λ��
	const unsigned char* m_pEnd;//�ļ����յ�ӳ���������ڴ��λ��
	union
	{
		const unsigned char* m_pShapeDefs;//�����UNIFONT shx�ļ�,ָ���һ���ζ��崦
		const unsigned short* m_pIndice;//�����REGFONT����BIGFONT shx�ļ�,ָ���ζ����������ĵ�һ��
	};
	union
	{
		int m_IndexCount;//��������
		int m_GlyphCount;//�ַ���Ŀ
	};
	std::string m_ShxFileName;

public:
	//����������������ڱ��������ļ��������ַ���
	void ResetNextGlyph();//�ӵ�һ���ַ���ʼ��ʾ
	//�������false����ʾ��ʾ��ϡ�
	bool ShowNextGlyph(IGlyphCallback* pGlyphCallback, double x, double y);
private:
	union
	{
		const unsigned char* m_pCurrentShapeDef;//�����UNIFONT shx�ļ�,ָ����һ��Ҫ��ʾ���ζ��崦
		const unsigned short* m_pCurrentIndice;//�����REGFONT����BIGFONT shx�ļ�,ָ���ζ�������������һ��Ҫ��ʾ����
	};
	int m_NextCharDefOffsetFromFirstShapeDef;//������REGFONT�ļ�
	int m_CurrentCount;
	friend class CRegBigFontShxParser;
};

void CShxParser::SetTextHeight(double height)
{
	//assert(height > 0.0);
	m_TextHeight = height>0.0f?height:-height;
}

double CShxParser::GetTextHeight()
{
	return m_TextHeight;
}

double CShxParser::GetTextExtent(const char* text)
{
	return DrawText(nullptr, text, 0, 0);
}

double CShxParser::GetTextExtent(const wchar_t* text)
{
	return DrawText(nullptr, text, 0, 0);
}
#pragma pop_macro("DrawText") 