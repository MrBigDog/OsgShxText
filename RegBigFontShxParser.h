#pragma once
#include "ShxParser.h"
#include "IGlyphCallback.h"

#pragma push_macro("DrawText")
#undef DrawText

class CRegBigFontShxParser
{
public:
	//ShxFileName���벻��·����Ϣ�����Զ���AutoCAD�İ�װĿ¼�µ�FontsĿ¼��Ѱ��
	CRegBigFontShxParser(const char* Reg_Uni_ShxFile, const char* Big_ShxFile);
	CRegBigFontShxParser(){}
	void Init(const char* Reg_Uni_ShxFile, const char* Big_ShxFile);
	void Cleanup();
	~CRegBigFontShxParser(void);
	//����Ҫ���Ƶ��ָ�
	inline void SetTextHeight(double height);
	inline double GetTextHeight();
	inline double GetDescendHeight();
	//�ڵ�ǰ�ָߺ�������,text�Ŀ��
	inline double GetTextExtent(const char* text);
	inline double GetTextExtent(const wchar_t* text);
	//��(x,y)Ϊ���½ǵ���hdc�ϻ����ı�text.
	double DrawText(IGlyphCallback* pGlyphCallback, const char* text, double x, double y);
	double DrawText(IGlyphCallback* pGlyphCallback, const wchar_t* text, double x, double y);
private:
	CShxParser m_RegFontShx;
	CShxParser m_BigFontShx;
};

void CRegBigFontShxParser::SetTextHeight(double height)
{
	//assert(height > 0.0);
	m_RegFontShx.SetTextHeight(height);
	m_BigFontShx.SetTextHeight(height);
}

double CRegBigFontShxParser::GetTextHeight()
{
	return m_RegFontShx.GetTextHeight();
}

double CRegBigFontShxParser::GetDescendHeight()
{
	return m_RegFontShx.m_DescendHeight * m_RegFontShx.m_TextHeight / m_RegFontShx.m_FontHeight; 
}

double CRegBigFontShxParser::GetTextExtent(const char* text)
{
	return DrawText(false, text, 0, 0);
}

double CRegBigFontShxParser::GetTextExtent(const wchar_t* text)
{
	return DrawText(false, text, 0, 0);
}
#pragma pop_macro("DrawText") 