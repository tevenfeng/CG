
// ddaDrawing.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CddaDrawingApp: 
// �йش����ʵ�֣������ ddaDrawing.cpp
//

class CddaDrawingApp : public CWinApp
{
public:
	CddaDrawingApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CddaDrawingApp theApp;